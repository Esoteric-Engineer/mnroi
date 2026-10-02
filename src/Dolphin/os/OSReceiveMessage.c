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

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int level);
extern void OSSleepThread(OSThreadQueue* queue);
extern void OSWakeupThread(OSThreadQueue* queue);

int OSReceiveMessage(OSMessageQueue* mq, OSMessage* msg, int flags)
{
    int enabled = OSDisableInterrupts();

    while (mq->usedCount == 0) {
        if (!(flags & 1)) {
            OSRestoreInterrupts(enabled);
            return 0;
        }
        OSSleepThread(&mq->queueReceive);
    }
    if (msg != 0) {
        *msg = mq->msgArray[mq->firstIndex];
    }

    mq->firstIndex = (mq->firstIndex + 1) % mq->msgCount;
    mq->usedCount--;
    OSWakeupThread(&mq->queueSend);
    OSRestoreInterrupts(enabled);
    return 1;
}
