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

int OSSetThreadPriority(OSThread* thread, long priority)
{
    OSThread* t;
    int enabled;

    if ((priority < 0) || (priority > 31)) {
        return 0;
    }
    enabled = OSDisableInterrupts();
    if (thread->base != priority) {
        thread->base = priority;
        t = thread;
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
        if (RunQueueHint != 0) {
            SelectThread(0);
        }
    }
    OSRestoreInterrupts(enabled);
    return 1;
}
