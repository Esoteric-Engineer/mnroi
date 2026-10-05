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
    if (*depth < 1.0f)
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

struct Sprite
{
    char pad0[0x58];
    unsigned short w; // +0x58
    unsigned short h; // +0x5A
};

struct SpriteOwner
{
    char pad0[0xC];
    struct Sprite *sprite; // +0xC
};

extern float lbl_8066F4DC;
extern float lbl_8066F4E0;
extern char lbl_80594EF0[];
extern float *fn_8042E7E4(float *scale);
extern void fn_8042F42C(char *obj, struct Sprite *sprite, int a);
extern void GXBegin(int prim, int fmt, int count);
extern void fn_8010160C(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void fn_80101590(void);

// Draws a screen-scaled sprite quad and returns its rounded width.
int fn_804485AC(register struct SpriteOwner *self, register float x, register float y, register unsigned int size, register float z, register unsigned int c0, register unsigned int c1, register unsigned int c2, register unsigned int c3, register int unused)
{
    float dy;
    float dx;
    float ratio;
    x = x * lbl_8066F4DC;
    y = y * lbl_8066F4E0;
    ratio = (float)size / (float)(int)self->sprite->h;
    dy = (float)(int)self->sprite->h * ratio * fn_8042E7E4(&lbl_8066F4DC)[1];
    dx = (float)(int)self->sprite->w * ratio * fn_8042E7E4(&lbl_8066F4DC)[0];
    y = y - dy * 0.8f;
    fn_8042F42C(lbl_80594EF0, self->sprite, 0);
    GXBegin(0x80, 2, 4);
    fn_801015B4(x, y, z);
    fn_8010160C(c0, c1, c2, c3);
    fn_801016BC(0.0f, 0.0f);
    fn_801015B4(x, y + dy, z);
    fn_8010160C(c0, c1, c2, c3);
    fn_801016BC(0.0f, 1.0f);
    fn_801015B4(x + dx, y + dy, z);
    fn_8010160C(c0, c1, c2, c3);
    fn_801016BC(1.0f, 1.0f);
    fn_801015B4(x + dx, y, z);
    fn_8010160C(c0, c1, c2, c3);
    fn_801016BC(1.0f, 0.0f);
    fn_80101590();
    return dx > 0.0f ? (int)(dx + 0.5) : -(int)(0.5 - dx);
}
