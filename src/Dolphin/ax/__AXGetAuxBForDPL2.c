extern unsigned char __AXBufferAuxB[];
extern unsigned long __AXAuxDspWritePositionDpl2;

void __AXGetAuxBForDPL2(unsigned long* out)
{
    *out = (unsigned long)(__AXBufferAuxB + __AXAuxDspWritePositionDpl2 * 0x780);
}
