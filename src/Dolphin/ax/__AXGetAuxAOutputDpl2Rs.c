extern unsigned char __AXBufferAuxB[];
extern unsigned long __AXAuxDspReadPosition;

void __AXGetAuxAOutputDpl2Rs(unsigned long* out)
{
    *out = (unsigned long)(__AXBufferAuxB + __AXAuxDspReadPosition * 0x780 + 0x500);
}
