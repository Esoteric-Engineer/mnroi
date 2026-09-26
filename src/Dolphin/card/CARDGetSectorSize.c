typedef long s32;
typedef unsigned long u32;
typedef int BOOL;

typedef struct CARDControl {
    BOOL attached;
    s32 result;
    u32 pad0;
    u32 sectorSize;
} CARDControl;

extern s32 fn_8040B0F0(s32 chan, CARDControl** card);
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

s32 CARDGetSectorSize(s32 chan, u32* size)
{
    CARDControl* card;
    s32 result;

    result = fn_8040B0F0(chan, &card);
    if (result < 0) {
        return result;
    }
    *size = card->sectorSize;
    return PutControlBlock(card, 0);
}
