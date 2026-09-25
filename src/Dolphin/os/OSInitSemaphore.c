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
extern void OSInitThreadQueue(OSThreadQueue* queue);

void OSInitSemaphore(OSSemaphore* sem, s32 count)
{
    int enabled = OSDisableInterrupts();
    OSInitThreadQueue(&sem->queue);
    sem->count = count;
    OSRestoreInterrupts(enabled);
}
