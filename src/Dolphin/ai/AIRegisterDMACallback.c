typedef void (*AIDCallback)(void);

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int level);
extern AIDCallback lbl_8066F40C;

AIDCallback AIRegisterDMACallback(AIDCallback callback)
{
    AIDCallback old_callback;
    int old;

    old_callback = lbl_8066F40C;
    old = OSDisableInterrupts();
    lbl_8066F40C = callback;
    OSRestoreInterrupts(old);
    return old_callback;
}
