typedef unsigned long u32;

typedef struct {
    char pad[0xC];
    u32 color;
} GXLightObjInt;

void GXInitLightColor(GXLightObjInt* lt_obj, u32* color)
{
    lt_obj->color = *color;
}
