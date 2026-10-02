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

long __AXSpbABS;
long __AXSpbABR;
long __AXSpbABL;
long __AXSpbAAS;
long __AXSpbAAR;
long __AXSpbAAL;
long __AXSpbAS;
long __AXSpbAR;
long __AXSpbAL;

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
    __AXDepopFade(&__AXSpbAL, (long*)&__AXStudio.dpopLHi, &__AXStudio.dpopLDelta);
    __AXDepopFade(&__AXSpbAR, (long*)&__AXStudio.dpopRHi, &__AXStudio.dpopRDelta);
    __AXDepopFade(&__AXSpbAS, (long*)&__AXStudio.dpopSHi, &__AXStudio.dpopSDelta);
    __AXDepopFade(&__AXSpbAAL, (long*)&__AXStudio.dpopALHi, &__AXStudio.dpopALDelta);
    __AXDepopFade(&__AXSpbAAR, (long*)&__AXStudio.dpopARHi, &__AXStudio.dpopARDelta);
    __AXDepopFade(&__AXSpbAAS, (long*)&__AXStudio.dpopASHi, &__AXStudio.dpopASDelta);
    __AXDepopFade(&__AXSpbABL, (long*)&__AXStudio.dpopBLHi, &__AXStudio.dpopBLDelta);
    __AXDepopFade(&__AXSpbABR, (long*)&__AXStudio.dpopBRHi, &__AXStudio.dpopBRDelta);
    __AXDepopFade(&__AXSpbABS, (long*)&__AXStudio.dpopBSHi, &__AXStudio.dpopBSDelta);

    DCFlushRange(&__AXStudio, sizeof(AXSTUDIO));
}
