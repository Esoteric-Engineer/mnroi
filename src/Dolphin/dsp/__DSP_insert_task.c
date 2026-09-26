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

void __DSP_insert_task(DSPTaskInfo* task)
{
    DSPTaskInfo* temp;

    if (__DSP_first_task == 0) {
        __DSP_first_task = lbl_8066FB00 = lbl_8066FB08 = task;
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
            lbl_8066FB00->next = task;
            task->next = 0;
            task->prev = lbl_8066FB00;
            lbl_8066FB00 = task;
        }
    }
}
