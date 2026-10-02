typedef long s32;

typedef struct OSThreadQueue {
    void* head;
    void* tail;
} OSThreadQueue;

typedef struct CARDControl {
    unsigned char pad0[0x8C];
    OSThreadQueue threadQueue;
    unsigned char pad1[0x110 - 0x94];
} CARDControl;

extern CARDControl __CARDBlock[2];

extern void OSWakeupThread(OSThreadQueue* queue);

void __CARDSyncCallback(s32 chan, s32 result)
{
    CARDControl* card;

    card = &__CARDBlock[chan];
    OSWakeupThread(&card->threadQueue);
}
