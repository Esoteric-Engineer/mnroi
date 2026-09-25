typedef long s32;

typedef struct CARDStat CARDStat;
typedef void (*CARDCallback)(s32, s32);

extern s32 fn_8040F63C(s32 chan, s32 fileNo, CARDStat* stat, CARDCallback callback);
extern s32 fn_8040B3E0(s32 chan);
extern void __CARDSyncCallback(s32 chan, s32 result);

s32 CARDSetStatus(s32 chan, s32 fileNo, CARDStat* stat)
{
    s32 result = fn_8040F63C(chan, fileNo, stat, __CARDSyncCallback);

    if (result < 0)
        return result;
    return fn_8040B3E0(chan);
}
