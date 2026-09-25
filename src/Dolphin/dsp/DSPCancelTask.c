typedef struct DSPTaskInfo {
    volatile unsigned long state;
    volatile unsigned long priority;
    volatile unsigned long flags;
} DSPTaskInfo;

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int);

DSPTaskInfo* DSPCancelTask(DSPTaskInfo* task)
{
    int old = OSDisableInterrupts();
    task->flags |= 2;
    OSRestoreInterrupts(old);
    return task;
}
