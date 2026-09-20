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
extern s64 __OSGetSystemTime(void);
extern void InsertAlarm(OSAlarm* alarm, s64 fire, OSAlarmHandler handler);

void OSSetAlarm(OSAlarm* alarm, s64 tick, OSAlarmHandler handler)
{
    int enabled = OSDisableInterrupts();
    alarm->period = 0;
    InsertAlarm(alarm, __OSGetSystemTime() + tick, handler);
    OSRestoreInterrupts(enabled);
}
