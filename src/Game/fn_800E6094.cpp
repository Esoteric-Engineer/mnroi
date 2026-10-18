// A PLAYER state's steering step: finds a target and kicks the entity toward it (tuning fields 0x74-0x7D); docs/versus.md row 20.

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

class Vec4
{
public:
    float x;
    float y;
    float z;
    float w;
    Vec4(float a, float b, float c, float d);
} __attribute__((aligned(8)));

struct Ent {
    int pad;
};

struct PEnt : Ent { // matching_notes 44
    int x;
};

struct Other {
    char pad0[0x2D4];
    int f2D4;
    int f2D8;
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

extern char lbl_8064AA80[];
extern char lbl_80593DD0[];

extern "C" {
PEnt *Entity_GetActor(void *self);
int fn_800A4468(void *p);
int fn_800E5F04(void *self, void *other);
int fn_800CCA88(void *self);
float fn_800B1884(Ent &actor, int id);
void *fn_803A20D8(char *tbl, int a, void *self, int b, int c, int d, int e, float f);
void fn_80393938(void *self, void *c, int flag);
int fn_800664C0(void *self);
void fn_8006645C(void *self, int v);
void fn_800A2B3C(void *self, int a, int b, int c, int d);
Vector *fn_800B1750(Ent &actor);
Target *fn_800E9630(void *self, float f, Vector *v, void *a, void *b);
void *fn_800B24AC(void *self);
void *fn_80318E84(void *p);
void fn_80434BA4(Vector *out, void *v);
void fn_80429038(Vector *out, Vector *a, void *b);
void fn_8042F76C(Vector *v);
int fn_801BCB08(Vector *a, Vector *b, float f, float g, float *f30, float *f34);
float *fn_8042FB28(void *p);
float fn_8042FE6C(Vector *v);
void fn_801BEBBC(Vector *out, void *m, Vector *in);
void fn_80435530(Vector *v, float s);
void fn_80065CB0(void *self, Vector *v);
int fn_800B0C58(void *node);
void *fn_800B14A0(void *node);
void *fn_80085928(void *p);
void fn_800B9CE8(void *a, int b, void *c, void *d);
void fn_8042DC84(Vector *dst, void *src);
int fn_80171F8C(void);
void fn_803190C4(void *a, Vector *v);
int fn_800B13D8(void *self);
void fn_800CDD84(void *self, int a, int b);
}

extern "C" int fn_800E6094(register void *self, Other *other)
{
    int base = fn_800A4468(other);
    float f10;
    float f14;
    Target *p = 0;
    int ret = 0;
    if (!fn_800E5F04(self, other))
        return 0;
    if (fn_800CCA88(self)) {
        f14 = fn_800B1884(*Entity_GetActor(self), base + 0x7D);
        f10 = fn_800B1884(*Entity_GetActor(self), base + 0x7A);
    } else {
        f10 = fn_800B1884(*Entity_GetActor(self), base + 0x74);
        f14 = fn_800B1884(*Entity_GetActor(self), base + 0x77);
    }
    if (other->f2D4) {
        fn_80393938(other, fn_803A20D8(lbl_8064AA80, 0, other, 0, other->f2D4, 0, 0, 0.0f), 1);
    }
    if (fn_800664C0(other) && other->f2D8) {
        fn_80393938(other, fn_803A20D8(lbl_8064AA80, 0, other, 0, other->f2D8, 0, 0, 0.0f), 1);
    }
    fn_8006645C(other, 0);
    fn_800A2B3C(other, 1, 0, 0, 0);
    if (f10 != 0.0f)
        p = fn_800E9630(self, f10, fn_800B1750(*Entity_GetActor(self)), other, other);
    if (p) {
        Vector v20;
        float f30;
        float f34;
        Vector v38;
        Vector v48;
        Vector v58;
        float f68;
        fn_80434BA4(&v20, fn_80318E84(fn_800B24AC(other)));
        p->s5(&v38, 0);
        fn_80429038(&v58, &v38, &v20);
        fn_8042F76C(&v58);
        if (!fn_801BCB08(&v20, &v38, f14, 20.0f, &f30, &f34))
            goto steer;
        f68 = f34;
        if (f34 > 70.0f)
            f68 = f30;
        if (f68 < -50.0f)
            goto steer;
        *fn_8042FB28(&v48) = f68;
        fn_8042FB28(&v48)[2] = fn_8042FE6C(&v58);
        fn_8042FB28(&v48)[1] = 0.0f;
        {
            Vector v70;
            fn_801BEBBC(&v70, lbl_80593DD0, &v48);
            fn_80435530(&v70, f14);
            fn_80065CB0(other, &v70);
        }
        ret = 1;
        if (fn_800B0C58(p) && fn_80085928(fn_800B14A0(p)))
            fn_800B9CE8(fn_80085928(fn_800B14A0(p)), 2, other, Entity_GetActor(self));
    } else {
    steer:
        Vector v70;
        fn_8042DC84(&v70, fn_800B1750(*Entity_GetActor(self)));
        v70.z += 0.7f;
        v70.x += (float)fn_80171F8C() * 4.656612873077393e-10f * 0.4f - 0.2f;
        fn_8042F76C(&v70);
        fn_80435530(&v70, f14);
        fn_80065CB0(other, &v70);
        ret = 1;
    }
    if (fn_800B24AC(other)) {
        Vec4 w((float)fn_80171F8C() * 4.656612873077393e-10f * 15.0f, 0.0f, (float)fn_80171F8C() * 4.656612873077393e-10f * 20.0f, 0.0f);
        fn_803190C4(fn_800B24AC(other), (Vector *)&w);
    }
    fn_800CDD84(self, fn_800B13D8(other), 1000);
    return ret;
}
