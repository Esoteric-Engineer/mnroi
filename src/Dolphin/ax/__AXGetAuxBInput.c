extern unsigned char __AXBufferAuxB[];
extern unsigned long __AXCallbackAuxB;
extern unsigned long __AXAuxDspWritePosition;

void __AXGetAuxBInput(unsigned long* out)
{
    if (__AXCallbackAuxB != 0) {
        *out = (unsigned long)(__AXBufferAuxB + __AXAuxDspWritePosition * 0x780);
    } else {
        *out = 0;
    }
}
