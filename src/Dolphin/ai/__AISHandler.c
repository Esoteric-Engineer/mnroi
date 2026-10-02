typedef unsigned char u8;
typedef unsigned long u32;

volatile u32 __AIRegs[8] : 0xCC006C00;

extern void (*__AIS_Callback)(u32);

extern void OSClearContext(void* context);
extern void OSSetCurrentContext(void* context);

void __AISHandler(u32 interrupt, void* context)
{
    u8 exceptionContext[0x2C8];

    __AIRegs[0] |= 8;
    OSClearContext(exceptionContext);
    OSSetCurrentContext(exceptionContext);
    if (__AIS_Callback) {
        __AIS_Callback(__AIRegs[2]);
    }
    OSClearContext(exceptionContext);
    OSSetCurrentContext(context);
}
