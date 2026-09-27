typedef long s32;

typedef void (*CARDCallback)(s32, s32);

extern s32 CARDFastDeleteAsync(s32 chan, s32 fileNo, CARDCallback callback);
extern s32 __CARDSync(s32 chan);
extern void __CARDSyncCallback(s32 chan, s32 result);

s32 CARDFastDelete(s32 chan, s32 fileNo)
{
    s32 result = CARDFastDeleteAsync(chan, fileNo, __CARDSyncCallback);

    if (result < 0)
        return result;
    return __CARDSync(chan);
}
