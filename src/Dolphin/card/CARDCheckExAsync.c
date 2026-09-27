typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long s32;
typedef int BOOL;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDDir {
    u8 gameName[4];
    u8 pad4[0x36 - 0x4];
    u16 startBlock;
    u16 length;
    u8 pad3A[0x40 - 0x3A];
} CARDDir;

typedef struct CARDControl {
    u8 pad0[0x10];
    u16 cBlock;
    u8 pad12[0x80 - 0x12];
    void* workArea;
    CARDDir* currentDir;
    u16* currentFat;
    u8 pad8C[0x110 - 0x8C];
} CARDControl;

#define CARD_SYSTEM_BLOCK_SIZE (8 * 1024u)
#define CARD_MAX_FILE 127
#define CARD_NUM_SYSTEM_BLOCK 5
#define CARD_FAT_AVAIL 0
#define CARD_FAT_CHECKSUM 0
#define CARD_FAT_CHECKSUMINV 1
#define CARD_FAT_CHECKCODE 2
#define CARD_FAT_FREEBLOCKS 3
#define CARDIsValidBlockNo(card, iBlock) (CARD_NUM_SYSTEM_BLOCK <= (iBlock) && (iBlock) < (card)->cBlock)

static inline void __CARDCheckSum(void* ptr, int length, u16* checksum, u16* checksumInv)
{
    u16* p;
    int i;

    length /= sizeof(u16);
    *checksum = *checksumInv = 0;
    for (i = 0, p = ptr; i < length; i++, p++) {
        *checksum += *p;
        *checksumInv += ~*p;
    }
    if (*checksum == 0xffff)
        *checksum = 0;
    if (*checksumInv == 0xffff)
        *checksumInv = 0;
}

extern s32 __CARDGetControlBlock(s32 chan, CARDControl** pcard);
extern s32 __CARDPutControlBlock(CARDControl* card, s32 result);
extern s32 VerifyID(CARDControl* card);
extern s32 VerifyDir(CARDControl* card, int* outCurrent);
extern s32 VerifyFAT(CARDControl* card, int* outCurrent);
extern s32 __CARDUpdateDir(s32 chan, CARDCallback callback);
extern s32 __CARDUpdateFatBlock(s32 chan, u16* fat, CARDCallback callback);
extern void* memcpy(void* dst, const void* src, unsigned long n);
extern void* memset(void* dst, int val, unsigned long n);
extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);

s32 CARDCheckExAsync(s32 chan, s32* xferBytes, CARDCallback callback)
{
    CARDControl* card;
    CARDDir* dir[2];
    u16* fat[2];
    u16* map;
    s32 result;
    int errors;
    int currentFat;
    int currentDir;
    s32 fileNo;
    u16 iBlock;
    u16 cBlock;
    u16 cFree;
    BOOL updateFat = 0;
    BOOL updateDir = 0;
    BOOL updateOrphan = 0;

    if (xferBytes)
        *xferBytes = 0;

    result = __CARDGetControlBlock(chan, &card);
    if (result < 0)
        return result;

    result = VerifyID(card);
    if (result < 0)
        return __CARDPutControlBlock(card, result);

    errors = VerifyDir(card, &currentDir);
    errors += VerifyFAT(card, &currentFat);
    if (1 < errors)
        return __CARDPutControlBlock(card, -6);

    dir[0] = (CARDDir*)((u8*)card->workArea + (1 + 0) * CARD_SYSTEM_BLOCK_SIZE);
    dir[1] = (CARDDir*)((u8*)card->workArea + (1 + 1) * CARD_SYSTEM_BLOCK_SIZE);
    fat[0] = (u16*)((u8*)card->workArea + (3 + 0) * CARD_SYSTEM_BLOCK_SIZE);
    fat[1] = (u16*)((u8*)card->workArea + (3 + 1) * CARD_SYSTEM_BLOCK_SIZE);

    switch (errors) {
    case 0:
        break;
    case 1:
        if (!card->currentDir) {
            card->currentDir = dir[currentDir];
            memcpy(dir[currentDir], dir[currentDir ^ 1], CARD_SYSTEM_BLOCK_SIZE);
            updateDir = 1;
        } else {
            card->currentFat = fat[currentFat];
            memcpy(fat[currentFat], fat[currentFat ^ 1], CARD_SYSTEM_BLOCK_SIZE);
            updateFat = 1;
        }
        break;
    }

    map = fat[currentFat ^ 1];
    memset(map, 0, CARD_SYSTEM_BLOCK_SIZE);

    for (fileNo = 0; fileNo < CARD_MAX_FILE; fileNo++) {
        CARDDir* ent;

        ent = &card->currentDir[fileNo];
        if (ent->gameName[0] == 0xff)
            continue;

        for (iBlock = ent->startBlock, cBlock = 0; iBlock != 0xFFFF && cBlock < ent->length;
             iBlock = card->currentFat[iBlock], ++cBlock) {
            if (!CARDIsValidBlockNo(card, iBlock) || 1 < ++map[iBlock])
                return __CARDPutControlBlock(card, -6);
        }
        if (cBlock != ent->length || iBlock != 0xFFFF)
            return __CARDPutControlBlock(card, -6);
    }

    cFree = 0;
    for (iBlock = CARD_NUM_SYSTEM_BLOCK; iBlock < card->cBlock; iBlock++) {
        u16 nextBlock;

        nextBlock = card->currentFat[iBlock];
        if (map[iBlock] == 0) {
            if (nextBlock != CARD_FAT_AVAIL) {
                card->currentFat[iBlock] = CARD_FAT_AVAIL;
                updateOrphan = 1;
            }
            cFree++;
        } else if (!CARDIsValidBlockNo(card, nextBlock) && nextBlock != 0xFFFF)
            return __CARDPutControlBlock(card, -6);
    }
    if (cFree != card->currentFat[CARD_FAT_FREEBLOCKS]) {
        card->currentFat[CARD_FAT_FREEBLOCKS] = cFree;
        updateOrphan = 1;
    }
    if (updateOrphan) {
        __CARDCheckSum(&card->currentFat[CARD_FAT_CHECKCODE], CARD_SYSTEM_BLOCK_SIZE - sizeof(u32),
            &card->currentFat[CARD_FAT_CHECKSUM], &card->currentFat[CARD_FAT_CHECKSUMINV]);
    }

    memcpy(fat[currentFat ^ 1], fat[currentFat], CARD_SYSTEM_BLOCK_SIZE);

    if (updateDir) {
        if (xferBytes)
            *xferBytes = CARD_SYSTEM_BLOCK_SIZE;
        return __CARDUpdateDir(chan, callback);
    }

    if (updateFat | updateOrphan) {
        if (xferBytes)
            *xferBytes = CARD_SYSTEM_BLOCK_SIZE;
        return __CARDUpdateFatBlock(chan, card->currentFat, callback);
    }

    __CARDPutControlBlock(card, 0);

    if (callback) {
        BOOL enabled;

        enabled = OSDisableInterrupts();
        (*callback)(chan, 0);
        OSRestoreInterrupts(enabled);
    }

    return 0;
}
