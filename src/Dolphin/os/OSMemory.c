typedef int BOOL;
typedef unsigned int u32;

volatile unsigned short __MEMRegs[64] : 0xCC004000;

extern void __OSMaskInterrupts(u32 mask);

BOOL OnReset(BOOL final)
{
    if (final) {
        __MEMRegs[8] = 0xFF;
        __OSMaskInterrupts(0xF0000000);
    }
    return 1;
}
