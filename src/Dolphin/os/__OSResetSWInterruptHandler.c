typedef unsigned long u32;
typedef long long s64;
typedef s64 OSTime;

extern volatile u32 __PIRegs[0x20] : 0xCC003000;

extern void (*lbl_8066F250)(void);
extern int lbl_8066F254;
extern int lbl_8066F258;
extern OSTime lbl_8066F268;

OSTime __OSGetSystemTime(void);
void __OSMaskInterrupts(u32 mask);

void __OSResetSWInterruptHandler(short exception, void* context)
{
    void (*callback)(void);
    u32 ticks;

    lbl_8066F268 = __OSGetSystemTime();
    ticks = ((*(u32*)0x800000F8) / 4 / 125000 * 100) / 8;
    while ((__OSGetSystemTime() - lbl_8066F268) < ticks && !(__PIRegs[0] & 0x00010000))
        ;
    if (!(__PIRegs[0] & 0x00010000)) {
        lbl_8066F258 = lbl_8066F254 = 1;
        __OSMaskInterrupts(0x200);
        if (lbl_8066F250) {
            callback = lbl_8066F250;
            lbl_8066F250 = 0;
            callback();
        }
    }
    __PIRegs[0] = 2;
}
