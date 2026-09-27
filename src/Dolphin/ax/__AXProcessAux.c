extern void DCInvalidateRange(void*, unsigned long);
extern void DCFlushRangeNoSync(void*, unsigned long);

unsigned char __AXBufferAuxA[3][0x780];
unsigned char __AXBufferAuxB[3][0x780];
extern void (*lbl_8066FA10)(void*, void*);
extern void (*lbl_8066FA14)(void*, void*);
extern void* lbl_8066FA18;
extern void* lbl_8066FA1C;
extern void* lbl_8066FA20;
extern void* lbl_8066FA24;
extern void* lbl_8066FA28;
extern void* lbl_8066FA2C;
extern unsigned long lbl_8066FA30;
extern unsigned long lbl_8066FA34;
extern unsigned long lbl_8066FA38;
extern unsigned long lbl_8066FA3C;
extern unsigned long lbl_8066FA40;
extern unsigned long lbl_8066FA58;

void __AXProcessAux(void)
{
    lbl_8066FA20 = __AXBufferAuxA[lbl_8066FA30];
    lbl_8066FA24 = __AXBufferAuxA[lbl_8066FA34];
    lbl_8066FA28 = __AXBufferAuxB[lbl_8066FA30];
    lbl_8066FA2C = __AXBufferAuxB[lbl_8066FA34];

    if (lbl_8066FA10 != 0) {
        if (lbl_8066FA58 == 2) {
            void* buf[4];
            unsigned char* p = __AXBufferAuxA[lbl_8066FA40];
            buf[0] = p;
            buf[1] = p + 0x280;
            buf[2] = p + 0x500;
            buf[3] = p + 0x1B80;
            DCInvalidateRange(buf[0], 0x780);
            DCInvalidateRange(buf[3], 0x280);
            lbl_8066FA10(buf, lbl_8066FA18);
            DCFlushRangeNoSync(buf[0], 0x780);
            DCFlushRangeNoSync(buf[3], 0x280);
        } else {
            void* buf[3];
            unsigned char* p = __AXBufferAuxA[lbl_8066FA40];
            buf[0] = p;
            buf[1] = p + 0x280;
            buf[2] = p + 0x500;
            DCInvalidateRange(buf[0], 0x780);
            lbl_8066FA10(buf, lbl_8066FA18);
            DCFlushRangeNoSync(buf[0], 0x780);
        }
    }

    if (lbl_8066FA14 != 0 && lbl_8066FA58 != 2) {
        void* buf[3];
        unsigned char* p = __AXBufferAuxB[lbl_8066FA40];
        buf[0] = p;
        buf[1] = p + 0x280;
        buf[2] = p + 0x500;
        DCInvalidateRange(buf[0], 0x780);
        lbl_8066FA14(buf, lbl_8066FA1C);
        DCFlushRangeNoSync(buf[0], 0x780);
    }

    lbl_8066FA30++;
    lbl_8066FA34++;
    lbl_8066FA38++;
    lbl_8066FA3C++;
    lbl_8066FA30 = lbl_8066FA30 % 3;
    lbl_8066FA40++;
    lbl_8066FA34 = lbl_8066FA34 % 3;
    lbl_8066FA38 = lbl_8066FA38 & 1;
    lbl_8066FA3C = lbl_8066FA3C & 1;
    lbl_8066FA40 = lbl_8066FA40 % 3;
}
