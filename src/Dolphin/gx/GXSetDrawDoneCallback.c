typedef unsigned long u32;
typedef void (*GXDrawDoneCallback)(void);

extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32 level);

extern GXDrawDoneCallback lbl_8066F494;

GXDrawDoneCallback GXSetDrawDoneCallback(GXDrawDoneCallback cb)
{
    GXDrawDoneCallback oldcb;
    u32 enabled;

    oldcb = lbl_8066F494;
    enabled = OSDisableInterrupts();
    lbl_8066F494 = cb;
    OSRestoreInterrupts(enabled);
    return oldcb;
}
