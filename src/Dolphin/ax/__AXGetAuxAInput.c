extern unsigned char __AXBufferAuxA[];
extern unsigned long __AXCallbackAuxA;
extern unsigned long __AXAuxDspWritePosition;

void __AXGetAuxAInput(unsigned long* out)
{
    if (__AXCallbackAuxA != 0) {
        *out = (unsigned long)(__AXBufferAuxA + __AXAuxDspWritePosition * 0x780);
    } else {
        *out = 0;
    }
}
