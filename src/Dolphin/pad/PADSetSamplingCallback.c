typedef int BOOL;
typedef void (*PADSamplingCallback)(void);

extern void SamplingHandler(short interrupt, void* context);
extern BOOL SIRegisterPollingHandler(void* handler);
extern BOOL SIUnregisterPollingHandler(void* handler);

extern PADSamplingCallback SamplingCallback;

PADSamplingCallback PADSetSamplingCallback(PADSamplingCallback callback)
{
    PADSamplingCallback prev;

    prev = SamplingCallback;
    SamplingCallback = callback;

    if (callback) {
        SIRegisterPollingHandler(&SamplingHandler);
    } else {
        SIUnregisterPollingHandler(&SamplingHandler);
    }

    return prev;
}
