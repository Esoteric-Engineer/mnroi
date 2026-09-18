typedef unsigned short u16;
typedef int s32;

typedef struct OSThread OSThread;
typedef struct OSMutex OSMutex;

typedef struct OSThreadQueue {
    OSThread* head;
    OSThread* tail;
} OSThreadQueue;

typedef struct OSMutexLink {
    OSMutex* next;
    OSMutex* prev;
} OSMutexLink;

struct OSMutex {
    OSThread* queueHead;
    OSThread* queueTail;
    OSThread* thread;
    s32 count;
    OSMutexLink link;
};

struct OSThread {
    unsigned char context[712];
    u16 state;
    u16 attr;
    s32 suspend;
    s32 priority;
    s32 base;
    void* val;
    void* queue;
    void* linkNext;
    void* linkPrev;
    void* queueJoinHead;
    void* queueJoinTail;
    void* mutex;
    OSMutex* queueMutexHead;
    OSMutex* queueMutexTail;
};

volatile unsigned long RunQueueBits = 0;
volatile unsigned long RunQueueHint = 0;
long Reschedule;

extern OSThreadQueue RunQueue[32];

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int level);

s32 OSDisableScheduler(void)
{
    register int enabled;
    long count;

    enabled = OSDisableInterrupts();
    count = Reschedule;
    Reschedule = count + 1;
    OSRestoreInterrupts(enabled);
    return count;
}

s32 OSEnableScheduler(void)
{
    register int enabled;
    long count;

    enabled = OSDisableInterrupts();
    count = Reschedule;
    Reschedule = count - 1;
    OSRestoreInterrupts(enabled);
    return count;
}

#pragma dont_inline on
void UnsetRun(OSThread* thread)
{
    OSThreadQueue* queue = thread->queue;
    OSThread* next = thread->linkNext;
    OSThread* prev = thread->linkPrev;

    if (next == 0) {
        queue->tail = prev;
    } else {
        next->linkPrev = prev;
    }

    if (prev == 0) {
        queue->head = next;
    } else {
        prev->linkNext = next;
    }

    if (!queue->head) {
        RunQueueBits &= ~(1 << (31 - thread->priority));
    }
    thread->queue = 0;
}
#pragma dont_inline reset

long __OSGetEffectivePriority(OSThread* thread)
{
    long priority = thread->base;
    OSMutex* mutex;

    for (mutex = thread->queueMutexHead; mutex; mutex = mutex->link.next) {
        OSThread* blocked = mutex->queueHead;
        if (blocked && blocked->priority < priority) {
            priority = blocked->priority;
        }
    }
    return priority;
}

OSThread* SetEffectivePriority(OSThread* thread, long priority)
{
    switch (thread->state) {
    case 1: {
        OSThread* prev;

        UnsetRun(thread);
        thread->priority = priority;

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

        thread->priority = priority;

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
            return ((OSMutex*)thread->mutex)->thread;
        }
        break;
    }
    case 2:
        RunQueueHint = 1;
        thread->priority = priority;
        break;
    }
    return 0;
}

void __OSPromoteThread(OSThread* thread, long priority)
{
    while (1) {
        if (thread->suspend > 0 || thread->priority <= priority) {
            break;
        }
        thread = SetEffectivePriority(thread, priority);
        if (thread == 0) {
            break;
        }
    }
}
