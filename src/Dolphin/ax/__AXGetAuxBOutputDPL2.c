extern unsigned char __AXBufferAuxB[];
extern unsigned long lbl_8066FA3C;

void __AXGetAuxBOutputDPL2(unsigned long* out)
{
    *out = (unsigned long)(__AXBufferAuxB + lbl_8066FA3C * 0x780);
}
