// Table lookups and plane tests; the .rodata float pool is read through extern_pool.

typedef struct Pair
{
    int a;
    int b; // +0x4
} Pair;

extern void fn_8032A24C(void *out, void *fmt, ...);
extern int fn_80436820(void *self);
extern int fn_800ACFA8(int v);

int fn_80436900(register void *fmt)
{
    Pair buf;
    fn_8032A24C(&buf, fmt, 0);
    return fn_800ACFA8(fn_80436820(&buf));
}

extern int lbl_8066B854;
extern int lbl_8066B858;
extern int lbl_8066B834;
extern int fn_803299D4(int v);

int fn_80436964(void)
{
    register int r = 0;
    if (lbl_8066B854 || lbl_8066B858 || (lbl_8066B834 && fn_803299D4(lbl_8066B834)))
        r = 1;
    return r;
}

typedef struct Entry
{
    unsigned short a; // +0x0
    char pad[4];
    unsigned short b; // +0x6
} Entry;

typedef struct Tris
{
    char pad0[0x2C];
    Entry *tbl[3];  // +0x2C
    float (*pts)[3]; // +0x38
    char pad1[4];
    int *vals;      // +0x40
} Tris;

extern void fn_804354B8(void *dst, void *src);

void fn_804369DC(register Tris *self, register void *out, register int a, register int b)
{
    fn_804354B8(out, &self->pts[self->tbl[a][b].a]);
}

int fn_80436A54(register Tris *self, register int a, register int b)
{
    return self->vals[self->tbl[a][b].b];
}

int fn_80436ABC(register char *self)
{
    return *(int *)(self + 0x118);
}

typedef struct Plane
{
    float x, y, z, d;
} Plane;

typedef struct PlaneSet
{
    char pad0[0x17];
    unsigned char count; // +0x17
    char pad1[8];
    Plane *planes;       // +0x20
} PlaneSet;

extern float fn_8042EBF4(void *a, void *b);

int fn_80436AE8(register PlaneSet *self, register void *p)
{
    unsigned int i = 0;
    while (i < self->count)
    {
        if (fn_8042EBF4(&self->planes[i], p) - self->planes[i].d < 0.0f)
            return 0;
        i++;
    }
    return 1;
}
