typedef int BOOL;
typedef void (*PADSamplingCallback)(void);

extern void SamplingHandler(short interrupt, void* context);
extern BOOL SIRegisterPollingHandler(void* handler);
extern BOOL SIUnregisterPollingHandler(void* handler);

extern PADSamplingCallback lbl_8066F3FC;

PADSamplingCallback PADSetSamplingCallback(PADSamplingCallback callback)
{
    PADSamplingCallback prev;

    prev = lbl_8066F3FC;
    lbl_8066F3FC = callback;

    if (callback) {
        SIRegisterPollingHandler(&SamplingHandler);
    } else {
        SIUnregisterPollingHandler(&SamplingHandler);
    }

    return prev;
}
