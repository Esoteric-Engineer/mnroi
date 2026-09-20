typedef unsigned long u32;

extern void* __OSGetExceptionHandler(u32 exception);
extern void __OSSetExceptionHandler(u32 exception, void* handler);
extern void OSRegisterResetFunction(void* info);

extern void DecrementerExceptionHandler(void);
extern struct {
    void* head;
    void* tail;
} AlarmQueue;
extern char ResetFunctionInfo[0x10];

void OSInitAlarm(void)
{
    if (__OSGetExceptionHandler(8) != DecrementerExceptionHandler) {
        AlarmQueue.tail = 0;
        AlarmQueue.head = 0;
        __OSSetExceptionHandler(8, DecrementerExceptionHandler);
        OSRegisterResetFunction(ResetFunctionInfo);
    }
}
