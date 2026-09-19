typedef unsigned short u16;
typedef unsigned int u32;

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int level);

volatile u16 __DSPRegs[0x200] : 0xCC005000;

void AIInitDMA(u32 start_addr, u32 length)
{
    int old;

    old = OSDisableInterrupts();
    __DSPRegs[24] = (__DSPRegs[24] & 0xFFFFFC00) | (start_addr >> 16);
    __DSPRegs[25] = (__DSPRegs[25] & 0xFFFF001F) | (start_addr & 0xFFFF);
    __DSPRegs[27] = (__DSPRegs[27] & 0xFFFF8000) | ((length >> 5) & 0xFFFF);
    OSRestoreInterrupts(old);
}
