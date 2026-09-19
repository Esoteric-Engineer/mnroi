typedef unsigned long u32;

extern void lbl_8017DBD4(int interrupt, void (*handler)(void));
extern u32 fn_8017DFD8(u32 mask);
extern u32 fn_8017FD74(void);
extern void fn_80191810(void);

extern u32 lbl_8066F470; // CPUFifo
extern u32 lbl_8066F474; // GPFifo
extern u32 lbl_8066F478; // __GXCurrentThread
extern u32 lbl_8066F480; // GXOverflowSuspendInProgress

void __GXFifoInit(void)
{
    lbl_8017DBD4(0x11, fn_80191810);
    fn_8017DFD8(0x4000);
    lbl_8066F478 = fn_8017FD74();
    lbl_8066F480 = 0;
    lbl_8066F470 = 0;
    lbl_8066F474 = 0;
}
