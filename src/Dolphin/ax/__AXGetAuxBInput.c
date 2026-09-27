extern unsigned char __AXBufferAuxB[];
extern unsigned long lbl_8066FA14;
extern unsigned long lbl_8066FA30;

void __AXGetAuxBInput(unsigned long* out)
{
    if (lbl_8066FA14 != 0) {
        *out = (unsigned long)(__AXBufferAuxB + lbl_8066FA30 * 0x780);
    } else {
        *out = 0;
    }
}
