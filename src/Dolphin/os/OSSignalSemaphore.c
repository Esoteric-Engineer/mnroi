typedef int s32;

typedef struct OSThread OSThread;

typedef struct OSThreadQueue {
    OSThread* head;
    OSThread* tail;
} OSThreadQueue;

typedef struct OSSemaphore {
    s32 count;
    OSThreadQueue queue;
} OSSemaphore;

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int level);
extern void OSWakeupThread(OSThreadQueue* queue);

s32 OSSignalSemaphore(OSSemaphore* sem)
{
    int enabled;
    s32 count;

    enabled = OSDisableInterrupts();
    count = sem->count;
    sem->count = count + 1;
    OSWakeupThread(&sem->queue);
    OSRestoreInterrupts(enabled);
    return count;
}
