// The AIObject+0xD0 target list: init, reset, timers and the throttled update steps (docs/ai.md row 11).
// .rodata 0x8049B520-0x8049B52C is fn_8014E288's pool. fn_80442080 returns PEnt * (matching_notes 50).

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
    void *f0;              // +0x0: AIObject
    int f4;                // +0x4
    char pad0[0x40];
    int f48;               // +0x48: count
    char pad1[0x80];
    int fCC;               // +0xCC: best target handle
    int fD0;               // +0xD0
    int fD4;               // +0xD4
    int fD8;               // +0xD8
    int fDC;               // +0xDC
    int fE0;               // +0xE0
    int fE4;               // +0xE4: target handle
    int fE8;               // +0xE8: effect handle
    int fEC;               // +0xEC
    char pad2[0xC];
    char fFC[8];           // +0xFC: bit set of 0x41
    int f104;              // +0x104
    int f108;              // +0x108
    int f10C;              // +0x10C
    int f110;              // +0x110
    unsigned int f114;     // +0x114: next refresh time
    unsigned int f118;     // +0x118
    unsigned int f11C;     // +0x11C
    unsigned int f120;     // +0x120: next best-target pick
    unsigned int f124;     // +0x124
    unsigned int f128;     // +0x128
    unsigned int f12C;     // +0x12C
    unsigned int f130;     // +0x130
};

extern char lbl_80593BE8[];

extern "C" {
unsigned int fn_8042EFF8(void *g);
int fn_8015EA18(unsigned int n);
void fn_80461828(void *p, unsigned int count);
void fn_804618B0(void *p);
void fn_8014DE58(Self *self);
void fn_8014DEB8(Self *self);
void fn_8014FAF4(Self *self);
void fn_8014FD94(Self *self);
Ent *fn_8014F8BC(Self *self);
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

extern "C" void fn_8014DDD4(register Self *self, void *ai)
{
    self->f0 = ai;
    fn_80461828(self->fFC, 0x41);
    fn_8014DE58(self);
    fn_8014DEB8(self);
}

extern "C" void fn_8014DE30(register Self *self)
{
    self->f0 = 0;
}

extern "C" void fn_8014DE58(register Self *self)
{
    self->fE8 = 0;
    self->fEC = 0;
    self->fE4 = 0;
    self->fD8 = 0;
    self->fDC = 0;
    self->fE0 = 0;
    self->f4 = 0;
    self->f48 = 0;
}

extern "C" void fn_8014DEB8(register Self *self)
{
    self->f114 = fn_8042EFF8(lbl_80593BE8) + 3000 + fn_8015EA18(250);
    self->f118 = fn_8042EFF8(lbl_80593BE8) + 3000 + fn_8015EA18(250);
    self->f11C = fn_8042EFF8(lbl_80593BE8) + 1000 + fn_8015EA18(250);
    self->f124 = fn_8042EFF8(lbl_80593BE8) + 1000 + fn_8015EA18(250);
    self->f128 = fn_8042EFF8(lbl_80593BE8) + 1000 + fn_8015EA18(250);
    self->f12C = fn_8042EFF8(lbl_80593BE8) + 1000 + fn_8015EA18(250);
    self->f130 = fn_8042EFF8(lbl_80593BE8) + 500 + fn_8015EA18(250);
    self->f120 = 0;
    self->fD0 = 0;
    self->fD4 = 0;
    self->f104 = 0;
    self->f108 = 0;
    self->f10C = 0;
    self->f110 = 0;
    fn_804618B0(self->fFC);
}

extern "C" void fn_8014E044(register Self *self)
{
    if (fn_8042EFF8(lbl_80593BE8) > self->f11C) {
        fn_8014FAF4(self);
        fn_8014FD94(self);
        self->f11C = fn_8042EFF8(lbl_80593BE8) + 1000;
    }
}

extern "C" void fn_8014E0B8(register Self *self)
{
    if (fn_8042EFF8(lbl_80593BE8) > self->f120) {
        Ent *p = fn_8014F8BC(self);
        if (p)
            self->fCC = fn_800B13D8(*p);
        else
            self->fCC = 0;
        self->f120 = fn_8042EFF8(lbl_80593BE8) + 1000;
    }
}

extern "C" void fn_8014E154(register Self *self)
{
    if (fn_8042EFF8(lbl_80593BE8) > self->f124) {
        self->fD8 = self->fCC;
        self->f124 = fn_8042EFF8(lbl_80593BE8) + 1000;
    }
}

extern "C" void fn_8014E1C0(register Self *self)
{
    if (fn_8042EFF8(lbl_80593BE8) > self->f128)
        self->f128 = fn_8042EFF8(lbl_80593BE8) + 1000;
}

extern "C" void fn_8014E224(register Self *self)
{
    if (fn_8042EFF8(lbl_80593BE8) > self->f12C)
        self->f12C = fn_8042EFF8(lbl_80593BE8) + 1000;
}

extern "C" void fn_8014E288(register Self *self)
{
    if (fn_8042EFF8(lbl_80593BE8) > self->f114) {
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

extern "C" void fn_8014E4FC(register Self *self)
{
    if (fn_8042EFF8(lbl_80593BE8) > self->f118) {
        fn_80461D04(self->f0, 13);
        Vector v;
        if (!fn_8015F6CC(self->f0, &v))
            fn_8042DC84(&v, fn_800B1750(*fn_80442080(self->f0)));
        float hi = 4.0f;
        float lo = 0.5f;
        PEnt *p = fn_8015F7A4(fn_80442080(self->f0), hi, 1, &v, lo);
        if (p)
            self->fEC = fn_800B13D8(*p);
        self->f118 = fn_8042EFF8(lbl_80593BE8) + 3000;
    }
    PEnt *a = fn_80442080(self->f0);
    void *b = fn_8044203C(self->f0);
    if (self->fEC)
        fn_80461CC0(self->f0, 13);
}
