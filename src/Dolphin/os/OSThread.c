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

// OSCheckActiveThreads's ASSERTREPORT condition strings; the function is dead-stripped (unreferenced), so only its string literals survive in the original.
#pragma force_active on
char lbl_804D1308[95] = "OSCheckActiveThreads: Failed RunQueue[prio].head != NULL && RunQueue[prio].tail != NULL in %d\n";
char lbl_804D1368[11] = "OSThread.c";
char lbl_804D1374[95] = "OSCheckActiveThreads: Failed RunQueue[prio].head == NULL && RunQueue[prio].tail == NULL in %d\n";
char lbl_804D13D4[70] = "OSCheckActiveThreads: Failed CheckThreadQueue(&RunQueue[prio]) in %d\n";
char lbl_804D141C[126] = "OSCheckActiveThreads: Failed __OSActiveThreadQueue.head == NULL || __OSActiveThreadQueue.head->linkActive.prev == NULL in %d\n";
char lbl_804D149C[126] = "OSCheckActiveThreads: Failed __OSActiveThreadQueue.tail == NULL || __OSActiveThreadQueue.tail->linkActive.next == NULL in %d\n";
char lbl_804D151C[122] = "OSCheckActiveThreads: Failed thread->linkActive.next == NULL || thread == thread->linkActive.next->linkActive.prev in %d\n";
char lbl_804D1598[122] = "OSCheckActiveThreads: Failed thread->linkActive.prev == NULL || thread == thread->linkActive.prev->linkActive.next in %d\n";
char lbl_804D1614[81] = "OSCheckActiveThreads: Failed *(thread->stackEnd) == OS_THREAD_STACK_MAGIC in %d\n";
char lbl_804D1668[113] = "OSCheckActiveThreads: Failed OS_PRIORITY_MIN <= thread->priority && thread->priority <= OS_PRIORITY_MAX+1 in %d\n";
char lbl_804D16DC[57] = "OSCheckActiveThreads: Failed 0 <= thread->suspend in %d\n";
char lbl_804D1718[73] = "OSCheckActiveThreads: Failed CheckThreadQueue(&thread->queueJoin) in %d\n";
char lbl_804D1764[81] = "OSCheckActiveThreads: Failed thread->queue == &RunQueue[thread->priority] in %d\n";
char lbl_804D17B8[82] = "OSCheckActiveThreads: Failed IsMember(&RunQueue[thread->priority], thread) in %d\n";
char lbl_804D180C[89] = "OSCheckActiveThreads: Failed thread->priority == __OSGetEffectivePriority(thread) in %d\n";
char lbl_804D1868[66] = "OSCheckActiveThreads: Failed !IsSuspended(thread->suspend) in %d\n";
char lbl_804D18AC[58] = "OSCheckActiveThreads: Failed thread->queue == NULL in %d\n";
char lbl_804D18E8[58] = "OSCheckActiveThreads: Failed thread->queue != NULL in %d\n";
char lbl_804D1924[68] = "OSCheckActiveThreads: Failed CheckThreadQueue(thread->queue) in %d\n";
char lbl_804D1968[68] = "OSCheckActiveThreads: Failed IsMember(thread->queue, thread) in %d\n";
char lbl_804D19AC[59] = "OSCheckActiveThreads: Failed thread->priority == 32 in %d\n";
char lbl_804D19E8[63] = "OSCheckActiveThreads: Failed !__OSCheckDeadLock(thread) in %d\n";
char lbl_804D1A28[103] = "OSCheckActiveThreads: Failed thread->queueMutex.head == NULL && thread->queueMutex.tail == NULL in %d\n";
char lbl_804D1A90[69] = "OSCheckActiveThreads: Failed. unkown thread state (%d) of thread %p\n";
char lbl_804D1AD8[61] = "OSCheckActiveThreads: Failed __OSCheckMutexes(thread) in %d\n";
#pragma force_active reset
