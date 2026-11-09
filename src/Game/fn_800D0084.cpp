// The WallClimb state (8): whether the actor can climb (ACTOR_ABILITIES 0x2), enter, exit and update.
// Owns .rodata 0x8048D02C-0x8048D068.

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

class Placement
{
public:
    char d[0x40];
    Placement();
};

class Surface
{
public:
    virtual void s0();
    virtual void s1();
    virtual int Kind(); // vtable +0x18
};

struct Ent {
    int pad;
};

struct ActBase : Ent {
    char d[0x194];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
    virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41();
    virtual void s42(); virtual void s43(); virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
    virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53();
    virtual void s54(); virtual void s55(); virtual void s56(); virtual void s57();
    virtual int s58(float a, Vector *v, float b); // +0x1D8
};

struct EObj {
    char pad0[0x10];
    unsigned int f10;
    char pad14[0x3AC - 0x14];
};

struct EBase : EObj {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(int state); // +0x30
};

struct Obj : EBase {
    char pad3B0[0x409 - 0x3B0];
    unsigned char b409;
    unsigned char b40A;
    unsigned char b40B;
    unsigned char b40C;
    int f410;
    float f414;
};

extern int lbl_8066F05C;
extern char lbl_80552110[];
extern char lbl_80593BE8[];

extern "C" {
ActBase *Entity_GetActor(void *self);
Surface *fn_804471D4(Placement *p);
void *fn_80434ED0(Surface *s);
int *fn_80434E7C(Placement *p);
int fn_8008A5B4(void *a, int b);
Ent &fn_80048A74(Placement *p);
int fn_800B0CC0(Ent *e);
int fn_800A4280(Ent *e);
int fn_800CC440(void *self);
int fn_8008603C(void *actor);
int fn_8008612C(void *actor);
int fn_80086314(void *actor);
int fn_80086374(void *actor);
int fn_800CC148(void *self, int id);
int fn_800CC0BC(void *self, int id);
float fn_800B2670(Ent &actor);
Vector *fn_800B1724(Ent &actor);
Vector *fn_800B1750(Ent &actor);
void fn_8042DC84(Vector *dst, Vector *src);
void fn_8042D80C(Vector *dst, Vector *src);
int fn_8004A758(Vector *a, Vector *b, float r, int c, Placement *p, void *d, int e, int f, int g);
int fn_800CDA20(void *self);
void fn_80066604(Ent &actor);
void fn_8009AEC8(Ent &actor, int v);
int fn_80097CE8(Ent &actor, int a, int mode, float speed, void *set, float blend, float f);
void fn_80065AF8(Ent &actor, int a, int b);
void fn_800CC3A4(void *self);
void fn_800CD7A8(void *self);
void fn_8006645C(Ent &actor, int a);
int fn_800664C0(Ent &actor);
void fn_800BEAC0(void *self, int v);
int fn_8009B04C(Ent &actor);
int fn_800C4D70(void *self, int a, float f, int b);
void fn_800BDFFC(void *self);
void fn_800BDF20(void *self);
void fn_800C05BC(void *self);
void fn_800CC3F4(void *self, int v);
void fn_800C7BEC(void *self);
float fn_800CC1D4(void *self, int id, Vector *stick);
unsigned int fn_80048C14(Placement *p, int v);
int fn_800C8CCC(void *self, int motion, float f, int a, int b);
void fn_800CF7E8(void *self, Vector *v, int mode);
Vector *fn_80437168(Placement *p);
char *fn_8043289C(char *g);
float fn_8042EBF4(Vector *a, void *b);
float fn_800B1884(Ent &actor, int id);
float fn_80426A84(void *g);
int fn_80084A60(void *actor, float f);
int fn_800CCA88(void *self);
int fn_800CC2E0(void *self);
void fn_800DA884(void *self, int motion);
int fn_80084B68(void *actor, float f);
void fn_8005AB90(Ent &actor, Vector *v);
int fn_800E339C(void *self);
void fn_800BD2D0(void *self, int handle);
int fn_800CC8BC(void *self);
Vector *fn_8042FB28(Vector *v);
float fn_8042EC54(Vector *v);
void fn_8005A9B8(Ent &actor, Vector *dir);
void fn_800C64A0(void *self, float z);
double fabs(double x);
extern float fabsf(float x);
}

extern "C" int fn_800D0084(register Obj *self, Placement *p)
{
    if (fn_804471D4(p)->Kind() == 0x18) {
        if (fn_8008A5B4(fn_80434ED0(fn_804471D4(p)), *fn_80434E7C(p)))
            return 0;
    } else {
        Ent &e = fn_80048A74(p);
        if (&e && fn_800B0CC0(&e) && fn_800A4280(&e))
            return 0;
    }
    return 1;
}

extern "C" int fn_800D01A4(register Obj *self)
{
    if (fn_800CC440(self))
        return 0;
    if (!fn_8008603C(Entity_GetActor(self)))
        return 0;
    if (fn_8008612C(Entity_GetActor(self)) && !fn_800CC148(self, 7) && !fn_800CC148(self, 0x18))
        return 0;
    if (fn_80086314(Entity_GetActor(self))) {
        if (!fn_800CC148(self, 7) && !fn_800CC148(self, 0x18))
            return 0;
    } else if (!fn_8008612C(Entity_GetActor(self)) && !fn_800CC148(self, 8) && !fn_800CC148(self, 0x18)) {
        return 0;
    }
    float f8 = 2.0f * fn_800B2670(*Entity_GetActor(self));
    Placement p;
    Vector v50;
    fn_8042DC84(&v50, fn_800B1724(*Entity_GetActor(self)));
    v50.z += 0.25f;
    Vector v60;
    fn_8042DC84(&v60, fn_800B1750(*Entity_GetActor(self)));
    if (!fn_8004A758(&v50, &v60, f8, 1, &p, 0, 0, 0, 10))
        return 0;
    if (!fn_800D0084(self, &p))
        return 0;
    return 1;
}

extern "C" int fn_800D0454(register Obj *self, int unused)
{
    if (fn_800CDA20(self))
        return 0;
    fn_80066604(*Entity_GetActor(self));
    fn_8009AEC8(*Entity_GetActor(self), 0);
    fn_80097CE8(*Entity_GetActor(self), 0x122, 1, 30.0f, 0, 7.5f, -1.0f);
    fn_80065AF8(*Entity_GetActor(self), 0, 0);
    fn_800CC3A4(self);
    fn_800CD7A8(self);
    return 1;
}

extern "C" int fn_800D0544(register Obj *self, int unused)
{
    fn_80065AF8(*Entity_GetActor(self), 1, 0);
    fn_8006645C(*Entity_GetActor(self), 0);
    return 1;
}

extern "C" void fn_800D05BC(register Obj *self)
{
    Vector v8;
    Vector v18;
    Vector v28;
    float f38;
    int f3C = 0;
    int f40 = 0;
    fn_800BEAC0(self, 0);
    if (fn_8009B04C(*Entity_GetActor(self)) == 0x64) {
        if (fn_800C4D70(self, 0, 0.0f, 0))
            return;
        fn_800BDFFC(self);
        return;
    }
    self->f10 &= ~0x1000;
    if (fn_8008612C(Entity_GetActor(self)) || fn_80086314(Entity_GetActor(self))) {
        if (!fn_800CC148(self, 7) && !fn_800CC148(self, 0x18)) {
            fn_800C05BC(self);
            self->s5(5);
            fn_800CC3F4(self, 0xFA);
            return;
        }
    } else if (!fn_800CC148(self, 8) && !fn_800CC148(self, 0x18)) {
        self->s5(5);
        fn_800CC3F4(self, 0xFA);
        return;
    }
    fn_800C7BEC(self);
    f38 = fn_800CC1D4(self, 7, &v18);
    float f44 = 2.0f * fn_800B2670(*Entity_GetActor(self));
    Placement p;
    Vector v88;
    fn_8042DC84(&v88, fn_800B1750(*Entity_GetActor(self)));
    if (!fn_8004A758(fn_800B1724(*Entity_GetActor(self)), &v88, f44, 1, &p, 0, 0, 0, 10)) {
        self->s5(5);
        fn_800CC3F4(self, 0xFA);
        return;
    }
    lbl_8066F05C = fn_80048C14(&p, 0);
    if (!fn_800D0084(self, &p)) {
        self->s5(5);
        fn_800CC3F4(self, 0xFA);
        return;
    }
    Vector v98;
    fn_8042DC84(&v98, fn_800B1724(*Entity_GetActor(self)));
    v98.z += 2.1f;
    if (!fn_8004A758(&v98, &v88, f44, 1, &p, 0, 0, 0, 10)) {
        if (fn_800C8CCC(self, 0x11A, 0.2f, 1, 0)) {
            self->s5(10);
        } else {
            Vector vA8;
            fn_8042D80C(&vA8, &v88);
            fn_800CF7E8(self, &vA8, 3);
            fn_800CC3F4(self, 0xFA);
        }
        return;
    }
    Vector vA8;
    fn_8042DC84(&vA8, fn_80437168(&p));
    float fB8 = v18.z;
    float fBC = v18.x;
    if (fn_8042EBF4(fn_800B1750(*Entity_GetActor(self)), fn_8043289C(lbl_80552110) + 0x370) < -0.2f)
        fBC = -fBC;
    if (!fn_80084A60(Entity_GetActor(self), fn_800B1884(*Entity_GetActor(self), 0x1E) * 0.5f * fn_80426A84(lbl_80593BE8))) {
        fn_800CF7E8(self, &vA8, 3);
        fn_800CC3F4(self, 0xFA);
        return;
    }
    if (fn_800CC0BC(self, 5) && !fn_800CC148(self, 0x18)) {
        fn_800CF7E8(self, &vA8, 3);
        fn_800CC3F4(self, 0xFA);
        return;
    }
    if (fn_800CC0BC(self, 2)) {
        if (fn_80086374(Entity_GetActor(self)) && fn_800CCA88(self)) {
            if (fn_800CC2E0(self))
                return;
            fn_800DA884(self, 0x64);
            if (!fn_80084B68(Entity_GetActor(self), self->f414)) {
                fn_8005AB90(*Entity_GetActor(self), fn_800B1750(*Entity_GetActor(self)));
                fn_800E339C(self);
                return;
            }
            self->b40A = 0;
            self->b409 = 0;
            self->b40B = 1;
            self->b40C = 0x15;
            self->f410 = 0xCA;
            f3C = fn_80097CE8(*Entity_GetActor(self), 0x64, 0, 30.0f, 0, 7.5f, -1.0f);
            fn_8006645C(*Entity_GetActor(self), 0);
            if (f3C > 0) {
                fn_800BD2D0(self, f3C);
                return;
            }
        }
        fn_8005AB90(*Entity_GetActor(self), fn_800B1750(*Entity_GetActor(self)));
        fn_800E339C(self);
        return;
    }
    if (!fn_800CC2E0(self) || fn_800CC8BC(self)) {
        if (fabsf(fB8) > fabs(fBC)) {
            if (fB8 < -0.1f)
                f40 = 0x11E;
            else if (fB8 > 0.1f)
                f40 = 0x11F;
        } else {
            if (fBC > 0.1f)
                f40 = 0x120;
            else if (fBC < -0.1f)
                f40 = 0x121;
        }
        if (f40)
            f3C = fn_80097CE8(*Entity_GetActor(self), f40, 0, 30.0f, 0, 7.5f, -1.0f);
        if (f3C > 0) {
            fn_800CD7A8(self);
            fn_800BD2D0(self, f3C);
            if (fn_800664C0(*Entity_GetActor(self)))
                fn_8006645C(*Entity_GetActor(self), 0);
        }
    }
    Vector vC0;
    fn_8042D80C(&vC0, &vA8);
    fn_8042FB28(&vC0)->z = 0.0f;
    float fD0 = fn_8042EC54(&vC0);
    if (fD0 > 0.1f)
        fn_8005A9B8(*Entity_GetActor(self), &vC0);
    if (fn_800CC2E0(self)) {
        fn_800BDF20(self);
        if (fn_8009B04C(*Entity_GetActor(self)) == 0x11E) {
            Vector vD8;
            if (Entity_GetActor(self)->s58(0.7f, &vD8, 0.2f) && !fn_800CC148(self, 0x18)) {
                fn_800C64A0(self, 0.0f);
                return;
            }
        }
    } else {
        if (!fn_800664C0(*Entity_GetActor(self)))
            fn_8006645C(*Entity_GetActor(self), 1);
        fn_80066604(*Entity_GetActor(self));
    }
}
