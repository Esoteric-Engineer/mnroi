// The WirePickup state's (0x22) event handler. Owns .rodata 0x8048D238-0x8048D260.
// Event 0x23 puts the wire's end at the picked object (10 ahead of the actor if there is none), 0x24 restarts the wire effect, and 0x5 and 0x14 launch the object at the actor, or hit it if fn_800A4160 holds.

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

struct Handle {
    char d[0xC8];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(Vector *pos, int z); // +0xE8
};

struct Tgt : Ent {
    char d[0x194];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(Vector *v, int z); // +0x30
};

struct Body {
    void *m() __asm__("fn_80317958");
};

struct PBody : Body { // matching_notes 46
    int pad;
};

struct PropBase : Ent {
    char pad4[0x2C - 4];
    unsigned int f2C;
    char pad30[0x198 - 0x30];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(int v); // +0xE8
};

struct Prop : PropBase {
    char pad19C[0x290 - 0x19C];
    unsigned int flags; // +0x290
    char pad294[0x2D8 - 0x294];
    int f2D8;
    float f2DC;
    int f2E0;
};

struct Obj {
    char pad0[0x18];
    unsigned int f18;
};

extern char lbl_80593BE8[];
extern char lbl_80593DD0[];
extern char lbl_8064AA80[];

extern "C" {
PEnt *Entity_GetActor(void *self);
int fn_800ACD20(Ent &actor, int id);
Handle *fn_80393D0C(Ent &actor, int id, int a, int b);
Prop *fn_800CE0FC(void *self);
int fn_800B0CC0(void *p);
Vector *fn_800B1724(Ent &actor);
Vector *fn_800B1750(Ent &actor);
void fn_8042DC84(Vector *dst, Vector *src);
void fn_8042FE08(Vector *out, Vector *dir, float t);
int fn_8010CDCC(Ent &self, int event, void *target, int a3, int a4, int a5, int a6);
void fn_800D5514(void *self);
void *fn_800B1478(void *p);
int fn_800A4468(void *p);
int fn_800A4160(void *p);
void fn_8002FD50(void *a, void *b, int c, int d, float f, Vector *g, void *h, int i, int j, float k, int *l, int m, int n, int o);
float fn_800B1884(Ent &actor, int id);
void fn_800A4678(void *p, int v);
void fn_8009AD04(void *p, int v);
void fn_8009AD58(void *p, int v);
int fn_800B13D8(Ent &actor);
int fn_800B1668(void *p);
void fn_80065F28(void *p, int v);
PBody *fn_800B24AC(void *p);
void *fn_80318E84(void *p);
void fn_80434BA4(Vector *out, void *v);
void fn_80429038(Vector *out, Vector *a, Vector *b);
float fn_8042EC54(Vector *v);
int fn_801BCB08(Vector *a, Vector *b, float f1, float f2, float *o1, float *o2);
float *fn_8042FB28(void *p);
float fn_8042FE6C(Vector *v);
void fn_801BEBBC(Vector *out, void *basis, Vector *in);
void fn_80435530(Vector *v, float f);
int fn_800664C0(Ent &actor);
void *fn_803A20D8(char *tbl, int a, void *self, int b, int c, int d, int e, float f);
void fn_80393938(void *self, void *c, int flag);
void fn_800A2B3C(void *p, int a, int b, int c, int d);
void fn_8006645C(Ent &actor, int a);
void fn_800B0738(void *p);
void fn_80065CB0(Ent &actor, Vector *v);
float fn_8043D930(void *p);
void fn_8006668C(Ent &actor, float v);
int fn_8042EFF8(void *p);
void fn_8007FD34(void *a, void *b);
void fn_80067050(Ent &actor, Vector *v);
float fn_804290F8(Vector *a, Vector *b);
void fn_800BD2D0(void *self, int handle);
double __ieee754_sqrt(double x);
}

extern "C" int fn_800D73F0(register Obj *self, int unused, int type, int value, int extra)
{
    switch (type) {
    case 0x23: {
        Handle *f28 = fn_80393D0C(*Entity_GetActor(self), fn_800ACD20(*Entity_GetActor(self), 0xA8), 0x15, 1);
        Prop &obj = *fn_800CE0FC(self);
        Vector v30;
        if (&obj && fn_800B0CC0(&obj)) {
            fn_8042DC84(&v30, fn_800B1724(obj));
        } else {
            fn_8042DC84(&v30, fn_800B1724(*Entity_GetActor(self)));
            fn_8042FE08(&v30, fn_800B1750(*Entity_GetActor(self)), 10.0f);
            v30.z += 3.0f;
        }
        if (f28)
            f28->s28(&v30, 0);
        fn_8010CDCC(*Entity_GetActor(self), 0x30, &obj, 0, 0x320, 0, 0);
        break;
    }
    case 0x24:
        fn_800D5514(self);
        break;
    case 0x14:
    case 5: {
        Prop &obj = *fn_800CE0FC(self);
        if (&obj && !(self->f18 & 0x8000000)) {
            int f28 = &obj && fn_800B0CC0(&obj) ? fn_800A4468(fn_800B1478(&obj)) : 0;
            Vector v30;
            Vector v40;
            float f50;
            Tgt *f54;
            float f58;
            if (fn_800A4160(&obj)) {
                fn_8002FD50(Entity_GetActor(self), &obj, 4, 3, 20.0f, fn_800B1724(obj), 0, 0x100, 1, 0.0f, 0, 0, 0xFF, 0xFF);
                return 1;
            }
            f50 = fn_800B1884(*Entity_GetActor(self), f28 + 0x31);
            f58 = fn_800B1884(*Entity_GetActor(self), f28 + 0x71);
            fn_800A4678(&obj, 0);
            fn_8009AD04(&obj, fn_800B13D8(*Entity_GetActor(self)));
            fn_8009AD58(&obj, fn_800B13D8(*Entity_GetActor(self)));
            f54 = (Tgt *)Entity_GetActor(self);
            fn_80065F28(&obj, fn_800B1668(&obj));
            fn_80434BA4(&v30, fn_80318E84(fn_800B24AC(&obj)));
            Vector v60;
            Vector v70;
            float f80;
            float f84;
            float f88;
            float f8c;
            f54->s5(&v60, 0);
            fn_80429038(&v70, &v60, &v30);
            f8c = fn_8042EC54(&v70);
            if (!fn_801BCB08(&v30, &v60, f58, 20.0f, &f84, &f88))
                return 0;
            f80 = f84;
            if (f80 < -50.0f)
                return 0;
            Vector v90;
            *fn_8042FB28(&v90) = f80;
            fn_8042FB28(&v90)[2] = fn_8042FE6C(&v70);
            fn_8042FB28(&v90)[1] = 0.0f;
            fn_801BEBBC(&v40, lbl_80593DD0, &v90);
            fn_80435530(&v40, f58);
            if (fn_800664C0(obj) && obj.f2D8)
                fn_80393938(&obj, fn_803A20D8(lbl_8064AA80, 0, &obj, 0, obj.f2D8, 0, 0, 0.0f), 1);
            fn_800A2B3C(&obj, 1, 0, 0, 0);
            fn_8010CDCC(obj, fn_800664C0(obj) ? 0x82 : 0x83, &obj, 0, 0, 0, 0);
            fn_8006645C(obj, 0);
            fn_800B0738(&obj);
            fn_80065CB0(obj, &v40);
            obj.f2C &= 0x7FFFFFFF;
            obj.f2DC = fn_8043D930(fn_800B24AC(&obj)->m());
            fn_8006668C(obj, 0.0f);
            obj.flags |= 0x20000;
            obj.f2E0 = fn_8042EFF8(lbl_80593BE8) + 0x1F4;
            fn_8007FD34(&obj, Entity_GetActor(self));
            obj.s28(0);
            Vector va0;
            Vector vb0;
            Vector vc0;
            float t;
            fn_8042DC84(&vc0, fn_800B1724(*Entity_GetActor(self)));
            vc0.z = 0.0f;
            fn_80067050(obj, &va0);
            va0.z = 0.0f;
            fn_8042DC84(&vb0, fn_800B1724(obj));
            t = fn_804290F8(&vc0, &vb0) / (float)__ieee754_sqrt(va0.x * va0.x + va0.y * va0.y);
            t = t * 1000.0f;
            t = t + 250.0f;
            fn_800BD2D0(self, (unsigned int)t);
        }
        break;
    }
    default:
        return 0;
    }
    return 1;
}
