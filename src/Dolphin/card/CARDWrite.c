typedef long s32;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDFileInfo {
    s32 chan;
} CARDFileInfo;

extern s32 CARDWriteAsync(CARDFileInfo* fileInfo, const void* buf, s32 length, s32 offset, CARDCallback callback);
extern s32 __CARDSync(s32 chan);
extern void __CARDSyncCallback(s32 chan, s32 result);

s32 CARDWrite(CARDFileInfo* fileInfo, const void* buf, s32 length, s32 offset)
{
    s32 result = CARDWriteAsync(fileInfo, buf, length, offset, __CARDSyncCallback);

    if (result < 0)
        return result;
    return __CARDSync(fileInfo->chan);
}
