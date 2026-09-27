typedef unsigned short u16;
typedef int BOOL;

volatile u16 __DSPRegs[0x200] : 0xCC005000;

extern void __DSP_debug_printf(const char* fmt, ...);
extern void OSRegisterVersion(const char* version);
extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL enabled);
extern void __OSSetInterruptHandler(short interrupt, void* handler);
extern unsigned long __OSUnmaskInterrupts(unsigned long mask);
extern void __DSPHandler(void);

extern BOOL lbl_8066FAE0;      /* __DSP_init_flag */
extern void* lbl_8066FAFC;     /* __DSP_tmp_task */
extern void* lbl_8066FB00;     /* __DSP_last_task */
extern void* __DSP_first_task;
extern void* lbl_8066FB08;     /* __DSP_curr_task */
extern const char* lbl_8066CEE8; /* __DSPVersion */

char lbl_804F29C0[] = "<< Dolphin SDK - DSP\trelease build: Apr 17 2003 12:34:16 (0x2301) >>";

void DSPInit(void)
{
    BOOL old;
    u16 tmp;

    __DSP_debug_printf("DSPInit(): Build Date: %s %s\n", "Apr 17 2003", "12:34:16");

    if (lbl_8066FAE0 == 1)
        return;

    OSRegisterVersion(lbl_8066CEE8);

    old = OSDisableInterrupts();
    __OSSetInterruptHandler(7, __DSPHandler);
    __OSUnmaskInterrupts(0x1000000);

    tmp = __DSPRegs[5];
    tmp = (tmp & ~0xA8) | 0x800;
    __DSPRegs[5] = tmp;

    tmp = __DSPRegs[5];
    __DSPRegs[5] = tmp = tmp & ~0xAC;

    __DSP_first_task = lbl_8066FB00 = lbl_8066FB08 = lbl_8066FAFC = 0;
    lbl_8066FAE0 = 1;

    OSRestoreInterrupts(old);
}
