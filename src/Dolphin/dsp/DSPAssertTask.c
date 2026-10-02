typedef unsigned short u16;
typedef int BOOL;

typedef struct DSPTaskInfo {
    volatile unsigned long state;
    volatile unsigned long priority;
    volatile unsigned long flags;
} DSPTaskInfo;

volatile u16 __DSPRegs[0x200] : 0xCC005000;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL enabled);

extern DSPTaskInfo* __DSP_curr_task;
extern BOOL __DSP_rude_task_pending;
extern DSPTaskInfo* __DSP_rude_task;

static inline void DSPAssertInt(void)
{
    BOOL old;
    u16 tmp;

    old = OSDisableInterrupts();
    tmp = __DSPRegs[5];
    tmp = (tmp & ~0xA8) | 2;
    __DSPRegs[5] = tmp;
    OSRestoreInterrupts(old);
}

DSPTaskInfo* DSPAssertTask(DSPTaskInfo* task)
{
    BOOL old = OSDisableInterrupts();

    if (__DSP_curr_task == task) {
        __DSP_rude_task = task;
        __DSP_rude_task_pending = 1;
        OSRestoreInterrupts(old);
        return task;
    }

    if (task->priority < __DSP_curr_task->priority) {
        __DSP_rude_task = task;
        __DSP_rude_task_pending = 1;
        if (__DSP_curr_task->state == 1) {
            DSPAssertInt();
        }
        OSRestoreInterrupts(old);
        return task;
    }

    OSRestoreInterrupts(old);
    return 0;
}
