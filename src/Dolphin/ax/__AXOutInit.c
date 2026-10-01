extern void DCFlushRange(void*, unsigned long);
extern void AIRegisterDMACallback(void*);
extern void AIInitDMA(void*, unsigned long);
extern void AIStartDMA(void);
extern void __AXOutAiCallback(void);
extern void __AXOutInitDSP(void);
extern void __AXNextFrame(void*, void*);

extern volatile unsigned long __AXOutFrame;
extern volatile unsigned long __AXAiDmaFrame;
extern unsigned long __AXOutDspReady;
extern void (*__AXUserFrameCallback)(void);
extern volatile unsigned long __AXDebugSteppingMode;
extern unsigned long __AXOutputBufferMode;

unsigned long __AXOutBuffer[480];
unsigned long __AXOutSBuffer[160];

void __AXOutInit(unsigned long outputMode)
{
    int i;

    __AXOutFrame = 0;
    __AXAiDmaFrame = 0;
    __AXOutputBufferMode = outputMode;
    __AXDebugSteppingMode = 0;
    for (i = 0; i < 480; i++) {
        __AXOutBuffer[i] = 0;
    }
    DCFlushRange(__AXOutBuffer, 0x780);
    for (i = 0; i < 160; i++) {
        __AXOutSBuffer[i] = 0;
    }
    DCFlushRange(__AXOutSBuffer, 0x280);
    __AXOutInitDSP();
    AIRegisterDMACallback(__AXOutAiCallback);
    if (__AXOutputBufferMode == 1) {
        __AXNextFrame(__AXOutSBuffer, &__AXOutBuffer[320]);
    } else {
        __AXNextFrame(__AXOutSBuffer, &__AXOutBuffer[160]);
    }
    __AXOutDspReady = 1;
    __AXUserFrameCallback = 0;
    if (__AXOutputBufferMode == 1) {
        AIInitDMA(&__AXOutBuffer[__AXAiDmaFrame * 160], 0x280);
        __AXAiDmaFrame = __AXAiDmaFrame + 1;
        __AXAiDmaFrame = __AXAiDmaFrame & 1;
    } else {
        AIInitDMA(&__AXOutBuffer[__AXOutFrame * 160], 0x280);
    }
    AIStartDMA();
}
