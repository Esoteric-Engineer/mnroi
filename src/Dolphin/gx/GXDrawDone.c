typedef unsigned char u8;
typedef unsigned long u32;

extern u8 lbl_8066F498;
extern u8 lbl_8066F49C[8];

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int level);
extern void OSSleepThread(void* queue);
extern void GXFlush(void);

typedef union {
    u8 u8;
    u32 u32;
} GXFifoObj;

#define GXWGFifo (*(GXFifoObj*)0xCC008000)

void GXDrawDone(void)
{
    int enabled;
    u32 reg;

    enabled = OSDisableInterrupts();
    reg = 0x45000002;
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = reg;
    GXFlush();
    lbl_8066F498 = 0;
    OSRestoreInterrupts(enabled);

    enabled = OSDisableInterrupts();
    while (!lbl_8066F498) {
        OSSleepThread(lbl_8066F49C);
    }
    OSRestoreInterrupts(enabled);
}
