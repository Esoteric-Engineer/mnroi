// Melee state (0xB) update: faces the target, carries it while flag 0x400 is set (event 0x59), and routes combo inputs.

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
    Vector(float x, float y, float z, float w) __asm__("fn_8042D768");
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
    virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
    virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41();
    virtual void s42(); virtual void s43(); virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
    virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53();
    virtual void s54(); virtual void s55(); virtual void s56();
    virtual int s57(float t); // +0x1D0
    virtual int s58(float a, Vector *v, float b); // +0x1D8
};

struct EObj {
    char pad0[0x10];
    unsigned int flags; // +0x10
    char pad14[0x18 - 0x14];
    unsigned int f18;
    char pad1C[0x3AC - 0x1C];
};

struct Obj : EObj {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(int state); // +0x30
};

struct Melee : Obj {
    char pad3B0[0x400 - 0x3B0];
    int i400;
    char pad404[0x4E4 - 0x404];
    int h4E4;
};

extern char lbl_80593BE8[];

extern "C" {
PEnt *Entity_GetActor(void *self);
ActBase *Entity_GetActorV(void *self) __asm__("Entity_GetActor");
int fn_80085EEC(void *actor);
void fn_800C7BEC(void *self);
void fn_800C05BC(void *self);
int fn_800CC76C(void *self);
void fn_800C8098(void *self);
int fn_800CC2E0(void *self);
int fn_8009B04C(Ent &actor);
void fn_800BDFFC(void *self);
int fn_8008582C(void *actor);
int fn_800C4D70(void *self, int a, float f, int b);
int fn_800CC79C(void *self);
int fn_800E0458(void *self);
void fn_80066604(Ent &actor);
void fn_800C64A0(void *self, float z);
int fn_80097CE8(Ent &actor, int a, int mode, float speed, void *set, float blend, float f);
void fn_800BD2D0(void *self, int handle);
int fn_800DDCB4(void *self, int a, int b);
void fn_800BEAC0(void *self, int v);
void fn_80067050(Ent &actor, Vector *v);
float fn_800B1884(Ent &actor, int id);
float fn_80426A84(void *p);
int fn_80084A60(void *actor, float f);
void fn_800D3398(void *self);
void fn_800BE638(void *self);
int fn_800861EC(void *actor);
void fn_8009AEC8(Ent &actor, int v);
Ent *fn_800C9FD0(void *self);
int fn_800B0C58(void *c);
void *fn_800B14A0(void *c);
PEnt *fn_80085954(void *p);
int fn_800CCCBC(Ent &c);
int fn_800CC85C(void *self);
void fn_800BE2F8(void *self, Vector *v);
Vector *fn_800B1724(Ent &actor);
Vector *fn_800B1750(Ent &actor);
void fn_80429038(Vector *out, Vector *a, Vector *b);
float fn_8042EC54(Vector *v);
float fn_8042EBF4(Vector *a, Vector *b);
void fn_8005A9B8(Ent &actor, Vector *dir);
int fn_800CC6DC(Ent &c);
void fn_80065E54(void *p, Vector *v);
void fn_80065CB0(void *p, Vector *v);
void fn_800E8884(void *self);
int fn_800CC0BC(void *self, int id);
void fn_800DD3F8(void *self);
int fn_800C45B0(void *self, int v);
int fn_800DF03C(void *self, int a, int b);
int fn_800E07A4(void *self, int v);
int fn_800CC8BC(void *self);
int fn_800CDA20(void *self);
int fn_800CC148(void *self, int id);
int fn_800E4048(void *self);
float fn_800CC1D4(void *self, int id, Vector *v);
int fn_800CBF20(void *self);
void *fn_800ACFA8(int handle);
void fn_80066A48(Ent &actor, void *p);
}

extern "C" void fn_800DBF1C(register Melee *self)
{
    int f8 = 1;
    int fc = 0;
    Vector v10 = Vector(0.0f, 0.0f, 1.0f, 1.0f);
    if (fn_80085EEC(Entity_GetActor(self))) {
        self->s5(1);
        return;
    }
    fn_800C7BEC(self);
    fn_800C05BC(self);
    if (fn_800CC76C(self))
        fn_800C8098(self);
    if (fn_800CC2E0(self)) {
        int f20 = 0;
        switch (fn_8009B04C(*Entity_GetActor(self))) {
        case 0x37:
        case 0x38:
        case 0x3B:
        case 0xF0:
            self->f18 |= 0x80000000;
            fn_800BDFFC(self);
            fc = 1;
            if (fn_8008582C(Entity_GetActor(self)))
                f8 = 1;
            if (fn_800C4D70(self, 0, 0.0f, 0))
                return;
            break;
        case 0x48:
        case 0x49:
        case 0x4A:
        case 0x4B:
            self->f18 |= 0x80000000;
            fn_800BDFFC(self);
            fc = 1;
            if (!fn_800CC79C(self) && Entity_GetActorV(self)->s57(0.15f) && !fn_800E0458(self)) {
                fn_80066604(*Entity_GetActor(self));
                fn_800C64A0(self, 0.0f);
                return;
            }
            break;
        case 0x39:
            self->f18 |= 0x80000000;
            fn_800BDFFC(self);
            fc = 1;
            if (fn_800C4D70(self, 1, 0.0f, 0)) {
                fn_80097CE8(*Entity_GetActor(self), 4, 1, 30.0f, 0, 7.5f, -1.0f);
                fn_800BD2D0(self, 0);
                fn_800DDCB4(self, 0x3A, 0);
                return;
            }
            break;
        case 0x3C:
            self->f18 |= 0x80000000;
            fn_800BDFFC(self);
            fc = 1;
            if (fn_800C4D70(self, 1, 0.0f, 0)) {
                fn_80097CE8(*Entity_GetActor(self), 4, 1, 30.0f, 0, 7.5f, -1.0f);
                fn_800BD2D0(self, 0);
                fn_800DDCB4(self, 0x3D, 0);
                return;
            }
            break;
        case 0xAC:
        case 0xAD:
        case 0xAE:
        case 0xB3:
        case 0xB4:
        case 0xB5:
            self->f18 |= 0x80000000;
            f8 = 0;
            if (!fn_800CC79C(self) && fn_800C4D70(self, 1, 0.0f, 0)) {
                fn_800BEAC0(self, 0);
                if (!fn_800E0458(self)) {
                    Vector v28;
                    fn_80067050(*Entity_GetActor(self), &v28);
                    fn_800C64A0(self, v28.z);
                }
            }
            fn_800BDFFC(self);
            fc = 1;
            break;
        case 0x50:
        case 0x5F:
        case 0x9F:
        case 0xA0:
        case 0xA1:
        case 0xA2:
        case 0xA3:
        case 0xA4:
        case 0xBA:
        case 0xBB:
        case 0xBC:
            self->f18 &= ~0x80000000;
            f8 = 0;
            break;
        case 0x3E:
        case 0x3F:
        case 0x40:
            self->f18 |= 0x80000000;
            fn_80084A60(Entity_GetActor(self), fn_800B1884(*Entity_GetActor(self), 0x29) * fn_80426A84(lbl_80593BE8));
            fn_800D3398(self);
            fn_800BE638(self);
            fc = 1;
            break;
        default:
            self->f18 &= ~0x80000000;
            if (!fn_800861EC(Entity_GetActor(self)) && !(self->flags & 2) && !Entity_GetActorV(self)->s58(0.7f, &v10, 0.7f)) {
                fn_8009AEC8(*Entity_GetActor(self), 0);
                self->s5(5);
                return;
            }
        }
        if (fn_800C9FD0(self) && fn_800B0C58(fn_800C9FD0(self)) && fn_80085954(fn_800B14A0(fn_800C9FD0(self)))
            && fn_800CCCBC(*fn_80085954(fn_800B14A0(fn_800C9FD0(self)))))
            f8 = 0;
        if (fn_800CC85C(self)) {
            fn_80066604(*Entity_GetActor(self));
        } else if (!fc) {
            if (self->flags & 2)
                fn_800BDFFC(self);
            else
                fn_800BE2F8(self, &v10);
        }
        if (fn_800C9FD0(self)) {
            if (f8 && fn_800B0C58(fn_800C9FD0(self)) && fn_80085954(fn_800B14A0(fn_800C9FD0(self)))
                && fn_800CCCBC(*fn_80085954(fn_800B14A0(fn_800C9FD0(self)))))
                f8 = 0;
            if (f8) {
                Vector v28;
                fn_80429038(&v28, fn_800B1724(*fn_800C9FD0(self)), fn_800B1724(*Entity_GetActor(self)));
                v28.z = 0.0f;
                float f38 = fn_8042EC54(&v28);
                if (f38 > 0.4f && fn_8042EBF4(&v28, fn_800B1750(*Entity_GetActor(self))) > 0.5f)
                    fn_8005A9B8(*Entity_GetActor(self), &v28);
            }
            if (fn_800B0C58(fn_800C9FD0(self)) && fn_80085954(fn_800B14A0(fn_800C9FD0(self)))
                && fn_800CC6DC(*fn_80085954(fn_800B14A0(fn_800C9FD0(self)))) == 0xD)
                self->flags &= ~0x400;
            if (self->flags & 0x400) {
                void *f3c = fn_800B14A0(fn_800C9FD0(self));
                Vector v28;
                if (f3c && fn_800B0C58(f3c)) {
                    fn_80065E54(f3c, fn_800B1724(*Entity_GetActor(self)));
                    fn_80067050(*Entity_GetActor(self), &v28);
                    fn_80065CB0(f3c, &v28);
                }
            }
        }
        fn_800E8884(self);
        if (self->flags & 4) {
            if (fn_800CC0BC(self, 2) || self->flags & 0x800) {
                if (self->i400) {
                    fn_800DD3F8(self);
                    return;
                }
            }
            if (fn_800CC0BC(self, 5) || self->flags & 8) {
                if (Entity_GetActorV(self)->s57(0.15f)) {
                    fn_800BEAC0(self, 0);
                    if (fn_800C45B0(self, 0))
                        return;
                }
            }
            if (fn_800CC0BC(self, 0x12) || self->flags & 0x20000) {
                fn_800BEAC0(self, 0);
                if (Entity_GetActorV(self)->s57(0.15f)) {
                    if (fn_800DF03C(self, 0, 0))
                        return;
                } else {
                    if (fn_800E07A4(self, 0))
                        return;
                }
            }
        } else {
            if (fn_800CC0BC(self, 2) && self->i400) {
                self->flags |= 0x800;
                self->flags &= ~0x20008;
            }
            if (fn_800CC0BC(self, 5)) {
                self->flags |= 8;
                self->flags &= ~0x20800;
            }
            if (fn_800CC0BC(self, 0x12)) {
                self->flags |= 0x20000;
                self->flags &= ~0x808;
            }
        }
        if (self->flags & 0x10000) {
            if (fn_800CC0BC(self, 5) || self->flags & 8) {
                if (Entity_GetActorV(self)->s57(0.15f) && fn_800C45B0(self, 0))
                    return;
            }
        }
        if (fn_800CC8BC(self)) {
            if (fn_800CC0BC(self, 2)) {
                self->s5(2);
                if (fn_800DDCB4(self, 0, 0))
                    return;
            }
            if (fn_800CC0BC(self, 0x12)) {
                if (Entity_GetActorV(self)->s57(0.15f)) {
                    if (fn_800DF03C(self, 0, 0))
                        return;
                } else {
                    if (fn_800E07A4(self, 0))
                        return;
                }
            }
            if (Entity_GetActorV(self)->s57(0.15f)) {
                if (!fn_800CDA20(self)) {
                    if (fn_800CC148(self, 0xC) && fn_800E4048(self))
                        return;
                    if (fn_800CC148(self, 0)) {
                        self->s5(0x15);
                        return;
                    }
                }
                if (fn_800CC148(self, 0xB) && !fn_800CDA20(self)) {
                    self->s5(0xE);
                    return;
                }
                if (fn_800CC0BC(self, 5) && fn_800C45B0(self, 0)) {
                    self->f18 &= ~0x80;
                    return;
                }
                Vector v28;
                float f38 = fn_800CC1D4(self, 0, &v28);
                if (f38 > 0.1f) {
                    fn_800BD2D0(self, 0);
                    fn_8009AEC8(*Entity_GetActor(self), 0);
                    self->s5(4);
                }
            } else if (fn_800CC148(self, 9) && fn_800CBF20(self)) {
                if (fn_800861EC(Entity_GetActor(self)))
                    self->s5(0x25);
                else
                    self->s5(0x17);
            }
        }
        return;
    } else {
        self->f18 &= ~0x80000000;
    }
    switch (fn_8009B04C(*Entity_GetActor(self))) {
    case 0x9F:
    case 0xA0:
    case 0xA1:
    case 0xA2:
    case 0xA3:
    case 0xA4:
    case 0xAC:
    case 0xAD:
    case 0xAE:
    case 0xB3:
    case 0xB4:
    case 0xB5:
    case 0xBA:
    case 0xBB:
    case 0xBC: {
        void *f3c = fn_800ACFA8(self->h4E4);
        if (f3c)
            fn_80066A48(*Entity_GetActor(self), f3c);
        break;
    }
    default:
        break;
    }
    if (Entity_GetActorV(self)->s57(0.15f))
        self->s5(2);
    else
        self->s5(5);
    fn_8009AEC8(*Entity_GetActor(self), 0);
    fn_800BD2D0(self, 0);
}
