extern long long OSGetTime(void);
extern void AIInitDMA(void*, unsigned long);
extern void DSPSendMailToDSP(unsigned long);
extern unsigned long DSPCheckMailToDSP(void);
extern void fn_80408D44(unsigned long);
extern void fn_80408134(void);
extern unsigned long __AXGetCommandListAddress(void);
extern void __AXServiceCallbackStack(void);
extern void fn_80406FE0(void);
extern void fn_8040726C(void*, void*);
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

extern AXOutBss lbl_80652640;
extern unsigned long lbl_8066FA60;
extern void (*lbl_8066FA78)(void);
extern unsigned long lbl_8066FA90;

void __AXOutNewFrame(unsigned long lessDspCycles)
{
    AXOutBss* b = &lbl_80652640;
    unsigned long cl;
    unsigned char* d;
    int i;

    b->profile.axFrameStart = OSGetTime();
    fn_80408D44(lessDspCycles);
    fn_80408134();
    cl = __AXGetCommandListAddress();
    DSPSendMailToDSP(0xBABE0180);
    while (DSPCheckMailToDSP() != 0) {
    }
    DSPSendMailToDSP(cl);
    while (DSPCheckMailToDSP() != 0) {
    }
    __AXServiceCallbackStack();
    b->profile.auxProcessingStart = OSGetTime();
    fn_80406FE0();
    b->profile.auxProcessingEnd = OSGetTime();
    b->profile.userCallbackStart = OSGetTime();
    if (lbl_8066FA78 != 0) {
        lbl_8066FA78();
    }
    b->profile.userCallbackEnd = OSGetTime();
    fn_8040726C(b->buf + 0x780, b->buf + lbl_8066FA60 * 0x280);
    lbl_8066FA60 = lbl_8066FA60 + 1;
    if (lbl_8066FA90 == 1) {
        lbl_8066FA60 = lbl_8066FA60 % 3;
    } else {
        lbl_8066FA60 = lbl_8066FA60 & 1;
        AIInitDMA(b->buf + lbl_8066FA60 * 0x280, 0x280);
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
