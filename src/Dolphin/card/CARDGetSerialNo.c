typedef long s32;
typedef unsigned char u8;
typedef unsigned long long u64;

typedef struct CARDID {
    u8 serial[32];
} CARDID;

typedef struct CARDControl {
    u8 pad[0x80];
    void* workArea;
} CARDControl;

extern s32 __CARDGetControlBlock(s32 chan, CARDControl** pcard);
extern s32 __CARDPutControlBlock(CARDControl* card, s32 result);

s32 CARDGetSerialNo(s32 chan, u64* serialNo)
{
    CARDControl* card;
    s32 result;
    CARDID* id;
    u64 code;
    int i;

    if (!(0 <= chan && chan < 2)) {
        return -128;
    }

    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return result;
    }

    id = (CARDID*)card->workArea;
    for (code = 0, i = 0; i < sizeof(id->serial) / sizeof(u64); ++i) {
        code ^= *(u64*)&id->serial[sizeof(u64) * i];
    }
    *serialNo = code;

    return __CARDPutControlBlock(card, 0);
}
