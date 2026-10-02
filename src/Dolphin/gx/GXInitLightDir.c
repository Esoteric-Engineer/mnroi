typedef float f32;

typedef struct {
    char pad[0x34];
    f32 ldir[3];
} GXLightObjInt;

void GXInitLightDir(GXLightObjInt* lt_obj, f32 nx, f32 ny, f32 nz)
{
    lt_obj->ldir[0] = -nx;
    lt_obj->ldir[1] = -ny;
    lt_obj->ldir[2] = -nz;
}
