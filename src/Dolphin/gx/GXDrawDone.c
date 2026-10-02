typedef unsigned char u8;
typedef unsigned long u32;

typedef void (*GXDrawSyncCallback)(unsigned short token);
typedef void (*GXDrawDoneCallback)(void);

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int level);
extern void OSSleepThread(void* queue);
extern void GXFlush(void);

typedef union {
    u8 u8;
    u32 u32;
} GXFifoObj;

#define GXWGFifo (*(GXFifoObj*)0xCC008000)

u8 FinishQueue[8];
u8 DrawDone;
GXDrawDoneCallback DrawDoneCB;
GXDrawSyncCallback TokenCB;

void GXDrawDone(void)
{
    int enabled;
    u32 reg;

    enabled = OSDisableInterrupts();
    reg = 0x45000002;
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = reg;
    GXFlush();
    DrawDone = 0;
    OSRestoreInterrupts(enabled);

    enabled = OSDisableInterrupts();
    while (!DrawDone) {
        OSSleepThread(FinishQueue);
    }
    OSRestoreInterrupts(enabled);
}
