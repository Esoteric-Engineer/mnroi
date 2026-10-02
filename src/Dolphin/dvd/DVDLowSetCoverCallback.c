typedef void (*DVDLowCallback)(unsigned long);

extern DVDLowCallback CoverCallback;

int OSDisableInterrupts(void);
void OSRestoreInterrupts(int level);

DVDLowCallback DVDLowSetCoverCallback(DVDLowCallback callback)
{
    int enabled;
    DVDLowCallback old;

    old = CoverCallback;
    enabled = OSDisableInterrupts();
    CoverCallback = callback;
    OSRestoreInterrupts(enabled);
    return old;
}
