typedef long s32;
typedef int BOOL;

typedef struct DVDDiskID {
    unsigned long pad[8];
} DVDDiskID;

typedef struct CARDControl {
    BOOL attached;
    s32 result;
    unsigned char pad8[0xD0 - 0x8];
    void* apiCallback;
    unsigned char padD4[0x10C - 0xD4];
    DVDDiskID* diskID;
} CARDControl;

extern CARDControl __CARDBlock[2];

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);

s32 __CARDGetControlBlock(s32 chan, CARDControl** pcard)
{
    BOOL enabled;
    s32 result;
    CARDControl* card;

    card = &__CARDBlock[chan];
    if (chan < 0 || chan >= 2 || !card->diskID) {
        return -128;
    }

    enabled = OSDisableInterrupts();
    if (!card->attached) {
        result = -3;
    } else if (card->result == -1) {
        result = -1;
    } else {
        card->result = -1;
        result = 0;
        card->apiCallback = 0;
        *pcard = card;
    }
    OSRestoreInterrupts(enabled);
    return result;
}
