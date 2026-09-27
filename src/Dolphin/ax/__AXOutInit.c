extern void DCFlushRange(void*, unsigned long);
extern void AIRegisterDMACallback(void*);
extern void AIInitDMA(void*, unsigned long);
extern void AIStartDMA(void);
extern void __AXOutAiCallback(void);
extern void __AXOutInitDSP(void);
extern void fn_8040726C(void*, void*);

extern volatile unsigned long lbl_8066FA60;
extern volatile unsigned long lbl_8066FA64;
extern unsigned long lbl_8066FA68;
extern void (*lbl_8066FA78)(void);
extern volatile unsigned long lbl_8066FA84;
extern unsigned long lbl_8066FA90;

unsigned long __AXOutBuffer[480];
unsigned long __AXOutSBuffer[160];

void __AXOutInit(unsigned long outputMode)
{
    int i;

    lbl_8066FA60 = 0;
    lbl_8066FA64 = 0;
    lbl_8066FA90 = outputMode;
    lbl_8066FA84 = 0;
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
    if (lbl_8066FA90 == 1) {
        fn_8040726C(__AXOutSBuffer, &__AXOutBuffer[320]);
    } else {
        fn_8040726C(__AXOutSBuffer, &__AXOutBuffer[160]);
    }
    lbl_8066FA68 = 1;
    lbl_8066FA78 = 0;
    if (lbl_8066FA90 == 1) {
        AIInitDMA(&__AXOutBuffer[lbl_8066FA64 * 160], 0x280);
        lbl_8066FA64 = lbl_8066FA64 + 1;
        lbl_8066FA64 = lbl_8066FA64 & 1;
    } else {
        AIInitDMA(&__AXOutBuffer[lbl_8066FA60 * 160], 0x280);
    }
    AIStartDMA();
}
