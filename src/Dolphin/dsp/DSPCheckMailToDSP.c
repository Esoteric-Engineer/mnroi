typedef unsigned short u16;
typedef unsigned int u32;

volatile u16 __DSPRegs[0x200] : 0xCC005000;

u32 DSPCheckMailToDSP(void) { return (__DSPRegs[0] & (1 << 15)) >> 15; }
