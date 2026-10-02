extern long long OSGetTime(void);
extern void AIInitDMA(void*, unsigned long);
extern void __AXOutNewFrame(unsigned long);
extern void DSPAssertTask(void*);

extern char __AXOutBuffer[];
extern unsigned char __AXDSPTask[0x80];
extern unsigned long __AXAiDmaFrame;
extern unsigned long __AXOutDspReady;
extern volatile long long __AXOsTime;
extern unsigned long __AXOutputBufferMode;

void __AXOutAiCallback(void)
{
    if (__AXOutDspReady == 0) {
        __AXOsTime = OSGetTime();
    }
    if (__AXOutDspReady == 1) {
        __AXOutDspReady = 0;
        __AXOutNewFrame(0);
    } else {
        __AXOutDspReady = 2;
        DSPAssertTask(__AXDSPTask);
    }
    if (__AXOutputBufferMode == 1) {
        AIInitDMA(__AXOutBuffer + __AXAiDmaFrame * 0x280, 0x280);
        __AXAiDmaFrame = __AXAiDmaFrame + 1;
        __AXAiDmaFrame = __AXAiDmaFrame % 3;
    }
}
