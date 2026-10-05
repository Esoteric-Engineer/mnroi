// Lays out one glyph quad: corner positions through fn_800FDFA8, then four fn_801015B4/fn_801016BC edge calls.
struct Obj
{
    int pad0;
    unsigned int count; // +0x4
};

struct Face
{
    float x0, y0, x1, y1;     // +0x0
    int a10, a14, a18, a1c, a20;
};

struct Owner
{
    struct Obj *obj; // +0x0
};

extern struct Face *fn_804489B4(struct Obj *obj, int index);
extern void fn_80101704(unsigned int color, unsigned int base, float v);
extern void fn_800FDFA8(float x, float y, int a, int b, int c, int d, float s, int e, float *p0, float *p1, float *p2, float *p3);
extern void fn_801015B4(float a, float b, float c);
extern void fn_80101684(unsigned int color);
extern void fn_801016BC(float a, float b);

float fn_80448364(register struct Owner *self, register char *glyph, register float x, register float y, register unsigned int *color, register float *depth, register float *scale, register float *extent, register float *origin, register int *flags)
{
    y = y + (float)self->obj->count * *scale;
    if (*depth < 0.0f)
    {
        unsigned int tint = (*color & 0xff000000) | 0xffffff;
        fn_80101704(tint, *color, *depth);
    }
    {
    struct Face *face;
    float a, b, c, d;
    face = fn_804489B4(self->obj, glyph[3]);
    fn_800FDFA8(x - 0.5f, y - 0.5f, face->a1c, face->a20, face->a10, face->a14, *scale, *flags, &a, &b, &c, &d);
    fn_801015B4(a, b, *extent);
    fn_80101684(*color);
    fn_801016BC(face->x0, face->y0);
    fn_801015B4(a, d, *extent);
    fn_80101684(*color);
    fn_801016BC(face->x0, face->y1);
    fn_801015B4(c, d, *extent);
    fn_80101684(*color);
    fn_801016BC(face->x1, face->y1);
    fn_801015B4(c, b, *extent);
    fn_80101684(*color);
    fn_801016BC(face->x1, face->y0);
    return (float)face->a18 * *scale + *origin;
    }
}
