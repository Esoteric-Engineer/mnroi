typedef long s32;
typedef unsigned long u32;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDFileInfo {
    s32 chan;
} CARDFileInfo;

extern s32 CARDCreateAsync(s32 chan, const char* fileName, u32 size, CARDFileInfo* fileInfo, CARDCallback callback);
extern s32 __CARDSync(s32 chan);
extern void __CARDSyncCallback(s32 chan, s32 result);

s32 CARDCreate(s32 chan, const char* fileName, u32 size, CARDFileInfo* fileInfo)
{
    s32 result = CARDCreateAsync(chan, fileName, size, fileInfo, __CARDSyncCallback);

    if (result < 0)
        return result;
    return __CARDSync(chan);
}
