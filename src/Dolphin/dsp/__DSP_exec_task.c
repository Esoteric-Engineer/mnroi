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

void __DSP_exec_task(DSPTaskInfo* curr, DSPTaskInfo* next)
{
    if (curr != 0) {
        DSPSendMailToDSP((u32)curr->dram_mmem_addr);
        while (DSPCheckMailToDSP())
            ;
        DSPSendMailToDSP(curr->dram_length);
        while (DSPCheckMailToDSP())
            ;
        DSPSendMailToDSP(curr->dram_addr);
        while (DSPCheckMailToDSP())
            ;
    } else {
        DSPSendMailToDSP(0);
        while (DSPCheckMailToDSP())
            ;
        DSPSendMailToDSP(0);
        while (DSPCheckMailToDSP())
            ;
        DSPSendMailToDSP(0);
        while (DSPCheckMailToDSP())
            ;
    }

    DSPSendMailToDSP((u32)next->iram_mmem_addr);
    while (DSPCheckMailToDSP())
        ;
    DSPSendMailToDSP(next->iram_length);
    while (DSPCheckMailToDSP())
        ;
    DSPSendMailToDSP(next->iram_addr);
    while (DSPCheckMailToDSP())
        ;

    if (next->state == 0) {
        DSPSendMailToDSP(next->dsp_init_vector);
        while (DSPCheckMailToDSP())
            ;
        DSPSendMailToDSP(0);
        while (DSPCheckMailToDSP())
            ;
        DSPSendMailToDSP(0);
        while (DSPCheckMailToDSP())
            ;
        DSPSendMailToDSP(0);
        while (DSPCheckMailToDSP())
            ;
    } else {
        DSPSendMailToDSP(next->dsp_resume_vector);
        while (DSPCheckMailToDSP())
            ;
        DSPSendMailToDSP((u32)next->dram_mmem_addr);
        while (DSPCheckMailToDSP())
            ;
        DSPSendMailToDSP(next->dram_length);
        while (DSPCheckMailToDSP())
            ;
        DSPSendMailToDSP(next->dram_addr);
        while (DSPCheckMailToDSP())
            ;
    }
}
