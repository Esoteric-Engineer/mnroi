typedef long s32;

typedef void (*CARDCallback)(s32, s32);

extern s32 CARDCheckExAsync(s32 chan, s32* xferBytes, CARDCallback callback);
extern s32 __CARDSync(s32 chan);
extern void __CARDSyncCallback(s32 chan, s32 result);

static inline s32 CARDCheckEx(s32 chan, s32* xferBytes)
{
    s32 result = CARDCheckExAsync(chan, xferBytes, __CARDSyncCallback);

    if (result < 0 || xferBytes == 0)
        return result;
    return __CARDSync(chan);
}

s32 CARDCheck(s32 chan)
{
    s32 xferBytes;

    return CARDCheckEx(chan, &xferBytes);
}
