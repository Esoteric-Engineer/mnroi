extern unsigned char __AXBufferAuxA[];
extern unsigned long __AXAuxDspReadPosition;

void __AXGetAuxAOutput(unsigned long* out)
{
    *out = (unsigned long)(__AXBufferAuxA + __AXAuxDspReadPosition * 0x780);
}
