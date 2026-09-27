extern unsigned char __AXBufferAuxB[];
extern unsigned long lbl_8066FA34;

void __AXGetAuxBOutput(unsigned long* out)
{
    *out = (unsigned long)(__AXBufferAuxB + lbl_8066FA34 * 0x780);
}
