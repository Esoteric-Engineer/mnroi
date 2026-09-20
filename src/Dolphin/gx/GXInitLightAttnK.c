typedef float f32;

typedef struct {
    char pad[0x1C];
    f32 k[3];
} GXLightObjInt;

void GXInitLightAttnK(GXLightObjInt* lt_obj, f32 x, f32 y, f32 z)
{
    lt_obj->k[0] = x;
    lt_obj->k[1] = y;
    lt_obj->k[2] = z;
}
