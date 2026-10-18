// A PLAYER state's chase step: picks a target by PLAYER field 213, then fires/clears state bits; docs/versus.md row 20.

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
    void *f4;
};

extern "C" {
int fn_80151B90(void *a, void *b);
int fn_80151430(void *a);
void fn_804643C8(void *a, int b);
int fn_80461D48(void *a, int b);
int fn_801368B8(void *a);
void fn_80442130(void *a, unsigned int bit);
void fn_80442174(void *a, unsigned int bit);
PEnt *fn_8044203C(void *a);
Ent *fn_800CD9B0(Ent &a);
Ent *fn_80134870(void *a);
void *fn_800B1724(Ent &node);
float fn_8015F608(void *a, void *b, Vector *out);
PEnt *fn_80442080(void *a);
float fn_800B1884(Ent &actor, int id);
PEnt *fn_8015F7A4(PEnt *a, float f1, int kind, Vector *v, float f2);
char *fn_804420AC(void *a);
int fn_800B13D8(Ent &actor);
void fn_8014B63C(char *p, int a, int b);
void *fn_804420D8(void *a);
void fn_801501AC(void *a, Ent *b);
float fn_8015E580(void *a, void *b);
int fn_80085F7C(void *a);
int fn_8008606C(void *a);
void fn_8015105C(void *a, int b);
PEnt *fn_8014F8BC(void *a);
void fn_800C98BC(void *self, PEnt *node, int v);
}

extern "C" int fn_80158844(register Self *self)
{
    if (fn_80151B90(self->f4, self)) {
        if (!fn_80151430(self->f4)) {
            fn_804643C8(self, 1);
            return 1;
        }
        if (fn_80461D48(self->f0, 0x1c) && fn_801368B8(self->f0))
            fn_80442130(self->f0, 0xe);
        Ent *e = fn_800CD9B0(*fn_8044203C(self->f0));
        if (!e) {
            e = fn_80134870(self->f0);
            if (!e)
                return 0;
            Vector v;
            float a = fn_8015F608(self->f0, fn_800B1724(*e), &v);
            float lo = fn_800B1884(*fn_80442080(self->f0), 213);
            float hi = 0.5f;
            Ent *t = fn_8015F7A4(fn_80442080(self->f0), lo, 1, &v, hi);
            if (t) {
                fn_8014B63C(fn_804420AC(self->f0), fn_800B13D8(*t), 0);
                fn_801501AC(fn_804420D8(self->f0), t);
                float lim = fn_800B1884(*fn_80442080(self->f0), 210);
                lim = 5.0f;
                float d = fn_8015E580(fn_800B1724(*t), fn_800B1724(*fn_80442080(self->f0)));
                if (d <= lim) {
                    fn_80442130(self->f0, 0x13);
                    if (fn_80085F7C(fn_80442080(self->f0)))
                        fn_80442174(self->f0, 0xe);
                    if (fn_8008606C(fn_80442080(self->f0)))
                        fn_80442174(self->f0, 0x20);
                    return 1;
                }
                if (fn_80461D48(self->f0, 0x33)) {
                    fn_804643C8(self, 1);
                    return 0;
                }
            }
        } else {
            fn_804643C8(self, 1);
            fn_8015105C(self->f4, 8);
            PEnt *t = fn_8014F8BC(fn_804420D8(self->f0));
            if (t) {
                fn_800C98BC(fn_8044203C(self->f0), t, 1);
                fn_8014B63C(fn_804420AC(self->f0), fn_800B13D8(*t), 0);
            }
        }
    } else {
    }
    return 1;
}
