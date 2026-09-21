typedef void (*DVDLowCallback)(unsigned long);

extern DVDLowCallback ResetCoverCallback;

int OSDisableInterrupts(void);
void OSRestoreInterrupts(int level);

DVDLowCallback DVDLowSetResetCoverCallback(DVDLowCallback callback)
{
    int enabled;
    DVDLowCallback old;

    old = ResetCoverCallback;
    enabled = OSDisableInterrupts();
    ResetCoverCallback = callback;
    OSRestoreInterrupts(enabled);
    return old;
}
