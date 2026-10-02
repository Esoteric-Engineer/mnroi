typedef float f32;

typedef struct {
    char pad[0x10];
    f32 a[3];
    f32 k[3];
} GXLightObjInt;

void GXInitLightAttn(GXLightObjInt* lt_obj, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2)
{
    lt_obj->a[0] = a0;
    lt_obj->a[1] = a1;
    lt_obj->a[2] = a2;
    lt_obj->k[0] = k0;
    lt_obj->k[1] = k1;
    lt_obj->k[2] = k2;
}
