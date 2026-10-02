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

typedef void (*OSSwitchThreadCallback)(OSThread* from, OSThread* to);

typedef struct RunQueueBlock {
    OSThreadQueue queues[32];
    OSThread idleThread;
    OSThread defaultThread;
    OSContext idleContext;
} RunQueueBlock;

extern void OSInitThreadQueue(OSThreadQueue* queue);
extern void OSClearContext(OSContext* context);
extern void OSSetCurrentContext(OSContext* context);
extern void OSClearStack(u32 val);
extern void DefaultSwitchThreadCallback(OSThread* from, OSThread* to);

extern char _stack_addr[];
extern char _stack_end[];

extern volatile long RunQueueHint;
extern volatile u32 RunQueueBits;
extern long Reschedule;

OSSwitchThreadCallback SwitchThreadCallback = DefaultSwitchThreadCallback;
RunQueueBlock RunQueue;

OSThread* __gUnkThread1 : 0x800000D8;
OSThread* __gCurrentThread : 0x800000E4;
OSThreadQueue __OSActiveThreadQueue : 0x800000DC;

void __OSThreadInit(void)
{
    RunQueueBlock* rq = &RunQueue;
    OSThread* thread = &rq->defaultThread;
    int prio;

    thread->state = 2;
    thread->attr = 1;
    thread->priority = thread->base = 0x10;
    thread->suspend = 0;
    thread->val = (void*)-1;
    thread->mutex = 0;

    OSInitThreadQueue(&thread->queueJoin);

    rq->defaultThread.queueMutex.head = rq->defaultThread.queueMutex.tail = 0;

    __gUnkThread1 = thread;
    OSClearContext(&thread->context);
    OSSetCurrentContext(&thread->context);
    rq->defaultThread.stackBase = _stack_addr;
    rq->defaultThread.stackEnd = (u32*)_stack_end;
    *rq->defaultThread.stackEnd = 0xDEADBABE;
    SwitchThreadCallback(__gCurrentThread, thread);
    __gCurrentThread = thread;
    OSClearStack(0);
    RunQueueBits = 0;
    RunQueueHint = 0;

    for (prio = 0; prio <= 31; prio++) {
        OSInitThreadQueue(&rq->queues[prio]);
    }
    OSInitThreadQueue(&__OSActiveThreadQueue);

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

    OSClearContext(&rq->idleContext);
    Reschedule = 0;
}
