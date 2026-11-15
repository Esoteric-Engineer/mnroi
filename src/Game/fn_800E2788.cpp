// Melee state (0xB) contact callback: deals the armed hit (f3F4 bit 8) through fn_800E7A4C.

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
    virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
    virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41();
    virtual void s42(); virtual void s43(); virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
    virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53();
    virtual void s54(); virtual void s55(); virtual void s56();
    virtual int s57(float t); // +0x1D0
};

struct Contact {
    char pad0[0x10];
    void *p10;
};

struct Obj {
    char pad0[0x18];
    unsigned int f18;
    char pad1C[0x3F4 - 0x1C];
    unsigned int f3F4;
    char pad3F8[0x408 - 0x3F8];
    char b408;
};

extern "C" {
PEnt *Entity_GetActor(void *self);
ActBase *Entity_GetActorV(void *self) __asm__("Entity_GetActor");
int fn_8009B04C(Ent &actor);
int fn_800B0CC0(void *actor);
PEnt *fn_800C9FD0(void *self);
int fn_800CD064(void *self);
void *fn_80436684(void *p);
void *fn_804366AC(void *p);
void fn_80434BA4(Vector *out, void *v);
void fn_800E7A4C(void *self, void *a, void *b, void *c, void *d, unsigned char e, int f, int g, int h, int i);
void fn_800E893C(void *self);
}

extern "C" int fn_800E2788(register Obj *self, PEnt *other, Contact *c, int a, int b)
{
    int f20 = fn_8009B04C(*Entity_GetActor(self));
    if (other && fn_800B0CC0(other) && other == fn_800C9FD0(self) && !fn_800CD064(self) && Entity_GetActorV(self)->s57(0.15f))
        self->f18 |= 0x100000;
    if (self->f3F4 & 8 && other) {
        Vector v28;
        Vector v38;
        self->f3F4 &= ~8;
        fn_80434BA4(&v28, fn_80436684(c->p10));
        fn_80434BA4(&v38, fn_804366AC(c->p10));
        self->b408 = 0;
        fn_800E7A4C(self, other, &v28, &v38, 0, 0, 1, 0xFF, 0xFF, 0);
        fn_800E893C(self);
        return 1;
    }
    return 0;
}
