// fn_800DDCB4 starts an attack: finds the target, splits near from far (PLAYER fields 1 and 2) and picks the motion.
// fn_800DEDB4 tries the attack named by the target's PLAYER string 0xCE + fn_8009AC68(target), flags 0x2000 in a versus match; fn_800DF03C starts a grab or throw.

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

class Global
{
public:
    char pad0[0x28];
    int unk28; // +0x28
};

struct State {
    char pad[0x75C];
};

class Ent
{
public:
    int pad;
    char *GetString(int id) __asm__("fn_800ACD20");
    int IsAlive() __asm__("fn_800B13D8");
};

struct ActBase : Ent {
    char d[0x194];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(Vector *out, int mode); // +0x30
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20();
    virtual int s21(); // +0xB0
    virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
    virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41();
    virtual void s42(); virtual void s43(); virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
    virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53();
    virtual void s54(); virtual void s55(); virtual void s56();
};

struct Act : ActBase {
    virtual int s57(float t); // +0x1D0
    char pad19C[0x304 - 0x19C];
    unsigned int f304;
    unsigned int abilities; // +0x308, ACTOR_ABILITIES
};

struct ActSub : Act {
    int pad;
};

class Actor60
{
public:
    void clearX();
};

struct Slot {
    char pad0[0x30];
} __attribute__((aligned(8)));

struct Query {
    char pad0[0x40];
    Slot slot[0x80]; // +0x40
    unsigned int count; // +0x1840
    char pad1844[0x1850 - 0x1844];
};

struct EObj {
    char pad0[0x10];
    unsigned int f10;
    char pad14[0x18 - 0x14];
    unsigned int f18;
    char pad1C[0xE0 - 0x1C];
    unsigned int fE0; // a time on the fn_8042EFF8 clock
    Ent *fE4; // the actor
    char padE8[0x3AC - 0xE8];
};

struct EBase : EObj {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(int state); // +0x30
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21();
    virtual void *s22(); // +0xB8
    virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28();
    virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void s35(); virtual void s36();
    virtual void s37(int state, int a, int b, float f, void *set, int id, int c, int d); // +0x130
};

struct Obj : EBase {
    char pad3B0[0x3EC - 0x3B0];
    char b3EC;
    char pad3ED[0x3F4 - 0x3ED];
    int f3F4;
    char pad3F8[0x404 - 0x3F8];
    float f404;
    char pad408[0x409 - 0x408];
    char b409;
    char b40A;
    char b40B;
    char b40C;
    int f410;
    float f414; // energy cost of the motion, set by fn_800DA884
    float f418; // rage points of the motion
    char pad41C[0x4E4 - 0x41C];
    int f4E4; // id of the grabbed entity
};

extern State lbl_80552110; // the game-state object G
extern Global *lbl_8066D654;
extern char lbl_8057217C[];
extern int lbl_8066BA80;
extern void *lbl_8066BE10;
extern char lbl_80593BE8[];

extern "C" {
int fn_80432844(State *g);
int fn_80432870(State *g);
int fn_800B0C58(void *actor);
void fn_800924BC(State *g);
Act *Entity_GetActor(void *self);
int fn_8009AC68(void *actor);
unsigned int strlen(const char *s);
int fn_80171F8C();
int fn_800578E4(char *a, Global *b, void *c, void *d, int e, int f, int g);
void fn_80086410(void *actor);
void fn_8007EBE4(void *a, void *b);
int fn_800CC148(void *self, int id);
int fn_8008606C(void *actor);
int fn_800860CC(void *actor);
Ent *fn_800CD9B0(void *self);
int fn_800B0CC0(void *c);
void *fn_800B1478(void *c);
int fn_800A4130(void *p);
void fn_800E893C(void *self);
int fn_800BEAC0(void *self, int v);
Vector *fn_800B1750(Ent &actor);
void fn_8042DC84(Vector *dst, Vector *src);
Ent *fn_800C9FD0(void *self);
float fn_800CC1D4(void *self, int id, Vector *v);
int fn_800CC60C(void *self);
int fn_80086374(void *actor);
float fn_800B1884(Ent &actor, int id);
Ent *fn_800E9AF8(void *self, float a, float b, float c, int d, Vector *dir);
Ent *fn_800E89B0(void *self, float a, float b, int c, Vector *dir, int d);
void fn_800CE3F0(void *self);
int fn_800CCA88(void *self);
int fn_80084B68(void *actor, float f);
int fn_8008582C(void *actor);
void *fn_800CE5B0(void *self);
int fn_8043B31C(void *p);
void fn_80428EEC(void *p, int v);
Vector *fn_800B1724(Ent &actor);
void fn_80429038(Vector *out, Vector *a, Vector *b);
Vector *fn_8042FB28(Vector *v);
float fn_8042EC54(Vector *v);
float fn_8042EBF4(Vector *a, Vector *b);
int fn_800B0C1C(void *c);
Act *fn_800B14C8(void *c);
Act *fn_80085954(void *p);
int fn_800CCC28(Ent &e);
void fn_800C98BC(void *self, int a, int b);
int fn_800E5F04(void *self, void *other);
int fn_80085D3C(void *actor);
void fn_8005A9B8(Ent &actor, Vector *dir);
void *fn_8009AE00(Ent &actor);
void *fn_8008FCEC(void *set, int a, int b, float f);
void *fn_800B14A0(void *c);
Ent *fn_80085928(void *p);
void fn_8042F76C(Vector *v);
float fn_801BE3C4(float f);
char *fn_8009AF80(Ent &actor);
int fn_804470BC(void *self, void *a, void *b, float v, float w, int mode);
int fn_80097CE8(Ent &actor, int a, int mode, float speed, void *set, float blend, float f);
void fn_800DA884(void *self, int motion);
int fn_80084A60(void *actor, float f);
void fn_800DBC90(void *self, int v);
void fn_800BD2D0(void *self, int handle);
void fn_8005A828(Ent &actor, Vector *p);
int fn_80447460(void *p);
void fn_8004E9C8(Query *q);
void fn_80434C88(Query *q);
void fn_80434CDC(Query *q, int bit);
void fn_80434D40(Query *q, int v);
void fn_80434D18(Query *q, void *ignore);
void *fn_800B1CC8(Ent &actor);
void fn_8004E4B4(Query *q, Vector *pos, float r, void *world);
Ent *fn_80434C2C(Slot *s);
void fn_800B9CE8(void *a, int b, int c, void *d);
ActSub *fn_800C9FD0A(void *self) __asm__("fn_800C9FD0");
void fn_800C98BCP(void *self, void *e, int b) __asm__("fn_800C98BC");
void fn_8009AEC8(Ent &a, int v);
EBase *fn_80085954O(void *p) __asm__("fn_80085954");
int fn_800CCC28O(EObj &c) __asm__("fn_800CCC28");
Actor60 *fn_8009AF80A(Ent &actor) __asm__("fn_8009AF80");
ActSub *fn_800E89B0A(void *self, float minDot, float radius, int useOwner, Vector *dir, int all) __asm__("fn_800E89B0");
void fn_800C05BC(void *self);
int fn_80085F4C(void *a);
int fn_800CC88C(void *c);
int fn_80085EEC(void *a);
int fn_80085F1C(void *a);
int fn_800CCA08(void *c);
int fn_8009B04C(Ent &a);
int fn_800CC6DC(EObj &c);
int fn_800CD85C(void *c);
int fn_800CE1B0(void *c);
int fn_800B13D8(Ent &a);
int fn_800CD0EC(void *c);
int fn_800CCA58(void *c);
int fn_8004AC84(Vector *a, Vector *b, int c, int id, int mask);
int fn_800866C0(void *a);
int fn_800CCF90(EObj &c);
float fn_80086730(void *a);
float fn_8008677C(void *a);
int fn_800CC9D8(void *c);
void fn_8005AB90(void *e, Vector *dir);
void *fn_800B1568(void *e);
float fn_8008FD58(void *set, int motion);
void fn_8006683C(Ent &a, void *e);
int fn_800B13D8P(void *e) __asm__("fn_800B13D8");
void fn_80429090(Vector *out, Vector *a, Vector *b, float s);
int fn_800B24AC(Ent &e);
int fn_80048EBC(void *a, Vector *v, int b, int c, int d, float f, int e);
void fn_80066A48(Ent &a, void *e);
void fn_800CD364(void *c, int v);
void fn_800DA884(void *self, int motion);
void fn_800C7FF4(EObj &c, Vector *v, float f);
void fn_800CD5A4(EObj &c, int v);
void fn_800CD5EC(void *c, int v);
void fn_80066604(Ent &a);
void fn_8019C514(void *p, int a, int b);
void fn_8009AF28(Ent &a);
void fn_8019C408(void *p);
void fn_800CD7A8(void *c);
void fn_8011C258(void *p, int v);
void fn_8010CDCC(Ent &a, int id, void *e, int b, int c, int d, int f);
void fn_80130F88(void *p, void *e);
void fn_80041588(void *a, void *b, int c);
int fn_8009AFC8(Ent &a);
unsigned int fn_8042EFF8(void *g);
}

extern "C" int fn_800DDCB4(register Obj *self, int motion, int retarget)
{
    int f10 = -1;
    int f14 = 0x27;
    float f18 = 0.0f;
    Vector v20;
    int f30 = 0;
    int f34 = fn_800CC148(self, 0xD);
    int f38 = 1;
    Ent *f3C = 0;
    int f40 = 0;
    Vector v48;
    int f58 = 0;
    Vector v60;
    if (fn_8008606C(Entity_GetActor(self)) && fn_800860CC(Entity_GetActor(self)) && Entity_GetActor(self)->s57(0.15f))
        f34 = 0;
    Ent *f70 = fn_800CD9B0(self);
    if (f70 && fn_800B0CC0(f70) && !fn_800A4130(fn_800B1478(f70)))
        return 0;
    fn_800E893C(self);
    if (fn_800BEAC0(self, 0))
        return 0;
    fn_8042DC84(&v60, fn_800B1750(*Entity_GetActor(self)));
    if (retarget) {
        f3C = fn_800C9FD0(self);
        fn_8042DC84(&v60, fn_800B1750(*Entity_GetActor(self)));
    } else {
        Vector v78;
        float f88 = fn_800CC1D4(self, 0, &v78);
        if (f88 > 0.2f && !fn_800CC60C(self))
            fn_8042DC84(&v60, &v78);
        else
            fn_8042DC84(&v60, fn_800B1750(*Entity_GetActor(self)));
        if ((motion == 0x5D || motion == 0x36) && fn_80086374(Entity_GetActor(self)))
            f3C = fn_800E9AF8(self, fn_800B1884(*Entity_GetActor(self), 0xA), fn_800B1884(*Entity_GetActor(self), 9),
                              fn_800B1884(*Entity_GetActor(self), 0x14), 0, &v60);
        else
            f3C = fn_800E89B0(self, fn_800B1884(*Entity_GetActor(self), 0xDF), fn_800B1884(*Entity_GetActor(self), 2), 0, &v60, 0);
    }
    self->f3F4 = 0;
    self->f18 &= ~0x100004;
    fn_800CE3F0(self);
    int f8C = 0;
    if (fn_800CCA88(self)) {
        if (fn_80084B68(Entity_GetActor(self), fn_800B1884(*Entity_GetActor(self), 0x1F)))
            f8C = 1;
        else if (!fn_8008582C(Entity_GetActor(self)))
            fn_80428EEC(lbl_8057217C, fn_8043B31C(fn_800CE5B0(self)));
    }
    if (motion) {
        f14 = motion;
        if (f14 == 0x50 || f14 == 0x4F)
            f38 = 0;
    } else if (f3C) {
        Vector v78;
        float f88;
        float f90;
        float f94 = fn_800B1884(*Entity_GetActor(self), 1);
        fn_80429038(&v78, fn_800B1724(*f3C), fn_800B1724(*Entity_GetActor(self)));
        float f98 = v78.z < 0.0f ? -v78.z : v78.z;
        fn_8042FB28(&v78)->z = 0.0f;
        f88 = fn_8042EC54(&v78);
        f90 = fn_8042EBF4(&v60, &v78);
        if (fn_800CD9B0(self) && fn_800A4130(fn_800B1478(fn_800CD9B0(self)))) {
            if (fn_800B0C1C(f3C) && fn_800CCC28(*fn_80085954(fn_800B14C8(f3C))) && f88 < f94 && f98 < 1.0f)
                f14 = 0xF1;
            else
                f14 = 0xEC;
            goto picked;
        }
        if (fn_800CD9B0(self))
            return 0;
        if (f88 > f94 && f90 < fn_800B1884(*Entity_GetActor(self), 0x13)) {
            fn_800C98BC(self, 0, 1);
            goto notarget;
        }
        if (fn_800B0C1C(f3C) && fn_800CCC28(*fn_80085954(fn_800B14C8(f3C))) && f98 < 0.5f
            && f88 < fn_800B1884(*Entity_GetActor(self), 0xA2)) {
            if (f8C)
                f14 = 0x34;
            else
                f14 = 0x2C;
        } else if (fn_800CC148(self, 0x19)
                   || (fn_800B0CC0(f3C) && fn_800E5F04(self, fn_800B1478(f3C)) && f98 < 1.0f
                       && ((fn_8008582C(Entity_GetActor(self)) && fn_80085D3C(Entity_GetActor(self))) || (!f8C && f88 < f94)))) {
            f14 = 0xE3;
        } else if (f8C) {
            if ((fn_80086374(Entity_GetActor(self)) && fn_800B0CC0(f3C))
                || (fn_80086374(Entity_GetActor(self)) && fn_800B0C1C(f3C) && f98 > 2.0f))
                return 0;
            if (f34) {
                f14 = 0x35;
            } else if (f88 > f94) {
                f14 = 0x33;
                f58 = 1;
            } else {
                f14 = 0x2F;
            }
        } else if (f34) {
            f14 = 0x2D;
        } else if (f88 > f94) {
            f14 = 0x2B;
        } else {
            f14 = 0x27;
        }
    } else {
    notarget:
        f38 = 0;
        fn_8005A9B8(*Entity_GetActor(self), &v60);
        if (fn_800CD9B0(self) && fn_800A4130(fn_800B1478(fn_800CD9B0(self)))) {
            f14 = 0xEC;
        } else if (f8C) {
            if (f34)
                f14 = 0x35;
            else if (fn_80086374(Entity_GetActor(self)))
                return 0;
            else if (Entity_GetActor(self)->abilities & 0x4000)
                f14 = 0x33;
            else
                f14 = 0x2F;
        } else if (f34) {
            f14 = 0x2D;
        }
    }
picked:
    if (f58 && f3C) {
        void *f9C = fn_8009AE00(*Entity_GetActor(self));
        if (fn_8008FCEC(f9C, 0x12F, 0, -1.0f) && fn_8008FCEC(f9C, 0x12E, 0, -1.0f)) {
            Vector v78;
            Vector vA0;
            fn_8042DC84(&vA0, fn_800B1724(*f3C));
            if (fn_800B0C58(f3C) && fn_80085928(fn_800B14A0(f3C)) && fn_800CCC28(*fn_80085928(fn_800B14A0(f3C)))
                && fn_800B1724(*Entity_GetActor(self))->z >= vA0.z - 0.4f)
                vA0.z -= 0.8f;
            fn_80429038(&v78, &vA0, fn_800B1724(*Entity_GetActor(self)));
            fn_8042F76C(&v78);
            float f98 = fn_801BE3C4(v78.z);
            fn_804470BC(fn_8009AF80(*Entity_GetActor(self)) + 0x94, fn_8008FCEC(f9C, 0x12E, 0, -1.0f), fn_8008FCEC(f9C, 0x12F, 0, -1.0f),
                        f98 * 0.022222223f, 0.0f, 0);
        }
    }
    f10 = fn_80097CE8(*Entity_GetActor(self), f14, 0, 30.0f, 0, 7.5f, -1.0f);
    if (f10 < 0)
        return 0;
    fn_800DA884(self, f14);
    if (f14 == 0x3C) {
        fn_80084A60(Entity_GetActor(self), self->f414);
        self->f10 |= 0x1000;
        self->f414 = 0.0f;
    } else if (f14 == 0x3D) {
        self->f10 |= 0x1000;
        self->f414 = 0.0f;
    }
    fn_800DBC90(self, 1);
    fn_800BD2D0(self, f10);
    if (f38 && f3C)
        fn_8005A828(*Entity_GetActor(self), fn_800B1724(*f3C));
    else if (f38)
        fn_8005A9B8(*Entity_GetActor(self), &v60);
    if (fn_8009AF80(*Entity_GetActor(self)) && fn_80447460(fn_8009AF80(*Entity_GetActor(self)) + 0x2C)) {
        Query q;
        fn_8004E9C8(&q);
        fn_80434C88(&q);
        fn_80434CDC(&q, 7);
        fn_80434D40(&q, 1);
        fn_80434D18(&q, Entity_GetActor(self));
        fn_8004E4B4(&q, fn_800B1724(*Entity_GetActor(self)), 7.0f, fn_800B1CC8(*Entity_GetActor(self)));
        Slot *f9C;
        Ent *hit;
        for (unsigned int i = 0; i < q.count; i++) {
            f9C = &q.slot[i];
            if (!f9C)
                continue;
            hit = fn_80434C2C(f9C);
            if (!fn_800B0C58(hit))
                continue;
            if (!fn_8008582C(fn_800B14A0(hit)))
                continue;
            fn_800B9CE8(fn_80085928(fn_800B14A0(hit)), 9, 0, Entity_GetActor(self));
        }
    } else if (f3C && fn_800B0C58(f3C) && fn_80085928(fn_800B14A0(f3C))) {
        fn_800B9CE8(fn_80085928(fn_800B14A0(f3C)), 4, 0, Entity_GetActor(self));
    }
    self->b3EC = 0;
    self->b40A = 0;
    self->b409 = 0;
    self->b40B = 1;
    self->b40C = 0x15;
    self->f410 = 0xCA;
    self->s5(0xB);
    return 1;
}

extern "C" int fn_800DEDB4(register void *self, void *target)
{
    int flags = 0x100670;
    float roll;

    if (fn_80432844(&lbl_80552110) != 0 || fn_80432870(&lbl_80552110) != 0) {
        flags |= 0x2000;
    }
    if (target == 0 || fn_800B0C58(target) == 0) {
        return 0;
    }
    fn_800924BC(&lbl_80552110);
    if (Entity_GetActor(self)->GetString(fn_8009AC68(target) + 0xCE) == 0 || strlen(Entity_GetActor(self)->GetString(fn_8009AC68(target) + 0xCE)) == 0) {
        return 0;
    }
    roll = (float)fn_80171F8C() * 4.656612873077393e-10f;
    if (roll < 0.33f) {
        flags |= 0x80;
    } else if (roll < 0.66f) {
        flags |= 0x100;
    }
    lbl_8066D654->unk28 = Entity_GetActor(self)->IsAlive();
    if (fn_800578E4(Entity_GetActor(self)->GetString(fn_8009AC68(target) + 0xCE), lbl_8066D654, Entity_GetActor(self), target, flags, 0, 0x3E7) == 0) {
        return 0;
    }
    fn_80086410(target);
    fn_80086410(Entity_GetActor(self));
    fn_8007EBE4(target, Entity_GetActor(self));
    return 1;
}

extern "C" int fn_800DF03C(register Obj *self, int super, int retarget)
{
    int f10 = -1;
    int f14 = 0x27;
    float f18 = 0.0f;
    Vector v20;
    int f30 = 0;
    Vector v38;
    Ent *f48 = fn_800CD9B0(self);
    Vector v50;
    float dist;
    float dot;
    int motion;
    int motion2;
    float f70;
    EBase *ctrl = 0;
    int f78 = 0;
    Act *target;
    Vector v80;
    Vector v90;
    Vector vA0;
    Vector vB0;
    Vector vC0;
    int fD0 = 0;
    int fD4 = 0;
    Vector vD8;
    float fE8;
    float fEC;
    float fF0;
    if (retarget) {
        target = (Act *)fn_800C9FD0A(self);
        if (!target || !fn_800B0C58(target))
            return 0;
        ctrl = fn_80085954O(target);
        if (!ctrl)
            return 0;
        fn_80429038(&v50, fn_800B1724(*target), fn_800B1724(*Entity_GetActor(self)));
    } else {
        fn_800BEAC0(self, 1);
        fn_800C05BC(self);
        if (f48)
            return 0;
        fE8 = fn_800CC1D4(self, 0, &vD8);
        if (fE8 > 0.2f && !fn_800CC60C(self))
            fn_8042DC84(&v80, &vD8);
        else
            fn_8042DC84(&v80, fn_800B1750(*Entity_GetActor(self)));
        if (fn_800CCA88(self) && fn_80084B68(Entity_GetActor(self), fn_800B1884(*Entity_GetActor(self), 0x25)))
            target = (Act *)fn_800E89B0A(self, fn_800B1884(*Entity_GetActor(self), 0xF1), fn_800B1884(*Entity_GetActor(self), 0x1C), 0, &v80, 1);
        else
            target = (Act *)fn_800E89B0A(self, fn_800B1884(*Entity_GetActor(self), 0xE0), fn_800B1884(*Entity_GetActor(self), 0x1B), 0, &v80, 1);
        if (!target || !fn_800B0C58(target) || !(ctrl = fn_80085954O(target)))
            goto fail;
        if (fn_80085F4C(target) || fn_800CC88C(ctrl) || fn_80085EEC(target) || fn_80085F1C(target))
            goto fail;
        if (fn_800CCA08(ctrl))
            goto fail;
        if (fn_800CCC28O(*ctrl) || fn_8009B04C(*fn_800B14C8(target)) == 0x7E || fn_8009B04C(*fn_800B14C8(target)) == 0x7D)
            goto fail;
        if (fn_800CC6DC(*ctrl) == 0xB) {
            if (fn_800CD85C(ctrl) || fn_80085D3C(target))
                goto fail;
            if (fn_800CE1B0(ctrl) == fn_800B13D8(*Entity_GetActor(self)))
                goto fail;
        }
        if (fn_800CD0EC(ctrl) || fn_800CC6DC(*ctrl) == 0xD)
            goto fail;
        if (fn_800CC6DC(*ctrl) == 7)
            goto fail;
        if (fn_800CC6DC(*ctrl) == 9)
            goto fail;
        if (fn_800CCA58(ctrl))
            goto fail;
        Entity_GetActor(self)->s5(&v90, 0);
        target->s5(&vB0, 0);
        fn_8042DC84(&vA0, fn_800B1724(*Entity_GetActor(self)));
        fn_8042DC84(&vC0, fn_800B1724(*target));
        vA0.z += 0.5f;
        vC0.z += 0.5f;
        if (fn_8004AC84(&vA0, &vC0, 0, fn_800B13D8(*Entity_GetActor(self)), 0x4D))
            goto fail;
        if (fn_8004AC84(&v90, &vB0, 0, fn_800B13D8(*Entity_GetActor(self)), 0x4D))
            goto fail;
        fn_80429038(&v50, fn_800B1724(*target), fn_800B1724(*Entity_GetActor(self)));
        if ((v50.z < 0.0f ? -v50.z : v50.z) > 0.5f)
            goto fail;
    }
    self->f18 &= ~0x100004;
    self->f3F4 = 0;
    dist = fn_8042EC54(&v50);
    dot = fn_8042EBF4(fn_800B1750(*Entity_GetActor(self)), &v50);
    if (!retarget && fn_80085D3C(fn_800B14C8(target)) && (fn_800866C0(fn_800B14C8(target)) || lbl_8066BA80) && fn_800CCA88(self)
        && !fn_80085EEC(fn_800B14C8(target)) && !fn_80085F1C(fn_800B14C8(target)) && !fn_800CCC28O(*fn_80085954O(fn_800B14C8(target)))
        && !fn_800CCF90(*fn_80085954O(fn_800B14C8(target))) && fn_800CC6DC(*fn_80085954O(fn_800B14C8(target))) != 0x16
        && (dist >= fn_800B1884(*Entity_GetActor(self), 5) ? dist <= fn_800B1884(*Entity_GetActor(self), 6) : 0)
        && fn_80086730(self->fE4) / fn_8008677C(self->fE4) >= 0.25f && !(target->f304 & 0x2000000)) {
        if (fn_800DEDB4(self, fn_800B14A0(target)))
            return 1;
        super = 1;
    }
    if (!super) {
        if (fn_800CCA88(self)) {
            fEC = fn_800B1884(*Entity_GetActor(self), 0x1C);
            fF0 = 0.0f;
            if (fEC > 5.0f && dist < fF0) {
                fD0 = 1;
                fEC = fn_800B1884(*Entity_GetActor(self), 0x1B);
            }
        } else {
            fEC = fn_800B1884(*Entity_GetActor(self), 0x1B);
        }
        if (dist > fEC)
            goto fail;
        if (fn_800CC9D8(ctrl) && fn_800CCA88(ctrl))
            goto fail;
    }
    fn_8005A9B8(*Entity_GetActor(self), &v50);
    fn_8005AB90(target, &v50);
    if (super) {
        motion = fn_8009AC68(fn_800B1568(target)) + 0xBA;
        motion2 = fn_8009AC68(fn_800B1568(target)) + 0xBD;
        f70 = fn_8008FD58(fn_8009AE00(*Entity_GetActor(self)), motion);
    } else if (!fD0 && fn_800CCA88(self) && fn_80084A60(Entity_GetActor(self), fn_800B1884(*Entity_GetActor(self), 0x25))) {
        motion = fn_8009AC68(fn_800B1568(target)) + 0xA2;
        motion2 = fn_8009AC68(fn_800B1568(target)) + 0xA9;
        f70 = fn_8008FD58(fn_8009AE00(*Entity_GetActor(self)), motion);
        self->f418 = fn_800B1884(*Entity_GetActor(self), 0xBD);
        fD4 = 1;
    } else {
        motion = fn_8009AC68(fn_800B1568(target)) + 0x9F;
        motion2 = fn_8009AC68(fn_800B1568(target)) + 0xA6;
        f70 = fn_8008FD58(fn_8009AE00(*Entity_GetActor(self)), motion);
        self->f418 = fn_800B1884(*Entity_GetActor(self), 0xBC);
    }
    fn_8006683C(*Entity_GetActor(self), target);
    self->f4E4 = fn_800B13D8P(target);
    if (f70 >= 0.0f)
        fn_80429090(&v38, fn_800B1724(*target), fn_800B1750(*target), f70);
    else
        fn_8042DC84(&v38, fn_800B1724(*self->fE4));
    if (fn_80048EBC(self->s22(), &v38, 0, fn_800B24AC(*target), Entity_GetActor(self)->s21(), -0.11f, 0)) {
        f78 = 1;
        fn_8042DC84(&v38, fn_800B1724(*Entity_GetActor(self)));
    }
    fn_8009AF80A(*Entity_GetActor(self))->clearX();
    f10 = fn_80097CE8(*Entity_GetActor(self), motion, 0, 30.0f, 0, 7.5f, -1.0f);
    if (f10 < 0) {
        fn_80066A48(*Entity_GetActor(self), target);
        return 0;
    }
    fn_800CD364(self, 0);
    fn_800DA884(self, motion);
    if (f78)
        fn_800C7FF4(*ctrl, &v38, 0.1f);
    else
        fn_800C7FF4(*self, &v38, 0.1f);
    self->s5(0xB);
    fn_800BD2D0(self, f10);
    fn_800CD5A4(*self, 1);
    fn_800CD5EC(self, 1);
    fn_80066604(*Entity_GetActor(self));
    fn_8019C514(fn_8009AF80(*fn_800B14C8(target)), 1, 0);
    fn_8019C514(fn_8009AF80(*fn_800B14C8(target)), 0, 0);
    fn_8009AF28(*fn_800B14C8(target));
    fn_8009AEC8(*fn_800B14C8(target), 0);
    fn_8019C408(fn_8009AF80(*fn_800B14C8(target)));
    fn_80066604(*fn_800B14C8(target));
    if (fn_800B0C1C(target) && fn_80085954O(fn_800B14C8(target))) {
        fn_800CD7A8(ctrl);
        fn_800CD5A4(*ctrl, 0);
        fn_800C98BCP(ctrl, Entity_GetActor(self), 1);
        fn_80085954O(fn_800B14C8(target))->s37(motion2, 0, 1, self->f404, fn_8009AE00(*Entity_GetActor(self)),
                                                fn_800B13D8(*Entity_GetActor(self)), 0, 0);
        fn_800CD5A4(*fn_80085954O(fn_800B14C8(target)), 1);
    }
    fn_8006683C(*Entity_GetActor(self), target);
    self->b40A = 0;
    self->b409 = 0;
    self->b40B = 1;
    self->b40C = 0x15;
    self->f410 = 0xCA;
    if (super) {
        if (fn_800CD85C(self))
            fn_8011C258(lbl_8066BE10, 0x6E);
        else
            fn_8011C258(lbl_8066BE10, 0x78);
    } else {
        fn_8011C258(lbl_8066BE10, 0x14);
        fn_8010CDCC(*Entity_GetActor(self), 0x22, target, 0, 0x64, 0, 0);
    }
    fn_80130F88(fn_800CE5B0(self), target);
    fn_80041588(target, Entity_GetActor(self), 1);
    return 1;
fail:
    if (super)
        return 0;
    if (!f48 && fn_8009AFC8(*Entity_GetActor(self)) == 4 && !fn_8009B04C(*Entity_GetActor(self))) {
        fn_80097CE8(*Entity_GetActor(self), 0xA5, 0, 30.0f, 0, 7.5f, -1.0f);
        self->fE0 = fn_8042EFF8(lbl_80593BE8) + 24000;
    }
    return 0;
}
