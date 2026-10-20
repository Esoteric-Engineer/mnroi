// A PLAYER state's lunge step: picks a target and steers the entity toward it (tuning fields 0x2E-0x31, 0x6E-0x71).

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
    char pad0[0x2C];
    unsigned int f2C; // +0x2C
    char pad1[0x168];
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28(int a); // vtable +0xE8
};

struct PEnt : Ent { // matching_notes 44
    int x;
};

struct Target {
    char pad0[0x198];
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5(Vector *out, int a); // vtable +0x30
};

struct Factors;

extern char lbl_80593DD0[];

extern "C" {
PEnt *Entity_GetActor(void *self);
int fn_800CDA20(void *self);
Ent *fn_800CD9B0(void *self);
int fn_800B0CC0(Ent *c);
Ent *fn_800B1478(Ent *c);
int fn_800A4468(Ent *p);
int fn_800CCA88(void *self);
float fn_800B1884(Ent &actor, int id);
void fn_800A4678(Ent *c, int v);
Target *fn_800E9630(void *self, float f, Vector *v, void *a, void *b);
void fn_8006645C(void *self, int v);
void fn_800B0738(Ent *c);
int fn_800B13D8(Ent &actor);
void fn_8009AD04(Ent *c, int v);
void fn_8009AD58(Ent *c, int v);
int fn_800B1668(Ent &c);
void fn_80065F28(Ent *c, int v);
Factors *fn_8009AD80(Ent &actor);
int fn_801A5104(void *f, int kind, int a, void *vec, int e);
int fn_800F92DC(void *self, Ent *c, Vector *a, Vector *b);
void *fn_800B24AC(Ent *c);
void *fn_80318E84(void *p);
void fn_80434BA4(Vector *out, void *v);
void fn_80429038(Vector *out, Vector *a, Vector *b);
float fn_8042EC54(Vector *v);
int fn_801BCB08(Vector *a, Vector *b, float f, float g, float *f30, float *f34);
float *fn_8042FB28(void *p);
float fn_8042FE6C(Vector *v);
void fn_801BEBBC(Vector *out, void *m, Vector *in);
void fn_80435530(Vector *v, float s);
int fn_800B0C58(void *node);
void *fn_800B14A0(void *node);
void *fn_80085928(void *p);
void fn_800B9CE8(void *a, int b, void *c, void *d);
Vector *fn_800B1750(Ent &actor);
void fn_8042DC84(Vector *dst, void *src);
void fn_8042F76C(Vector *v);
void fn_8043CEE4(Vector *out, Vector *v);
float fn_8042EBF4(Vector *a, Vector *b);
void fn_80428FA8(Vector *v, float x, float y, float z);
void fn_80065CB0(Ent *c, Vector *v);
void fn_800CDD84(void *self, int a, int b);
int fn_8010CDCC(Ent &self, int event, Ent *target, int a3, int a4, int a5, int a6);
}

extern "C" int fn_800F97F4(register void *self, int a4, int kind, int a6, int a7)
{
    switch (kind) {
    case 4: {
        if (!fn_800CDA20(self) || !fn_800B0CC0(fn_800CD9B0(self)))
            return 0;
        Ent &c = *fn_800CD9B0(self);
        int base = fn_800B0CC0(&c) ? fn_800A4468(fn_800B1478(&c)) : 0;
        Vector v20;
        Vector v30;
        float f40;
        Target *p;
        float f48;
        if (fn_800CCA88(self)) {
            f40 = fn_800B1884(*Entity_GetActor(self), base + 0x31);
            f48 = fn_800B1884(*Entity_GetActor(self), base + 0x71);
        } else {
            f40 = fn_800B1884(*Entity_GetActor(self), base + 0x2E);
            f48 = fn_800B1884(*Entity_GetActor(self), base + 0x6E);
        }
        fn_800A4678(&c, 0);
        p = fn_800E9630(self, f40, 0, 0, 0);
        fn_8006645C(&c, 0);
        fn_800B0738(&c);
        fn_8009AD04(&c, fn_800B13D8(*Entity_GetActor(self)));
        fn_8009AD58(&c, fn_800B13D8(*Entity_GetActor(self)));
        c.f2C = c.f2C & 0x7FFFFFFF;
        c.s28(0);
        fn_80065F28(&c, fn_800B1668(c));
        int f4c = 0;
        Vector v50;
        {
            Vector v60;
            unsigned short s70 = fn_800B0CC0(&c) ? fn_800A4468(fn_800B1478(&c)) : 0;
            fn_801A5104(fn_8009AD80(*Entity_GetActor(self)), 0x24, s70, &v60, fn_800B1668(*Entity_GetActor(self)));
            f4c = fn_800F92DC(self, &c, &v60, &v50);
        }
        fn_80434BA4(&v20, fn_80318E84(fn_800B24AC(&c)));
        if (p) {
            Vector v60;
            Vector v78;
            float f88;
            float f8c;
            float f90;
            float f94;
            p->s5(&v60, 0);
            fn_80429038(&v78, &v60, &v20);
            f94 = fn_8042EC54(&v78);
            if (!fn_801BCB08(&v20, &v60, f48, 20.0f, &f8c, &f90))
                goto steer;
            f88 = f8c;
            if (f88 < -50.0f)
                goto steer;
            {
                Vector v98;
                *fn_8042FB28(&v98) = f88;
                fn_8042FB28(&v98)[2] = fn_8042FE6C(&v78);
                fn_8042FB28(&v98)[1] = 0.0f;
                fn_801BEBBC(&v30, lbl_80593DD0, &v98);
                fn_80435530(&v30, f48);
                if (fn_800B0C58(p) && fn_80085928(fn_800B14A0(p)))
                    fn_800B9CE8(fn_80085928(fn_800B14A0(p)), 2, &c, Entity_GetActor(self));
            }
        } else {
        steer:
            fn_8042DC84(&v30, fn_800B1750(*Entity_GetActor(self)));
            v30.z += 0.2f;
            fn_8042F76C(&v30);
            fn_80435530(&v30, f48);
        }
        if (f4c) {
            Vector v98;
            fn_8043CEE4(&v98, &v30);
            if (fn_8042EBF4(&v98, &v50) < -0.2f)
                fn_80428FA8(&v30, 0.0f, 0.0f, 5.0f);
        }
        fn_80065CB0(&c, &v30);
        fn_800CDD84(self, fn_800B13D8(c), 1000);
        fn_8010CDCC(*Entity_GetActor(self), 0x22, &c, 0, 0, 0, 0);
        break;
    }
    default:
        return 0;
    }
    return 1;
}
