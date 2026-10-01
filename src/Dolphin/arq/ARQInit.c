char lbl_804EEF40[] = "<< Dolphin SDK - ARQ\trelease build: Apr 17 2003 12:33:56 (0x2301) >>";
static char* __ARQVersion = lbl_804EEF40;

extern void* __ARQRequestQueueHi;
extern void* __ARQRequestQueueLo;
extern void* __ARQRequestPendingHi;
extern void* __ARQRequestPendingLo;
extern void* __ARQCallbackHi;
extern void* __ARQCallbackLo;
extern unsigned long __ARQChunkSize;
extern int __ARQ_init_flag;

extern void OSRegisterVersion(char* version);
extern void ARRegisterDMACallback(void (*callback)(void));
extern void __ARQInterruptServiceRoutine(void);

void ARQInit(void)
{
    if (__ARQ_init_flag != 1) {
        OSRegisterVersion(__ARQVersion);
        __ARQRequestQueueHi = __ARQRequestQueueLo = 0;
        __ARQChunkSize = 0x1000;
        ARRegisterDMACallback(__ARQInterruptServiceRoutine);
        __ARQRequestPendingHi = 0;
        __ARQRequestPendingLo = 0;
        __ARQCallbackHi = 0;
        __ARQCallbackLo = 0;
        __ARQ_init_flag = 1;
    }
}
