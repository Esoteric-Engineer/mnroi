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

void __DSP_insert_task(DSPTaskInfo* task)
{
    DSPTaskInfo* temp;

    if (__DSP_first_task == 0) {
        __DSP_first_task = __DSP_last_task = __DSP_curr_task = task;
        task->next = task->prev = 0;
    } else {
        temp = __DSP_first_task;
        while (temp) {
            if (task->priority < temp->priority) {
                task->prev = temp->prev;
                temp->prev = task;
                task->next = temp;
                if (task->prev == 0) {
                    __DSP_first_task = task;
                } else {
                    task->prev->next = task;
                }
                break;
            }
            temp = temp->next;
        }
        if (temp == 0) {
            __DSP_last_task->next = task;
            task->next = 0;
            task->prev = __DSP_last_task;
            __DSP_last_task = task;
        }
    }
}
