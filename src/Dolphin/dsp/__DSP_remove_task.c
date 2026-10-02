typedef struct DSPTaskInfo {
    volatile unsigned long state;
    volatile unsigned long priority;
    volatile unsigned long flags;
    unsigned long pad[11];
    struct DSPTaskInfo* next;
    struct DSPTaskInfo* prev;
} DSPTaskInfo;

extern DSPTaskInfo* __DSP_first_task;
extern DSPTaskInfo* __DSP_last_task;
extern DSPTaskInfo* __DSP_curr_task;

void __DSP_remove_task(DSPTaskInfo* task)
{
    task->flags = 0;
    task->state = 3;
    if (__DSP_first_task == task) {
        if (task->next) {
            __DSP_first_task = task->next;
            task->next->prev = 0;
        } else {
            __DSP_first_task = __DSP_last_task = __DSP_curr_task = 0;
        }
    } else if (__DSP_last_task == task) {
        __DSP_last_task = task->prev;
        task->prev->next = 0;
        __DSP_curr_task = __DSP_first_task;
    } else {
        __DSP_curr_task = task->next;
        task->prev->next = task->next;
        task->next->prev = task->prev;
    }
}
