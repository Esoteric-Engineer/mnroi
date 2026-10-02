typedef long s32;
typedef int BOOL;

typedef struct OSThreadQueue {
    void* head;
    void* tail;
} OSThreadQueue;

typedef struct CARDControl {
    unsigned char pad0[4];
    s32 result;
    unsigned char pad1[0x8C - 8];
    OSThreadQueue threadQueue;
    unsigned char pad2[0x110 - 0x94];
} CARDControl;

extern CARDControl __CARDBlock[2];

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern void OSSleepThread(OSThreadQueue* queue);

static inline s32 CARDGetResultCode(s32 chan)
{
    CARDControl* card;

    if (chan < 0 || chan >= 2) {
        return -128;
    }
    card = &__CARDBlock[chan];
    return card->result;
}

s32 __CARDSync(s32 chan)
{
    CARDControl* block;
    s32 result;
    s32 enabled;

    block = &__CARDBlock[chan];
    enabled = OSDisableInterrupts();
    while ((result = CARDGetResultCode(chan)) == -1) {
        OSSleepThread(&block->threadQueue);
    }
    OSRestoreInterrupts(enabled);
    return result;
}
