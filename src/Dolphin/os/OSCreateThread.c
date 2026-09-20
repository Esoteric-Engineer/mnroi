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

struct OSFpuInfo {
    char pad[0x40];
    u32 enabled;
};

extern struct OSFpuInfo lbl_8057C570;
extern u32 lbl_8066C3D0;

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int level);
extern void lbl_8017C74C(OSContext* context, u32 pc, u32 sp);
extern void OSExitThread(void* val);

OSThreadQueue __OSActiveThreadQueue : 0x800000DC;


int fn_8018037C(OSThread* thread, void* (*func)(void*), void* param, void* stack,
                u32 stackSize, s32 priority, u16 attr)
{
    int enabled;
    u32 sp;
    int i;
    u64 fill = (u64)-1;

    if (priority < 0 || priority > 31) {
        return 0;
    }

    thread->state = 1;
    thread->attr = attr & 1;
    thread->base = priority;
    thread->priority = priority;
    thread->suspend = 1;
    thread->val = (void*)-1;
    thread->mutex = 0;
    thread->queueJoin.tail = 0;
    thread->queueJoin.head = 0;
    thread->queueMutex.tail = 0;
    thread->queueMutex.head = 0;

    sp = (u32)stack;
    sp &= ~7;
    sp -= 8;
    ((u32*)sp)[0] = 0;
    ((u32*)sp)[1] = 0;
    lbl_8017C74C(&thread->context, (u32)func, sp);
    thread->context.lr = (u32)OSExitThread;
    thread->context.gpr[3] = (u32)param;
    thread->stackBase = stack;
    thread->stackEnd = (u32*)((u32)stack - stackSize);
    *thread->stackEnd = 0xDEADBABE;
    thread->error = 0;
    thread->specific[0] = 0;
    thread->specific[1] = 0;

    enabled = OSDisableInterrupts();

    if (lbl_8057C570.enabled != 0) {
        thread->context.srr1 |= 0x900;
        thread->context.state |= 1;
        thread->context.fpscr = (lbl_8066C3D0 & 0xF8) | 4;
        for (i = 0; i < 32; i++) {
            thread->context.fpr[i] = (u64)-1;
            thread->context.psf[i] = (u64)-1;
        }
    }

    {
        OSThread* prev = __OSActiveThreadQueue.tail;
        if (prev == 0) {
            __OSActiveThreadQueue.head = thread;
        } else {
            prev->activeNext = thread;
        }
        thread->activePrev = prev;
        thread->activeNext = 0;
        __OSActiveThreadQueue.tail = thread;
    }

    OSRestoreInterrupts(enabled);
    return 1;
}
