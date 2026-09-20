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


extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int level);
extern void OSClearContext(OSContext* context);
extern void fn_80181698(OSThread* thread);
extern void fn_80180CE8(OSThreadQueue* queue);
extern void SelectThread(int yield);
extern volatile long RunQueueHint;

OSThreadQueue __OSActiveThreadQueue : 0x800000DC;
OSThread* __gCurrentThread : 0x800000E4;

void OSExitThread(void* val)
{
    OSThread* currentThread;
    int enabled;

    enabled = OSDisableInterrupts();
    currentThread = __gCurrentThread;

    OSClearContext(&currentThread->context);
    if (currentThread->attr & 1) {
        OSThread* next = currentThread->activeNext;
        OSThread* prev = currentThread->activePrev;
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
        currentThread->state = 0;
    } else {
        currentThread->state = 8;
        currentThread->val = val;
    }
    fn_80181698(currentThread);
    fn_80180CE8(&currentThread->queueJoin);
    RunQueueHint = 1;

    if (RunQueueHint != 0) {
        SelectThread(0);
    }

    OSRestoreInterrupts(enabled);
}
