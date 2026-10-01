typedef unsigned long u32;
typedef void (*GXDrawDoneCallback)(void);

extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32 level);

extern GXDrawDoneCallback DrawDoneCB;

GXDrawDoneCallback GXSetDrawDoneCallback(GXDrawDoneCallback cb)
{
    GXDrawDoneCallback oldcb;
    u32 enabled;

    oldcb = DrawDoneCB;
    enabled = OSDisableInterrupts();
    DrawDoneCB = cb;
    OSRestoreInterrupts(enabled);
    return oldcb;
}
