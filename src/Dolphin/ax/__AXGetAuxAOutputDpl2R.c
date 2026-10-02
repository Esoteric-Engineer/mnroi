extern unsigned char __AXBufferAuxA[];
extern unsigned long __AXAuxDspReadPosition;

void __AXGetAuxAOutputDpl2R(unsigned long* out)
{
    *out = (unsigned long)(__AXBufferAuxA + __AXAuxDspReadPosition * 0x780 + 0x280);
}
