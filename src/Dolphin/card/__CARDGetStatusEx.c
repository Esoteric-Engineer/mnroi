typedef unsigned char u8;
typedef long s32;

typedef struct CARDControl CARDControl;

typedef struct CARDDir {
    u8 pad[0x40];
} CARDDir;

extern s32 __CARDGetControlBlock(s32 chan, CARDControl** card);
extern s32 __CARDPutControlBlock(CARDControl* card, s32 result);
extern CARDDir* __CARDGetDirBlock(CARDControl* card);
extern s32 __CARDIsReadable(CARDControl* card, CARDDir* ent);
extern void* memcpy(void* dst, const void* src, unsigned long n);

s32 __CARDGetStatusEx(s32 chan, s32 fileNo, CARDDir* dirent)
{
    CARDControl* card;
    CARDDir* dir;
    CARDDir* ent;
    s32 result;

    if (fileNo < 0 || fileNo >= 127) {
        return -128;
    }

    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return result;
    }

    dir = __CARDGetDirBlock(card);
    ent = &dir[fileNo];
    result = __CARDIsReadable(card, ent);
    if (result >= 0) {
        memcpy(dirent, ent, 0x40);
    }
    return __CARDPutControlBlock(card, result);
}
