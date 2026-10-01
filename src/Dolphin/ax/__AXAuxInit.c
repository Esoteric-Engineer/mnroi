unsigned long __AXAuxCpuReadWritePosition;
unsigned long __AXAuxDspReadPositionDpl2;
unsigned long __AXAuxDspWritePositionDpl2;
unsigned long __AXAuxDspReadPosition;
unsigned long __AXAuxDspWritePosition;
void* __AXAuxBDspRead;
void* __AXAuxBDspWrite;
void* __AXAuxADspRead;
void* __AXAuxADspWrite;
void* __AXContextAuxB;
void* __AXContextAuxA;
void (*__AXCallbackAuxB)(void*, void*);
void (*__AXCallbackAuxA)(void*, void*);

extern unsigned long __AXBufferAuxA[];
extern unsigned long __AXBufferAuxB[];

void __AXAuxInit(void)
{
    unsigned long* a;
    unsigned long* b;
    int i;

    __AXCallbackAuxA = 0;
    __AXCallbackAuxB = 0;
    __AXContextAuxA = 0;
    __AXContextAuxB = 0;
    __AXAuxDspWritePosition = 0;
    __AXAuxDspReadPosition = 1;
    __AXAuxDspWritePositionDpl2 = 0;
    __AXAuxDspReadPositionDpl2 = 1;
    __AXAuxCpuReadWritePosition = 2;

    a = __AXBufferAuxA;
    b = __AXBufferAuxB;
    for (i = 0; i < 0x1E0; i++) {
        *a++ = 0;
        *b++ = 0;
    }
}
