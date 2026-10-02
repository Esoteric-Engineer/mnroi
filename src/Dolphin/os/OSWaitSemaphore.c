typedef long s32;

typedef struct OSThread OSThread;

typedef struct OSThreadQueue {
    OSThread* head;
    OSThread* tail;
} OSThreadQueue;

typedef struct OSSemaphore {
    volatile s32 count;
    OSThreadQueue queue;
} OSSemaphore;

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int level);
extern void OSSleepThread(OSThreadQueue* queue);

s32 OSWaitSemaphore(OSSemaphore* sem)
{
    int enabled;
    s32 count;

    enabled = OSDisableInterrupts();
    while ((count = sem->count) <= 0) {
        OSSleepThread(&sem->queue);
    }
    sem->count--;
    OSRestoreInterrupts(enabled);
    return count;
}
