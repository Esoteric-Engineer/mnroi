typedef unsigned char u8;
typedef unsigned long u32;

typedef struct {
    u32 image1;
    u32 image2;
    u32 sizes;
    u8 is32bMipmap;
    u8 isCached;
} GXTexRegion;

#define SET_REG_FIELD(reg, size, shift, val)                                  \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift),                    \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXInitTexCacheRegion(GXTexRegion* region, u8 is_32b_mipmap, u32 tmem_even, int size_even, u32 tmem_odd, int size_odd)
{
    u32 WidthExp2;

    switch (size_even) {
    case 0:
        WidthExp2 = 3;
        break;
    case 1:
        WidthExp2 = 4;
        break;
    case 2:
        WidthExp2 = 5;
        break;
    }
    region->image1 = 0;
    SET_REG_FIELD(region->image1, 15, 0, tmem_even >> 5);
    SET_REG_FIELD(region->image1, 3, 15, WidthExp2);
    SET_REG_FIELD(region->image1, 3, 18, WidthExp2);
    SET_REG_FIELD(region->image1, 1, 21, 0);
    switch (size_odd) {
    case 0:
        WidthExp2 = 3;
        break;
    case 1:
        WidthExp2 = 4;
        break;
    case 2:
        WidthExp2 = 5;
        break;
    case 3:
        WidthExp2 = 0;
        break;
    }
    region->image2 = 0;
    SET_REG_FIELD(region->image2, 15, 0, tmem_odd >> 5);
    SET_REG_FIELD(region->image2, 3, 15, WidthExp2);
    SET_REG_FIELD(region->image2, 3, 18, WidthExp2);
    region->is32bMipmap = is_32b_mipmap;
    region->isCached = 1;
}
