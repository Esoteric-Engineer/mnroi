typedef long s32;
typedef unsigned short u16;

typedef void (*CARDCallback)(s32, s32);

extern u16 __CARDGetFontEncode(void);
extern s32 fn_8040D69C(s32 chan, u16 encode, CARDCallback callback);
extern s32 fn_8040B3E0(s32 chan);
extern void __CARDSyncCallback(s32 chan, s32 result);

s32 CARDFormat(s32 chan)
{
    s32 result = fn_8040D69C(chan, __CARDGetFontEncode(), __CARDSyncCallback);

    if (result < 0)
        return result;
    return fn_8040B3E0(chan);
}
