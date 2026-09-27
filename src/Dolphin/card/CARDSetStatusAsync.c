typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long s32;
typedef long long s64;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDControl {
    u8 pad0[0x110];
} CARDControl;

typedef struct CARDDir {
    u8 pad0[7];
    u8 bannerFormat;
    u8 pad1[0x28 - 0x8];
    u32 time;
    u32 iconAddr;
    u16 iconFormat;
    u16 iconSpeed;
    u8 pad2[0x3C - 0x34];
    u32 commentAddr;
} CARDDir;

typedef struct CARDStat {
    u8 pad0[0x2E];
    u8 bannerFormat;
    u8 pad1;
    u32 iconAddr;
    u16 iconFormat;
    u16 iconSpeed;
    u32 commentAddr;
} CARDStat;

u32 __OSBusClock : 0x800000F8;

extern s32 __CARDGetControlBlock(s32 chan, CARDControl** card);
extern s32 __CARDPutControlBlock(CARDControl* card, s32 result);
extern CARDDir* __CARDGetDirBlock(CARDControl* card);
extern s32 __CARDIsWritable(CARDControl* card, CARDDir* ent);
extern s32 __CARDUpdateDir(s32 chan, CARDCallback callback);
extern void fn_8040F330(CARDDir* ent, CARDStat* stat);
extern s64 OSGetTime(void);

s32 CARDSetStatusAsync(s32 chan, s32 fileNo, CARDStat* stat, CARDCallback callback)
{
    CARDControl* card;
    CARDDir* dir;
    CARDDir* ent;
    s32 result;

    if (fileNo < 0 || fileNo >= 127 ||
        (stat->iconAddr != 0xFFFFFFFF && stat->iconAddr >= 0x200) ||
        (stat->commentAddr != 0xFFFFFFFF && (stat->commentAddr % 0x2000) > 0x1FC0))
        return -128;

    result = __CARDGetControlBlock(chan, &card);
    if (result < 0)
        return result;

    dir = __CARDGetDirBlock(card);
    ent = &dir[fileNo];
    result = __CARDIsWritable(card, ent);
    if (result < 0)
        return __CARDPutControlBlock(card, result);

    ent->bannerFormat = stat->bannerFormat;
    ent->iconAddr = stat->iconAddr;
    ent->iconFormat = stat->iconFormat;
    ent->iconSpeed = stat->iconSpeed;
    ent->commentAddr = stat->commentAddr;
    fn_8040F330(ent, stat);

    if (ent->iconAddr == 0xFFFFFFFF)
        ent->iconSpeed = (ent->iconSpeed & ~3) | 1;

    ent->time = (u32)(OSGetTime() / (__OSBusClock / 4));
    result = __CARDUpdateDir(chan, callback);
    if (result < 0)
        __CARDPutControlBlock(card, result);
    return result;
}
