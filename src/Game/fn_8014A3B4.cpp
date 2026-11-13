// The Mover (AIObject+0x210): init, destroy, update, aim points beside a target, height hold, volume probes ahead (docs/ai.md row 11).
// .rodata 0x8049B3C0-0x8049B408. fn_80442080 returns Sub * so Ent & arguments convert (matching_notes 49).

inline int sn_return_decl(int a) { return a; }

__asm__(".section .rodata\n\t.globl lbl_8049B3C0\nlbl_8049B3C0:\n\t.4byte 0x6C696400\n\t.text"); // 8-aligns the claim: the end of the previous file's "invalid"

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

struct Sub : Ent { // matching_notes 44
    int x;
};

extern "C" {
Vector *fn_800B1724(Ent &actor);
void fn_8042DC84(Vector *dst, Vector *src);
void fn_8042D8A8(Vector *dst, Vector *src);
void fn_8042F76C(Vector *v);
void fn_8042FE08(Vector *v, Vector *dir, float s);
void fn_80433FFC(Vector *v);
float fn_800B2670(Ent &actor);
float fn_800B1884(Ent &actor, int id);
int fn_800B0C1C(Ent &c);
int fn_800B0C58(Ent &c);
Sub *fn_800B14C8(Ent &c);
int fn_80095608(Ent &a);
int fn_80085D3C(Ent &a);
void *fn_80085980(Ent &a);
Ent *fn_80134870(void *a);
int fn_801332C0(Ent &a);
void fn_80149270(void *a, float f, Vector *v);
Sub *fn_80085954(Ent &a);
int fn_800CCA58(Ent &a);
int fn_800CCAE8(Ent &a);
}

struct Nav {
    char d[0xB0];
};

struct NavFlags {
    char pad[0x9C];
    unsigned int f9C;
};

struct Mover {
    void *f0;              // +0x0: AIObject
    Ent *f4;               // +0x4: its entity
    int f8;                // +0x8: dest-thing handle
    int fC;
    int f10;
    char pad0[0xC];
    Nav f20;               // +0x20
    int fD0;
    char pad1[0xC];
    Vector fE0;
    Vector fF0[24];
    int f270;
    int f274;
    float f278;
    int f27C;              // +0x27C: MOVE_DEST flag
    Vector f280;
    int f290;
    int f294;              // +0x294: WAYPOINT flag
    char pad2[0x8];
    Vector f2A0;
    int f2B0;
    int f2B4;
    int f2B8;
    unsigned int f2BC;     // +0x2BC: ticks left
    int f2C0;
    char pad3[0x4];
    float f2C8;
    char pad4[0x4];
    Vector f2D0;
    Vector f2E0;
};

extern "C" {
Sub *fn_80442080(void *ai);
void fn_80428FA8(Vector *v, float x, float y, float z);
extern Vector lbl_80593DD0;
}

extern "C" void fn_8014A3B4(register Mover *self, void *ai)
{
    int i;

    if (!ai) {
        return;
    }
    self->f0 = ai;
    self->f4 = fn_80442080(self->f0);
    fn_80428FA8(&self->fE0, 0.0f, 0.0f, 0.0f);
    self->f270 = 0;
    self->f274 = 0;
    fn_8042DC84(&self->f280, fn_800B1724(*self->f4));
    fn_8042DC84(&self->f2A0, &self->f280);
    fn_8042DC84(&self->f2D0, fn_800B1724(*self->f4));
    self->f2C8 = 0.0f;
    self->f8 = 0;
    self->f27C = 0;
    self->f294 = 0;
    self->fC = 0;
    self->f10 = 2000;
    self->f278 = 0.0f;
    self->f290 = -1;
    self->f2B0 = 0;
    self->f2B4 = 1;
    self->fD0 = 0;
    self->f2B8 = 0;
    self->f2BC = 0;
    self->f2C0 = 0;
    for (i = 0; i < 24; i++) {
        fn_8042DC84(&self->fF0[i], &lbl_80593DD0);
    }
}

extern "C" void fn_8014A554(register Mover *self)
{
}

extern "C" void fn_8014A574(Ent &self, Ent &target, Vector *out)
{
    Vector a;
    Vector b;
    float d;

    fn_8042DC84(&b, fn_800B1724(self));
    fn_8042D8A8(&b, fn_800B1724(target));
    b.z = 0.0f;
    fn_8042F76C(&b);
    d = fn_800B2670(self) + fn_800B2670(target);
    if (fn_800B0C1C(target) && fn_80095608(*fn_800B14C8(target)) && !fn_80085D3C(self))
        d = fn_800B1884(self, 211);
    else
        d = fn_800B1884(self, 209);
    fn_8042DC84(&a, fn_800B1724(target));
    fn_8042FE08(&a, &b, d);
    if (!fn_800B0C58(target)) {
        if (fn_80134870(fn_80085980(self))) {
            fn_8042DC84(&b, fn_800B1724(*fn_80134870(fn_80085980(self))));
            fn_8042D8A8(&b, fn_800B1724(target));
            fn_8042F76C(&b);
            fn_80433FFC(&b);
            fn_8042DC84(&a, fn_800B1724(target));
            fn_8042FE08(&a, &b, d);
        }
    } else {
        int t = fn_801332C0(self);
        if (t)
            fn_80149270(fn_80085980(self), d, &a);
        if (fn_800CCA58(*fn_80085954(self)) || fn_800CCAE8(*fn_80085954(self)))
            a.z = fn_800B1724(target)->z;
    }
    fn_8042DC84(out, &a);
}

extern "C" int fn_80149388(void *ai, float dist, Vector *out, int byCamera);

extern "C" void fn_8014A860(Ent &self, Ent &target, Vector *out)
{
    Vector a;
    Vector b;
    float d;

    fn_8042DC84(&b, fn_800B1724(self));
    fn_8042D8A8(&b, fn_800B1724(target));
    b.z = 0.0f;
    fn_8042F76C(&b);
    d = fn_800B1884(self, 212);
    fn_8042DC84(&a, fn_800B1724(target));
    fn_8042FE08(&a, &b, d);
    int t = fn_801332C0(self);
    if (t)
        fn_80149388(fn_80085980(self), d, &a, 0);
    a.z = fn_800B1724(target)->z;
    fn_8042DC84(out, &a);
}

extern "C" {
int fn_800861EC(void *actor);
float fn_8015E64C(void *ai);
int fn_8042F024(void *clock);
float fn_8014B824(Mover *self);
extern char lbl_80593BE8[];
}

extern "C" void fn_8014A9B0(register Mover *self)
{
    if (!fn_800861EC(fn_80442080(self->f0))) {
        return;
    }
    float range = fn_800B1884(*fn_80442080(self->f0), 214);
    float z = fn_800B1724(*fn_80442080(self->f0))->z;
    float tz = fn_8014B824(self);
    if (fn_80134870(self->f0))
        tz = fn_800B1724(*fn_80134870(self->f0))->z;
    if (fn_8015E64C(self->f0) <= fn_800B1884(*fn_80442080(self->f0), 212)
        && z <= 2.0f * range + tz && z >= tz + 1.0f) {
        if (!self->f2B8)
            self->f2B8 = 1;
        self->f2BC = 3000;
        return;
    }
    if (self->f2BC) {
        if (self->f2BC <= fn_8042F024(lbl_80593BE8))
            self->f2BC = 0;
        else
            self->f2BC -= fn_8042F024(lbl_80593BE8);
        self->f2B8 = 1;
    } else {
        self->f2B8 = 0;
    }
}

extern "C" {
Sub *fn_804633E4(Mover *self);
int fn_80067050(Ent &actor, Vector *v);
float fn_8042EC54(Vector *v);
Vector *fn_800B1750(Ent &actor);
void fn_80429090(Vector *out, Vector *a, Vector *b, float s);
int fn_8013379C(void *ai, Vector *v);
}

// Is there a volume 5 units ahead along the flat velocity (or the facing when still)?
extern "C" int fn_8014AB90(register Mover *self)
{
    Vector dir;

    fn_80067050(*fn_80442080(self->f0), &dir);
    dir.z = 0.0f;
    float len = fn_8042EC54(&dir);
    if (len < 0.01f)
        fn_8042DC84(&dir, fn_800B1750(*fn_804633E4(self)));
    Vector p;
    fn_80429090(&p, fn_800B1724(*fn_804633E4(self)), &dir, 5.0f);
    if (fn_8013379C(self->f0, &p))
        return 1;
    return 0;
}

// fn_8014AB90 at 15 units.
extern "C" int fn_8014ACA0(register Mover *self)
{
    Vector dir;

    fn_80067050(*fn_80442080(self->f0), &dir);
    dir.z = 0.0f;
    float len = fn_8042EC54(&dir);
    if (len < 0.01f)
        fn_8042DC84(&dir, fn_800B1750(*fn_804633E4(self)));
    Vector p;
    fn_80429090(&p, fn_800B1724(*fn_804633E4(self)), &dir, 15.0f);
    if (fn_8013379C(self->f0, &p))
        return 1;
    return 0;
}

class AIActor
{
public:
    char d[0x5bc];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(int v); // +0x80
};

extern "C" {
Ent *fn_800ACFA8(int h);
int fn_80462650(Mover *self);
int fn_801368B8(void *ai);
NavFlags *fn_80442010(Mover *self);
void fn_8014BE08(Nav *nav, void *ai, Vector *dest, int a, int b, int c);
int fn_8014BC7C(Nav *nav, void *ai, Ent *dest, int a, int b, int c);
int fn_804623BC(Nav *nav);
int fn_8044734C(Mover *self);
int fn_80444D04(int x);
void fn_8014C31C(Nav *nav);
int fn_8014D034(Nav *nav);
unsigned int fn_8042EFF8(void *clock);
void fn_80447C38(Vector *v);
void fn_8042D854(Vector *dst, Vector *src);
void fn_80435530(Vector *v, float s);
float fn_80434040(Vector *v);
float fn_80426A84(void *clock);
void fn_8042FDBC(Vector *out, Vector *v, float s);
void *fn_804634CC(Mover *self);
Sub *fn_8044203C(void *ai);
int fn_800CCC28(Ent &e);
int fn_804421B8(void *ai, int bit);
int fn_800CD0EC(Ent &e);
int fn_800CD064(Ent &e);
int fn_800CC6DC(Ent &e);
void fn_8014B900(Mover *self);
AIActor *fn_800CDA94(Ent &e);
}

// Per-frame update: refresh the path, then steer and track the stuck time at +0x278.
extern "C" void fn_8014ADB0(register Mover *self)
{
    Ent *t = fn_800ACFA8(self->f8);

    if (!t)
        self->f8 = 0;
    fn_8014A9B0(self);
    if (!fn_80462650(self)) {
        if (fn_801368B8(self->f0)) {
            if (!(fn_80442010(self)->f9C & 0x200000) && t)
                fn_8014BE08(&self->f20, self->f0, fn_800B1724(*t), 0, 1, 0);
        } else {
            if ((fn_80442010(self)->f9C & 0x200000) && t)
                fn_8014BE08(&self->f20, self->f0, fn_800B1724(*t), 0, 1, 0);
        }
        if (fn_804623BC(&self->f20)) {
            if (fn_8044734C(self) && fn_80444D04(fn_8044734C(self)) && !fn_801368B8(self->f0))
                fn_8014C31C(&self->f20);
            if (fn_8014D034(&self->f20)) {
                self->fD0 = 0;
                self->f2B0 = 0;
            }
        } else if (!fn_804623BC(&self->f20) && self->f8
                   && fn_8042EFF8(lbl_80593BE8) > (unsigned int)(self->fC + self->f10)) {
            int r = fn_8014BC7C(&self->f20, self->f0, t, 0, 0, 0);
            self->fC = fn_8042EFF8(lbl_80593BE8);
        }
    }
    if (self->f274) {
        fn_80447C38(&self->fE0);
        Vector c;
        fn_8042DC84(&c, fn_800B1724(*fn_80442080(self->f0)));
        c.z += 0.2f;
        int i;
        for (i = 0; i < self->f274; i++)
            fn_8042D854(&self->fE0, &self->fF0[i]);
        fn_80435530(&self->fE0, 1.0f / (float)self->f274);
        float s = fn_80434040(&self->fE0);
    }
    Vector vel;
    fn_80067050(*fn_804633E4(self), &vel);
    float speed = fn_80434040(&vel);
    fn_8042FDBC(&self->f2D0, &self->fE0, fn_80426A84(lbl_80593BE8) * 30.0f * speed);
    fn_8042D854(&self->f2D0, fn_800B1724(*fn_804633E4(self)));
    int a = fn_800CCC28(*fn_8044203C(fn_804634CC(self)));
    int b = fn_804421B8(fn_804634CC(self), 7);
    int c = fn_804421B8(fn_804634CC(self), 25);
    int d = fn_800CD0EC(*fn_8044203C(fn_804634CC(self))) || fn_800CD064(*fn_8044203C(fn_804634CC(self)));
    int e = fn_800CC6DC(*fn_8044203C(fn_804634CC(self))) == 21 || fn_800CC6DC(*fn_8044203C(fn_804634CC(self))) == 22;
    float len = fn_80434040(&self->fE0);
    if ((a || b || d || e) && len > 0.0f) {
        fn_8014B900(self);
        fn_800CDA94(*fn_8044203C(self->f0))->s15(0);
        fn_80447C38(&self->fE0);
        self->f278 = 0.0f;
    } else {
        vel.z = 0.0f;
        float h = fn_80434040(&vel);
        if (h < 1.5f && len >= 0.0f)
            self->f278 += fn_80426A84(lbl_80593BE8);
        else
            self->f278 = 0.0f;
    }
}
