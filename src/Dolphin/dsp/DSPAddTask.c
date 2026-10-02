typedef struct DSPTaskInfo {
    volatile unsigned long state;
    volatile unsigned long priority;
    volatile unsigned long flags;
} DSPTaskInfo;

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int);
extern void __DSP_insert_task(DSPTaskInfo* task);
extern void __DSP_boot_task(DSPTaskInfo* task);
extern DSPTaskInfo* __DSP_first_task;

DSPTaskInfo* DSPAddTask(DSPTaskInfo* task)
{
    int old = OSDisableInterrupts();
    __DSP_insert_task(task);
    task->state = 0;
    task->flags = 1;
    OSRestoreInterrupts(old);
    if (task == __DSP_first_task) {
        __DSP_boot_task(task);
    }
    return task;
}
