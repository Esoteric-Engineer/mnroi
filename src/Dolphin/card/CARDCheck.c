typedef long s32;

typedef void (*CARDCallback)(s32, s32);

extern s32 fn_8040C4B4(s32 chan, s32* xferBytes, CARDCallback callback);
extern s32 fn_8040B3E0(s32 chan);
extern void __CARDSyncCallback(s32 chan, s32 result);

static inline s32 CARDCheckEx(s32 chan, s32* xferBytes)
{
    s32 result = fn_8040C4B4(chan, xferBytes, __CARDSyncCallback);

    if (result < 0 || xferBytes == 0)
        return result;
    return fn_8040B3E0(chan);
}

s32 CARDCheck(s32 chan)
{
    s32 xferBytes;

    return CARDCheckEx(chan, &xferBytes);
}
