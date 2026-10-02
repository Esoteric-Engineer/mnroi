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

extern void* __DSP_tmp_task;
extern void* __DSP_last_task;
extern void* __DSP_first_task;
extern void* __DSP_curr_task;

char lbl_804F29C0[] = "<< Dolphin SDK - DSP\trelease build: Apr 17 2003 12:34:16 (0x2301) >>";
static char* __DSPVersion = lbl_804F29C0;

BOOL __DSP_init_flag;

void DSPInit(void)
{
    BOOL old;
    u16 tmp;

    __DSP_debug_printf("DSPInit(): Build Date: %s %s\n", "Apr 17 2003", "12:34:16");

    if (__DSP_init_flag == 1)
        return;

    OSRegisterVersion(__DSPVersion);

    old = OSDisableInterrupts();
    __OSSetInterruptHandler(7, __DSPHandler);
    __OSUnmaskInterrupts(0x1000000);

    tmp = __DSPRegs[5];
    tmp = (tmp & ~0xA8) | 0x800;
    __DSPRegs[5] = tmp;

    tmp = __DSPRegs[5];
    __DSPRegs[5] = tmp = tmp & ~0xAC;

    __DSP_first_task = __DSP_last_task = __DSP_curr_task = __DSP_tmp_task = 0;
    __DSP_init_flag = 1;

    OSRestoreInterrupts(old);
}
