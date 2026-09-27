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

s32 OSTryWaitSemaphore(OSSemaphore* sem)
{
    int enabled;
    s32 count;
    s32 ret;

    enabled = OSDisableInterrupts();
    ret = count = sem->count;
    if (count > 0) {
        sem->count = count - 1;
    }
    OSRestoreInterrupts(enabled);
    return ret;
}
