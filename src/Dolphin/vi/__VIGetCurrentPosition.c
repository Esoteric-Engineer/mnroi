typedef unsigned long u32;
typedef unsigned short u16;
typedef short s16;

extern volatile u16 __VIRegs[0x100] : 0xCC002000;
extern void fn_80189994(u32 hcount, u32 vcount, s16* x, s16* y);

inline static void getCurrentPosition(u32* h, u32* v)
{
    u32 hcount;
    u32 vcount0;
    u32 vcount;

    vcount = __VIRegs[22] & 0x7FF;
    do {
        vcount0 = vcount;
        hcount = __VIRegs[23] & 0x7FF;
        vcount = __VIRegs[22] & 0x7FF;
    } while (vcount0 != vcount);
    *h = hcount;
    *v = vcount;
}

void __VIGetCurrentPosition(s16* x, s16* y)
{
    u32 hcount;
    u32 vcount;

    getCurrentPosition(&hcount, &vcount);
    fn_80189994(hcount, vcount, x, y);
}
