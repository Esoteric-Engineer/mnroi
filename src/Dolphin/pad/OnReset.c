typedef unsigned int u32;
typedef int BOOL;
typedef void (*PADSamplingCallback)(void);

extern BOOL SIBusy(void);
extern PADSamplingCallback PADSetSamplingCallback(PADSamplingCallback callback);
extern BOOL PADRecalibrate(u32 mask);

extern PADSamplingCallback lbl_8066F3FC;
extern u32 lbl_8066F3E0;
extern long lbl_8066C49C;
extern BOOL lbl_8066F400;

static inline BOOL PADSync(void)
{
    return lbl_8066F3E0 == 0 && lbl_8066C49C == 32 && !SIBusy();
}

BOOL OnReset_8018B438(BOOL final)
{
    BOOL sync;

    if (lbl_8066F3FC) {
        PADSetSamplingCallback(0);
    }

    if (!final) {
        sync = PADSync();
        if (!lbl_8066F400 && sync) {
            lbl_8066F400 = PADRecalibrate(0xF0000000);
            return 0;
        }
        return sync;
    } else {
        lbl_8066F400 = 0;
    }

    return 1;
}
