extern unsigned char __AXBufferAuxB[];
extern unsigned long __AXAuxDspReadPosition;

void __AXGetAuxBOutput(unsigned long* out)
{
    *out = (unsigned long)(__AXBufferAuxB + __AXAuxDspReadPosition * 0x780);
}
