typedef unsigned int u32;

typedef struct DVDQueue
{
    struct DVDQueue* next;
    struct DVDQueue* prev;
} DVDQueue;

int OSDisableInterrupts(void);
void OSRestoreInterrupts(int level);

DVDQueue WaitingQueue[4];

void __DVDClearWaitingQueue(void)
{
    u32 i;
    DVDQueue* q;

    for (i = 0; i < 4; i++)
    {
        q = &WaitingQueue[i];
        q->next = q;
        q->prev = q;
    }
}

int __DVDPushWaitingQueue(long prio, DVDQueue* block)
{
    int enabled = OSDisableInterrupts();
    DVDQueue* q = &WaitingQueue[prio];

    q->prev->next = block;
    block->prev = q->prev;
    block->next = q;
    q->prev = block;
    OSRestoreInterrupts(enabled);
    return 1;
}

DVDQueue* __DVDPopWaitingQueue(void)
{
    u32 i;
    int enabled;
    DVDQueue* q;

    enabled = OSDisableInterrupts();
    for (i = 0; i < 4; i++)
    {
        q = &WaitingQueue[i];
        if (q->next != q)
        {
            DVDQueue* tmp;
            OSRestoreInterrupts(enabled);
            enabled = OSDisableInterrupts();
            q = &WaitingQueue[i];
            tmp = q->next;
            q->next = tmp->next;
            tmp->next->prev = q;
            OSRestoreInterrupts(enabled);
            tmp->next = 0;
            tmp->prev = 0;
            return tmp;
        }
    }
    OSRestoreInterrupts(enabled);
    return 0;
}

int __DVDCheckWaitingQueue(void)
{
    u32 i;
    int enabled;
    DVDQueue* q;

    enabled = OSDisableInterrupts();
    for (i = 0; i < 4; i++)
    {
        q = &WaitingQueue[i];
        if (q->next != q)
        {
            OSRestoreInterrupts(enabled);
            return 1;
        }
    }
    OSRestoreInterrupts(enabled);
    return 0;
}

int __DVDDequeueWaitingQueue(DVDQueue* block)
{
    int enabled = OSDisableInterrupts();
    DVDQueue* prev = block->prev;
    DVDQueue* next = block->next;

    if (prev == 0 || next == 0)
    {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    prev->next = next;
    next->prev = prev;
    OSRestoreInterrupts(enabled);
    return 1;
}
