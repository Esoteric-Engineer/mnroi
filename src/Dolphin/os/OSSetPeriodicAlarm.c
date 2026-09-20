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

typedef void (*OSAlarmHandler)(OSAlarm*, void*);

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int level);
extern s64 fn_80180FDC(s64 time);
extern void InsertAlarm(OSAlarm* alarm, s64 fire, OSAlarmHandler handler);

void OSSetPeriodicAlarm(OSAlarm* alarm, s64 start, s64 period, OSAlarmHandler handler)
{
    int enabled = OSDisableInterrupts();
    alarm->period = period;
    alarm->start = fn_80180FDC(start);
    InsertAlarm(alarm, 0, handler);
    OSRestoreInterrupts(enabled);
}
