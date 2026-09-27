extern unsigned char __AXBufferAuxB[];
extern unsigned long lbl_8066FA30;

void __AXGetAuxAInputDpl2(unsigned long* out)
{
    *out = (unsigned long)(__AXBufferAuxB + lbl_8066FA30 * 0x780 + 0x500);
}
