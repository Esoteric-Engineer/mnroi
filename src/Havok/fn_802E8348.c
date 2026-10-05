// Havok, built at -O2: a getter that returns a constant, and a copy of the 16-byte vector at +0x10 out through a pointer (docs/prodg.md, "Middleware").

typedef struct Vec4 {
    float x, y, z, w;
} Vec4;

int fn_802E8348(void)
{
    return 7;
}

void fn_802E8350(char *self, Vec4 *out)
{
    Vec4 *v = (Vec4 *)(self + 0x10);

    out->x = v->x;
    out->y = v->y;
    out->z = v->z;
    out->w = v->w;
}
