typedef unsigned short u16;
typedef unsigned int u32;

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int level);

volatile u16 __DSPRegs[0x200] : 0xCC005000;

u32 ARGetDMAStatus(void)
{
    int old;
    u32 val;

    old = OSDisableInterrupts();
    val = __DSPRegs[5] & 0x200;
    OSRestoreInterrupts(old);
    return val;
}
