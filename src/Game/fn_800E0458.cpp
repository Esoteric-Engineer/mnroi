// fn_800E0458 skips the current animation ahead to the grab's cancel point and recurses into the grabbed victim.

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

class Ent
{
public:
    int pad;
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
};

struct ActSub : Act {
    int pad;
};

class Actor1F0
{
public:
    void clear();
};

struct Clip;

struct Channel {
    int f0;
    float time; // +0x4
};

struct EObj {
    char pad0[0x10];
    unsigned int f10;
    char pad14[0x18 - 0x14];
    unsigned int f18;
    char pad1C[0xB8 - 0x1C];
    unsigned int fB8; // a time on the fn_8042EFF8 clock
    char padBC[0x3AC - 0xBC];
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
    char pad3B0[0x3F4 - 0x3B0];
    int f3F4;
    char pad3F8[0x404 - 0x3F8];
    float f404;
    char pad408[0x409 - 0x408];
    char b409;
    char b40A;
    char b40B;
    char b40C;
    int f410;
    float f414;
    float f418; // rage points of the motion
    char pad41C[0x4E4 - 0x41C];
    int f4E4; // id of the grabbed entity
};

extern void *lbl_8066BE10;

extern "C" {
Act *Entity_GetActor(void *self);
char *fn_8009AF80(Ent &actor);
Actor1F0 *fn_8009AF80B(Ent &actor) __asm__("fn_8009AF80");
Clip *fn_804355C0(Channel *ch);
float fn_80199F24(Clip *clip, int tag);
int fn_800CD0EC(void *self);
Vector *fn_800B1750(Ent &actor);
void fn_8002FD50(void *a, void *b, int c, int d, float f, void *g, void *h, int i, int j, float k, int l, Vector *m, int n, int o);
int fn_800CC2E0(void *self);
float fn_80447434(Channel *ch);
void fn_8019DB24(Channel *ch, float time);
void fn_8019BA58(void *self, int force, int root, int noTargets);
void fn_80066604(Ent &a);
void fn_80065AF8(Ent &actor, int a, int b);
int fn_800CC70C(void *self);
int fn_800C9FD0I(void *self) __asm__("fn_800C9FD0");
void fn_800CD364(void *c, int v);
void fn_800CD364O(EObj &c, int v) __asm__("fn_800CD364");
int fn_800B0C58(void *actor);
EBase *fn_80085954O(void *p) __asm__("fn_80085954");
int fn_800E0458(register Obj *self);
int fn_800E0458V(void *self) __asm__("fn_800E0458");

int fn_800BEAC0(void *self, int v);
void fn_800C05BC(void *self);
Ent *fn_800CD9B0(void *self);
ActSub *fn_800C9FD0A(void *self) __asm__("fn_800C9FD0");
Vector *fn_800B1724(Ent &actor);
void fn_80429038(Vector *out, Vector *a, Vector *b);
Vector *fn_8042FB28(Vector *v);
float fn_800B1884(Ent &actor, int id);
ActSub *fn_800E89B0A(void *self, float minDot, float radius, int useOwner, Vector *dir, int all) __asm__("fn_800E89B0");
Act *fn_800B14C8(void *c);
int fn_800CC6DC(EObj &c);
int fn_800CCC28O(EObj &c) __asm__("fn_800CCC28");
int fn_800C4D70(void *self, int a, float f, int b);
float fn_8042EC54(Vector *v);
float fn_8042EBF4(Vector *a, Vector *b);
void fn_8042DC84(Vector *dst, Vector *src);
int fn_800B13D8(Ent &a);
int fn_800B13D8P(void *e) __asm__("fn_800B13D8");
int fn_8004AC84(Vector *a, Vector *b, int c, int id, int mask);
void fn_8005A9B8(Ent &actor, Vector *dir);
void fn_8005AB90(void *e, Vector *dir);
int fn_800CCA88(void *self);
int fn_80084A60(void *actor, float f);
void *fn_800B1568(void *e);
int fn_8009AC68(void *actor);
int fn_800861EC(void *actor);
void *fn_8009AE00(Ent &actor);
float fn_8008FD58(void *set, int motion);
void fn_8006683C(Ent &a, void *e);
void fn_80429090(Vector *out, Vector *a, Vector *b, float s);
int fn_800B24AC(Ent &e);
int fn_80048EBC(void *a, Vector *v, int b, int c, int d, float f, int e);
void fn_80066A48(Ent &a, void *e);
int fn_80097CE8(Ent &actor, int a, int mode, float speed, void *set, float blend, float f);
void fn_800DA884(void *self, int motion);
void fn_800C7FF4(EObj &c, Vector *v, float f);
void fn_800BD2D0(void *self, int handle);
void fn_800CD5A4(EObj &c, int v);
void fn_8019C514(void *p, int a, int b);
void fn_8009AF28(Ent &a);
void fn_8009AEC8(Ent &a, int v);
void fn_8019C408(void *p);
int fn_800B0C1C(void *c);
void fn_800CD7A8(EObj &c);
Act *fn_80085954(void *p);
void fn_800C98BCP(void *self, void *e, int b) __asm__("fn_800C98BC");
void fn_80086A2C(void *p, float f);
void fn_8011C258(void *p, int v);
void fn_8010CDCC(Ent &a, int id, void *e, int b, int c, int d, int f);
void *fn_800CE5B0(void *self);
void fn_80130F88(void *p, void *e);
}

extern "C" int fn_800E0458(register Obj *self)
{
    int f18 = 0;
    Channel *ch = (Channel *)(fn_8009AF80(*Entity_GetActor(self)) + 0x2C);
    Clip *clip = fn_804355C0(ch);
    if (!clip)
        return 0;
    float tag = fn_80199F24(clip, 0x53);
    if (tag >= ch->time) {
        if (fn_800CD0EC(self) && !(self->f10 & 1)) {
            float f28 = 10.0f;
            fn_8002FD50(Entity_GetActor(self), Entity_GetActor(self), 7, 0, f28, 0, 0, 0x20, 1, 0.0f, 0,
                        fn_800B1750(*Entity_GetActor(self)), 0xFF, 0xFF);
            self->f10 |= 1;
        }
        if (fn_800CC2E0(self) && fn_80447434(ch) != 0.0f)
            self->fB8 -= (unsigned int)(1000.0f / fn_80447434(ch) * (tag - ch->time));
        fn_8019DB24(ch, tag);
        fn_8019BA58(fn_8009AF80(*Entity_GetActor(self)), 1, 1, 0);
        fn_8009AF80B(*Entity_GetActor(self))->clear();
        self->f18 |= 4;
        fn_80066604(*Entity_GetActor(self));
        fn_80065AF8(*Entity_GetActor(self), 1, 0);
        if (!fn_800CC70C(self)) {
            Ent *victim;
            victim = (Ent *)(ActSub *)fn_800C9FD0I(self);
            fn_800CD364(self, 1);
            if (victim && fn_800B0C58(victim) && fn_80085954O(victim)) {
                fn_800CD364O(*fn_80085954O(victim), 1);
                fn_800E0458V(fn_80085954(victim));
            }
        }
        return 1;
    }
    return 0;
}

extern "C" int fn_800E07A4(register Obj *self, int retarget)
{
    int f0C = -1;
    float f10 = 0.0f;
    Vector v18;
    Vector v28;
    Ent *f38 = fn_800CD9B0(self);
    Vector v40;
    float dist;
    float dot;
    int motion;
    int motion2;
    float reach;
    float az;
    EBase *ctrl = 0;
    float rage;
    Act *target;
    Vector v78;
    Vector v88;
    Vector v98;
    Vector vA8;
    int fB8 = 0;
    fn_800BEAC0(self, 0);
    fn_800C05BC(self);
    if (retarget) {
        target = (Act *)fn_800C9FD0A(self);
        if (!target || !fn_800B0C58(target))
            return 0;
        ctrl = fn_80085954O(target);
        if (!ctrl)
            return 0;
        fn_80429038(&v40, fn_800B1724(*target), fn_800B1724(*Entity_GetActor(self)));
        az = v40.z < 0.0f ? -v40.z : v40.z;
        fn_8042FB28(&v40)->z = 0.0f;
    } else {
        if (f38)
            return 0;
        target = (Act *)fn_800E89B0A(self, fn_800B1884(*Entity_GetActor(self), 0xEB), fn_800B1884(*Entity_GetActor(self), 0x1D), 0, 0, 0);
        if (!target || !fn_800B0C58(target) || !(ctrl = fn_80085954O(target)))
            goto fail;
        if (target->s57(0.15f))
            goto fail;
        ctrl = fn_80085954O(fn_800B14C8(target));
        if (fn_800CC6DC(*ctrl) == 0xB)
            goto fail;
        if (fn_800CC6DC(*ctrl) == 9)
            goto fail;
        if (fn_800CCC28O(*ctrl))
            goto fail;
        if (fn_800C4D70(ctrl, 1, 1.0f, 0))
            goto fail;
        fn_80429038(&v40, fn_800B1724(*target), fn_800B1724(*Entity_GetActor(self)));
        az = v40.z < 0.0f ? -v40.z : v40.z;
        fn_8042FB28(&v40)->z = 0.0f;
        dist = fn_8042EC54(&v40);
        if (dist <= 0.0001f)
            goto fail;
        dot = fn_8042EBF4(fn_800B1750(*Entity_GetActor(self)), &v40);
        self->f3F4 = 0;
        if (az > 1.5f)
            goto fail;
        Entity_GetActor(self)->s5(&v78, 0);
        target->s5(&v88, 0);
        fn_8042DC84(&v98, fn_800B1724(*Entity_GetActor(self)));
        fn_8042DC84(&vA8, fn_800B1724(*target));
        v98.z += 0.5f;
        vA8.z += 0.5f;
        if (fn_8004AC84(&v98, &vA8, 0, fn_800B13D8(*Entity_GetActor(self)), 0x4D))
            goto fail;
        if (fn_8004AC84(&v78, &v88, 0, fn_800B13D8(*Entity_GetActor(self)), 0x4D))
            goto fail;
    }
    self->f18 &= ~0x100004;
    fn_8005A9B8(*Entity_GetActor(self), &v40);
    fn_8005AB90(target, fn_800B1750(*Entity_GetActor(self)));
    if (fn_800CCA88(self) && fn_80084A60(Entity_GetActor(self), fn_800B1884(*Entity_GetActor(self), 0x25))) {
        motion = fn_8009AC68(fn_800B1568(target)) + 0xB3;
        motion2 = fn_8009AC68(fn_800B1568(target)) + 0xB6;
        rage = fn_800B1884(*Entity_GetActor(self), 0xBD);
        if (fn_800861EC(target))
            motion2 = 0xB9;
        fB8 = 1;
    } else {
        motion = fn_8009AC68(fn_800B1568(target)) + 0xAC;
        motion2 = fn_8009AC68(fn_800B1568(target)) + 0xAF;
        rage = fn_800B1884(*Entity_GetActor(self), 0xBC);
        if (fn_800861EC(target))
            motion2 = 0xB2;
    }
    reach = fn_8008FD58(fn_8009AE00(*Entity_GetActor(self)), motion);
    fn_8006683C(*Entity_GetActor(self), target);
    self->f4E4 = fn_800B13D8P(target);
    fn_80429090(&v28, fn_800B1724(*target), fn_800B1750(*target), reach);
    if (!retarget) {
        if (fn_80048EBC(self->s22(), &v28, 0, fn_800B24AC(*target), Entity_GetActor(self)->s21(), -0.11f, 0)) {
            fn_80066A48(*Entity_GetActor(self), target);
            goto fail;
        }
    }
    f0C = fn_80097CE8(*Entity_GetActor(self), motion, 0, 30.0f, 0, 7.5f, -1.0f);
    if (f0C < 0) {
        fn_80066A48(*Entity_GetActor(self), target);
        return 0;
    }
    fn_800CD364(self, 0);
    fn_800DA884(self, motion);
    fn_800C7FF4(*self, &v28, 0.1f);
    self->s5(0xB);
    fn_800BD2D0(self, f0C);
    fn_800CD5A4(*self, 1);
    fn_80066604(*Entity_GetActor(self));
    fn_8019C514(fn_8009AF80(*fn_800B14C8(target)), 1, 0);
    fn_8019C514(fn_8009AF80(*fn_800B14C8(target)), 0, 0);
    fn_8009AF28(*fn_800B14C8(target));
    fn_8009AEC8(*fn_800B14C8(target), 0);
    fn_8019C408(fn_8009AF80(*fn_800B14C8(target)));
    fn_80066604(*fn_800B14C8(target));
    if (fn_800B0C1C(target) && fn_80085954(fn_800B14C8(target))) {
        fn_800CD7A8(*fn_80085954O(fn_800B14C8(target)));
        fn_800CD5A4(*fn_80085954O(fn_800B14C8(target)), 0);
        fn_800C98BCP(fn_80085954(fn_800B14C8(target)), Entity_GetActor(self), 1);
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
    self->f418 = 0.0f;
    fn_80065AF8(*Entity_GetActor(self), 0, 0);
    fn_80065AF8(*target, 0, 0);
    fn_80086A2C(Entity_GetActor(self), rage);
    fn_80086A2C(fn_800B14C8(target), -rage * fn_800B1884(*Entity_GetActor(self), 0xC2));
    fn_8011C258(lbl_8066BE10, 0x14);
    fn_8010CDCC(*Entity_GetActor(self), 0x22, target, 0, 0x64, 0, 0);
    fn_80130F88(fn_800CE5B0(self), target);
    return 1;
fail:
    return 0;
}
