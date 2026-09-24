typedef unsigned short u16;
typedef unsigned int u32;

volatile u16 __DSPRegs[0x200] : 0xCC005000;

u32 __ARGetInterruptStatus(void) { return __DSPRegs[5] & 0x20; }
