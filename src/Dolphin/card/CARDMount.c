typedef long s32;

typedef void (*CARDCallback)(s32, s32);

extern s32 CARDMountAsync(s32 chan, void* workArea, CARDCallback detachCallback, CARDCallback attachCallback);
extern s32 __CARDSync(s32 chan);
extern void __CARDSyncCallback(s32 chan, s32 result);

s32 CARDMount(s32 chan, void* workArea, CARDCallback detachCallback)
{
    s32 result = CARDMountAsync(chan, workArea, detachCallback, __CARDSyncCallback);

    if (result < 0)
        return result;
    return __CARDSync(chan);
}
