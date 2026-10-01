typedef unsigned char u8;
typedef unsigned long u32;
typedef long long OSTime;

typedef void (*AISCallback)(u32);
typedef void (*AIDCallback)(void);

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int level);

OSTime buffer;
OSTime max_wait;
OSTime min_wait;
OSTime bound_48KHz;
OSTime bound_32KHz;
int __AIDBusy;
int __AI_init_flag;
u8* __OldStack;
u8* __CallbackStack;
AIDCallback __AID_Callback;
AISCallback __AIS_Callback;

AIDCallback AIRegisterDMACallback(AIDCallback callback)
{
    AIDCallback old_callback;
    int old;

    old_callback = __AID_Callback;
    old = OSDisableInterrupts();
    __AID_Callback = callback;
    OSRestoreInterrupts(old);
    return old_callback;
}
