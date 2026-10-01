typedef void (*GXBreakPtCallback)(void);

extern GXBreakPtCallback BreakPointCB;

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int level);

GXBreakPtCallback GXSetBreakPtCallback(GXBreakPtCallback cb)
{
    GXBreakPtCallback oldcb = BreakPointCB;
    int enabled = OSDisableInterrupts();

    BreakPointCB = cb;
    OSRestoreInterrupts(enabled);
    return oldcb;
}
