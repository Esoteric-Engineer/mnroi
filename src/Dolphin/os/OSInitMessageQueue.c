typedef struct OSThread OSThread;

typedef struct OSThreadQueue {
    OSThread* head;
    OSThread* tail;
} OSThreadQueue;

typedef void* OSMessage;

typedef struct OSMessageQueue {
    OSThreadQueue queueSend;
    OSThreadQueue queueReceive;
    OSMessage* msgArray;
    int msgCount;
    int firstIndex;
    int usedCount;
} OSMessageQueue;

extern void OSInitThreadQueue(OSThreadQueue* queue);

void OSInitMessageQueue(OSMessageQueue* mq, OSMessage* msgArray, int msgCount)
{
    OSInitThreadQueue(&mq->queueSend);
    OSInitThreadQueue(&mq->queueReceive);
    mq->msgArray = msgArray;
    mq->msgCount = msgCount;
    mq->firstIndex = 0;
    mq->usedCount = 0;
}
