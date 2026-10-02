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

extern OSContext* OSGetCurrentContext(void);
extern u32 OSSaveContext(OSContext* context);
extern void OSSetCurrentContext(OSContext* context);
extern void OSLoadContext(OSContext* context);
extern void OSClearContext(OSContext* context);
extern int OSEnableInterrupts(void);
extern int OSDisableInterrupts(void);

extern volatile long RunQueueHint;
extern volatile u32 RunQueueBits;
extern OSThreadQueue RunQueue[32];
extern long Reschedule;
extern OSSwitchThreadCallback SwitchThreadCallback;

OSThread* __gCurrentThread : 0x800000E4;

static inline OSThread* OSGetCurrentThread(void)
{
    return __gCurrentThread;
}

OSThread* SelectThread(int yield)
{
    OSContext* currentContext;
    OSThread* currentThread;
    OSThread* nextThread;
    long priority;
    OSThreadQueue* queue;
    OSThreadQueue* rq = RunQueue;

    if (Reschedule > 0) {
        return 0;
    }

    currentContext = OSGetCurrentContext();
    currentThread = OSGetCurrentThread();

    if (currentContext != &currentThread->context) {
        return 0;
    }

    if (currentThread) {
        if (currentThread->state == 2) {
            if (yield == 0) {
                priority = __cntlzw(RunQueueBits);
                if (currentThread->priority <= priority) {
                    return 0;
                }
            }
            currentThread->state = 1;
            {
                OSThread* prev;
                currentThread->queue = &rq[currentThread->priority];
                prev = ((OSThreadQueue*)currentThread->queue)->tail;
                if (prev == 0) {
                    ((OSThreadQueue*)currentThread->queue)->head = currentThread;
                } else {
                    prev->linkNext = currentThread;
                }
                currentThread->linkPrev = prev;
                currentThread->linkNext = 0;
                ((OSThreadQueue*)currentThread->queue)->tail = currentThread;
                RunQueueBits |= 1 << (31 - currentThread->priority);
                RunQueueHint = 1;
            }
        }
        if (!(currentThread->context.state & 2) && (OSSaveContext(&currentThread->context) != 0)) {
            return 0;
        }
    }

    if (RunQueueBits == 0) {
        SwitchThreadCallback(__gCurrentThread, 0);
        __gCurrentThread = 0;
        OSSetCurrentContext((OSContext*)((u8*)rq + 0x730));
        do {
            OSEnableInterrupts();
            while (RunQueueBits == 0)
                ;
            OSDisableInterrupts();
        } while (RunQueueBits == 0);
        OSClearContext((OSContext*)(rq + 230));
    }

    RunQueueHint = 0;
    priority = __cntlzw(RunQueueBits);

    queue = &rq[priority];
    nextThread = queue->head;

    {
        OSThread* next = nextThread->linkNext;
        if (next == 0) {
            queue->tail = 0;
        } else {
            next->linkPrev = 0;
        }
        queue->head = next;
    }

    if (!queue->head) {
        RunQueueBits &= ~(1 << (31 - priority));
    }
    nextThread->queue = 0;
    nextThread->state = 2;
    SwitchThreadCallback(__gCurrentThread, nextThread);
    __gCurrentThread = nextThread;
    OSSetCurrentContext(&nextThread->context);
    OSLoadContext(&nextThread->context);
    return nextThread;
}
