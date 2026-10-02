typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned long u32;
typedef long s32;
typedef long long s64;
typedef s64 OSTime;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDControl {
    u8 pad0[0x8];
    u16 size;
    u8 pad0A[0xC - 0xA];
    s32 sectorSize;
    u16 cBlock;
    u8 pad12[0x28 - 0x12];
    s32 formatStep;
    u8 pad2C[0x80 - 0x2C];
    void* workArea;
    u8 pad84[0xD0 - 0x84];
    CARDCallback apiCallback;
    u8 padD4[0x110 - 0xD4];
} CARDControl;

typedef struct CARDID {
    u8 serial[32];
    u16 deviceID;
    u16 size;
    u16 encode;
    u8 padding[512 - 32 - 5 * 2];
    u16 checkSum;
    u16 checkSumInv;
} CARDID;

typedef struct CARDDir {
    u8 pad0[0x40];
} CARDDir;

typedef struct CARDDirCheck {
    u8 padding0[56];
    u16 padding1;
    s16 checkCode;
    u16 checkSum;
    u16 checkSumInv;
} CARDDirCheck;

typedef struct OSSram {
    u16 checkSum;
    u16 checkSumInv;
    u32 ead0;
    u32 ead1;
    u32 counterBias;
    s8 displayOffsetH;
    u8 ntd;
    u8 language;
    u8 flags;
} OSSram;

typedef struct OSSramEx {
    u8 flashID[2][12];
} OSSramEx;

#define CARD_SYSTEM_BLOCK_SIZE (8 * 1024u)
#define CARD_NUM_SYSTEM_BLOCK 5
#define CARD_WORKAREA_SIZE (5 * 8 * 1024u)
#define CARD_MAX_FILE 127
#define CARD_FAT_CHECKSUM 0
#define CARD_FAT_CHECKSUMINV 1
#define CARD_FAT_CHECKCODE 2
#define CARD_FAT_FREEBLOCKS 3
#define CARD_FAT_LASTSLOT 4
#define CARDGetDirCheck(dir) ((CARDDirCheck*)&(dir)[CARD_MAX_FILE])

extern s32 __CARDGetControlBlock(s32 chan, CARDControl** pcard);
extern s32 __CARDPutControlBlock(CARDControl* card, s32 result);
extern void __CARDCheckSum(void* ptr, int length, u16* checksum, u16* checksumInv);
extern void __CARDDefaultApiCallback(s32 chan, s32 result);
extern void FormatCallback(s32 chan, s32 result);
extern s32 __CARDEraseSector(s32 chan, u32 addr, CARDCallback callback);
extern void* memset(void* dst, int val, unsigned long n);
extern void DCStoreRange(void* addr, u32 nBytes);
extern OSSram* __OSLockSram(void);
extern void __OSUnlockSram(int commit);
extern OSSramEx* __OSLockSramEx(void);
extern void __OSUnlockSramEx(int commit);
extern OSTime OSGetTime(void);
extern volatile u16 __VIRegs[0x100] : 0xCC002000;

s32 __CARDFormatRegionAsync(s32 chan, u16 encode, CARDCallback callback)
{
    CARDControl* card;
    CARDID* id;
    CARDDir* dir;
    u16* fat;
    s16 i;
    s32 result;
    OSSram* sram;
    OSSramEx* sramEx;
    u16 dvdstatus;
    OSTime time;
    OSTime rand;

    result = __CARDGetControlBlock(chan, &card);
    if (result < 0)
        return result;

    id = (CARDID*)card->workArea;
    memset(id, 0xff, CARD_SYSTEM_BLOCK_SIZE);
    dvdstatus = __VIRegs[55];

    id->encode = encode;

    sram = __OSLockSram();
    *(u32*)&id->serial[20] = sram->counterBias;
    *(u32*)&id->serial[24] = sram->language;
    __OSUnlockSram(0);

    rand = time = OSGetTime();

    sramEx = __OSLockSramEx();
    for (i = 0; i < 12; i++) {
        rand = (rand * 1103515245 + 12345) >> 16;
        id->serial[i] = (u8)(sramEx->flashID[chan][i] + rand);
        rand = ((rand * 1103515245 + 12345) >> 16) & 0x7FFF;
    }
    __OSUnlockSramEx(0);

    *(u32*)&id->serial[28] = dvdstatus;
    *(OSTime*)&id->serial[12] = time;

    id->deviceID = 0;
    id->size = card->size;
    __CARDCheckSum(id, sizeof(CARDID) - sizeof(u32), &id->checkSum, &id->checkSumInv);

    for (i = 0; i < 2; i++) {
        CARDDirCheck* check;

        dir = (CARDDir*)((u8*)card->workArea + (1 + i) * CARD_SYSTEM_BLOCK_SIZE);
        memset(dir, 0xff, CARD_SYSTEM_BLOCK_SIZE);
        check = CARDGetDirCheck(dir);
        check->checkCode = i;
        __CARDCheckSum(dir, CARD_SYSTEM_BLOCK_SIZE - sizeof(u32), &check->checkSum, &check->checkSumInv);
    }
    for (i = 0; i < 2; i++) {
        fat = (u16*)((u8*)card->workArea + (3 + i) * CARD_SYSTEM_BLOCK_SIZE);
        memset(fat, 0x00, CARD_SYSTEM_BLOCK_SIZE);
        fat[CARD_FAT_CHECKCODE] = (u16)i;
        fat[CARD_FAT_FREEBLOCKS] = (u16)(card->cBlock - CARD_NUM_SYSTEM_BLOCK);
        fat[CARD_FAT_LASTSLOT] = CARD_NUM_SYSTEM_BLOCK - 1;
        __CARDCheckSum(&fat[CARD_FAT_CHECKCODE], CARD_SYSTEM_BLOCK_SIZE - sizeof(u32), &fat[CARD_FAT_CHECKSUM],
                       &fat[CARD_FAT_CHECKSUMINV]);
    }

    card->apiCallback = callback ? callback : __CARDDefaultApiCallback;
    DCStoreRange(card->workArea, CARD_WORKAREA_SIZE);

    card->formatStep = 0;
    result = __CARDEraseSector(chan, (u32)card->sectorSize * card->formatStep, FormatCallback);
    if (result < 0)
        __CARDPutControlBlock(card, result);
    return result;
}
