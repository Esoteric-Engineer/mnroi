typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef float f32;

typedef struct GXTexObj {
    u32 dummy[8];
} GXTexObj;

typedef struct TEXHeader {
    u16 height;
    u16 width;
    u32 format;
    void* data;
    u32 wrapS;
    u32 wrapT;
    u32 minFilter;
    u32 magFilter;
    f32 LODBias;
    u8 edgeLODEnable;
    u8 minLOD;
    u8 maxLOD;
    u8 unpacked;
} TEXHeader;

typedef struct TEXDescriptor {
    TEXHeader* textureHeader;
    void* CLUTHeader;
} TEXDescriptor;

typedef struct TEXPalette {
    u32 versionNumber;
    u32 numDescriptors;
    TEXDescriptor* descriptorArray;
} TEXPalette;

extern void GXInitTexObj(GXTexObj* obj, void* image_ptr, u16 width, u16 height, u32 format,
                         u32 wrap_s, u32 wrap_t, u32 mipmap);
extern void GXInitTexObjLOD(GXTexObj* obj, u32 min_filt, u32 mag_filt, f32 min_lod, f32 max_lod,
                            f32 lod_bias, u32 bias_clamp, u32 do_edge_lod, u32 max_aniso);

/* The unit owns the .sdata2 int-to-float literal; keep it from being dead-stripped. */
#pragma force_active on

TEXDescriptor* TEXGet(TEXPalette* pal, u32 id)
{
    return &pal->descriptorArray[id];
}

void TEXGetGXTexObjFromPalette(TEXPalette* pal, GXTexObj* to, u32 id)
{
    TEXDescriptor* tdp = TEXGet(pal, id);

    GXInitTexObj(to, tdp->textureHeader->data, tdp->textureHeader->width,
                 tdp->textureHeader->height, tdp->textureHeader->format,
                 tdp->textureHeader->wrapS, tdp->textureHeader->wrapT,
                 (tdp->textureHeader->minLOD == tdp->textureHeader->maxLOD) ? 0 : 1);

    GXInitTexObjLOD(to, tdp->textureHeader->minFilter, tdp->textureHeader->magFilter,
                    tdp->textureHeader->minLOD, tdp->textureHeader->maxLOD,
                    tdp->textureHeader->LODBias, 0, tdp->textureHeader->edgeLODEnable, 0);
}
