extern unsigned char __AXBufferAuxB[];
extern unsigned long lbl_8066FA34;

void __AXGetAuxAOutputDpl2Rs(unsigned long* out)
{
    *out = (unsigned long)(__AXBufferAuxB + lbl_8066FA34 * 0x780 + 0x500);
}
