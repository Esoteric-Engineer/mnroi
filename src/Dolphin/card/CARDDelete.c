typedef long s32;

typedef void (*CARDCallback)(s32, s32);

extern s32 CARDDeleteAsync(s32 chan, const char* fileName, CARDCallback callback);
extern s32 __CARDSync(s32 chan);
extern void __CARDSyncCallback(s32 chan, s32 result);

s32 CARDDelete(s32 chan, const char* fileName)
{
    s32 result = CARDDeleteAsync(chan, fileName, __CARDSyncCallback);

    if (result < 0)
        return result;
    return __CARDSync(chan);
}
