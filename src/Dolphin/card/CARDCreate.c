typedef long s32;
typedef unsigned long u32;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDFileInfo {
    s32 chan;
} CARDFileInfo;

extern s32 fn_8040E568(s32 chan, const char* fileName, u32 size, CARDFileInfo* fileInfo, CARDCallback callback);
extern s32 fn_8040B3E0(s32 chan);
extern void __CARDSyncCallback(s32 chan, s32 result);

s32 CARDCreate(s32 chan, const char* fileName, u32 size, CARDFileInfo* fileInfo)
{
    s32 result = fn_8040E568(chan, fileName, size, fileInfo, __CARDSyncCallback);

    if (result < 0)
        return result;
    return fn_8040B3E0(chan);
}
