typedef unsigned long u32;
typedef long long s64;

typedef struct OSAlarm {
    void* handler;
    u32 tag;
    s64 fire;
    struct OSAlarm* prev;
    struct OSAlarm* next;
    s64 period;
    s64 start;
} OSAlarm;

typedef struct OSAlarmQueue {
    OSAlarm* head;
    OSAlarm* tail;
} OSAlarmQueue;

extern OSAlarmQueue AlarmQueue;

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int level);
extern s64 __OSGetSystemTime(void);
extern void PPCMtdec(u32 val);

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

void OSCancelAlarm(OSAlarm* alarm)
{
    OSAlarm* next;
    int enabled;

    enabled = OSDisableInterrupts();

    if (alarm->handler == 0) {
        OSRestoreInterrupts(enabled);
        return;
    }

    next = alarm->next;
    if (next == 0) {
        AlarmQueue.tail = alarm->prev;
    } else {
        next->prev = alarm->prev;
    }
    if (alarm->prev) {
        alarm->prev->next = next;
    } else {
        AlarmQueue.head = next;
        if (next) {
            SetTimer(next);
        }
    }
    alarm->handler = 0;
    OSRestoreInterrupts(enabled);
}
