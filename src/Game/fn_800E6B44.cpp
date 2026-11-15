// fn_800E6B44 is the one-shot hit of events 0x05 and 0x1F-0x21 (volumes 0, 1, 4, 5).
// In Melee motions 0x9F-0xBC it lands at the volume's attachment at once, otherwise it tests the volume (fn_800F46D8).
// fn_800E6D54 lands a hit on an actor: the target's block, redirect or BlockBroken first, then damage (fn_8002FD50) and the target's reaction.
// See docs/characters.md.

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

struct Act : ActBase {
    int pad;
};

struct Fx {
    char d[0x10];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(Vector *pos, int a, int b); // +0x30
};

struct EObj {
    char pad0[0x10];
    unsigned int f10; // +0x10
    char pad14[0x18 - 0x14];
    unsigned int f18; // +0x18
    char pad1C[0x3AC - 0x1C];
};

struct EBase : EObj {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(int mode); // +0x30
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void s35(); virtual void s36();
    virtual int s37(int id, Vector *pos, int a, float f, int b, int c, int d, int e); // +0x130
    virtual void s38(Vector *pos, int a, int b, int c); // +0x138
};

struct ESub : EBase {
    int pad;
};

struct Slot {
    char pad[0x80];
};

struct Self : EBase {
    char pad3B0[0x3F4 - 0x3B0];
    unsigned int f3F4; // +0x3F4, hit flags
    float f3F8; // +0x3F8, hit strength
    int f3FC; // +0x3FC, hit reaction
    int f400;
    float f404; // +0x404
    char pad408[0x414 - 0x408];
    float f414; // +0x414, energy cost
    float f418; // +0x418
    char pad41C[0x580 - 0x41C];
    Slot slots[7]; // +0x580
};

extern void *lbl_8066C6C8;

extern "C" {
PEnt *Entity_GetActor(void *self);
int fn_80084A60(void *actor, float f);
int fn_800CD064(void *self);
PEnt *fn_800C9FD0(void *self);
void *fn_8009AD80(Ent &actor);
int fn_801A5104(void *model, unsigned char kind, unsigned short index, Vector *out, int e);
Vector *fn_800B1750(Ent &actor);
void fn_800E7A4C(Self *self, Ent *a, Vector *b, Vector *c, int d, unsigned char e, int f, int g, int h, int i);
void fn_800F46D8(Slot *slot);

void *fn_800CE5B0(void *self);
void fn_80130F88(void *a, void *b);
ESub *fn_80085954(void *actor);
int fn_80085F4C(void *actor);
int fn_800CC82C(EBase *c);
int fn_800CC60C(void *c);
int fn_800CC60CR(Ent &c) __asm__("fn_800CC60C");
PEnt *fn_80085954P(void *actor) __asm__("fn_80085954");
int fn_800CCC28(EBase *c);
int fn_8009B04C(Ent &actor);
int fn_800CC9D8(EBase *c);
int fn_800CC6DC(EBase *c);
void fn_800D98B0(void *actor, float a, float b, int c);
float fn_8042EBF4(Vector *a, Vector *b);
void fn_800D9408(void *actor, void *src, char *msg, int a, int b);
void fn_800DDCB4(EBase *c, int motion, int z);
float fn_80433D20(void *record, int id, int slot);
void fn_80086818(void *actor, float f);
void fn_800E673C(void *self, int a, int b, void *c, int d, int e, unsigned char flags, unsigned char f2);
int fn_800B18EC(void *actor, int id);
void fn_800E8628(void *c, int reaction);
int fn_800CDA20(void *self);
void *fn_800CD9B0(void *self);
PEnt *fn_800B1478(void *c);
int fn_800A4130(void *p);
unsigned int fn_8009ABEC(Ent &e);
int fn_800E82C0(void *self, int x);
void *fn_800B1568(Ent &e);
int fn_8009ABC0(void *p);
void fn_8010D050(void *actor, int event, int bank, int a2, int a3, void *target, int a5);
int fn_8008627C(void *actor);
Vector *fn_800B1724(Ent &actor);
void fn_8005A828(void *actor, Vector *v);
void fn_800E8508(EBase *c, int reaction);
void fn_80086A2C(void *actor, float f);
float fn_800B1884(void *actor, int id);
float fn_8002FD50(void *self, void *src, int kind, int type, float dmg, int p20, int p24, unsigned int flags, int p2C,
                  float f30, int *blocked, Vector *pBC, int pC0, int pC4);
int fn_800CD21C(EBase *c);
int fn_800B13D8(Ent &actor);
void fn_80041588(void *actor, void *src, int a);
int fn_80085EEC(void *actor);
int fn_80085F1C(void *actor);
int fn_80085EBC(void *actor);
Fx *fn_800707CC(void *actor);
void fn_8042FDBC(Vector *out, Vector *v, float f);
void fn_80040B98(void *actor, Vector *v, int a);
int fn_800B0C1C(void *c);
void *fn_800B14C8(void *c);
EBase *fn_80085928(void *p);
}

extern "C" void fn_800E6B44(register Self *self, unsigned int slot)
{
    Vector pos;
    int kind;
    int index;
    if (!(self->f10 & 0x1000) && self->f414 != 0.0f) {
        fn_80084A60(Entity_GetActor(self), self->f414);
        self->f10 |= 0x1000;
    }
    if (fn_800CD064(self)) {
        if (!fn_800C9FD0(self))
            return;
        switch (slot) {
        case 0:
            kind = 0x15;
            index = 1;
            break;
        case 1:
            kind = 0x15;
            index = 2;
            break;
        case 4:
            kind = 0x13;
            index = 2;
            break;
        case 5:
            kind = 0x13;
            index = 1;
            break;
        }
        if (!fn_801A5104(fn_8009AD80(*Entity_GetActor(self)), kind, index, &pos, 0))
            return;
        self->f3FC = 0;
        fn_800E7A4C(self, fn_800C9FD0(self), &pos, fn_800B1750(*Entity_GetActor(self)), 0, 0, 1, 0xFF, 0xFF, 0);
    } else {
        Slot *s = &self->slots[slot];
        fn_800F46D8(s);
    }
}

extern "C" void fn_800E6D54(register Self *self, Act *a, int b, int c, int d, unsigned char e, int f, int g, int h)
{
    fn_80130F88(fn_800CE5B0(self), a);
    ESub *tc = fn_80085954(a);
    int blocking = 0;
    int superblock = 0;
    int i40 = 0;
    int stopped = 0;
    unsigned char fl = 0;
    float dot;
    float angle;
    float cone;
    float guard;
    int id;
    int x;
    if (fn_80085F4C(a))
        return;
    if (fn_800CC82C(tc))
        return;
    if (fn_800CC60C(self) && fn_80085954(a) && fn_800CC60CR(*fn_80085954P(a)))
        return;
    if (fn_800CCC28(tc)) {
        switch (fn_8009B04C(*Entity_GetActor(self))) {
        case 0x2C: case 0x2D:
        case 0x33: case 0x34: case 0x35:
        case 0x39: case 0x3A:
        case 0x3C: case 0x3D:
        case 0x42:
        case 0x45:
        case 0x48: case 0x49: case 0x4A: case 0x4B:
        case 0xF1:
            break;
        default:
            return;
        }
    }
    if (fn_800CC9D8(tc)) {
        blocking = 1;
        fl |= 4;
        if (fn_800CC6DC(tc) == 0x16) {
            superblock = 1;
            fl |= 2;
            stopped = 1;
            fl &= ~8;
            fn_800D98B0(a, self->f3F8, 0.0f, 1);
        } else {
            if (fn_8042EBF4(fn_800B1750(*Entity_GetActor(self)), fn_800B1750(*a)) < -0.56 && fn_800CC6DC(tc) == 0x15
                && fn_8009B04C(*a) == 0x4D && (tc->f10 & 1)) {
                if (self->f10 & 0x2000) {
                    fn_800D9408(a, Entity_GetActor(self), "SoftRedirect", 0, 0xFFA08000);
                    fn_800DDCB4(tc, 0x50, 0);
                    self->s37(0x5F, 0, 0, 1.0f, 0, 0, 0, 0);
                } else {
                    fn_800D9408(a, Entity_GetActor(self), "HardRedirect", 0, 0xFFA08000);
                    fn_800DDCB4(tc, 0x4F, 0);
                    self->s37(0x5E, 0, 0, 1.0f, 0, 0, 0, 0);
                }
                fn_80086818(a, fn_80433D20(lbl_8066C6C8, 5, 0));
                fl |= 0x10;
                fn_800E673C(self, 1, d, a, b, c, fl, e);
                return;
            }
            dot = fn_8042EBF4(fn_800B1750(*Entity_GetActor(self)), fn_800B1750(*a));
            angle = 140.0f;
            cone = angle / 180.0f + -1.0f;
            guard = fn_800B18EC(a, d + 0x81);
            if (dot > cone) {
                stopped = 0;
                fl &= ~8;
            } else if (guard < self->f3F8) {
                fn_800D9408(Entity_GetActor(self), 0, "BlockBroken", 0, 0xFFA08000);
                fl |= 0x20;
                fn_800E8628(fn_80085954(a), self->f3FC);
                self->f3FC = 0;
                stopped = 1;
            } else {
                fn_800D98B0(a, self->f3F8, guard, 0);
                stopped = 1;
                fl |= 8;
            }
        }
    }
    fn_800E673C(self, 1, d, a, b, c, fl, e);
    id = 200;
    if (fn_800CDA20(self) && fn_800CD9B0(self) && fn_800A4130(fn_800B1478(fn_800CD9B0(self))))
        id = fn_8009ABEC(*fn_800B1478(fn_800CD9B0(self)));
    else if ((g == 0x28 || g == 0x2A) && (h == 1 || h == 2))
        id = 210;
    else if (self->f18 & 0x1000)
        id = 201;
    x = fn_800E82C0(self, self->f3FC);
    fn_8010D050(Entity_GetActor(self), 9, id, x, fn_8009ABC0(fn_800B1568(*Entity_GetActor(self))), a, 0);
    if (stopped) {
        if (superblock) {
            if (fn_8008627C(a))
                self->s38(fn_800B1724(*a), 0x100, 0, 0);
        } else {
            fn_8005A828(a, fn_800B1724(*Entity_GetActor(self)));
            fn_800E8508(tc, self->f3FC);
        }
        fn_80086818(a, fn_80433D20(lbl_8066C6C8, 4, 0));
        return;
    }
    fn_80086A2C(Entity_GetActor(self), self->f418);
    fn_80086A2C(a, -self->f418 * fn_800B1884(a, 0xC2));
    fn_8002FD50(a, Entity_GetActor(self), 1, d, self->f3F8, b, c, self->f3F4 | 0x10000000, f, 0.0f, 0,
                fn_800B1750(*Entity_GetActor(self)), g, h);
    if ((self->f3FC != 0x7E) & fn_800CCC28(tc))
        self->f3FC = 0x7D;
    if (fn_800CD21C(tc) && fn_8009B04C(*a) != 0x72 && fn_8009B04C(*Entity_GetActor(self)) == 0x37 && !a->s57(0.15f)) {
        tc->s37(0x7F, fn_800B1724(*Entity_GetActor(self)), 1, self->f404, 0, fn_800B13D8(*Entity_GetActor(self)), 0, 0);
        fn_80041588(a, Entity_GetActor(self), 1);
    } else if (self->f3FC) {
        tc->s37(self->f3FC, fn_800B1724(*Entity_GetActor(self)), 1, self->f404, 0, fn_800B13D8(*Entity_GetActor(self)), 0,
                0);
        fn_80041588(a, Entity_GetActor(self), 1);
    }
    if (!fn_80085EEC(a) && !fn_80085F1C(a)) {
    } else {
        fn_800D9408(Entity_GetActor(self), a, "Killed", 0, 0xFFA08000);
        if (fn_80085EBC(a)) {
            Fx *fx = fn_800707CC(a);
            if (fx) {
                Vector v;
                fn_8042FDBC(&v, fn_800B1750(*Entity_GetActor(self)), 100.0f);
                fx->s5(&v, 0, 0);
                fn_80040B98(Entity_GetActor(self), &v, 0);
            }
        }
    }
    int m = fn_8009B04C(*Entity_GetActor(self));
    if (m == 0x4A && a && fn_800B0C1C(a) && fn_800CCC28(fn_80085928(fn_800B14C8(a))))
        self->s5(5);
}
