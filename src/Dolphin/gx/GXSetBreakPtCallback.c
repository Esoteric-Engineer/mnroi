typedef void (*GXBreakPtCallback)(void);

extern GXBreakPtCallback lbl_8066F484;

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int level);

GXBreakPtCallback GXSetBreakPtCallback(GXBreakPtCallback cb)
{
    GXBreakPtCallback oldcb = lbl_8066F484;
    int enabled = OSDisableInterrupts();

    lbl_8066F484 = cb;
    OSRestoreInterrupts(enabled);
    return oldcb;
}
