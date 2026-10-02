extern long long OSGetTime(void);
extern void AIInitDMA(void*, unsigned long);
extern void DSPSendMailToDSP(unsigned long);
extern unsigned long DSPCheckMailToDSP(void);
extern void __AXSyncPBs(unsigned long);
extern void __AXPrintStudio(void);
extern unsigned long __AXGetCommandListAddress(void);
extern void __AXServiceCallbackStack(void);
extern void __AXProcessAux(void);
extern void __AXNextFrame(void*, void*);
extern unsigned long __AXGetNumVoices(void);
extern void* __AXGetCurrentProfile(void);

typedef struct AXProfile {
    long long axFrameStart;
    long long auxProcessingStart;
    long long auxProcessingEnd;
    long long userCallbackStart;
    long long userCallbackEnd;
    long long axFrameEnd;
    unsigned long axNumVoices;
} AXProfile;

typedef struct AXOutBss {
    char buf[0x4A00];
    char task[0x50];
    AXProfile profile;
} AXOutBss;

extern AXOutBss __AXOutBuffer;

unsigned long __AXOutputBufferMode;
unsigned long __AXOutThreadQueue[2];
unsigned long __AXDebugSteppingMode;
unsigned long __AXDSPDoneFlag;
unsigned long __AXDSPInitFlag;
void (*__AXUserFrameCallback)(void);
long long __AXOsTime;
unsigned long __AXOutDspReady;
unsigned long __AXAiDmaFrame;
unsigned long __AXOutFrame;

void __AXOutNewFrame(unsigned long lessDspCycles)
{
    AXOutBss* b = &__AXOutBuffer;
    unsigned long cl;
    unsigned char* d;
    int i;

    b->profile.axFrameStart = OSGetTime();
    __AXSyncPBs(lessDspCycles);
    __AXPrintStudio();
    cl = __AXGetCommandListAddress();
    DSPSendMailToDSP(0xBABE0180);
    while (DSPCheckMailToDSP() != 0) {
    }
    DSPSendMailToDSP(cl);
    while (DSPCheckMailToDSP() != 0) {
    }
    __AXServiceCallbackStack();
    b->profile.auxProcessingStart = OSGetTime();
    __AXProcessAux();
    b->profile.auxProcessingEnd = OSGetTime();
    b->profile.userCallbackStart = OSGetTime();
    if (__AXUserFrameCallback != 0) {
        __AXUserFrameCallback();
    }
    b->profile.userCallbackEnd = OSGetTime();
    __AXNextFrame(b->buf + 0x780, b->buf + __AXOutFrame * 0x280);
    __AXOutFrame = __AXOutFrame + 1;
    if (__AXOutputBufferMode == 1) {
        __AXOutFrame = __AXOutFrame % 3;
    } else {
        __AXOutFrame = __AXOutFrame & 1;
        AIInitDMA(b->buf + __AXOutFrame * 0x280, 0x280);
    }
    b->profile.axFrameEnd = OSGetTime();
    b->profile.axNumVoices = __AXGetNumVoices();
    d = (unsigned char*)__AXGetCurrentProfile();
    if (d != 0) {
        unsigned char* p = (unsigned char*)&b->profile;
        for (i = 0x38; i != 0; i--) {
            *d++ = *p++;
        }
    }
}
