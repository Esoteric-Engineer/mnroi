typedef unsigned int u32;

typedef struct DVDQueue
{
    struct DVDQueue* next;
    struct DVDQueue* prev;
} DVDQueue;

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
