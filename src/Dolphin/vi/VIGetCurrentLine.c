typedef unsigned long u32;
typedef unsigned short u16;
typedef int BOOL;

typedef struct VITiming {
    u16 pad[12];
    u16 nhlines;
    u16 hlw;
} VITiming;

extern volatile u16 __VIRegs[0x100] : 0xCC002000;
extern VITiming* lbl_8066F3C0;
extern BOOL OSDisableInterrupts(void);
extern void OSRestoreInterrupts(BOOL enabled);

inline static u32 getCurrentHalfLine(void)
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
    return ((vcount - 1) * 2) + ((hcount - 1) / lbl_8066F3C0->hlw);
}

u32 VIGetCurrentLine(void)
{
    u32 halfLine;
    VITiming* tm;
    BOOL enabled;

    tm = lbl_8066F3C0;
    enabled = OSDisableInterrupts();
    halfLine = getCurrentHalfLine();
    OSRestoreInterrupts(enabled);
    if (halfLine >= tm->nhlines) {
        halfLine -= tm->nhlines;
    }
    return halfLine >> 1;
}
