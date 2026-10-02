typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;
typedef int s32;

typedef struct OSThread OSThread;
typedef struct OSMutex OSMutex;

typedef struct OSThreadQueue {
    OSThread* head;
    OSThread* tail;
} OSThreadQueue;

typedef struct OSMutexQueue {
    OSMutex* head;
    OSMutex* tail;
} OSMutexQueue;

typedef struct OSMutexLink {
    OSMutex* next;
    OSMutex* prev;
} OSMutexLink;

typedef struct OSContext {
    u32 gpr[32];
    u32 cr;
    u32 lr;
    u32 ctr;
    u32 xer;
    u64 fpr[32];
    u32 fpscr_pad;
    u32 fpscr;
    u32 srr0;
    u32 srr1;
    u16 mode;
    u16 state;
    u32 gqr[8];
    u32 psf_pad;
    u64 psf[32];
} OSContext;

struct OSThread {
    OSContext context;
    u16 state;
    u16 attr;
    s32 suspend;
    s32 priority;
    s32 base;
    void* val;
    void* queue;
    OSThread* linkNext;
    OSThread* linkPrev;
    OSThreadQueue queueJoin;
    OSMutex* mutex;
    OSMutexQueue queueMutex;
    OSThread* activeNext;
    OSThread* activePrev;
    void* stackBase;
    u32* stackEnd;
    s32 error;
    void* specific[2];
};

struct OSMutex {
    OSThreadQueue queue;
    OSThread* thread;
    long count;
    OSMutexLink link;
};

extern void OSInitThreadQueue(OSThreadQueue* queue);
extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int level);
extern OSThread* fn_8017FD74(void);
extern void __OSPromoteThread(OSThread* thread, long priority);
extern void OSSleepThread(OSThreadQueue* queue);
extern void OSWakeupThread(OSThreadQueue* queue);
extern long __OSGetEffectivePriority(OSThread* thread);

void OSInitMutex(OSMutex* mutex)
{
    OSInitThreadQueue(&mutex->queue);
    mutex->thread = 0;
    mutex->count = 0;
}

void OSLockMutex(OSMutex* mutex)
{
    int enabled = OSDisableInterrupts();
    OSThread* currentThread = fn_8017FD74();

    while (1) {
        OSThread* ownerThread = mutex->thread;
        if (ownerThread == 0) {
            mutex->thread = currentThread;
            mutex->count++;
            {
                OSMutex* prev = currentThread->queueMutex.tail;
                if (prev == 0) {
                    currentThread->queueMutex.head = mutex;
                } else {
                    prev->link.next = mutex;
                }
                mutex->link.prev = prev;
                mutex->link.next = 0;
                currentThread->queueMutex.tail = mutex;
            }
            break;
        } else if (ownerThread == currentThread) {
            mutex->count++;
            break;
        } else {
            currentThread->mutex = mutex;
            __OSPromoteThread(mutex->thread, currentThread->priority);
            OSSleepThread(&mutex->queue);
            currentThread->mutex = 0;
        }
    }
    OSRestoreInterrupts(enabled);
}

void OSUnlockMutex(OSMutex* mutex)
{
    int enabled = OSDisableInterrupts();
    OSThread* currentThread = fn_8017FD74();

    if (mutex->thread == currentThread) {
        if (!--mutex->count) {
            {
                OSMutex* next = mutex->link.next;
                OSMutex* prev = mutex->link.prev;
                if (next == 0) {
                    currentThread->queueMutex.tail = prev;
                } else {
                    next->link.prev = prev;
                }
                if (prev == 0) {
                    currentThread->queueMutex.head = next;
                } else {
                    prev->link.next = next;
                }
            }
            mutex->thread = 0;

            if (currentThread->priority < currentThread->base) {
                currentThread->priority = __OSGetEffectivePriority(currentThread);
            }
            OSWakeupThread(&mutex->queue);
        }
    }
    OSRestoreInterrupts(enabled);
}

void __OSUnlockAllMutex(OSThread* thread)
{
    OSMutex* mutex;

    while (thread->queueMutex.head) {
        mutex = thread->queueMutex.head;
        {
            OSMutex* next = mutex->link.next;
            if (next == 0) {
                thread->queueMutex.tail = 0;
            } else {
                next->link.prev = 0;
            }
            thread->queueMutex.head = next;
        }
        mutex->count = 0;
        mutex->thread = 0;
        OSWakeupThread(&mutex->queue);
    }
}
