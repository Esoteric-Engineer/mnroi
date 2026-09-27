extern unsigned char __AXBufferAuxB[];
extern unsigned long lbl_8066FA38;

void __AXGetAuxBForDPL2(unsigned long* out)
{
    *out = (unsigned long)(__AXBufferAuxB + lbl_8066FA38 * 0x780);
}
