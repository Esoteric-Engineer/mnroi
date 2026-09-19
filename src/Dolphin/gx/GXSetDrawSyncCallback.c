typedef unsigned long u32;
typedef void (*GXDrawSyncCallback)(unsigned short token);

extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32 level);

extern GXDrawSyncCallback lbl_8066F490;

GXDrawSyncCallback GXSetDrawSyncCallback(GXDrawSyncCallback cb)
{
    GXDrawSyncCallback oldcb;
    u32 enabled;

    oldcb = lbl_8066F490;
    enabled = OSDisableInterrupts();
    lbl_8066F490 = cb;
    OSRestoreInterrupts(enabled);
    return oldcb;
}
