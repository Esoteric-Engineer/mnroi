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

extern DSPTaskInfo* lbl_8066FB08; /* __DSP_curr_task */
extern BOOL lbl_8066FAF4;         /* __DSP_rude_task_pending */
extern DSPTaskInfo* lbl_8066FAF8; /* __DSP_rude_task */

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

    if (lbl_8066FB08 == task) {
        lbl_8066FAF8 = task;
        lbl_8066FAF4 = 1;
        OSRestoreInterrupts(old);
        return task;
    }

    if (task->priority < lbl_8066FB08->priority) {
        lbl_8066FAF8 = task;
        lbl_8066FAF4 = 1;
        if (lbl_8066FB08->state == 1) {
            DSPAssertInt();
        }
        OSRestoreInterrupts(old);
        return task;
    }

    OSRestoreInterrupts(old);
    return 0;
}
