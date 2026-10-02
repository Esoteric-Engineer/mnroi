extern unsigned char __AXBufferAuxB[];
extern unsigned long __AXAuxDspReadPositionDpl2;

void __AXGetAuxBOutputDPL2(unsigned long* out)
{
    *out = (unsigned long)(__AXBufferAuxB + __AXAuxDspReadPositionDpl2 * 0x780);
}
