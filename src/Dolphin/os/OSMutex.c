typedef struct OSThread OSThread;
typedef struct OSThreadQueue {
    OSThread* head;
    OSThread* tail;
} OSThreadQueue;

typedef struct OSMutex {
    OSThreadQueue queue;
    OSThread* thread;
    long count;
} OSMutex;

extern void OSInitThreadQueue(OSThreadQueue* queue);

void OSInitMutex(OSMutex* mutex)
{
    OSInitThreadQueue(&mutex->queue);
    mutex->thread = 0;
    mutex->count = 0;
}
