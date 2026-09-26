extern void OSInitThreadQueue(void*);
extern long DSPCheckInit(void);
extern void DSPInit(void);
extern void* DSPAddTask(void*);
extern void __AXDSPInitCallback(void);
extern void __AXDSPResumeCallback(void);
extern void __AXDSPDoneCallback(void);

typedef struct AXDSPTask {
    volatile unsigned long state;
    volatile unsigned long priority;
    volatile unsigned long flags;
    unsigned short* iram_mmem_addr;
    unsigned long iram_length;
    unsigned long iram_addr;
    unsigned short* dram_mmem_addr;
    unsigned long dram_length;
    unsigned long dram_addr;
    unsigned short dsp_init_vector;
    unsigned short dsp_resume_vector;
    void (*init_cb)(void*);
    void (*res_cb)(void*);
    void (*done_cb)(void*);
    void (*req_cb)(void*);
} AXDSPTask;

typedef struct AXOutBss {
    char buf[0x4A00];
    AXDSPTask task;
} AXOutBss;

extern AXOutBss lbl_80652640;
extern char lbl_804F0B00[];
extern unsigned short lbl_8066CEE0;
extern unsigned long lbl_8066FA80;
extern volatile long lbl_8066FA7C;
extern unsigned long lbl_8066FA88[2];

void __AXOutInitDSP(void)
{
    AXOutBss* b = &lbl_80652640;
    b->task.iram_mmem_addr = (unsigned short*)lbl_804F0B00;
    b->task.iram_length = lbl_8066CEE0;
    b->task.iram_addr = 0;
    b->task.dram_mmem_addr = (unsigned short*)(b->buf + 0xA00);
    b->task.dram_length = 0x2000;
    b->task.dram_addr = 0;
    b->task.dsp_init_vector = 0x10;
    b->task.dsp_resume_vector = 0x30;
    b->task.init_cb = (void (*)(void*))__AXDSPInitCallback;
    b->task.res_cb = (void (*)(void*))__AXDSPResumeCallback;
    b->task.done_cb = (void (*)(void*))__AXDSPDoneCallback;
    b->task.req_cb = 0;
    b->task.priority = 0;
    lbl_8066FA7C = 0;
    lbl_8066FA80 = 0;
    OSInitThreadQueue(lbl_8066FA88);
    if (DSPCheckInit() == 0) {
        DSPInit();
    }
    DSPAddTask(&b->task);
    while (lbl_8066FA7C == 0) {
    }
}
