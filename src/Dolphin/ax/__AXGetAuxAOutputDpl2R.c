extern unsigned char __AXBufferAuxA[];
extern unsigned long lbl_8066FA34;

void __AXGetAuxAOutputDpl2R(unsigned long* out)
{
    *out = (unsigned long)(__AXBufferAuxA + lbl_8066FA34 * 0x780 + 0x280);
}
