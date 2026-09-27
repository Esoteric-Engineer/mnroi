typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long s32;
typedef long long s64;
typedef s64 OSTime;

typedef struct CARDID {
    u8 serial[32];
    u16 deviceID;
    u16 size;
    u16 encode;
    u8 padding[512 - 32 - 5 * 2];
    u16 checkSum;
    u16 checkSumInv;
} CARDID;

typedef struct CARDControl {
    u8 pad0[0x8];
    u16 size;
    u8 pad1[0x80 - 0xA];
    void* workArea;
    u8 pad2[0x110 - 0x84];
} CARDControl;

typedef struct OSSramEx {
    u8 flashID[2][12];
} OSSramEx;

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

extern CARDControl __CARDBlock[2];
extern OSSramEx* __OSLockSramEx(void);
extern void __OSUnlockSramEx(int commit);
extern u16 __CARDGetFontEncode(void);

s32 VerifyID(CARDControl* card)
{
    CARDID* id;
    u16 checksum;
    u16 checksumInv;
    OSSramEx* sramEx;
    OSTime rand;
    int i;

    id = card->workArea;

    if (id->deviceID != 0 || id->size != card->size)
        return -6;

    __CARDCheckSum(id, sizeof(CARDID) - sizeof(u32), &checksum, &checksumInv);
    if (id->checkSum != checksum || id->checkSumInv != checksumInv)
        return -6;

    rand = *(OSTime*)&id->serial[12];
    sramEx = __OSLockSramEx();
    for (i = 0; i < 12; i++) {
        rand = (rand * 1103515245 + 12345) >> 16;
        if (id->serial[i] != (u8)(sramEx->flashID[card - __CARDBlock][i] + rand)) {
            __OSUnlockSramEx(0);
            return -6;
        }
        rand = ((rand * 1103515245 + 12345) >> 16) & 0x7FFF;
    }

    __OSUnlockSramEx(0);

    if (id->encode != __CARDGetFontEncode())
        return -13;

    return 0;
}
