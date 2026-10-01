typedef void (*ARCallback)(void);

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int level);

extern ARCallback __AR_Callback;

ARCallback ARRegisterDMACallback(ARCallback callback)
{
    ARCallback old_callback;
    int old;

    old_callback = __AR_Callback;
    old = OSDisableInterrupts();
    __AR_Callback = callback;
    OSRestoreInterrupts(old);
    return old_callback;
}
