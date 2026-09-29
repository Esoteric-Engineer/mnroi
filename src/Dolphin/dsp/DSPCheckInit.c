typedef int BOOL;

extern BOOL __DSP_init_flag;

BOOL DSPCheckInit(void) { return __DSP_init_flag; }
