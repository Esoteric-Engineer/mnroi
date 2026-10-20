// The player controller's ground state: reads the actions (fn_800CC0BC), hands off to the jump, attack, grab and ranged states, otherwise picks the stand/walk/run clip and moves the actor; the tuning fields it reads are in tools/nvbtool.py.

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

struct ActBase : Ent {
    char d[0x194];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20();
    virtual int s21(); // +0xB0
    virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33();
    virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44(); virtual void s45();
    virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
    virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55(); virtual void s56();
};

struct Act : ActBase {
    virtual int s57(float t); // +0x1D0
};

struct Handle {
    char d[0xC8];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
    virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41();
    virtual void s42(); virtual void s43(); virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
    virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53();
    virtual void s54(); // +0x1B8
    virtual void s55();
    virtual void s56(); // +0x1C8
};

struct EObj {
    char pad0[0x8];
    unsigned char b8;
    char pad9[0x18 - 0x9];
    unsigned int f18;
    char pad1C[0xE0 - 0x1C];
    unsigned int fE0; // a time on the fn_8042EFF8 clock
    char padE4[0x3A0 - 0xE4];
    Handle *h; // +0x3A0
    char pad3A4[0x3AC - 0x3A4];
};

struct EBase : EObj {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(int state); // +0x30
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21();
    virtual void *s22(); // +0xB8
};

struct Obj : EBase {
    char pad3B0[0x440 - 0x3B0];
    Vector v440;
    char pad450[0x470 - 0x450];
    Vector v470;
    char pad480[0x540 - 0x480];
    Vector v540;
    char pad550[0x55C - 0x550];
    unsigned int f55C;
};

extern char lbl_80593BE8[];

__asm__(".section .rodata\n\t.globl lbl_8048C9D0\nlbl_8048C9D0:\n\t.float 5.0\n\t.text"); // 8-aligns the claim: fn_800C0784's 5.0f

extern "C" {
Act *Entity_GetActor(void *self);
int fn_800861EC(void *actor);
int fn_80085EEC(void *actor);
float fn_80086614(void *actor);
int fn_80085F1C(void *actor);
void fn_80030930(void *a, int b, int c, int d, float f1, int e, int f, int g, int h, float f2);
int fn_804439A4(void *g);
void fn_800C7BEC(void *self);
int fn_800CC76C(void *self);
void fn_800C8098(void *self);
float fn_800CC1D4(void *self, int id, Vector *v);
void fn_8042DC84(Vector *dst, Vector *src);
int fn_800CC2E0(void *self);
void fn_8006668C(Ent &actor, float v);
void fn_800BDFFC(void *self);
int fn_8009B04C(Ent &actor);
void fn_8009AEC8(Ent &actor, int v);
void fn_800CC3A4(void *self);
int fn_800CC338(void *self);
int fn_800CD288(void *self);
void fn_800CA8A0(void *self);
int fn_800419E8(int a);
int fn_8008618C(void *actor);
float fn_80086730(void *actor);
float fn_800B1884(Ent &actor, int id);
void fn_800BED04(void *self, int a, int b);
int fn_80097CE8(Ent &actor, int a, int mode, float speed, void *set, float blend, float f);
void fn_800BD3A8(void *self, int handle);
void fn_800BD2D0(void *self, int handle);
void fn_80066604(Ent &actor);
int fn_800BEAC0(void *self, int v);
int fn_800B9D64(void *self, Vector *v, float f, int z);
int fn_800CBF20(void *self);
int fn_800CC148(void *self, int id);
Vector *fn_800B1750(Ent &actor);
int fn_800C388C(void *self, Vector *dir, Vector *out, float f, Vector *v);
void fn_80067050(Ent &actor, Vector *v);
void fn_80065CB0(Ent &actor, Vector *v);
int fn_800CDA20(void *self);
Ent *fn_800CD9B0(void *self);
void *fn_800B1478(void *c);
int fn_800A4130(void *p);
int fn_800CC0BC(void *self, int id);
void fn_800F8B90(void *self);
int fn_800C45B0(void *self, int a);
int fn_800DDCB4(void *self, int a, int b);
int fn_800BD52C(void *self);
int fn_800DF03C(void *self, int a, int b);
int fn_800860CC(void *actor);
int fn_80084B68(void *actor, float f);
int fn_800D01A4(void *self);
int fn_800D572C(void *self);
int fn_800BD480(void *self);
int fn_800860FC(void *actor);
int fn_800CCA88(void *self);
int fn_800D5FEC(void *self, int a);
int fn_800E4048(void *self);
int fn_800F0328(void *self);
int fn_800D2CF8(void *self);
Ent *fn_8008529C(void *actor);
int fn_800B0CC0(void *c);
int fn_8005ABF0(void *actor);
void fn_800C02FC(void *self, void *target);
void fn_8042D8A8(Vector *dst, Vector *src);
float fn_80434040(Vector *v);
double __ieee754_sqrt(double x);
float fn_8042EBF4(Vector *a, Vector *b);
int fn_800CC6AC(void *self);
char *fn_8009AF80(Ent &actor);
float fn_80085A30(void *actor);
void fn_80435578(void *p, float v);
float fn_80086DE4(void *actor);
void fn_80097EC4(Ent &actor, int anim, float f);
int fn_800A43A0(void *c);
int fn_80085FDC(void *actor);
int fn_8009AFC8(Ent &actor);
float fn_80426A84(void *g);
int fn_80084A60(void *actor, float f);
int fn_800ACD20(Ent &actor, int id);
Handle *fn_80393D0C(Ent &actor, int id, int a, int b);
void fn_80098008(Ent &actor, float f);
Handle *fn_80393B28(Ent &actor, Handle *h);
Vector *fn_800B17A8(Ent &actor);
void fn_8042D80C(Vector *dst, Vector *src);
unsigned int fn_8042F024(void *g);
float fn_80086D9C(void *actor);
int fn_8008612C(void *actor);
int fn_800D14F0(void *self);
float fn_80086D54(void *actor);
int fn_800A4408(void *c);
void fn_8042FDBC(Vector *out, Vector *v, float f);
void fn_8042D854(Vector *dst, Vector *src);
unsigned int fn_8042EFF8(void *g);
void *fn_800B1724(Ent &actor);
float fn_800B2670(Ent &actor);
void fn_80429090(Vector *out, void *a, Vector *b, float s);
int fn_80171F8C(void);
int fn_80048EBC(void *a, Vector *v, int b, int c, int d, float f, int e);
}

extern "C" void fn_800C0F48(register Obj *self)
{
    float f8 = 1.0f;
    Vector v10;
    float f20;
    float f24 = 1.0f;
    Vector v28;
    int f38 = 0;
    int f3C = 0;
    int f40 = 0;
    int f44 = 1;
    int f48 = 0;
    if (fn_800861EC(Entity_GetActor(self))) {
        self->s5(0x25);
        return;
    }
    if (fn_80085EEC(Entity_GetActor(self))) {
        self->s5(1);
        return;
    }
    if (fn_80086614(Entity_GetActor(self)) < 1.0f && !fn_80085F1C(Entity_GetActor(self))) {
        fn_80030930(Entity_GetActor(self), 0, 0, 0, 0.0f, 0, 0, 0, 1, 0.0f);
        return;
    }
    if (fn_804439A4(lbl_80593BE8))
        return;
    fn_800C7BEC(self);
    if (fn_800CC76C(self))
        fn_800C8098(self);
    Vector v50;
    float f60 = fn_800CC1D4(self, 0, &v50);
    if (f60 != 0.0f)
        fn_8042DC84(&self->v440, &v50);
    if (fn_800CC2E0(self)) {
        fn_8006668C(*Entity_GetActor(self), 0.0f);
        fn_800BDFFC(self);
        switch (fn_8009B04C(*Entity_GetActor(self))) {
        case 0x23:
        case 0x24:
        case 0x25:
            f44 = 1;
            f48 = 1;
            break;
        case 0x13:
            f44 = 0;
            f48 = 1;
            break;
        case 0xE:
        case 0x11:
        case 0xCA:
        case 0xD5:
        case 0xFA:
        case 0x10A:
            f44 = 1;
            f48 = 0;
            if (f60 > 0.1f) {
                fn_8009AEC8(*Entity_GetActor(self), 0);
                fn_800CC3A4(self);
            }
            break;
        case 0xF:
        case 0x12:
        case 0xCD:
        case 0xD8:
        case 0xF5:
        case 0x105:
            f44 = 1;
            f48 = 1;
            break;
        case 0x10:
            f44 = 1;
            f48 = 1;
            if (f60 > 0.7f) {
                fn_8009AEC8(*Entity_GetActor(self), 0);
                fn_800CC3A4(self);
            }
            break;
        case 0x1B:
        case 0x1C:
            f44 = 0;
            if (f60 > 0.1f && !fn_800CC338(self) && !fn_800CD288(self)) {
                fn_8009AEC8(*Entity_GetActor(self), 0);
                fn_800CC3A4(self);
            }
            break;
        case 0x22:
            f48 = 1;
            break;
        }
        if (f48 && f60 == 0.0f) {
            fn_8009AEC8(*Entity_GetActor(self), 0);
            fn_800CA8A0(self);
            fn_800CC3A4(self);
        }
    } else {
        self->f18 &= ~0x1000000;
    }
    if (fn_800CC338(self) || fn_800CD288(self) || fn_800419E8(1) == 3)
        return;
    if (fn_8008618C(Entity_GetActor(self)) && fn_80086730(Entity_GetActor(self)) < fn_800B1884(*Entity_GetActor(self), 0xDE)
        && Entity_GetActor(self)->s57(0.15f)) {
        fn_800BED04(self, 0, 0);
        int f64 = fn_80097CE8(*Entity_GetActor(self), 0x26, 0, 30.0f, 0, 7.5f, -1.0f);
        if (f64 > 0) {
            fn_800BD3A8(self, f64);
            fn_800BD2D0(self, f64);
            fn_80066604(*Entity_GetActor(self));
            return;
        }
    }
    self->f18 &= ~0x80;
    if (fn_800BEAC0(self, 0))
        return;
    if (f44) {
        if (self->b8 == 4)
            f38 = fn_800B9D64(self, &self->v440, fn_800B1884(*Entity_GetActor(self), 0x3F), 0);
        else
            f38 = fn_800B9D64(self, &self->v440, fn_800B1884(*Entity_GetActor(self), 0x3F), 0);
    }
    int f64 = fn_800CBF20(self) && fn_800CC148(self, 9);
    Vector v68;
    if (fn_800861EC(Entity_GetActor(self))) {
        self->s5(0x25);
    } else if (!fn_800C388C(self, fn_800B1750(*Entity_GetActor(self)), &v68, 0.7f, &v28) && !f64) {
        Vector v78;
        fn_80067050(*Entity_GetActor(self), &v78);
        v78.z = 0.0f;
        fn_80065CB0(*Entity_GetActor(self), &v78);
        self->s5(5);
        return;
    }
    if (fn_800CDA20(self)) {
        if (!fn_800A4130(fn_800B1478(fn_800CD9B0(self)))) {
            if (fn_800CC0BC(self, 0xA) || fn_800CC0BC(self, 6)) {
                fn_800F8B90(self);
                return;
            }
            if (fn_800CC0BC(self, 5) && fn_800C45B0(self, 0))
                return;
        } else {
            if (fn_800CC0BC(self, 5) && fn_800C45B0(self, 0))
                return;
            if (fn_800CC0BC(self, 6)) {
                fn_800F8B90(self);
                return;
            }
        }
        if (fn_800CC0BC(self, 2) && fn_800DDCB4(self, 0, 0))
            return;
    } else {
        if (fn_800CC0BC(self, 0x12)) {
            if (fn_800BD52C(self))
                return;
            if (fn_800DF03C(self, 0, 0))
                return;
        }
        if (fn_800860CC(Entity_GetActor(self)) && fn_800CC0BC(self, 9)
            && fn_80084B68(Entity_GetActor(self), fn_800B1884(*Entity_GetActor(self), 0xC4))) {
            if (fn_800D01A4(self)) {
                self->s5(8);
                return;
            }
            if (fn_800D572C(self))
                return;
        }
        if (fn_800CC148(self, 0x18) && fn_800D01A4(self)) {
            self->s5(8);
            return;
        }
        if (fn_800CC0BC(self, 4)) {
            if (fn_800BD480(self))
                return;
            if (fn_800860FC(Entity_GetActor(self)) && fn_800CCA88(self) && fn_800D5FEC(self, 0))
                return;
        }
        if (self->f18 & 0x20000) {
            if (fn_800CC0BC(self, 0)) {
                self->f18 &= ~0x20000;
                self->s5(0x15);
                return;
            }
        } else if (fn_800CC148(self, 0)) {
            self->s5(0x15);
            return;
        }
        if (fn_800CC148(self, 0xC) && fn_800E4048(self))
            return;
        if (fn_800CC0BC(self, 5)) {
            fn_800C45B0(self, 0);
            return;
        }
        if (fn_800CC0BC(self, 2) && fn_800DDCB4(self, 0, 0))
            return;
        if (fn_800CC0BC(self, 1) && fn_800F0328(self))
            return;
    }
    if (fn_800CC148(self, 0xB) && !fn_800CDA20(self)) {
        self->s5(0xE);
        return;
    }
    if (fn_800CC0BC(self, 0x13)) {
        self->s5(0x1D);
        return;
    }
    if (f64 && fn_800CC148(self, 9) && fn_800CBF20(self) && fn_800D2CF8(self)) {
        if (fn_800861EC(Entity_GetActor(self)))
            self->s5(0x25);
        else
            self->s5(0x17);
        return;
    }
    if (fn_800CC2E0(self))
        return;
    fn_80067050(*Entity_GetActor(self), &v10);
    Ent &f88 = *fn_8008529C(Entity_GetActor(self));
    Vector v78;
    if (&f88 && fn_800B0CC0(&f88) && fn_8005ABF0(&f88)) {
        fn_800C02FC(self, &f88);
        fn_80067050(f88, &v78);
        fn_8042D8A8(&v10, &v78);
        fn_8042D8A8(&v10, &self->v540);
        f3C = 1;
    }
    if (v10.z > 0.0f)
        f20 = fn_80434040(&v10);
    else
        f20 = __ieee754_sqrt(v10.x * v10.x + v10.y * v10.y);
    f24 = fn_8042EBF4(&v50, fn_800B1750(*Entity_GetActor(self)));
    switch ((unsigned int)fn_800CC6AC(self)) {
    case 3:
        if (f20 < 0.08f) {
            if (f38) {
                fn_80435578(fn_8009AF80(*Entity_GetActor(self)), fn_80085A30(Entity_GetActor(self)) * 20.441538f);
            } else {
                fn_8009AEC8(*Entity_GetActor(self), 0);
                self->s5(2);
            }
        } else if (f20 >= fn_80086DE4(Entity_GetActor(self))) {
            fn_8009AEC8(*Entity_GetActor(self), 0);
            self->s5(4);
        } else if (fn_800CDA20(self)) {
            int f8C = 0xC6;
            Ent &f90 = *fn_800CD9B0(self);
            if (fn_800B0CC0(&f90)) {
                void *f94 = fn_800B1478(&f90);
                if (fn_800A4130(f94))
                    f8C = 0xF2;
                else if (!fn_800A43A0(f94))
                    f8C = 0xD1;
            }
            fn_80097EC4(*Entity_GetActor(self), f8C, f20);
        } else {
            fn_80097EC4(*Entity_GetActor(self), 1, f20);
        }
        break;
    case 4:
        if (f20 < 0.08f) {
            fn_8009AEC8(*Entity_GetActor(self), 0);
            if (f38)
                self->s5(3);
            else
                self->s5(2);
        } else if ((f20 < fn_80086DE4(Entity_GetActor(self)) && f60 < 0.7f) || f20 < 1.0f) {
            self->s5(3);
        } else {
            int f94 = fn_800CC148(self, 0xD);
            if (fn_800CDA20(self)) {
                int f90 = 0xC7;
                Ent &f8C = *fn_800CD9B0(self);
                if (fn_800B0CC0(&f8C)) {
                    void *f98 = fn_800B1478(&f8C);
                    if (fn_800A4130(f98))
                        f90 = 0xF3;
                    else if (!fn_800A43A0(f98))
                        f90 = 0xD2;
                }
                fn_80097EC4(*Entity_GetActor(self), f90, f20);
            } else {
                if (f94 && fn_80085FDC(Entity_GetActor(self))
                    && (fn_80084B68(Entity_GetActor(self), fn_800B1884(*Entity_GetActor(self), 0x1E))
                        || fn_8009AFC8(*Entity_GetActor(self)) == 3)) {
                    f40 = 1;
                    if (!fn_80084A60(Entity_GetActor(self), fn_80426A84(lbl_80593BE8) * fn_800B1884(*Entity_GetActor(self), 0x1E))) {
                        f40 = 0;
                        goto walk;
                    }
                    if (fn_8009AFC8(*Entity_GetActor(self)) != 3) {
                        fn_80097CE8(*Entity_GetActor(self), 3, 1, 30.0f, 0, 7.5f, -1.0f);
                        if (!self->h) {
                            self->h = fn_80393D0C(*Entity_GetActor(self), fn_800ACD20(*Entity_GetActor(self), 0x64), 0xFF, 0xFF);
                            if (self->h)
                                self->h->s56();
                        }
                    }
                    fn_80098008(*Entity_GetActor(self), f20);
                } else {
                walk:
                    if (f24 < -0.6f) {
                        int f98 = fn_80097CE8(*Entity_GetActor(self), 0x13, 0, 30.0f, 0, 7.5f, -1.0f);
                        if (f98 > 0) {
                            fn_800BD2D0(self, f98);
                            return;
                        }
                    }
                    if (fn_8009AFC8(*Entity_GetActor(self)) == 3 && self->h) {
                        self->h = fn_80393B28(*Entity_GetActor(self), self->h);
                        if (self->h) {
                            self->h->s54();
                            self->h = 0;
                        }
                    }
                    if (fn_8009AFC8(*Entity_GetActor(self)) != 2)
                        fn_80097CE8(*Entity_GetActor(self), 2, 1, 30.0f, 0, 7.5f, -1.0f);
                    fn_80098008(*Entity_GetActor(self), f20);
                }
            }
        }
        break;
    case 2:
        if (f60 >= 0.7f && !fn_800CDA20(self)) {
            int f98 = 0x22;
            float f9C = fn_8042EBF4(&v50, fn_800B17A8(*Entity_GetActor(self)));
            if ((f9C < 0.0f ? -f9C : f9C) > (f24 < 0.0f ? -f24 : f24)) {
                if (f9C > 0.0f) {
                    fn_8042DC84(&self->v470, fn_800B17A8(*Entity_GetActor(self)));
                    f98 = 0x24;
                    self->f18 |= 0x1000000;
                } else {
                    fn_8042D80C(&self->v470, fn_800B17A8(*Entity_GetActor(self)));
                    f98 = 0x23;
                    self->f18 |= 0x1000000;
                }
            } else if (f24 < 0.0f) {
                fn_8042D80C(&self->v470, fn_800B1750(*Entity_GetActor(self)));
                f98 = 0x25;
                self->f18 |= 0x1000000;
            }
            int f94 = fn_80097CE8(*Entity_GetActor(self), f98, 0, 30.0f, 0, 7.5f, -1.0f);
            if (f94 > 0) {
                self->s5(4);
                fn_800BD2D0(self, f94);
                return;
            }
        } else if (f60 != 0.0f && !fn_800CDA20(self)) {
            self->f55C += fn_8042F024(lbl_80593BE8);
            if (self->f55C <= 0xF9)
                f60 = 0.0f;
        }
        if (f20 >= fn_80086DE4(Entity_GetActor(self))) {
            if (f60 != 0.0f) {
                fn_8009AEC8(*Entity_GetActor(self), 0);
                self->s5(4);
            } else {
                fn_80066604(*Entity_GetActor(self));
                f20 = 0.0f;
            }
        } else if (f20 > 0.08f || f38) {
            if (f60 != 0.0f) {
                fn_8009AEC8(*Entity_GetActor(self), 0);
                self->s5(3);
            } else {
                fn_80066604(*Entity_GetActor(self));
                f20 = 0.0f;
            }
        } else if (fn_800CDA20(self)) {
            int f98 = 0xC5;
            Ent &f94 = *fn_800CD9B0(self);
            if (fn_800B0CC0(&f94)) {
                void *f90 = fn_800B1478(&f94);
                if (fn_800A4130(f90))
                    f98 = 0xEB;
                else if (!fn_800A43A0(f90))
                    f98 = 0xD0;
            }
            fn_80097CE8(*Entity_GetActor(self), f98, 1, 30.0f, 0, 7.5f, -1.0f);
        } else if (fn_800CCA88(self)) {
            fn_80097CE8(*Entity_GetActor(self), 0x1D, 1, 30.0f, 0, 7.5f, -1.0f);
        } else {
            fn_80097CE8(*Entity_GetActor(self), 4, 1, 30.0f, 0, 7.5f, -1.0f);
        }
        break;
    }
    Vector vA0;
    float f9C;
    if (f60 == 0.0f || f24 < 0.0f) {
        f9C = 0.0f;
    } else if (f60 < 0.7f) {
        float fB0 = fn_80086D9C(Entity_GetActor(self));
        f9C = fB0 * 0.5f + (fB0 - fB0 * 0.5f) * f60;
    } else {
        if (fn_800CC148(self, 8) && fn_8008612C(Entity_GetActor(self))) {
            switch (fn_800D14F0(self)) {
            case 1:
                self->s5(0x19);
                return;
                break;
            case 2:
                self->s5(0x1A);
                return;
                break;
            case 0:
                break;
            default:
                break;
            }
        }
        if (f40)
            f9C = fn_800B1884(*Entity_GetActor(self), 0x9D);
        else
            f9C = fn_80086D54(Entity_GetActor(self));
    }
    if (fn_800CDA20(self)) {
        void *f98 = fn_800B1478(fn_800CD9B0(self));
        float fB0;
        if (fn_800A4130(f98))
            fB0 = fn_800B1884(*Entity_GetActor(self), 0x6D);
        else if (fn_800A43A0(f98))
            fB0 = fn_800B1884(*Entity_GetActor(self), 0x69);
        else if (fn_800A4408(f98))
            fB0 = fn_800B1884(*Entity_GetActor(self), 0x6A);
        else
            fB0 = fn_800B1884(*Entity_GetActor(self), 0x6B);
        f9C = f9C < fB0 ? f9C : fB0;
    }
    if (f9C > f20) {
        float fB0 = fn_800B1884(*Entity_GetActor(self), 0x3D);
        float fB4 = f20 + f8 * f8 * fn_80426A84(lbl_80593BE8) * 0.2f * fB0;
        f9C = f9C < fB4 ? f9C : fB4;
    } else if (f9C < f20) {
    }
    if (f9C != 0.0f && f60 != 0.0f)
        fn_8006668C(*Entity_GetActor(self), 0.0f);
    else
        fn_8006668C(*Entity_GetActor(self), 4.0f);
    fn_8042FDBC(&vA0, &v68, f9C);
    vA0.z += v10.z;
    vA0.z = vA0.z < 1.8f ? vA0.z : 1.8f;
    if (f3C) {
        fn_8042D854(&vA0, &v78);
        fn_8042D854(&vA0, &self->v540);
    }
    fn_80065CB0(*Entity_GetActor(self), &vA0);
    if (fn_800CC6AC(self) == 2 && f20 < 0.1f && f60 == 0.0f && !f38 && !fn_800CDA20(self) && !(self->f18 & 0x40000000)
        && self->fE0 < fn_8042EFF8(lbl_80593BE8)) {
        Vector vB8;
        fn_80429090(&vB8, fn_800B1724(*Entity_GetActor(self)), fn_800B1750(*Entity_GetActor(self)),
                    2.0f * fn_800B2670(*Entity_GetActor(self)));
        if ((float)fn_80171F8C() * 4.656612873077393e-10f < 0.2f
            && !fn_80048EBC(self->s22(), &vB8, 0, 0, Entity_GetActor(self)->s21(), -0.11f, 0)) {
            int f98 = fn_80097CE8(*Entity_GetActor(self), 5, 0, 30.0f, 0, 7.5f, -1.0f);
            self->fE0 = fn_8042EFF8(lbl_80593BE8) + 24000;
        } else {
            self->fE0 = fn_8042EFF8(lbl_80593BE8) + 12000;
        }
    }
}
