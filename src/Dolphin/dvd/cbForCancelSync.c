typedef struct DVDCommandBlock DVDCommandBlock;

extern char __DVDThreadQueue[8];

void OSWakeupThread(void* queue);

void cbForCancelSync(long result, DVDCommandBlock* block) {
    OSWakeupThread(__DVDThreadQueue);
}
