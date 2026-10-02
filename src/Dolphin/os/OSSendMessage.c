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

int OSSendMessage(OSMessageQueue* mq, OSMessage msg, int flags)
{
    int enabled;
    long lastIndex;

    enabled = OSDisableInterrupts();
    while (mq->msgCount <= mq->usedCount) {
        if (!(flags & 1)) {
            OSRestoreInterrupts(enabled);
            return 0;
        }
        OSSleepThread(&mq->queueSend);
    }
    lastIndex = (mq->firstIndex + mq->usedCount) % mq->msgCount;
    mq->msgArray[lastIndex] = msg;
    mq->usedCount++;
    OSWakeupThread(&mq->queueReceive);
    OSRestoreInterrupts(enabled);
    return 1;
}
