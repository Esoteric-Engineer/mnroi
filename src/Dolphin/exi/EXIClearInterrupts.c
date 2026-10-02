typedef unsigned long u32;

volatile u32 __EXIRegs[0x40] : 0xCC006800;

u32 EXIClearInterrupts(long chan, int exi, int tc, int ext)
{
    u32 cpr;
    u32 prev;

    cpr = prev = __EXIRegs[chan * 5];
    prev &= 0x7F5;
    if (exi != 0) {
        prev |= 2;
    }
    if (tc != 0) {
        prev |= 8;
    }
    if (ext != 0) {
        prev |= 0x800;
    }
    __EXIRegs[chan * 5] = prev;
    return cpr;
}
