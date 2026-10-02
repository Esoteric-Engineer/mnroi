typedef unsigned char u8;
typedef unsigned long u32;

typedef void (*DVDLowCallback)(u32);

extern DVDLowCallback Callback;

extern u32 __OSMaskInterrupts(u32 mask);
extern void OSClearContext(void* context);
extern void OSSetCurrentContext(void* context);

void AlarmHandlerForTimeout(void* alarm, void* context)
{
    u8 tmpContext[0x2C8];
    DVDLowCallback callback;

    __OSMaskInterrupts(0x400);
    OSClearContext(tmpContext);
    OSSetCurrentContext(tmpContext);
    callback = Callback;
    Callback = 0;
    if (callback) {
        callback(0x10);
    }
    OSClearContext(tmpContext);
    OSSetCurrentContext(context);
}
