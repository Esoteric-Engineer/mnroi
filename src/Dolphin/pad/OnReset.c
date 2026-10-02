typedef unsigned int u32;
typedef int BOOL;
typedef void (*PADSamplingCallback)(void);

extern BOOL SIBusy(void);
extern PADSamplingCallback PADSetSamplingCallback(PADSamplingCallback callback);
extern BOOL PADRecalibrate(u32 mask);

extern PADSamplingCallback SamplingCallback;
extern u32 ResettingBits;
extern long ResettingChan;
extern BOOL Recalibrated;

static inline BOOL PADSync(void)
{
    return ResettingBits == 0 && ResettingChan == 32 && !SIBusy();
}

BOOL OnReset_8018B438(BOOL final)
{
    BOOL sync;

    if (SamplingCallback) {
        PADSetSamplingCallback(0);
    }

    if (!final) {
        sync = PADSync();
        if (!Recalibrated && sync) {
            Recalibrated = PADRecalibrate(0xF0000000);
            return 0;
        }
        return sync;
    } else {
        Recalibrated = 0;
    }

    return 1;
}
