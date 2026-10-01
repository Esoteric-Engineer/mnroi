typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned long u32;

volatile u16 __DSPRegs[0x20] : 0xCC005000;

extern void (*__AID_Callback)(void);
extern void* __CallbackStack;
extern int __AIDBusy;

extern void OSClearContext(void* context);
extern void OSSetCurrentContext(void* context);
extern void __AICallbackStackSwitch(void (*cb)(void));

void __AIDHandler(u32 interrupt, void* context)
{
    u8 exceptionContext[0x2C8];
    u16 tmp;

    tmp = __DSPRegs[5];
    tmp = (tmp & ~0xA0) | 8;
    __DSPRegs[5] = tmp;
    OSClearContext(exceptionContext);
    OSSetCurrentContext(exceptionContext);
    if (__AID_Callback) {
        if (__AIDBusy == 0) {
            __AIDBusy = 1;
            if (__CallbackStack) {
                __AICallbackStackSwitch(__AID_Callback);
            } else {
                __AID_Callback();
            }
            __AIDBusy = 0;
        }
    }
    OSClearContext(exceptionContext);
    OSSetCurrentContext(context);
}
