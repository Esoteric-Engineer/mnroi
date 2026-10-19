// Actor setup step (guess): starts a motion/stance on the actor, via fn_8009FF54. Type-ID use: docs/characters.md section 5.
// The unit owns the 0.2f pool at 0x8048AF14.

inline int sn_return_decl(int a) { return a; }

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

struct Obj {
    char pad0[0x290];
    unsigned int flags; // +0x290
    char pad1[4];
    float f298;
    int f29C;
    int f2A0;
    char pad2[0x2C];
    char v2D0[0x10]; // +0x2D0
    char pad3[0x10];
    char v2F0[0x10]; // +0x2F0
};

extern "C" {
void *memset(void *p, int c, unsigned int n);
int fn_800A0FE4(void *self);
int fn_800A0DD4(void *self);
int fn_8010CDCC(void *self, int event, void *target, int a3, int a4, int a5, int a6);
void fn_80066604(void *self);
void fn_8006645C(void *self, int v);
int fn_800B1D48(void *self);
int fn_800B24AC(void *self);
float fn_80434040(void *v);
float fn_800B24D8(void *self);
float fn_800670CC(void *self);
void *fn_8009ACC0(void *self);
int fn_8009ABEC(void *self);
int fn_8009AC94(void *self);
void *fn_800B1724(void *self);
void *fn_800B1750(void *self);
void fn_8009F010(void *self, void *v);
int fn_8009FF54(void *self, void *p, int type, int b, void *a, void *c, void *d, float f1, int two, float f2, int e, int f, int g, int h, int i, int *out);
int fn_800B0C58(void *a);
void *fn_800B14A0(void *a);
void *fn_80085954(void *p);
int fn_800CCA08(void *p);
void fn_8042DC84(void *dst, void *src);
void fn_80429038(void *out, void *a, void *b);
int fn_800B13D8(void *a);
void fn_8009AD04(void *self, int v);
}

extern "C" void fn_8009E998(register Obj *self, void *p, int two, int e, float f1, void *c, void *d, float f2)
{
    if (self->flags & 0x10) {
        fn_8009F010(self, d);
        fn_8010CDCC(self, 9, 0, 0, 200, 0, 0);
    }
}

extern "C" int fn_8009EA20(register Obj *self, Obj *a, int b, int c)
{
    float scale;
    void *p;
    register void *t;
    int out;
    int result;

    if (fn_800A0FE4(self) != 0 && fn_800A0DD4(self) == 0) {
        fn_8010CDCC(self, 1, 0, 0, 0, 0, 0);
        fn_80066604(self);
        memset(self->v2D0, 0, 0x10);
        fn_8006645C(self, 1);
        self->flags |= 0x800;
        return 1;
    }

    if (fn_800B1D48(self) == 4 || fn_800B24AC(self) == 0) {
        scale = fn_80434040(self->v2D0) * fn_800B24D8(self);
    } else {
        scale = fn_800670CC(self) * fn_800B24D8(self);
    }

    p = fn_8009ACC0(self);
    out = 0;
    result = fn_8009FF54(self, p, fn_8009ABEC(self), fn_8009AC94(self), a, fn_800B1724(self), fn_800B1750(self), self->f298, 2, scale,
                         self->f29C, self->f2A0, b, c, 0, &out);

    if (out != 0) {
        if (fn_800B0C58(a) != 0 && fn_80085954(fn_800B14A0(a)) != 0 &&
            (t = fn_80085954(fn_800B14A0(a)), fn_800CCA08(t) != 0)) {
            if (fn_8009ACC0(self) != 0) {
                Vector v40;
                Vector v50;
                fn_8042DC84(&v40, fn_800B1724(fn_8009ACC0(self)));
                fn_8042DC84(&v50, fn_800B1724(a));
                v40.z += 0.2f;
                fn_80429038(self->v2F0, &v40, &v50);
            } else {
                fn_8042DC84(self->v2F0, self->v2D0);
            }
            self->flags |= 0x10000000;
        } else {
            self->flags |= 0x8000000;
        }
        fn_8009AD04(self, fn_800B13D8(a));
        result = 0;
    } else {
    }
    return result;
}
