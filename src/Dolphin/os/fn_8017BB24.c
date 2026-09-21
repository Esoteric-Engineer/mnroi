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

extern int fn_80186590(OSAlarm* alarm);
extern void OSCancelAlarm(OSAlarm* alarm);

#pragma peephole off
int fn_8017BB24(int final)
{
    OSAlarm* alarm;
    OSAlarm* next;

    if (final) {
        alarm = AlarmQueue.head;
        next = alarm ? alarm->next : 0;
        while (alarm) {
            if (!fn_80186590(alarm)) {
                OSCancelAlarm(alarm);
            }
            alarm = next;
            next = alarm ? alarm->next : 0;
        }
    }
    return 1;
}
