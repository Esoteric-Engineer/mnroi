typedef unsigned long u32;
typedef unsigned char u8;

typedef struct {
    u32 dummy[4];
} GXTexRegion;

typedef struct {
    u32 dummy[8];
} GXTexObj;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    char pad0[0x208];
    GXTexRegion TexRegions0[8];
    GXTexRegion TexRegions1[8];
    GXTexRegion TexRegions2[8];
} __GXDataStruct;

extern __GXDataStruct* const __GXData;

extern int GXGetTexObjFmt(const GXTexObj* obj);
extern u8 GXGetTexObjMipMap(const GXTexObj* obj);

#pragma peephole off
GXTexRegion* __GXDefaultTexRegionCallback(const GXTexObj* t_obj, int id)
{
    int fmt = GXGetTexObjFmt(t_obj);
    u8 mipmap = GXGetTexObjMipMap(t_obj);

    id = id % 8;
    switch (fmt) {
    case 6:
        if (mipmap) {
            return &__GXData->TexRegions2[id];
        }
        return &__GXData->TexRegions1[id];
    case 8:
    case 9:
    case 10:
        return &__GXData->TexRegions0[id];
    default:
        if (mipmap) {
            return &__GXData->TexRegions1[id];
        }
        return &__GXData->TexRegions0[id];
    }
}
