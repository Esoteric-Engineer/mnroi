typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long s32;

extern void* memcpy(void* dst, const void* src, unsigned long n);

typedef struct CARDControl {
    u8 pad0[0xC];
    u32 sectorSize;
    u8 pad1[0x110 - 0x10];
} CARDControl;

typedef struct CARDDir {
    u8 gameName[4];
    u8 company[2];
    u8 pad0;
    u8 bannerFormat;
    u8 fileName[0x20];
    u32 time;
    u32 iconAddr;
    u16 iconFormat;
    u16 iconSpeed;
    u8 pad1[0x38 - 0x34];
    u16 length;
    u8 pad2[0x3C - 0x3A];
    u32 commentAddr;
} CARDDir;

typedef struct CARDStat {
    u8 fileName[0x20];
    u32 length;
    u32 time;
    u8 gameName[4];
    u8 company[2];
    u8 bannerFormat;
    u32 iconAddr;
    u16 iconFormat;
    u16 iconSpeed;
    u32 commentAddr;
} CARDStat;

extern s32 fn_8040B0F0(s32 chan, CARDControl** card);
extern s32 __CARDPutControlBlock(CARDControl* card, s32 result);
extern CARDDir* __CARDGetDirBlock(CARDControl* card);
extern s32 fn_8040DF78(CARDControl* card, CARDDir* ent);
extern void fn_8040F330(CARDDir* ent, CARDStat* stat);

s32 CARDGetStatus(s32 chan, s32 fileNo, CARDStat* stat)
{
    CARDControl* card;
    CARDDir* dir;
    CARDDir* ent;
    s32 result;

    if (fileNo < 0 || fileNo >= 127)
        return -128;

    result = fn_8040B0F0(chan, &card);
    if (result < 0)
        return result;

    dir = __CARDGetDirBlock(card);
    ent = &dir[fileNo];
    result = fn_8040DF78(card, ent);

    if (result >= 0) {
        memcpy(stat->gameName, ent->gameName, 4);
        memcpy(stat->company, ent->company, 2);
        stat->length = (u32)ent->length * card->sectorSize;
        memcpy(stat->fileName, ent->fileName, 0x20);
        stat->time = ent->time;
        stat->bannerFormat = ent->bannerFormat;
        stat->iconAddr = ent->iconAddr;
        stat->iconFormat = ent->iconFormat;
        stat->iconSpeed = ent->iconSpeed;
        stat->commentAddr = ent->commentAddr;
        fn_8040F330(ent, stat);
    }
    return __CARDPutControlBlock(card, result);
}
