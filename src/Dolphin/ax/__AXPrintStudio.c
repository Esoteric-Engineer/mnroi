extern void DCFlushRange(void*, unsigned long);

typedef struct AXSTUDIO {
    unsigned short dpopLHi;
    unsigned short dpopLLo;
    short dpopLDelta;
    unsigned short dpopRHi;
    unsigned short dpopRLo;
    short dpopRDelta;
    unsigned short dpopSHi;
    unsigned short dpopSLo;
    short dpopSDelta;
    unsigned short dpopALHi;
    unsigned short dpopALLo;
    short dpopALDelta;
    unsigned short dpopARHi;
    unsigned short dpopARLo;
    short dpopARDelta;
    unsigned short dpopASHi;
    unsigned short dpopASLo;
    short dpopASDelta;
    unsigned short dpopBLHi;
    unsigned short dpopBLLo;
    short dpopBLDelta;
    unsigned short dpopBRHi;
    unsigned short dpopBRLo;
    short dpopBRDelta;
    unsigned short dpopBSHi;
    unsigned short dpopBSLo;
    short dpopBSDelta;
} AXSTUDIO;

AXSTUDIO __AXStudio __attribute__((aligned(32)));

extern long lbl_8066FA98;
extern long lbl_8066FA9C;
extern long lbl_8066FAA0;
extern long lbl_8066FAA4;
extern long lbl_8066FAA8;
extern long lbl_8066FAAC;
extern long lbl_8066FAB0;
extern long lbl_8066FAB4;
extern long lbl_8066FAB8;

static inline void __AXDepopFade(long* hostSum, long* dspVolume, short* dspDelta)
{
    int frames;
    long delta;

    if ((frames = *hostSum / 160) != 0) {
        delta = frames;
        if (delta > 20) {
            delta = 20;
        }
        if (delta < -20) {
            delta = -20;
        }
        *dspVolume = *hostSum;
        *hostSum -= delta * 160;
        *dspDelta = -delta;
    } else {
        *hostSum = 0;
        *dspVolume = 0;
        *dspDelta = 0;
    }
}

void __AXPrintStudio(void)
{
    __AXDepopFade(&lbl_8066FA98, (long*)&__AXStudio.dpopLHi, &__AXStudio.dpopLDelta);
    __AXDepopFade(&lbl_8066FA9C, (long*)&__AXStudio.dpopRHi, &__AXStudio.dpopRDelta);
    __AXDepopFade(&lbl_8066FAA0, (long*)&__AXStudio.dpopSHi, &__AXStudio.dpopSDelta);
    __AXDepopFade(&lbl_8066FAA4, (long*)&__AXStudio.dpopALHi, &__AXStudio.dpopALDelta);
    __AXDepopFade(&lbl_8066FAA8, (long*)&__AXStudio.dpopARHi, &__AXStudio.dpopARDelta);
    __AXDepopFade(&lbl_8066FAAC, (long*)&__AXStudio.dpopASHi, &__AXStudio.dpopASDelta);
    __AXDepopFade(&lbl_8066FAB0, (long*)&__AXStudio.dpopBLHi, &__AXStudio.dpopBLDelta);
    __AXDepopFade(&lbl_8066FAB4, (long*)&__AXStudio.dpopBRHi, &__AXStudio.dpopBRDelta);
    __AXDepopFade(&lbl_8066FAB8, (long*)&__AXStudio.dpopBSHi, &__AXStudio.dpopBSDelta);

    DCFlushRange(&__AXStudio, sizeof(AXSTUDIO));
}
