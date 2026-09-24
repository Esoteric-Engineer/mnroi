typedef int BOOL;
typedef struct DVDCommandBlock {
    char pad0[0x8];
    unsigned long command;
    int state;
} DVDCommandBlock;

extern char __DVDThreadQueue[8];

BOOL OSDisableInterrupts(void);
void OSRestoreInterrupts(BOOL level);
void OSSleepThread(void* queue); 
int DVDCancelAsync(volatile DVDCommandBlock* block, void (*callback)(long, DVDCommandBlock*));
void cbForCancelSync(long result, DVDCommandBlock* block);

long DVDCancel(volatile DVDCommandBlock* block) {
    int result;
    long state;
    unsigned long command;
    BOOL enabled;

    result = DVDCancelAsync(block, cbForCancelSync);
    if (result == 0) {
        return -1;
    }
    enabled = OSDisableInterrupts();
    while (1) {
        state = block->state;
        if (state == 0 || state == -1 || state == 10) {
            break;
        }
        if (state == 3) {
            command = block->command;
            if (command == 4 || command == 5 || command == 13 || command == 15) {
                break;
            }
        }
        OSSleepThread(__DVDThreadQueue);
    }
    OSRestoreInterrupts(enabled);
    return 0;
}
