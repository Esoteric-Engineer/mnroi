extern unsigned char __AXBufferAuxA[];
extern unsigned long lbl_8066FA10;
extern unsigned long lbl_8066FA30;

void __AXGetAuxAInput(unsigned long* out)
{
    if (lbl_8066FA10 != 0) {
        *out = (unsigned long)(__AXBufferAuxA + lbl_8066FA30 * 0x780);
    } else {
        *out = 0;
    }
}
