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


typedef struct OSMutex {
    OSThreadQueue queue;
    OSThread* thread;
} OSMutex;

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int level);
extern void OSClearContext(OSContext* context);
extern void fn_80181698(OSThread* thread);
extern void OSWakeupThread(OSThreadQueue* queue);
extern void UnsetRun(OSThread* thread);
extern long __OSGetEffectivePriority(OSThread* thread);
extern OSThread* SetEffectivePriority(OSThread* thread, long priority);
extern void SelectThread(int yield);
extern volatile long RunQueueHint;

OSThreadQueue __OSActiveThreadQueue : 0x800000DC;

void OSCancelThread(OSThread* thread)
{
    int enabled = OSDisableInterrupts();

    switch (thread->state) {
    case 1:
        if (thread->suspend <= 0) {
            UnsetRun(thread);
        }
        break;
    case 2:
        RunQueueHint = 1;
        break;
    case 4: {
        OSThread* next = thread->linkNext;
        OSThread* prev = thread->linkPrev;
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
        thread->queue = 0;
        if ((thread->suspend <= 0) && thread->mutex) {
            OSThread* t = ((OSMutex*)thread->mutex)->thread;
            while (1) {
                long priority;
                if (t->suspend > 0) {
                    break;
                }
                priority = __OSGetEffectivePriority(t);
                if (t->priority == priority) {
                    break;
                }
                t = SetEffectivePriority(t, priority);
                if (t != 0) {
                    continue;
                }
                break;
            }
        }
        break;
    }
    default:
        OSRestoreInterrupts(enabled);
        return;
    }
    OSClearContext(&thread->context);
    if (thread->attr & 1) {
        OSThread* next = thread->activeNext;
        OSThread* prev = thread->activePrev;
        if (next == 0) {
            __OSActiveThreadQueue.tail = prev;
        } else {
            next->activePrev = prev;
        }
        if (prev == 0) {
            __OSActiveThreadQueue.head = next;
        } else {
            prev->activeNext = next;
        }
        thread->state = 0;
    } else {
        thread->state = 8;
    }
    fn_80181698(thread);
    OSWakeupThread(&thread->queueJoin);
    if (RunQueueHint != 0) {
        SelectThread(0);
    }
    OSRestoreInterrupts(enabled);
}
