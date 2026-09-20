typedef unsigned long u32;

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int level);
extern u32 fn_8017DC78(u32 mask, u32 current);

#pragma peephole off
u32 __OSMaskInterrupts(u32 global)
{
    int enabled;
    u32 prev;
    u32 local;
    u32 mask;

    enabled = OSDisableInterrupts();
    prev = *(u32*)0x800000C4;
    local = *(u32*)0x800000C8;
    mask = ~(prev | local) & global;
    global |= prev;
    *(u32*)0x800000C4 = global;
    while (mask) {
        mask = fn_8017DC78(mask, global | local);
    }
    OSRestoreInterrupts(enabled);
    return prev;
}

u32 __OSUnmaskInterrupts(u32 global)
{
    int enabled;
    u32 prev;
    u32 local;
    u32 mask;

    enabled = OSDisableInterrupts();
    prev = *(u32*)0x800000C4;
    local = *(u32*)0x800000C8;
    mask = (prev | local) & global;
    global = prev & ~global;
    *(u32*)0x800000C4 = global;
    while (mask) {
        mask = fn_8017DC78(mask, global | local);
    }
    OSRestoreInterrupts(enabled);
    return prev;
}
