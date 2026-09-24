typedef void (*ARCallback)(void);

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int level);

extern ARCallback lbl_8066F9B8;

ARCallback ARRegisterDMACallback(ARCallback callback)
{
    ARCallback old_callback;
    int old;

    old_callback = lbl_8066F9B8;
    old = OSDisableInterrupts();
    lbl_8066F9B8 = callback;
    OSRestoreInterrupts(old);
    return old_callback;
}
