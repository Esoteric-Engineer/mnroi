// A PLAYER state's approach step: picks a target (fn_8015F7A4), sets state bit 0x13 within PLAYER field 210 (240 when fn_800860FC).
// Owns .rodata 0x8049B904-0x8049B910 (0.5f, 0.0f, 20.0f).

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
int fn_800CD21C(Ent &a);
int fn_80461D48(void *a, int b);
int fn_801368B8(void *a);
void fn_80442130(void *a, unsigned int bit);
void fn_80442174(void *a, unsigned int bit);
PEnt *fn_8044203C(void *a);
Ent *fn_800CD9B0(Ent &a);
int fn_8015F6CC(void *a, Vector *out);
int fn_800CCA58(Ent &a);
PEnt *fn_80442080(void *a);
int fn_800860FC(void *a);
Ent *fn_80134870(void *a);
void *fn_800B1724(Ent &node);
float fn_8015E8A8(void *a, void *b);
float fn_800B1884(Ent &actor, int id);
PEnt *fn_8015F7A4(PEnt *a, float f1, int kind, Vector *v, float f2);
void *fn_800B1478(Ent &a);
int fn_800A3F44(void *a);
char *fn_804420AC(void *a);
int fn_800B13D8(Ent &actor);
void fn_8014B63C(char *p, int a, int b);
void *fn_804420D8(void *a);
void fn_801501AC(void *a, Ent *b);
float fn_8015E580(void *a, void *b);
int fn_8008606C(void *a);
int fn_8015F384(void *a);
int fn_800B0CC0(Ent &a);
int fn_800A4130(void *a);
float fn_8046439C(void *a);
int fn_8015ED50(void *a, void *b);
void fn_8015105C(void *a, int b);
PEnt *fn_8014F8BC(void *a);
void fn_800C98BC(void *self, PEnt *node, int v);
}

extern "C" int fn_80158038(register Self *self)
{
    if (fn_80151B90(self->f4, self)) {
        if (!fn_80151430(self->f4)) {
            fn_804643C8(self, 1);
            return 1;
        }
        if (fn_800CD21C(*fn_8044203C(self->f0))) {
            fn_804643C8(self, 1);
            return 1;
        }
        if (fn_80461D48(self->f0, 0x1c) && fn_801368B8(self->f0))
            fn_80442130(self->f0, 0xe);
        Ent *e = fn_800CD9B0(*fn_8044203C(self->f0));
        if (!e) {
            Vector v;
            if (fn_8015F6CC(self->f0, &v)) {
                float hi = 0.5f;
                if (fn_800CCA58(*fn_8044203C(self->f0)) && fn_800860FC(fn_80442080(self->f0)))
                    hi = 0.0f;
                if (fn_80134870(self->f0)) {
                    if (fn_8015E8A8(self->f0, fn_800B1724(*fn_80134870(self->f0)))
                        > fn_800B1884(*fn_80442080(self->f0), 216))
                        hi = 0.0f;
                }
                Ent *t = fn_8015F7A4(fn_80442080(self->f0), 20.0f, 2, &v, hi);
                if (t && !fn_800A3F44(fn_800B1478(*t))) {
                    fn_8014B63C(fn_804420AC(self->f0), fn_800B13D8(*t), 0);
                    fn_801501AC(fn_804420D8(self->f0), t);
                    float d = fn_8015E580(fn_800B1724(*t), fn_800B1724(*fn_80442080(self->f0)));
                    float lim = fn_800B1884(*fn_80442080(self->f0), 210);
                    if (fn_800860FC(fn_80442080(self->f0)))
                        lim = fn_800B1884(*fn_80442080(self->f0), 240);
                    if (d <= lim) {
                        fn_80442130(self->f0, 0x13);
                        if (fn_801368B8(self->f0) && !fn_800860FC(fn_80442080(self->f0)))
                            fn_80442174(self->f0, 0xe);
                        if (fn_8008606C(fn_80442080(self->f0)))
                            fn_80442174(self->f0, 0x20);
                    } else {
                        fn_80442130(self->f0, 0x12);
                        if (fn_80461D48(self->f0, 0x34)) {
                            fn_804643C8(self, 1);
                            return 1;
                        }
                    }
                } else {
                    fn_804643C8(self, 1);
                    return 1;
                }
            } else {
                if (fn_80461D48(self->f0, 0x33)) {
                    fn_804643C8(self, 1);
                    return 1;
                }
            }
        } else {
            fn_804643C8(self, 1);
            if (!fn_8015F384(self->f0)) {
                if (fn_800B0CC0(*e) && fn_800A4130(fn_800B1478(*e)) && fn_8046439C(self->f0) > 0.0f) {
                    if (fn_80134870(self->f0) && fn_8015ED50(self->f0, fn_800B1724(*fn_80134870(self->f0))))
                        fn_8015105C(self->f4, 8);
                    else
                        fn_80442130(self->f0, 0x10);
                } else {
                    fn_804643C8(self, 1);
                    fn_8015105C(self->f4, 7);
                }
                PEnt *t = fn_8014F8BC(fn_804420D8(self->f0));
                if (t) {
                    fn_800C98BC(fn_8044203C(self->f0), t, 1);
                    fn_8014B63C(fn_804420AC(self->f0), fn_800B13D8(*t), 0);
                }
            }
        }
    } else {
    }
    return 1;
}
