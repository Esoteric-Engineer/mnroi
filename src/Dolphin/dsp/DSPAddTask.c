typedef struct DSPTaskInfo {
    volatile unsigned long state;
    volatile unsigned long priority;
    volatile unsigned long flags;
} DSPTaskInfo;

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int);
extern void fn_8040A05C(DSPTaskInfo* task);
extern void fn_80409ED0(DSPTaskInfo* task);
extern DSPTaskInfo* __DSP_first_task;

DSPTaskInfo* DSPAddTask(DSPTaskInfo* task)
{
    int old = OSDisableInterrupts();
    fn_8040A05C(task);
    task->state = 0;
    task->flags = 1;
    OSRestoreInterrupts(old);
    if (task == __DSP_first_task) {
        fn_80409ED0(task);
    }
    return task;
}
