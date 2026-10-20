// fn_800F0AA0 offsets the z of a target-supplied vector by a random amount that grows with distance (tuning fields 7, 8); fn_800F0C70 fires the projectile named by PLAYER field 90 + b409 (214 + b409 for 4 and 5) toward the target.

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
};

struct Act : ActBase {
    virtual int s57(float t); // +0x1D0
};

struct EObj {
    char pad0[0x10];
    unsigned int f10;
    char pad14[0x3AC - 0x14];
};

struct Obj : EObj {
    char pad3AC[0x409 - 0x3AC];
    unsigned char b409; // projectile index
    unsigned char b40A; // muzzle effect index
    unsigned char b40B;
    unsigned char b40C;
    char pad40D[0x414 - 0x40D];
    float f414; // energy cost of the motion
};

struct Mgr {
    char pad0[0x78];
    int f78;
};

struct Mtx {
    char d[0x40];
};

struct State {
    char pad[0x75C];
};

extern State lbl_80552110; // the game-state object G
extern Vector lbl_80593DE0;

struct TObj {
    char d[0x198];
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5(Vector *out, int mode); // vtable +0x30
};

extern "C" {
Act *Entity_GetActor(void *self);
void *fn_800B1724(Ent &node);
float fn_800B1884(Ent &actor, int id);
float fn_804290F8(void *a, void *b);
int fn_80171F8C(void);
void fn_80429038(void *out, void *a, void *b);
void fn_8042F76C(void *v);
Vector *fn_800B1750(Ent &actor);
void fn_8042DC84(void *dst, void *src);
int fn_800ACD20(Ent &actor, int id);
void *fn_800FD5FC(int name, int flag);
TObj *fn_800C9FD0(void *self);
int fn_800B0CC0(void *e);
Mgr *fn_800531AC();
int fn_80426AB0(State *g);
int fn_8008582C(void *actor);
const TObj *fn_80432924(State *g);
TObj *fn_800E9AF8(void *self, float a, float b, float c, int d, Vector *e);
void fn_80393D0C(Ent &actor, int id, int a, int b);
int fn_800CC60C(void *self);
void *fn_80085980(void *actor);
TObj *fn_80134870(void *a);
int fn_800B0C58(void *actor);
int fn_800CD288(void *self);
int fn_80084A60(void *actor, float f);
void *fn_8009AD80(Ent &actor);
int fn_800B1668(Ent &c);
int fn_801A5104(void *f, int kind, unsigned short a, void *vec, int e);
int fn_800B1318(Ent &actor);
float fn_800B2620(Ent &actor);
void fn_80429090(void *out, void *a, void *b, float s);
void *fn_800B14A0(void *e);
void *fn_80085928(void *e);
int fn_800CCC28(void *e);
int fn_800CC6DC(void *e);
int fn_800CD064(void *self);
int fn_800CD7D4(void *self);
void fn_8005A9B8(Ent &actor, Vector *dir);
void fn_8042D80C(void *dst, void *src);
void fn_8042D7B0(void *p);
int fn_800862DC(void *actor);
void fn_801BC080(void *m, void *v);
int fn_800B13D8(Ent &actor);
void *fn_800503B8(void *tpl, void *m, void *actor, int a, int b, int c, int d, int e);
void fn_800A1100(void *p, void *target, int a);
void fn_800B9CE8(void *a, int b, void *c, void *d);
int fn_800B24AC(void *p);
void fn_8006683C(Ent &actor, void *p);
int fn_8009ABEC(void *p);
void fn_8010D050(void *actor, int event, int bank, int a2, int a3, void *target, int a5);
}

extern "C" void fn_800F0AA0(register Obj *self, void *dir, TObj *target, void *out)
{
    float dist = fn_804290F8(fn_800B1724(*Entity_GetActor(self)), fn_800B1724(*(Ent *)target));
    float spread = 0.0f;
    float lo = fn_800B1884(*Entity_GetActor(self), 7);
    float hi = fn_800B1884(*Entity_GetActor(self), 8);
    if (dist > hi)
        dist = hi;
    if (dist > lo) {
        spread = fn_80171F8C() * 4.656613e-10f - 0.5f;
        spread = spread * ((dist - lo) / hi);
        Vector v;
        target->s5(&v, 0);
        v.z += spread;
        fn_80429038(out, &v, dir);
        fn_8042F76C(out);
    }
}

extern "C" int fn_800F0C70(register Obj *self, int retarget, int noTarget, int face, Vector *at)
{
    void *f18 = 0;
    Vector v20;
    Vector v30;
    Vector v40;
    TObj *f50;
    int f54 = 0;
    fn_8042DC84(&v40, fn_800B1750(*Entity_GetActor(self)));
    switch (self->b409) {
    case 4:
    case 5:
        f18 = fn_800FD5FC(fn_800ACD20(*Entity_GetActor(self), self->b409 + 0xD6), 0);
        break;
    default:
        f18 = fn_800FD5FC(fn_800ACD20(*Entity_GetActor(self), self->b409 + 0x5A), 0);
        break;
    }
    if (retarget && fn_800C9FD0(self) && !fn_800B0CC0(fn_800C9FD0(self))) {
        f50 = fn_800C9FD0(self);
    } else {
        Mgr *f58 = fn_800531AC();
        if (fn_80426AB0(&lbl_80552110) && fn_8008582C(Entity_GetActor(self)) && f58 && f58->f78)
            f50 = (TObj *)fn_80432924(&lbl_80552110);
        else
            f50 = fn_800E9AF8(self, fn_800B1884(*Entity_GetActor(self), 0xA), fn_800B1884(*Entity_GetActor(self), 9),
                              fn_800B1884(*Entity_GetActor(self), 0x14), noTarget, 0);
    }
    fn_80393D0C(*Entity_GetActor(self), fn_800ACD20(*Entity_GetActor(self), self->b40A + 0x5E), self->b40C, self->b40B);
    if (fn_800CC60C(self) && fn_80134870(fn_80085980(Entity_GetActor(self)))
        && fn_800B0C58(fn_80134870(fn_80085980(Entity_GetActor(self)))))
        f50 = fn_80134870(fn_80085980(Entity_GetActor(self)));
    if (!f18)
        return 0;
    if (!fn_800CD288(self) && !(self->f10 & 0x1000) && self->f414 != 0.0f) {
        fn_80084A60(Entity_GetActor(self), self->f414);
        self->f10 |= 0x1000;
    }
    if (!fn_801A5104(fn_8009AD80(*Entity_GetActor(self)), self->b40C, self->b40B, &v20, fn_800B1668(*Entity_GetActor(self)))) {
        if (fn_800B1318(*Entity_GetActor(self)) == 1)
            fn_8042DC84(&v20, fn_800B1724(*Entity_GetActor(self)));
        else
            fn_80429090(&v20, fn_800B1724(*Entity_GetActor(self)), &lbl_80593DE0, fn_800B2620(*Entity_GetActor(self)) * 0.9f);
    }
    if (at)
        fn_8042DC84(&v20, at);
    if (f50) {
        Vector v60;
        f50->s5(&v60, 0);
        if (fn_800B0C58(f50)
            && (fn_800CCC28(fn_80085928(fn_800B14A0(f50))) || fn_800CC6DC(fn_80085928(fn_800B14A0(f50))) == 0xD))
            v60.z += 0.2f;
        fn_80429038(&v30, &v60, &v20);
        fn_8042F76C(&v30);
        if (!fn_800CD064(self) && !fn_800CD7D4(self))
            fn_8005A9B8(*Entity_GetActor(self), &v30);
        if (fn_800CC60C(self))
            fn_800F0AA0(self, &v20, f50, &v30);
    } else if (noTarget) {
        fn_8042D80C(&v30, fn_800B1750(*Entity_GetActor(self)));
        fn_8005A9B8(*Entity_GetActor(self), &v30);
    } else {
        fn_8042DC84(&v30, fn_800B1750(*Entity_GetActor(self)));
        fn_8005A9B8(*Entity_GetActor(self), &v30);
    }
    Mtx m;
    fn_8042D7B0(&m);
    if (!fn_800862DC(Entity_GetActor(self)) && Entity_GetActor(self)->s57(0.15f))
        fn_801BC080(&m, fn_800B1750(*Entity_GetActor(self)));
    else
        fn_801BC080(&m, &v30);
    fn_8042DC84((char *)&m + 0x30, &v20);
    void *f58 = fn_800503B8(f18, &m, Entity_GetActor(self), fn_800B13D8(*Entity_GetActor(self)), 0, 0, 0, 1);
    if (f58) {
        fn_800A1100(f58, f50, 0);
        if (f50 && fn_800B0C58(f50) && fn_80085928(fn_800B14A0(f50)))
            fn_800B9CE8(fn_80085928(fn_800B14A0(f50)), 6, f58, Entity_GetActor(self));
        if (fn_800B24AC(f58))
            fn_8006683C(*Entity_GetActor(self), f58);
        f54 = fn_8009ABEC(f58);
    }
    if (f54)
        fn_8010D050(Entity_GetActor(self), 0xC, f54, 500, 0, 0, 0);
    if (face)
        fn_8005A9B8(*Entity_GetActor(self), &v40);
    return 1;
}
