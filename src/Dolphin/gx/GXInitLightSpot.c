#pragma force_active on
#pragma fp_contract off

typedef float f32;

typedef enum {
    GX_SP_OFF,
    GX_SP_FLAT,
    GX_SP_COS,
    GX_SP_COS2,
    GX_SP_SHARP,
    GX_SP_RING1,
    GX_SP_RING2
} GXSpotFn;

typedef struct {
    char pad[0x10];
    f32 a[3];
} GXLightObjInt;

extern f32 cosf(f32 x);

void GXInitLightSpot(GXLightObjInt* lt_obj, f32 cutoff, GXSpotFn spot_func)
{
    f32 a0, a1, a2;
    f32 r;
    f32 d;
    f32 cr;

    if (cutoff <= 0.0f || cutoff > 90.0f) {
        spot_func = GX_SP_OFF;
    }

    r = (3.1415927f * cutoff) / 180.0f;
    cr = cosf(r);
    switch (spot_func) {
    case GX_SP_FLAT:
        a0 = -1000.0f * cr;
        a1 = 1000.0f;
        a2 = 0.0f;
        break;
    case GX_SP_COS:
        d = 1.0f / (1.0f - cr);
        a0 = -cr * d;
        a1 = d;
        a2 = 0.0f;
        break;
    case GX_SP_COS2:
        d = 1.0f / (1.0f - cr);
        a0 = 0.0f;
        a1 = -cr * d;
        a2 = d;
        break;
    case GX_SP_SHARP:
        d = 1.0f / ((1.0f - cr) * (1.0f - cr));
        a0 = d * (cr * (cr - 2.0f));
        a1 = 2.0f * d;
        a2 = -d;
        break;
    case GX_SP_RING1:
        d = 1.0f / ((1.0f - cr) * (1.0f - cr));
        a2 = -4.0f * d;
        a0 = a2 * cr;
        a1 = (4.0f * (1.0f + cr)) * d;
        break;
    case GX_SP_RING2:
        d = 1.0f / ((1.0f - cr) * (1.0f - cr));
        a0 = 1.0f - d * ((2.0f * cr) * cr);
        a1 = (4.0f * cr) * d;
        a2 = -2.0f * d;
        break;
    case GX_SP_OFF:
    default:
        a0 = 1.0f;
        a1 = 0.0f;
        a2 = 0.0f;
        break;
    }
    lt_obj->a[0] = a0;
    lt_obj->a[1] = a1;
    lt_obj->a[2] = a2;
}
