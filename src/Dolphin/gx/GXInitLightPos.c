typedef float f32;

typedef struct {
    char pad[0x1C];
    f32 lpos[3];
} GXLightObjInt;

void GXInitLightPos(GXLightObjInt* lt_obj, f32 x, f32 y, f32 z)
{
    lt_obj->lpos[0] = x;
    lt_obj->lpos[1] = y;
    lt_obj->lpos[2] = z;
}
