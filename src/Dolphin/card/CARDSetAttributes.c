typedef unsigned char u8;
typedef long s32;

typedef void (*CARDCallback)(s32, s32);

extern s32 fn_8040F8BC(s32 chan, s32 fileNo, u8 attr, CARDCallback callback);
extern s32 __CARDSync(s32 chan);
extern void __CARDSyncCallback(s32 chan, s32 result);

s32 CARDSetAttributes(s32 chan, s32 fileNo, u8 attr)
{
    s32 result = fn_8040F8BC(chan, fileNo, attr, __CARDSyncCallback);

    if (result < 0)
        return result;
    return __CARDSync(chan);
}
