typedef struct DSPTaskInfo {
    volatile unsigned long state;
    volatile unsigned long priority;
    volatile unsigned long flags;
    unsigned long pad[11];
    struct DSPTaskInfo* next;
    struct DSPTaskInfo* prev;
} DSPTaskInfo;

extern DSPTaskInfo* __DSP_first_task;
extern DSPTaskInfo* lbl_8066FB00; /* __DSP_last_task */
extern DSPTaskInfo* lbl_8066FB08; /* __DSP_curr_task */

void __DSP_remove_task(DSPTaskInfo* task)
{
    task->flags = 0;
    task->state = 3;
    if (__DSP_first_task == task) {
        if (task->next) {
            __DSP_first_task = task->next;
            task->next->prev = 0;
        } else {
            __DSP_first_task = lbl_8066FB00 = lbl_8066FB08 = 0;
        }
    } else if (lbl_8066FB00 == task) {
        lbl_8066FB00 = task->prev;
        task->prev->next = 0;
        lbl_8066FB08 = __DSP_first_task;
    } else {
        lbl_8066FB08 = task->next;
        task->prev->next = task->next;
        task->next->prev = task->prev;
    }
}
