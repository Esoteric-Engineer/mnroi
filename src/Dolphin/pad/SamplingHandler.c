typedef short s16;
typedef unsigned char u8;
typedef unsigned int u32;
typedef void (*PADSamplingCallback)(void);

typedef struct OSContext {
    u8 pad[0x2C8];
} OSContext;

extern PADSamplingCallback lbl_8066F3FC;

void OSClearContext(OSContext* context);
void OSSetCurrentContext(OSContext* context);

void SamplingHandler(s16 interrupt, OSContext* context)
{
    OSContext exceptionContext;

    if (lbl_8066F3FC) {
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);
        (*lbl_8066F3FC)();
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
}
