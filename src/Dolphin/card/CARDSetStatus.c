typedef long s32;

typedef struct CARDStat CARDStat;
typedef void (*CARDCallback)(s32, s32);

extern s32 CARDSetStatusAsync(s32 chan, s32 fileNo, CARDStat* stat, CARDCallback callback);
extern s32 __CARDSync(s32 chan);
extern void __CARDSyncCallback(s32 chan, s32 result);

s32 CARDSetStatus(s32 chan, s32 fileNo, CARDStat* stat)
{
    s32 result = CARDSetStatusAsync(chan, fileNo, stat, __CARDSyncCallback);

    if (result < 0)
        return result;
    return __CARDSync(chan);
}
