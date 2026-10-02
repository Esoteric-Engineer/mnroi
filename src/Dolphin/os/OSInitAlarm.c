typedef unsigned long u32;
typedef int BOOL;

extern void* __OSGetExceptionHandler(u32 exception);
extern void __OSSetExceptionHandler(u32 exception, void* handler);
extern void OSRegisterResetFunction(void* info);
extern BOOL fn_8017BB24(BOOL final);

extern void DecrementerExceptionHandler(void);

struct {
    void* head;
    void* tail;
} AlarmQueue;

typedef struct OSResetFunctionInfo OSResetFunctionInfo;
struct OSResetFunctionInfo {
    BOOL (*func)(BOOL final);
    u32 priority;
    OSResetFunctionInfo* next;
    OSResetFunctionInfo* prev;
};

OSResetFunctionInfo ResetFunctionInfo = {
    fn_8017BB24,
    0xFFFFFFFF,
};

// OSCheckAlarmQueue's ASSERTREPORT strings; the function itself is dead-stripped.
#pragma force_active on
char lbl_804D0888[140] =
    "OSCheckAlarmQueue: Failed AlarmQueue.head == NULL && AlarmQueue.tail == NULL || AlarmQueue.head != NULL && AlarmQueue.tail != NULL in %d";
char lbl_804D0914[92] = "OSCheckAlarmQueue: Failed AlarmQueue.head == NULL || AlarmQueue.head->prev == NULL in %d";
char lbl_804D0970[92] = "OSCheckAlarmQueue: Failed AlarmQueue.tail == NULL || AlarmQueue.tail->next == NULL in %d";
char lbl_804D09CC[84] = "OSCheckAlarmQueue: Failed alarm->next == NULL || alarm->next->prev == alarm in %d";
char lbl_804D0A20[80] = "OSCheckAlarmQueue: Failed alarm->next != NULL || AlarmQueue.tail == alarm in %d";
#pragma force_active reset

void OSInitAlarm(void)
{
    if (__OSGetExceptionHandler(8) != DecrementerExceptionHandler) {
        AlarmQueue.tail = 0;
        AlarmQueue.head = 0;
        __OSSetExceptionHandler(8, DecrementerExceptionHandler);
        OSRegisterResetFunction(&ResetFunctionInfo);
    }
}
