// The WirePickup state's (0x22) per-frame update. Owns .rodata 0x8048D228-0x8048D238.

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

struct Tgt : Ent {
    char d[0x194];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(Vector *v, int z); // +0x30
};

struct PropBase : Ent {
    char pad4[0x2C - 4];
    unsigned int f2C;
    char pad30[0x198 - 0x30];
    virtual void s0();
};

struct Prop : PropBase {
    char pad19C[0x2D4 - 0x19C];
    int f2D4;
    int f2D8;
};

struct EObj {
    char pad0[0x10];
    unsigned int f10;
    char pad14[0x3AC - 0x14];
};

struct Obj : EObj {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(int state); // +0x30
};

extern char lbl_80593BE8[];
extern char lbl_80593DD0[];
extern char lbl_8064AA80[];

extern "C" {
PEnt *Entity_GetActor(void *self);
int fn_804439A4(void *p);
int fn_800CC2E0(void *self);
void fn_800BDFFC(void *self);
void fn_80066604(Ent &actor);
void fn_800CD77C(void *self);
Prop *fn_800CE0FC(void *self);
int fn_800B0CC0(void *p);
int fn_800B1138(void *p);
int fn_8009B234(void *p);
int fn_8009B04C(Ent &actor);
void fn_8009AEC8(Ent &actor, int v);
void fn_800CC3A4(void *self);
int fn_8008615C(void *actor);
int fn_800CC0BC(void *self, int id);
void fn_800D5514(void *self);
float fn_800B1884(Ent &actor, int id);
void fn_800A4678(void *p, int v);
Tgt *fn_800E9630(void *self, float f, int a, int b, int c);
void fn_80434BA4(Vector *out, void *v);
void *fn_80318E84(void *p);
void *fn_800B24AC(void *p);
int fn_800B13D8(Ent &actor);
void fn_8009AD04(void *p, int v);
void fn_80429038(Vector *out, Vector *a, Vector *b);
float fn_8042EC54(Vector *v);
int fn_801BCB08(Vector *a, Vector *b, float f1, float f2, float *o1, float *o2);
float *fn_8042FB28(void *p);
float fn_8042FE6C(Vector *v);
void fn_801BEBBC(Vector *out, void *basis, Vector *in);
void fn_80435530(Vector *v, float f);
int fn_800B0C58(void *p);
void *fn_800B14A0(void *p);
void *fn_80085928(void *p);
void fn_800B9CE8(void *a, int b, void *c, void *d);
Vector *fn_800B1750(Ent &actor);
void fn_8042DC84(Vector *dst, Vector *src);
void fn_8042F76C(Vector *v);
int fn_800A4370(void *p);
int fn_800B1D48(void *p);
int fn_800664C0(Ent &actor);
Prop *fn_800B1478(void *p);
void *fn_803A20D8(char *tbl, int a, void *self, int b, int c, int d, int e, float f);
void fn_80393938(void *self, void *c, int flag);
void fn_8006645C(Ent &actor, int a);
void fn_800A2B3C(void *p, int a, int b, int c, int d);
void fn_80065CB0(Ent &actor, Vector *v);
void fn_800CDD84(void *self, int a, int b);
int fn_8010CDCC(Ent &self, int event, void *target, int a3, int a4, int a5, int a6);
void fn_800BD2D0(void *self, int handle);
int fn_800CC8BC(void *self);
int fn_800CB7A0(void *self);
void fn_800C7BEC(void *self);
int fn_800CD9B0(void *self);
}

extern "C" void fn_800D6AFC(register Obj *self)
{
    if (fn_804439A4(lbl_80593BE8))
        return;
    if (fn_800CC2E0(self)) {
        fn_800BDFFC(self);
    } else {
        fn_80066604(*Entity_GetActor(self));
        fn_800CD77C(self);
    }
    Prop &obj = *fn_800CE0FC(self);
    if (!&obj || !fn_800B0CC0(&obj) || fn_800B1138(&obj) || fn_8009B234(&obj)) {
        if (fn_8009B04C(*Entity_GetActor(self)) == 0x4D) {
            fn_8009AEC8(*Entity_GetActor(self), 0);
            fn_800CC3A4(self);
        }
        if (!(self->f10 & 1))
            self->s5(2);
        else
            self->s5(0x17);
        return;
    }
    if (fn_8008615C(Entity_GetActor(self)) && (fn_800CC0BC(self, 2) || fn_800CC0BC(self, 0xA))) {
        fn_800D5514(self);
        Prop *f0c = &obj;
        Vector v10;
        Vector v20;
        float f30;
        Tgt *f34;
        float f38;
        f30 = fn_800B1884(*Entity_GetActor(self), 0x31);
        f38 = fn_800B1884(*Entity_GetActor(self), 0x71);
        fn_800A4678(f0c, 0);
        f34 = fn_800E9630(self, f30, 0, 0, 0);
        fn_80434BA4(&v10, fn_80318E84(fn_800B24AC(f0c)));
        fn_8009AD04(f0c, fn_800B13D8(*Entity_GetActor(self)));
        if (f34) {
            Vector v40;
            Vector v50;
            float f60;
            float f64;
            float f68;
            float f6c;
            f34->s5(&v40, 0);
            fn_80429038(&v50, &v40, &v10);
            f6c = fn_8042EC54(&v50);
            if (!fn_801BCB08(&v10, &v40, f38, 20.0f, &f64, &f68))
                goto fallback;
            f60 = f64;
            if (f60 < -50.0f)
                goto fallback;
            Vector v70;
            *fn_8042FB28(&v70) = f60;
            fn_8042FB28(&v70)[2] = fn_8042FE6C(&v50);
            fn_8042FB28(&v70)[1] = 0.0f;
            fn_801BEBBC(&v20, lbl_80593DD0, &v70);
            fn_80435530(&v20, f38);
            if (fn_800B0C58(f34) && fn_80085928(fn_800B14A0(f34)))
                fn_800B9CE8(fn_80085928(fn_800B14A0(f34)), 2, f0c, Entity_GetActor(self));
            goto done;
        }
    fallback:
        fn_8042DC84(&v20, fn_800B1750(*Entity_GetActor(self)));
        v20.z += 0.2f;
        fn_8042F76C(&v20);
        fn_80435530(&v20, f38);
    done:
        if (fn_800A4370(f0c) && fn_800B1D48(f0c) == 3 && fn_800664C0(*f0c) && fn_800B0CC0(f0c)) {
            if (fn_800B1478(f0c)->f2D4)
                fn_80393938(f0c, fn_803A20D8(lbl_8064AA80, 0, f0c, 0, fn_800B1478(f0c)->f2D4, 0, 0, 0.0f), 1);
            if (fn_800664C0(*f0c) && fn_800B1478(f0c)->f2D8)
                fn_80393938(f0c, fn_803A20D8(lbl_8064AA80, 0, f0c, 0, fn_800B1478(f0c)->f2D8, 0, 0, 0.0f), 1);
            fn_8006645C(*f0c, 0);
            fn_800A2B3C(fn_800B1478(f0c), 1, 0, 0, 0);
        }
        fn_80065CB0(*f0c, &v20);
        fn_800CDD84(self, fn_800B13D8(*f0c), 0x3E8);
        fn_8010CDCC(*Entity_GetActor(self), 0x22, f0c, 0, 0, 0, 0);
        if (!(self->f10 & 1)) {
            self->s5(2);
        } else {
            fn_800BD2D0(self, 0);
            self->s5(0x17);
            return;
        }
    }
    if (fn_800CC8BC(self) && fn_800CB7A0(self))
        return;
    fn_800C7BEC(self);
    if (fn_800CD9B0(self) || !fn_800CC2E0(self)) {
        if (!(self->f10 & 1))
            self->s5(2);
        else
            self->s5(0x17);
    }
}
