typedef unsigned long u32;
typedef long long s64;

typedef struct OSAlarm OSAlarm;
typedef void (*OSAlarmHandler)(OSAlarm* alarm, void* context);

struct OSAlarm {
    OSAlarmHandler handler;
    u32 tag;
    s64 fire;
    OSAlarm* prev;
    OSAlarm* next;
    s64 period;
    s64 start;
};

typedef struct OSAlarmQueue {
    OSAlarm* head;
    OSAlarm* tail;
} OSAlarmQueue;

typedef struct OSContext {
    u32 gpr[32];
    u32 pad[(0x1C8 - 0x80) / 4];
    double fpr[32];
} OSContext;

extern OSAlarmQueue AlarmQueue;

extern s64 __OSGetSystemTime(void);
extern void PPCMtdec(u32 val);
extern void InsertAlarm(OSAlarm* alarm, s64 fire, OSAlarmHandler handler);
extern void OSLoadContext(OSContext* context);
extern void OSClearContext(OSContext* context);
extern void OSSetCurrentContext(OSContext* context);
extern int OSDisableScheduler(void);
extern int OSEnableScheduler(void);
extern void __OSReschedule(void);

static void SetTimer(OSAlarm* alarm)
{
    s64 delta = alarm->fire - __OSGetSystemTime();

    if (delta < 0) {
        PPCMtdec(0);
    } else if (delta < 0x80000000) {
        PPCMtdec((u32)delta);
    } else {
        PPCMtdec(0x7FFFFFFF);
    }
}

static void DecrementerExceptionCallback(register u32 exception, register OSContext* context)
{
    OSAlarm* alarm;
    OSAlarm* next;
    OSContext context2;
    OSAlarmHandler handler;
    s64 time;

    time = __OSGetSystemTime();
    alarm = AlarmQueue.head;
    if (alarm == 0) {
        OSLoadContext(context);
    }

    if (time < alarm->fire) {
        SetTimer(alarm);
        OSLoadContext(context);
    }

    next = alarm->next;
    AlarmQueue.head = next;
    if (next == 0) {
        AlarmQueue.tail = 0;
    } else {
        next->prev = 0;
    }
    handler = alarm->handler;
    alarm->handler = 0;
    if (0 < alarm->period) {
        InsertAlarm(alarm, 0, handler);
    }

    if (AlarmQueue.head) {
        SetTimer(AlarmQueue.head);
    }

    OSDisableScheduler();
    OSClearContext(&context2);
    OSSetCurrentContext(&context2);
    handler(alarm, context);
    OSClearContext(&context2);
    OSSetCurrentContext(context);
    OSEnableScheduler();
    __OSReschedule();
    OSLoadContext(context);
}

asm void DecrementerExceptionHandler(register u32 type, register OSContext* ctx)
{
    nofralloc
    stw r0, 0(r4)
    stw r1, 4(r4)
    stw r2, 8(r4)
    stmw r6, 24(r4)

    mfspr r0, 0x391
    stw r0, 424(r4)
    mfspr r0, 0x392
    stw r0, 428(r4)
    mfspr r0, 0x393
    stw r0, 432(r4)
    mfspr r0, 0x394
    stw r0, 436(r4)
    mfspr r0, 0x395
    stw r0, 440(r4)
    mfspr r0, 0x396
    stw r0, 444(r4)
    mfspr r0, 0x397
    stw r0, 448(r4)

    stwu r1, -8(r1)
    b DecrementerExceptionCallback
}
