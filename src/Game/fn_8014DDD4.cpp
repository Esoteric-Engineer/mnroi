// The AIObject+0xD0 target list: init, reset, timers, the throttled steps and the update (docs/ai.md row 11).
// .rodata 0x8049B520-0x8049B534 is fn_8014E288's and fn_8014E4FC's pool, 0x8049B534-0x8049B548 fn_8014E648's,
// 0x8049B548-0x8049B550 fn_8014F8BC's, 0x8049B560-0x8049B568 fn_8014FAF4's, 0x8049B568-0x8049B570 fn_8014FD94's.

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
    int f4;                // +0x4: count of f8
    int f8[16];            // +0x8: nearby actor handles
    int f48;               // +0x48: count of f4C
    int f4C[16];           // +0x4C: visible actor handles
    float f8C[16];         // +0x8C: their query distances (guess)
    int fCC;               // +0xCC: best target handle
    unsigned int fD0;      // +0xD0
    unsigned int fD4;      // +0xD4
    int fD8;               // +0xD8
    int fDC;               // +0xDC
    int fE0;               // +0xE0
    int fE4;               // +0xE4: target handle
    int fE8;               // +0xE8: effect handle
    int fEC;               // +0xEC
    int fF0;               // +0xF0
    int fF4;               // +0xF4
    int fF8;               // +0xF8
    char fFC[8];           // +0xFC: bit set of 0x41
    int f104;              // +0x104
    unsigned int f108;     // +0x108
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

struct Slot {
    char pad0[0x20];
    float f20;             // +0x20: distance (guess)
    char pad24[0xC];
};

struct Query { // as in Game/fn_800F43D4.cpp
    char pad0[0x40];
    Slot slot[0x80];    // +0x40
    unsigned int count; // +0x1840
    char pad1844[0xC];
};

struct Act : Ent {
    char pad4[0x28];
    unsigned int f2C;      // +0x2C: bit 0x800 skips the actor
    char pad30[0x20];
    char f50[0x10];        // +0x50
    char f60[0x18];        // +0x60
    char f78[0x40];        // +0x78: transform
};

struct Ctrl : Ent {
    char pad4[0x3AC - 0x4];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void s40(); virtual void s41();
    virtual int s42(); // +0x158
};

struct Sub : Ent { // matching_notes 50
    int x;
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
PEnt *AI_GetEntity(void *a);
void *AI_GetActor(void *a);
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
void fn_8014E044(Self *self);
void fn_8014E0B8(Self *self);
void fn_8014E154(Self *self);
void fn_8014E1C0(Self *self);
void fn_8014E224(Self *self);
void fn_8014E288(Self *self);
void fn_8014E4FC(Self *self);
void *fn_8013726C(void *ai);
void *fn_80147ACC(void *reg, PEnt *e);
int fn_801464E4(void *rec, void *pos);
float fn_804290F8(void *a, void *b);
int fn_80463994(void *ai, int bit);
int fn_800B0C58(Ent &e);
void *fn_800B14A0(Ent &e);
Ctrl *fn_80085954(void *e);
int fn_800CC9D8(Ent &e);
int fn_800CCA58(Ent &e);
int fn_800CCC28(Ent &e);
int fn_800CD064(Ent &e);
int fn_800CD0EC(Ent &e);
int fn_800CCAE8(Ent &e);
int fn_800CCE00(Ent &e);
int fn_800CD014(Ent &e);
int fn_80086B6C(void *e);
unsigned int fn_804324EC(void *g);
int fn_8015F008(void *ai);
int fn_8015EE34(void *ai, Ent *e);
int fn_804622B4(void *list);
void *fn_804622FC(void *list, int i);
int fn_80146A88(void *o, Vector *a, Vector *b, Vector *hit);
Sub *fn_8044203C_S(void *ai) __asm__("AI_GetActor");
int fn_80462880(void *ai);
void fn_804639E4(void *ai, int v);
int fn_800861EC(void *e);
int fn_801368B8(void *ai);
Vector *fn_800B17A8(Ent &e);
void fn_8042D80C(Vector *dst, Vector *src);
int fn_8015E2FC(void *ai, Vector *to, float r, int *hit, float height);
void fn_8044243C(void *set, int bit);
int fn_80442508(void *set, int bit);
int fn_800B1258(Ent &e);
int fn_800B0CC0(Ent &e);
void *fn_800B1478(Ent &e);
int fn_800A4538(void *p);
void *AI_GetMover(void *ai);
float fn_8046393C(void *m);
int fn_800CC8EC(Ent &e);
int fn_800CCB38(Ent &e);
int fn_800CCEEC(Ent &e);
int fn_800CCE78(Ent &e);
void *fn_80461DD4(void *ai);
int fn_800CDA20(Ent &e);
Ent *fn_800CD9B0(Ent &e);
int fn_800A4130(void *p);
int fn_8013338C(void *e);
int fn_800B0C1C(Ent &e);
int AI_GetBrain(void *ai);
int fn_80151AF8(int brain, int id);
int fn_800CCF60(Ent &e);
int fn_8013379C(void *ai, int a);
void fn_80135668(void *ai, int a);
int fn_8014AB90(void *m);
int fn_800860CC(void *e);
int fn_8014ACA0(void *m);
int fn_80463968(void *ai);
Ent *fn_80462530(Self *self);
Ent *fn_804638B4(Self *self);
Ent *fn_804638F8(Self *self);
void fn_801501AC(Self *self, Ent *actor);
void fn_8004E9C8(Query *q);
void fn_80434C88(Query *q);
void fn_80434CDC(Query *q, int bit);
void fn_80434D18(Query *q, void *ignore);
void fn_8004E4B4(Query *q, void *pos, float r, void *world);
void fn_8004E430(Query *q);
void fn_800B16D8(Ent &actor, Vector *out);
float fn_800B2620(Ent &actor);
Ent *fn_80434C2C(Slot *s);
Act *fn_80434C2C_A(Slot *s) __asm__("fn_80434C2C");
void *fn_800B1CC8(Ent &actor);
int fn_80085EEC(void *actor);
int fn_8015F278(void *a, Ent *e);
int fn_800B244C(Ent &e);
int fn_800B11F8(Ent &e);
int fn_800B1D48(Ent &e);
int fn_800B1318(Ent &e);
void fn_80436100(Vector *v, void *m);
int fn_8015ED50(void *ai, void *pos);
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
            if (fn_8015E8A8(self->f0, fn_800B1724(*fn_80134870(self->f0))) > fn_800B1884(*AI_GetEntity(self->f0), 216))
                hi = 20.0f;
        }
        Vector v;
        if (!fn_8015F6CC(self->f0, &v))
            fn_8042DC84(&v, fn_800B1750(*AI_GetEntity(self->f0)));
        PEnt *p = fn_8015F7A4(AI_GetEntity(self->f0), hi, 2, &v, lo);
        if (p)
            self->fE8 = fn_800B13D8(*p);
        self->f114 = fn_8042EFF8(lbl_80593BE8) + 3000;
    }
    PEnt *a = AI_GetEntity(self->f0);
    void *b = AI_GetActor(self->f0);
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
            fn_8042DC84(&v, fn_800B1750(*AI_GetEntity(self->f0)));
        float hi = 4.0f;
        float lo = 0.5f;
        PEnt *p = fn_8015F7A4(AI_GetEntity(self->f0), hi, 1, &v, lo);
        if (p)
            self->fEC = fn_800B13D8(*p);
        self->f118 = fn_8042EFF8(lbl_80593BE8) + 3000;
    }
    PEnt *a = AI_GetEntity(self->f0);
    void *b = AI_GetActor(self->f0);
    if (self->fEC)
        fn_80461CC0(self->f0, 13);
}

// Sets the AIObject+0xC condition bits from the target, the encounter and the actor's state.
extern "C" void fn_8014E648(register Self *self)
{
    fn_8014E154(self);
    fn_8014E1C0(self);
    fn_8014E224(self);
    Ent *target = fn_80134870(self->f0);
    if (!target)
        target = fn_80134870(self->f0);
    void *rec = fn_80147ACC(fn_8013726C(self->f0), AI_GetEntity(self->f0));
    if (rec) {
        fn_80461CC0(self->f0, 3);
        if (!fn_801464E4(rec, fn_800B1724(*AI_GetEntity(self->f0))))
            fn_80461CC0(self->f0, 4);
    }
    float d;
    if (target) {
        fn_80461CC0(self->f0, 2);
        if (fn_80463994(self->f0, 0)) {
            d = fn_804290F8(fn_800B1724(*target), fn_800B1724(*AI_GetEntity(self->f0)));
            if (d > fn_800B1884(*AI_GetEntity(self->f0), 213))
                fn_80461CC0(self->f0, 10);
            else if (d > fn_800B1884(*AI_GetEntity(self->f0), 212))
                fn_80461CC0(self->f0, 9);
            else if (d > fn_800B1884(*AI_GetEntity(self->f0), 211))
                fn_80461CC0(self->f0, 8);
            else if (d > fn_800B1884(*AI_GetEntity(self->f0), 210))
                fn_80461CC0(self->f0, 7);
            else if (d > fn_800B1884(*AI_GetEntity(self->f0), 209))
                fn_80461CC0(self->f0, 6);
            else
                fn_80461CC0(self->f0, 5);
        }
        if (fn_80463994(self->f0, 5)) {
            if (fn_800B0C58(*target)) {
                Ctrl *ctrl = fn_80085954(fn_800B14A0(*target));
                if (ctrl) {
                    if (ctrl->s42())
                        fn_80461CC0(self->f0, 0x25);
                    if (fn_800CC9D8(*ctrl))
                        fn_80461CC0(self->f0, 0x26);
                    if (fn_800CCA58(*ctrl))
                        fn_80461CC0(self->f0, 0x27);
                    if (fn_800CCC28(*ctrl))
                        fn_80461CC0(self->f0, 0x28);
                    if (fn_800CD064(*ctrl) || fn_800CD0EC(*ctrl))
                        fn_80461CC0(self->f0, 0x29);
                    if (fn_800CCAE8(*ctrl))
                        fn_80461CC0(self->f0, 0x2A);
                    if (fn_800CCE00(*ctrl))
                        fn_80461CC0(self->f0, 0x2C);
                    if (fn_800CD014(*ctrl))
                        fn_80461CC0(self->f0, 0x2D);
                    if (fn_80086B6C(fn_800B14A0(*target)))
                        fn_80461CC0(self->f0, 0x30);
                    if (self->f104 != fn_800B13D8(*target)) {
                        self->f104 = fn_800B13D8(*target);
                        self->f108 = 0;
                        self->f110 = fn_80086B6C(fn_800B14A0(*target));
                    }
                    if (self->f108) {
                        if (self->f108 < fn_804324EC(lbl_80593BE8))
                            self->f108 = 0;
                        else
                            self->f108 -= fn_804324EC(lbl_80593BE8);
                    }
                    self->f10C = self->f110;
                    if (fn_80086B6C(fn_800B14A0(*target)))
                        self->f110 = 1;
                    else
                        self->f110 = 0;
                    if (!self->f10C && self->f110)
                        self->f108 = 200;
                    if (self->f108)
                        fn_80461CC0(self->f0, 0x31);
                }
            }
            if (rec && !fn_801464E4(rec, fn_800B1724(*target)))
                fn_80461CC0(self->f0, 0x2B);
            if (!fn_8015F008(self->f0) && fn_8015EE34(self->f0, target)) {
                if (!self->fD0 && self->fD4 > 2000)
                    fn_80461CC0(self->f0, 0x2E);
                self->fD0 += fn_804324EC(lbl_80593BE8);
                self->fD4 = 0;
            } else {
                if (!self->fD4 && self->fD0 > 2000)
                    fn_80461CC0(self->f0, 0x2F);
                self->fD4 += fn_804324EC(lbl_80593BE8);
                self->fD0 = 0;
            }
        }
        for (int i = 0; i < fn_804622B4(fn_8013726C(self->f0)); i++) {
            void *o = fn_804622FC(fn_8013726C(self->f0), i);
            if (!o)
                continue;
            Vector a;
            Vector b;
            Vector c;
            fn_8042DC84(&a, fn_800B1724(*AI_GetEntity(self->f0)));
            fn_8042DC84(&b, fn_800B1724(*target));
            a.z = 0.0f;
            b.z = 0.0f;
            if (fn_80146A88(o, &a, &b, &c)) {
                c.z = a.z;
                Vector e;
                d = fn_804290F8(&c, &a);
                if (d < 10.0f)
                    fn_80461CC0(self->f0, 0x40);
                break;
            }
        }
    }
    if (fn_80463994(self->f0, 1))
        fn_8014E288(self);
    else
        self->fE8 = 0;
    if (fn_80463994(self->f0, 2))
        fn_8014E4FC(self);
    else
        self->fEC = 0;
    if (fn_80463994(self->f0, 3)) {
        if (fn_800CCC28(*fn_8044203C_S(self->f0))) {
            fn_80461CC0(self->f0, 15);
            if (!fn_80462880(self->f0))
                fn_804639E4(self->f0, fn_8042EFF8(lbl_80593BE8));
        } else if (fn_80462880(self->f0)) {
            fn_804639E4(self->f0, 0);
        }
    }
    if (fn_800CCA58(*fn_8044203C_S(self->f0)))
        fn_80461CC0(self->f0, 0x1B);
    if (fn_800861EC(AI_GetEntity(self->f0)) || fn_801368B8(self->f0))
        fn_80461CC0(self->f0, 0x1A);
    if (fn_8042EFF8(lbl_80593BE8) > self->f130) {
        self->f130 = fn_8042EFF8(lbl_80593BE8) + fn_8015EA18(500);
        self->fF0 = 0;
        self->fF4 = 0;
        self->fF8 = 0;
        Vector v;
        Vector *pos = fn_800B1750(*AI_GetEntity(self->f0));
        Vector *top = fn_800B17A8(*AI_GetEntity(self->f0));
        fn_8042D80C(&v, top);
        d = 2.0f;
        fn_804618B0(self->fFC);
        int hit;
        Ent *e;
        if (fn_8015E2FC(self->f0, pos, d, &hit, 0.0f)) {
            fn_8044243C(self->fFC, 0x14);
            e = fn_800ACFA8(hit);
            if (e && fn_800B1258(*e) && fn_800B0CC0(*e) && !fn_800A4538(fn_800B1478(*e))) {
                fn_8044243C(self->fFC, 0x18);
                self->fF0 = hit;
            }
        }
        if (fn_8015E2FC(self->f0, top, d, &hit, 0.0f)) {
            fn_8044243C(self->fFC, 0x13);
            e = fn_800ACFA8(hit);
            if (e && fn_800B1258(*e) && fn_800B0CC0(*e) && !fn_800A4538(fn_800B1478(*e))) {
                fn_8044243C(self->fFC, 0x17);
                self->fF4 = hit;
            }
        }
        if (fn_8015E2FC(self->f0, &v, d, &hit, 0.0f)) {
            fn_8044243C(self->fFC, 0x12);
            e = fn_800ACFA8(hit);
            if (e && fn_800B1258(*e) && fn_800B0CC0(*e) && !fn_800A4538(fn_800B1478(*e))) {
                fn_8044243C(self->fFC, 0x16);
                self->fF8 = hit;
            }
        }
    }
    if (fn_80442508(self->fFC, 0x14))
        fn_80461CC0(self->f0, 0x14);
    if (fn_80442508(self->fFC, 0x13))
        fn_80461CC0(self->f0, 0x13);
    if (fn_80442508(self->fFC, 0x12))
        fn_80461CC0(self->f0, 0x12);
    if (fn_80442508(self->fFC, 0x18))
        fn_80461CC0(self->f0, 0x18);
    if (fn_80442508(self->fFC, 0x17))
        fn_80461CC0(self->f0, 0x17);
    if (fn_80442508(self->fFC, 0x16))
        fn_80461CC0(self->f0, 0x16);
    fn_8014E0B8(self);
    d = fn_8046393C(AI_GetMover(self->f0));
    if (d > 2.0f) {
        fn_80461CC0(self->f0, 0x34);
        fn_80461CC0(self->f0, 0x33);
    } else if (d > 1.0f) {
        fn_80461CC0(self->f0, 0x33);
        int hit;
        if (fn_8015E2FC(self->f0, fn_800B1750(*AI_GetEntity(self->f0)), 1.5f, &hit, 0.0f))
            fn_80461CC0(self->f0, 0x34);
    }
    if (fn_800CC8EC(*fn_8044203C_S(self->f0)))
        fn_80461CC0(self->f0, 0x32);
    if (fn_800CCB38(*fn_8044203C_S(self->f0)))
        fn_80461CC0(self->f0, 0x20);
    if (fn_800CCEEC(*fn_8044203C_S(self->f0))
        || (fn_80442508(fn_80461DD4(self->f0), 7) && !fn_80442508(fn_80461DD4(self->f0), 8)))
        fn_80461CC0(self->f0, 0x1E);
    if (fn_800CCE78(*fn_8044203C_S(self->f0))
        || (fn_80442508(fn_80461DD4(self->f0), 7) && fn_80442508(fn_80461DD4(self->f0), 8)))
        fn_80461CC0(self->f0, 0x1F);
    if (fn_800CDA20(*fn_8044203C_S(self->f0))) {
        if (fn_800A4130(fn_800B1478(*fn_800CD9B0(*fn_8044203C_S(self->f0)))))
            fn_80461CC0(self->f0, 0xE);
        else
            fn_80461CC0(self->f0, 0xC);
    }
    if (fn_80463994(self->f0, 6))
        fn_8014E044(self);
    if (fn_8013338C(AI_GetEntity(self->f0)) || (fn_80134870(self->f0) && !fn_800B0C1C(*fn_80134870(self->f0))))
        fn_80461CC0(self->f0, 0x35);
    if (fn_80151AF8(AI_GetBrain(self->f0), 6))
        fn_80461CC0(self->f0, 0x37);
    if (fn_80151AF8(AI_GetBrain(self->f0), 14))
        fn_80461CC0(self->f0, 0x38);
    if (fn_800CCF60(*fn_8044203C_S(self->f0)))
        fn_80461CC0(self->f0, 0x24);
    if (fn_8013379C(self->f0, 0)) {
        fn_80461CC0(self->f0, 0x3C);
        fn_80135668(self->f0, 1);
    }
    if (fn_8014AB90(AI_GetMover(self->f0)))
        fn_80461CC0(self->f0, 0x3D);
    if (fn_800860CC(AI_GetEntity(self->f0)) && fn_8014ACA0(AI_GetMover(self->f0)))
        fn_80461CC0(self->f0, 0x3E);
    if (fn_80463968(self->f0))
        fn_80461CC0(self->f0, 0x3F);
}

extern "C" void fn_8014F7B0(register Self *self, int mode)
{
    Ent *e = 0;
    switch (mode) {
    case 0: {
        Ent *best = fn_8014F8BC(self);
        if (best)
            self->fCC = fn_800B13D8(*best);
        else
            self->fCC = 0;
        e = fn_80462530(self);
        break;
    }
    case 1:
        e = fn_804638B4(self);
        break;
    case 2:
        e = fn_804638F8(self);
        break;
    case 3:
        e = fn_80462530(self);
        break;
    }
    fn_801501AC(self, e);
}

extern "C" Ent *fn_8014F8BC(register Self *self)
{
    Query q;
    fn_8004E9C8(&q);
    fn_80434C88(&q);
    fn_80434CDC(&q, 7);
    fn_80434D18(&q, AI_GetEntity(self->f0));
    fn_8004E4B4(&q, fn_800B1724(*AI_GetEntity(self->f0)), 200.0f, fn_800B1CC8(*AI_GetEntity(self->f0)));
    Slot *s;
    Ent *e;
    float bestDist = 3.4028235e38f;
    Ent *best = 0;
    unsigned int i;
    for (i = 0; i < q.count; i++) {
        s = &q.slot[i];
        if (s == 0)
            continue;
        e = fn_80434C2C(s);
        if (e == 0)
            continue;
        if (fn_800B0C58(*e) && fn_80085EEC(fn_800B14A0(*e)))
            continue;
        if (fn_8015F278(AI_GetEntity(self->f0), e))
            continue;
        float dist = fn_804290F8(fn_800B1724(*AI_GetEntity(self->f0)), fn_800B1724(*e));
        if (dist < bestDist) {
            bestDist = dist;
            best = e;
        }
    }
    if (best == 0)
        return 0;
    if (!fn_800B0C58(*best))
        return 0;
    return (Ent *)fn_800B14A0(*best);
}

// 0x8049B550-0x8049B560: a dead-stripped function's pool.
__asm__(".section .rodata\n\t.float 10.0\n\t.float 2.0\n\t.long 0x7F7FFFFF\n\t.float 0.0\n\t.text");
inline Ent *sn_return_decl_e(Ent *e) { return e; } // sets the return flag: run B starts here

extern "C" void fn_8014FAF4(register Self *self)
{
    self->f4 = 0;
    Query q;
    fn_8004E9C8(&q);
    PEnt *a = AI_GetEntity(self->f0);
    fn_80434C88(&q);
    fn_80434CDC(&q, 0);
    fn_80434CDC(&q, 7);
    fn_80434D18(&q, a);
    fn_8004E4B4(&q, fn_800B1724(*a), 10.0f, fn_800B1CC8(*a));
    fn_8004E430(&q);
    Slot *s;
    Ent *e;
    Vector v;
    unsigned int i;
    void *p;
    fn_800B16D8(*a, &v);
    v.z += fn_800B2620(*a) / 2.0f;
    for (i = 0; i < q.count; i++) {
        if (i <= 15) {
            s = &q.slot[i];
            e = fn_80434C2C(s);
            if (e == 0)
                continue;
            if (fn_800B0C58(*e)) {
                p = fn_800B14A0(*e);
                self->f8[self->f4++] = fn_800B13D8(*(Ent *)p);
            }
        }
    }
}

extern "C" int fn_8014FCAC(register Self *self)
{
    return self->f4;
}

extern "C" void *fn_8014FCD8(register Self *self, int i)
{
    if (i < 0 && i >= self->f4)
        return 0;
    int h = self->f8[i];
    if (h == 0)
        return 0;
    Ent *e = fn_800ACFA8(h);
    if (e)
        return fn_800B14A0(*e);
    return 0;
}

extern "C" void fn_8014FD94(register Self *self)
{
    self->f48 = 0;
    Query q;
    fn_8004E9C8(&q);
    PEnt *a = AI_GetEntity(self->f0);
    fn_80434C88(&q);
    fn_80434CDC(&q, 2);
    fn_80434CDC(&q, 8);
    fn_8004E4B4(&q, fn_800B1724(*a), 10.0f, fn_800B1CC8(*a));
    fn_8004E430(&q);
    Slot *s;
    Act *e;
    Vector v;
    unsigned int i;
    fn_800B16D8(*a, &v);
    v.z += fn_800B2620(*a) / 2.0f;
    for (i = 0; i < q.count; i++) {
        if (i <= 15) {
            s = &q.slot[i];
            e = fn_80434C2C_A(s);
            if (e == 0)
                continue;
            if (!fn_800B0CC0(*e))
                continue;
            if (fn_800B244C(*e))
                continue;
            if (fn_800B11F8(*e))
                continue;
            if (e->f2C & 0x800)
                continue;
            if (!fn_800B1D48(*e))
                continue;
            if (!fn_800B1318(*e))
                continue;
            Vector lo;
            Vector hi;
            Vector pos;
            fn_8042DC84(&pos, fn_800B1724(*e));
            fn_8042DC84(&lo, e->f50);
            fn_8042DC84(&hi, e->f60);
            fn_80436100(&lo, e->f78);
            fn_80436100(&hi, e->f78);
            if (!fn_8015ED50(self->f0, fn_800B1724(*e)) && !fn_8015ED50(self->f0, &lo)
                && !fn_8015ED50(self->f0, &hi))
                continue;
            self->f4C[self->f48] = fn_800B13D8(*e);
            self->f8C[self->f48] = s->f20;
            self->f48++;
        }
    }
}
