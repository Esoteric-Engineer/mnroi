extern void SelectThread(int yield);
extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int level);
extern volatile long RunQueueHint;

void __OSReschedule(void)
{
    if (RunQueueHint != 0) {
        SelectThread(0);
    }
}

void OSYieldThread(void)
{
    int enabled = OSDisableInterrupts();

    SelectThread(1);
    OSRestoreInterrupts(enabled);
}
