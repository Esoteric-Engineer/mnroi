extern unsigned char __AXBufferAuxB[];
extern unsigned long __AXAuxDspWritePosition;

void __AXGetAuxAInputDpl2(unsigned long* out)
{
    *out = (unsigned long)(__AXBufferAuxB + __AXAuxDspWritePosition * 0x780 + 0x500);
}
