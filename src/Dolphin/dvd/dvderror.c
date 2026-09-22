typedef unsigned char u8;
typedef unsigned int u32;
typedef int BOOL;

typedef struct OSSramEx {
    u8 pad0[0x24];
    u8 dvdErrorCode;
} OSSramEx;

extern void* __OSLockSramEx(void);
extern void __OSUnlockSramEx(BOOL commit);

extern u32 ErrorTable[18];

#define DIDNT_MATCH 29

static u8 ErrorCode2Num(u32 errorCode)
{
    u32 i;

    for (i = 0; i < 18; i++) {
        if (errorCode == ErrorTable[i]) {
            return i;
        }
    }

    if (errorCode >= 0x100000 && errorCode <= 0x100008) {
        return 17;
    }

    return DIDNT_MATCH;
}

static u8 Convert(u32 error)
{
    u32 statusCode;
    u32 errorCode;
    u8 errorNum;

    if (error == 0x01234567) {
        return -1;
    } else if (error == 0x01234568) {
        return -2;
    }

    statusCode = (error >> 24) & 0xFF;
    errorCode = error & 0x00FFFFFF;
    errorNum = ErrorCode2Num(errorCode);
    if (statusCode >= 6) {
        statusCode = 6;
    }

    return statusCode * 30 + errorNum;
}

void __DVDStoreErrorCode(u32 error)
{
    OSSramEx* sram;
    u8 num;

    num = Convert(error);
    sram = (OSSramEx*)__OSLockSramEx();
    sram->dvdErrorCode = num;
    __OSUnlockSramEx(1);
}
