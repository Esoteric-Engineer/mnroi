typedef unsigned short u16;
typedef unsigned long u32;

typedef struct DSPTaskInfo {
    volatile u32 state;
    volatile u32 priority;
    volatile u32 flags;
    u16* iram_mmem_addr;
    u32 iram_length;
    u32 iram_addr;
    u16* dram_mmem_addr;
    u32 dram_length;
    u32 dram_addr;
    u16 dsp_init_vector;
    u16 dsp_resume_vector;
} DSPTaskInfo;

extern void DSPSendMailToDSP(u32 mail);
extern u32 DSPCheckMailToDSP(void);
extern u32 DSPCheckMailFromDSP(void);
extern u32 DSPReadMailFromDSP(void);
extern void __DSP_debug_printf(const char* fmt, ...);

void __DSP_boot_task(DSPTaskInfo* task)
{
    volatile u32 mail;

    while (DSPCheckMailFromDSP() == 0)
        ;
    mail = DSPReadMailFromDSP();

    DSPSendMailToDSP(0x80F3A001);
    while (DSPCheckMailToDSP())
        ;
    DSPSendMailToDSP((u32)task->iram_mmem_addr);
    while (DSPCheckMailToDSP())
        ;
    DSPSendMailToDSP(0x80F3C002);
    while (DSPCheckMailToDSP())
        ;
    DSPSendMailToDSP(task->iram_addr & 0xFFFF);
    while (DSPCheckMailToDSP())
        ;
    DSPSendMailToDSP(0x80F3A002);
    while (DSPCheckMailToDSP())
        ;
    DSPSendMailToDSP(task->iram_length);
    while (DSPCheckMailToDSP())
        ;
    DSPSendMailToDSP(0x80F3B002);
    while (DSPCheckMailToDSP())
        ;
    DSPSendMailToDSP(0);
    while (DSPCheckMailToDSP())
        ;
    DSPSendMailToDSP(0x80F3D001);
    while (DSPCheckMailToDSP())
        ;
    DSPSendMailToDSP(task->dsp_init_vector);
    while (DSPCheckMailToDSP())
        ;

    __DSP_debug_printf("DSP is booting task: 0x%08X\n", task);
    __DSP_debug_printf("__DSP_boot_task()  : IRAM MMEM ADDR: 0x%08X\n", (u32)task->iram_mmem_addr);
    __DSP_debug_printf("__DSP_boot_task()  : IRAM DSP ADDR : 0x%08X\n", task->iram_addr);
    __DSP_debug_printf("__DSP_boot_task()  : IRAM LENGTH   : 0x%08X\n", task->iram_length);
    __DSP_debug_printf("__DSP_boot_task()  : DRAM MMEM ADDR: 0x%08X\n", task->dram_length);
    __DSP_debug_printf("__DSP_boot_task()  : Start Vector  : 0x%08X\n", task->dsp_init_vector);
}

// dsp_task.c's __DSP_add_task() string; that function is dead-stripped, so nothing references this.
#pragma force_active on
char lbl_804F2B50[] = "__DSP_add_task() : Added task    : 0x%08X\n";
#pragma force_active reset
