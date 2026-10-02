typedef unsigned char u8;
typedef unsigned short u16;
typedef long s32;
typedef unsigned long u32;
typedef int BOOL;

typedef struct CARDControl {
    BOOL attached;
    s32 result;
    u32 pad0;
    u32 sectorSize;
} CARDControl;

typedef struct CARDDir {
    u8 gameName[4];
    u8 company[2];
    u8 pad6[2];
    u8 fileName[32];
    u8 pad28[0x40 - 0x28];
} CARDDir;

extern s32 __CARDGetControlBlock(s32 chan, CARDControl** card);
extern u16* __CARDGetFatBlock(CARDControl* card);
extern CARDDir* __CARDGetDirBlock(CARDControl* card);
extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);

static inline s32 PutControlBlock(CARDControl* card, s32 result)
{
    BOOL enabled = OSDisableInterrupts();

    if (card->attached) {
        card->result = result;
    } else if (card->result == -1) {
        card->result = result;
    }
    OSRestoreInterrupts(enabled);
    return result;
}

s32 CARDFreeBlocks(s32 chan, s32* byteNotUsed, s32* filesNotUsed)
{
    CARDControl* card;
    s32 result;
    u16* fat;
    CARDDir* dir;
    CARDDir* ent;
    u16 fileNo;

    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return result;
    }

    fat = __CARDGetFatBlock(card);
    dir = __CARDGetDirBlock(card);
    if (fat == 0 || dir == 0) {
        return PutControlBlock(card, -6);
    }

    if (byteNotUsed) {
        *byteNotUsed = (s32)(card->sectorSize * fat[3]);
    }

    if (filesNotUsed) {
        *filesNotUsed = 0;
        for (fileNo = 0; fileNo < 127; fileNo++) {
            ent = &dir[fileNo];
            if (ent->fileName[0] == 0xff) {
                ++*filesNotUsed;
            }
        }
    }

    return PutControlBlock(card, 0);
}
