typedef unsigned long u32;
typedef void (*GXDrawSyncCallback)(unsigned short token);

extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32 level);

extern GXDrawSyncCallback TokenCB;

GXDrawSyncCallback GXSetDrawSyncCallback(GXDrawSyncCallback cb)
{
    GXDrawSyncCallback oldcb;
    u32 enabled;

    oldcb = TokenCB;
    enabled = OSDisableInterrupts();
    TokenCB = cb;
    OSRestoreInterrupts(enabled);
    return oldcb;
}
