typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef float f32;

typedef unsigned char GXBool;
typedef int GXTexFmt;
typedef int GXTexWrapMode;

typedef struct {
    u32 mode0;
    u32 mode1;
    u32 image0;
    u32 image3;
    void* userData;
    GXTexFmt fmt;
    u32 tlutName;
    u16 loadCnt;
    u8 loadFmt;
    u8 flags;
} GXTexObj;

void GXGetTexObjAll(const GXTexObj* obj, void** image_ptr, u16* width, u16* height,
                    GXTexFmt* format, GXTexWrapMode* wrap_s, GXTexWrapMode* wrap_t,
                    u8* mipmap)
{
    *image_ptr = (void*)((obj->image3 & 0x001FFFFF) << 5);
    *width = (obj->image0 & 0x3FF) + 1;
    *height = ((obj->image0 >> 10) & 0x3FF) + 1;
    *format = obj->fmt;
    *wrap_s = obj->mode0 & 3;
    *wrap_t = (obj->mode0 >> 2) & 3;
    *mipmap = (obj->flags & 1) == 1;
}

void* GXGetTexObjData(const GXTexObj* obj)
{
    return (void*)((obj->image3 & 0x001FFFFF) << 5);
}

u16 GXGetTexObjWidth(const GXTexObj* obj)
{
    return (obj->image0 & 0x3FF) + 1;
}

u16 GXGetTexObjHeight(const GXTexObj* obj)
{
    return ((obj->image0 >> 10) & 0x3FF) + 1;
}

GXTexFmt GXGetTexObjFmt(const GXTexObj* obj)
{
    return obj->fmt;
}

GXBool GXGetTexObjMipMap(const GXTexObj* obj)
{
    return (obj->flags & 1) == 1;
}

asm f32 GXGetTexObjMinLOD(register const GXTexObj* obj)
{
    // clang-format off
    nofralloc
    stwu    r1, -24(r1)
    lis     r0, 0x4330
    lwz     r3, 4(obj)
    lfd     f2, -11800(r13)
    extrwi  r3, r3, 8, 16
    lfs     f0, -11768(r13)
    stw     r3, 20(r1)
    stw     r0, 16(r1)
    lfd     f1, 16(r1)
    fsubs   f1, f1, f2
    fmuls   f1, f1, f0
    addi    r1, r1, 24
    blr
    // clang-format on
}
