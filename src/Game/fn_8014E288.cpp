// A PLAYER state's throttled (3000 ticks) effect refresh; uses PLAYER field 216 (guess); docs/versus.md row 20.

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

struct Ent {
    int pad;
};

struct PEnt : Ent { // matching_notes 44
    int x;
};

struct Self {
    void *f0;
    char pad0[0xE4];
    int fE8; // +0xE8: effect handle
    char pad1[0x28];
    unsigned int f114; // +0x114: next refresh time
};

extern char lbl_80593BE8[];

extern "C" {
int fn_8042EFF8(void *g);
void fn_80461D04(void *a, int b);
void fn_80461CC0(void *a, int b);
Ent *fn_80134870(void *a);
PEnt *fn_80442080(void *a);
void *fn_8044203C(void *a);
void *fn_800B1724(Ent &node);
Vector *fn_800B1750(Ent &actor);
Ent *fn_800B1590(Ent &a);
Ent *fn_800ACFA8(int handle);
int fn_800B13D8(Ent &actor);
float fn_800B1884(Ent &actor, int id);
float fn_8015E8A8(void *a, void *b);
int fn_8015F6CC(void *a, Vector *out);
PEnt *fn_8015F7A4(PEnt *a, float f1, int kind, Vector *v, float f2);
void fn_8042DC84(Vector *dst, void *src);
void fn_80429038(Vector *out, void *a, void *b);
void fn_8042F76C(Vector *v);
float fn_8042EBF4(Vector *a, Vector *b);
}

extern "C" void fn_8014E288(register Self *self)
{
    if ((unsigned int)fn_8042EFF8(lbl_80593BE8) > self->f114) {
        fn_80461D04(self->f0, 11);
        float lo = 0.5f;
        float hi = 4.0f;
        if (fn_80134870(self->f0)) {
            if (fn_8015E8A8(self->f0, fn_800B1724(*fn_80134870(self->f0))) > fn_800B1884(*fn_80442080(self->f0), 216))
                hi = 20.0f;
        }
        Vector v;
        if (!fn_8015F6CC(self->f0, &v))
            fn_8042DC84(&v, fn_800B1750(*fn_80442080(self->f0)));
        PEnt *p = fn_8015F7A4(fn_80442080(self->f0), hi, 2, &v, lo);
        if (p)
            self->fE8 = fn_800B13D8(*p);
        self->f114 = fn_8042EFF8(lbl_80593BE8) + 3000;
    }
    PEnt *a = fn_80442080(self->f0);
    void *b = fn_8044203C(self->f0);
    if (self->fE8) {
        Ent *c = fn_800B1590(*fn_800ACFA8(self->fE8));
        if (c) {
            Vector v;
            fn_80429038(&v, fn_800B1724(*c), fn_800B1724(*a));
            fn_8042F76C(&v);
            float f = fn_8042EBF4(&v, fn_800B1750(*a));
            if (f > 0.5f)
                fn_80461CC0(self->f0, 11);
        }
    }
}
