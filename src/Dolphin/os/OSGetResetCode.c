typedef unsigned long u32;

extern int __OSRebootParams[8];
volatile u32 __PIRegs[0x100] : 0xCC003000;

#pragma peephole off
u32 OSGetResetCode(void)
{
    if (__OSRebootParams[0] != 0) {
        return __OSRebootParams[1] | 0x80000000;
    }
    return (__PIRegs[9] & ~7) >> 3;
}
