typedef struct OSContext OSContext;

volatile OSContext* __OSCurrentContext : 0x800000D4;

OSContext* OSGetCurrentContext(void)
{
    return (OSContext*)__OSCurrentContext;
}
