extern void DCInvalidateRange(void*, unsigned long);
extern void DCFlushRangeNoSync(void*, unsigned long);

unsigned char __AXBufferAuxA[3][0x780] __attribute__((aligned(32)));
unsigned char __AXBufferAuxB[3][0x780] __attribute__((aligned(32)));
extern void (*__AXCallbackAuxA)(void*, void*);
extern void (*__AXCallbackAuxB)(void*, void*);
extern void* __AXContextAuxA;
extern void* __AXContextAuxB;
extern void* __AXAuxADspWrite;
extern void* __AXAuxADspRead;
extern void* __AXAuxBDspWrite;
extern void* __AXAuxBDspRead;
extern unsigned long __AXAuxDspWritePosition;
extern unsigned long __AXAuxDspReadPosition;
extern unsigned long __AXAuxDspWritePositionDpl2;
extern unsigned long __AXAuxDspReadPositionDpl2;
extern unsigned long __AXAuxCpuReadWritePosition;
extern unsigned long __AXClMode;

void __AXProcessAux(void)
{
    __AXAuxADspWrite = __AXBufferAuxA[__AXAuxDspWritePosition];
    __AXAuxADspRead = __AXBufferAuxA[__AXAuxDspReadPosition];
    __AXAuxBDspWrite = __AXBufferAuxB[__AXAuxDspWritePosition];
    __AXAuxBDspRead = __AXBufferAuxB[__AXAuxDspReadPosition];

    if (__AXCallbackAuxA != 0) {
        if (__AXClMode == 2) {
            void* buf[4];
            unsigned char* p = __AXBufferAuxA[__AXAuxCpuReadWritePosition];
            buf[0] = p;
            buf[1] = p + 0x280;
            buf[2] = p + 0x500;
            buf[3] = p + 0x1B80;
            DCInvalidateRange(buf[0], 0x780);
            DCInvalidateRange(buf[3], 0x280);
            __AXCallbackAuxA(buf, __AXContextAuxA);
            DCFlushRangeNoSync(buf[0], 0x780);
            DCFlushRangeNoSync(buf[3], 0x280);
        } else {
            void* buf[3];
            unsigned char* p = __AXBufferAuxA[__AXAuxCpuReadWritePosition];
            buf[0] = p;
            buf[1] = p + 0x280;
            buf[2] = p + 0x500;
            DCInvalidateRange(buf[0], 0x780);
            __AXCallbackAuxA(buf, __AXContextAuxA);
            DCFlushRangeNoSync(buf[0], 0x780);
        }
    }

    if (__AXCallbackAuxB != 0 && __AXClMode != 2) {
        void* buf[3];
        unsigned char* p = __AXBufferAuxB[__AXAuxCpuReadWritePosition];
        buf[0] = p;
        buf[1] = p + 0x280;
        buf[2] = p + 0x500;
        DCInvalidateRange(buf[0], 0x780);
        __AXCallbackAuxB(buf, __AXContextAuxB);
        DCFlushRangeNoSync(buf[0], 0x780);
    }

    __AXAuxDspWritePosition++;
    __AXAuxDspReadPosition++;
    __AXAuxDspWritePositionDpl2++;
    __AXAuxDspReadPositionDpl2++;
    __AXAuxDspWritePosition = __AXAuxDspWritePosition % 3;
    __AXAuxCpuReadWritePosition++;
    __AXAuxDspReadPosition = __AXAuxDspReadPosition % 3;
    __AXAuxDspWritePositionDpl2 = __AXAuxDspWritePositionDpl2 & 1;
    __AXAuxDspReadPositionDpl2 = __AXAuxDspReadPositionDpl2 & 1;
    __AXAuxCpuReadWritePosition = __AXAuxCpuReadWritePosition % 3;
}
