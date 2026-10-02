typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;
typedef int s32;

typedef struct OSThread OSThread;

typedef struct OSThreadQueue {
    OSThread* head;
    OSThread* tail;
} OSThreadQueue;

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
    void* mutex;
    OSThreadQueue queueMutex;
    OSThread* activeNext;
    OSThread* activePrev;
    void* stackBase;
    u32* stackEnd;
    s32 error;
    void* specific[2];
};

typedef struct OSMutex OSMutex;
struct OSMutex {
    OSThreadQueue queue;
    OSThread* thread;
    s32 count;
    OSMutex* next;
    OSMutex* prev;
};

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int level);
extern long __OSGetEffectivePriority(OSThread* thread);
extern OSThread* SetEffectivePriority(OSThread* thread, long priority);
extern void SelectThread(int yield);
extern volatile long RunQueueHint;
extern volatile u32 RunQueueBits;
extern OSThreadQueue RunQueue[32];

static inline long EffPrio(OSThread* thread)
{
    long priority = thread->base;
    OSMutex* m;
    for (m = (OSMutex*)thread->queueMutex.head; m; m = m->next) {
        OSThread* b = m->queue.head;
        if (b) {
            long bp = b->priority;
            if (bp < priority) {
                priority = bp;
            }
        }
    }
    return priority;
}

long OSResumeThread(OSThread* thread)
{
    int enabled = OSDisableInterrupts();
    long suspendCount;

    suspendCount = thread->suspend--;
    if (thread->suspend < 0) {
        thread->suspend = 0;
    } else if (thread->suspend == 0) {
        switch (thread->state) {
        case 1: {
            OSThread* prev;
            thread->priority = EffPrio(thread);
            thread->queue = &RunQueue[thread->priority];
            prev = ((OSThreadQueue*)thread->queue)->tail;
            if (prev == 0) {
                ((OSThreadQueue*)thread->queue)->head = thread;
            } else {
                prev->linkNext = thread;
            }
            thread->linkPrev = prev;
            thread->linkNext = 0;
            ((OSThreadQueue*)thread->queue)->tail = thread;
            RunQueueBits |= 1 << (31 - thread->priority);
            RunQueueHint = 1;
            break;
        }
        case 4: {
            OSThread* next = thread->linkNext;
            OSThread* prev = thread->linkPrev;
            OSThread* n;
            OSThread* p;
            if (next == 0) {
                ((OSThreadQueue*)thread->queue)->tail = prev;
            } else {
                next->linkPrev = prev;
            }
            if (prev == 0) {
                ((OSThreadQueue*)thread->queue)->head = next;
            } else {
                prev->linkNext = next;
            }
            thread->priority = EffPrio(thread);
            for (n = ((OSThreadQueue*)thread->queue)->head; n && n->priority <= thread->priority; n = n->linkNext)
                ;
            if (n == 0) {
                p = ((OSThreadQueue*)thread->queue)->tail;
                if (p == 0) {
                    ((OSThreadQueue*)thread->queue)->head = thread;
                } else {
                    p->linkNext = thread;
                }
                thread->linkPrev = p;
                thread->linkNext = 0;
                ((OSThreadQueue*)thread->queue)->tail = thread;
            } else {
                thread->linkNext = n;
                p = n->linkPrev;
                n->linkPrev = thread;
                thread->linkPrev = p;
                if (p == 0) {
                    ((OSThreadQueue*)thread->queue)->head = thread;
                } else {
                    p->linkNext = thread;
                }
            }
            if (thread->mutex) {
                OSThread* t = ((OSMutex*)thread->mutex)->thread;
                while (1) {
                    long pr;
                    if (t->suspend > 0) {
                        break;
                    }
                    pr = __OSGetEffectivePriority(t);
                    if (t->priority == pr) {
                        break;
                    }
                    t = SetEffectivePriority(t, pr);
                    if (t != 0) {
                        continue;
                    }
                    break;
                }
            }
            break;
        }
        }
        if (RunQueueHint != 0) {
            SelectThread(0);
        }
    }
    OSRestoreInterrupts(enabled);
    return suspendCount;
}
