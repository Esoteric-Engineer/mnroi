// The Mover (AIObject+0x210): init, destroy, update, aim points beside a target, height hold, volume probes, waypoint, chase, stop, clear path, heading point (docs/ai.md row 11).
// .rodata 0x8049B3C0-0x8049B468, the whole file's. AI_GetEntity returns Sub * so Ent & arguments convert (matching_notes 50).

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
Sub *AI_GetEntity(void *ai);
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
    self->f4 = AI_GetEntity(self->f0);
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

extern "C" void fn_8014A574(Ent *self, Ent *target, Vector *out)
{
    Vector a;
    Vector b;
    float d;

    fn_8042DC84(&b, fn_800B1724(*self));
    fn_8042D8A8(&b, fn_800B1724(*target));
    b.z = 0.0f;
    fn_8042F76C(&b);
    d = fn_800B2670(*self) + fn_800B2670(*target);
    if (fn_800B0C1C(*target) && fn_80095608(*fn_800B14C8(*target)) && !fn_80085D3C(*self))
        d = fn_800B1884(*self, 211);
    else
        d = fn_800B1884(*self, 209);
    fn_8042DC84(&a, fn_800B1724(*target));
    fn_8042FE08(&a, &b, d);
    if (!fn_800B0C58(*target)) {
        if (fn_80134870(fn_80085980(*self))) {
            fn_8042DC84(&b, fn_800B1724(*fn_80134870(fn_80085980(*self))));
            fn_8042D8A8(&b, fn_800B1724(*target));
            fn_8042F76C(&b);
            fn_80433FFC(&b);
            fn_8042DC84(&a, fn_800B1724(*target));
            fn_8042FE08(&a, &b, d);
        }
    } else {
        int t = fn_801332C0(*self);
        if (t)
            fn_80149270(fn_80085980(*self), d, &a);
        if (fn_800CCA58(*fn_80085954(*self)) || fn_800CCAE8(*fn_80085954(*self)))
            a.z = fn_800B1724(*target)->z;
    }
    fn_8042DC84(out, &a);
}

extern "C" int fn_80149388(void *ai, float dist, Vector *out, int byCamera);

extern "C" void fn_8014A860(Ent *self, Ent *target, Vector *out)
{
    Vector a;
    Vector b;
    float d;

    fn_8042DC84(&b, fn_800B1724(*self));
    fn_8042D8A8(&b, fn_800B1724(*target));
    b.z = 0.0f;
    fn_8042F76C(&b);
    d = fn_800B1884(*self, 212);
    fn_8042DC84(&a, fn_800B1724(*target));
    fn_8042FE08(&a, &b, d);
    int t = fn_801332C0(*self);
    if (t)
        fn_80149388(fn_80085980(*self), d, &a, 0);
    a.z = fn_800B1724(*target)->z;
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
    if (!fn_800861EC(AI_GetEntity(self->f0))) {
        return;
    }
    float range = fn_800B1884(*AI_GetEntity(self->f0), 214);
    float z = fn_800B1724(*AI_GetEntity(self->f0))->z;
    float tz = fn_8014B824(self);
    if (fn_80134870(self->f0))
        tz = fn_800B1724(*fn_80134870(self->f0))->z;
    if (fn_8015E64C(self->f0) <= fn_800B1884(*AI_GetEntity(self->f0), 212)
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
Sub *AI_GetMoverEntity(Mover *self);
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

    fn_80067050(*AI_GetEntity(self->f0), &dir);
    dir.z = 0.0f;
    float len = fn_8042EC54(&dir);
    if (len < 0.01f)
        fn_8042DC84(&dir, fn_800B1750(*AI_GetMoverEntity(self)));
    Vector p;
    fn_80429090(&p, fn_800B1724(*AI_GetMoverEntity(self)), &dir, 5.0f);
    if (fn_8013379C(self->f0, &p))
        return 1;
    return 0;
}

// fn_8014AB90 at 15 units.
extern "C" int fn_8014ACA0(register Mover *self)
{
    Vector dir;

    fn_80067050(*AI_GetEntity(self->f0), &dir);
    dir.z = 0.0f;
    float len = fn_8042EC54(&dir);
    if (len < 0.01f)
        fn_8042DC84(&dir, fn_800B1750(*AI_GetMoverEntity(self)));
    Vector p;
    fn_80429090(&p, fn_800B1724(*AI_GetMoverEntity(self)), &dir, 15.0f);
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
int AI_IsMoverAboveTarget(Mover *self);
int fn_801368B8(void *ai);
NavFlags *AI_GetPath(Mover *self);
int fn_8014BE08(Nav *nav, void *ai, Vector *dest, int a, int b, int c);
int fn_8014BC7C(Nav *nav, void *ai, Ent *dest, int a, int b, int c);
int AI_IsPathBuilt(Nav *nav);
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
void *AI_GetMoverAI(Mover *self);
Sub *AI_GetActor(void *ai);
int fn_800CCC28(Ent &e);
int AI_IsBehaviorEnabled(void *ai, int bit);
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
    if (!AI_IsMoverAboveTarget(self)) {
        if (fn_801368B8(self->f0)) {
            if (!(AI_GetPath(self)->f9C & 0x200000) && t)
                fn_8014BE08(&self->f20, self->f0, fn_800B1724(*t), 0, 1, 0);
        } else {
            if ((AI_GetPath(self)->f9C & 0x200000) && t)
                fn_8014BE08(&self->f20, self->f0, fn_800B1724(*t), 0, 1, 0);
        }
        if (AI_IsPathBuilt(&self->f20)) {
            if (fn_8044734C(self) && fn_80444D04(fn_8044734C(self)) && !fn_801368B8(self->f0))
                fn_8014C31C(&self->f20);
            if (fn_8014D034(&self->f20)) {
                self->fD0 = 0;
                self->f2B0 = 0;
            }
        } else if (!AI_IsPathBuilt(&self->f20) && self->f8
                   && fn_8042EFF8(lbl_80593BE8) > (unsigned int)(self->fC + self->f10)) {
            int r = fn_8014BC7C(&self->f20, self->f0, t, 0, 0, 0);
            self->fC = fn_8042EFF8(lbl_80593BE8);
        }
    }
    if (self->f274) {
        fn_80447C38(&self->fE0);
        Vector c;
        fn_8042DC84(&c, fn_800B1724(*AI_GetEntity(self->f0)));
        c.z += 0.2f;
        int i;
        for (i = 0; i < self->f274; i++)
            fn_8042D854(&self->fE0, &self->fF0[i]);
        fn_80435530(&self->fE0, 1.0f / (float)self->f274);
        float s = fn_80434040(&self->fE0);
    }
    Vector vel;
    fn_80067050(*AI_GetMoverEntity(self), &vel);
    float speed = fn_80434040(&vel);
    fn_8042FDBC(&self->f2D0, &self->fE0, fn_80426A84(lbl_80593BE8) * 30.0f * speed);
    fn_8042D854(&self->f2D0, fn_800B1724(*AI_GetMoverEntity(self)));
    int a = fn_800CCC28(*AI_GetActor(AI_GetMoverAI(self)));
    int b = AI_IsBehaviorEnabled(AI_GetMoverAI(self), 7);
    int c = AI_IsBehaviorEnabled(AI_GetMoverAI(self), 25);
    int d = fn_800CD0EC(*AI_GetActor(AI_GetMoverAI(self))) || fn_800CD064(*AI_GetActor(AI_GetMoverAI(self)));
    int e = fn_800CC6DC(*AI_GetActor(AI_GetMoverAI(self))) == 21 || fn_800CC6DC(*AI_GetActor(AI_GetMoverAI(self))) == 22;
    float len = fn_80434040(&self->fE0);
    if ((a || b || d || e) && len > 0.0f) {
        fn_8014B900(self);
        fn_800CDA94(*AI_GetActor(self->f0))->s15(0);
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

extern "C" {
Ent *fn_80085928(Ent *a);
int fn_800CC9D8(Ent *a);
}

// Push a point into the 24-entry ring at +0xF0 that the update averages into the heading +0xE0.
extern "C" void fn_8014B420(register Mover *self, Vector *v)
{
    if (!v)
        return;
    fn_8042DC84(&self->fF0[self->f270], v);
    if (++self->f270 > 23)
        self->f270 = 0;
    if (self->f274 < 24)
        self->f274++;
    if (fn_800CC9D8(fn_80085928(AI_GetEntity(AI_GetMoverAI(self)))) && fn_80434040(v) > 0.1f) {
        int unused = 0;
    }
}

extern "C" {
Mover *AI_GetMover(void *ai);
void AI_SetMoverWaypoint(Mover *self, Vector *v);
void AI_SetMoverMoveDest(Mover *self, Vector *v);
void fn_8014C660(Nav *nav);
}

// Set a waypoint and repath to it, at most once per +0x10 ms; index -1 keeps +0x290.
extern "C" int fn_8014B518(register Mover *self, Vector *dest, int index)
{
    AI_SetMoverWaypoint(AI_GetMover(self->f0), 0);
    AI_SetMoverMoveDest(self, dest);
    if (index != -1)
        self->f290 = index;
    if (fn_8042EFF8(lbl_80593BE8) < (unsigned int)(self->fC + self->f10))
        return 1;
    int r = 0;
    self->fC = fn_8042EFF8(lbl_80593BE8);
    self->f8 = 0;
    if (AI_IsPathBuilt(&self->f20))
        fn_8014C660(&self->f20);
    r = fn_8014BE08(&self->f20, self->f0, dest, 0, 1, 0);
    self->fD0 = 0;
    return r;
}

extern "C" int fn_804633B0(Nav *nav);

// Chase actor `id`: aim beside it and repath, at most once per +0x10 ms unless forced.
extern "C" int fn_8014B63C(register Mover *self, int id, int force)
{
    if (self->f8 == id && !force && fn_8042EFF8(lbl_80593BE8) < (unsigned int)(self->fC + self->f10))
        return 1;
    self->f8 = id;
    Ent *t = fn_800ACFA8(id);
    if (!t)
        return 0;
    Vector dest;
    if (fn_800861EC(AI_GetEntity(self->f0)))
        fn_8014A860(AI_GetEntity(self->f0), t, &dest);
    else
        fn_8014A574(AI_GetEntity(self->f0), t, &dest);
    AI_SetMoverMoveDest(self, &dest);
    int r = 0;
    self->fC = fn_8042EFF8(lbl_80593BE8);
    if (AI_IsMoverAboveTarget(self) && !force)
        return 0;
    self->fD0 = 0;
    r = fn_8014BE08(&self->f20, self->f0, &dest, 0, 1, 0);
    if (!r || fn_804633B0(&self->f20))
        AI_SetMoverWaypoint(self, &dest);
    return r;
}

extern "C" {
int AI_HasMoverWaypoint(Mover *self);
int AI_HasMoverMoveDest(Mover *self);
}

// Height to hold: the waypoint's, else the move destination's, else the target's, else our own.
extern "C" float fn_8014B824(register Mover *self)
{
    register Sub *e = AI_GetMoverEntity(self);
    float z = fn_800B1724(*e)->z;

    if (AI_HasMoverWaypoint(self))
        return self->f2A0.z;
    else if (AI_HasMoverMoveDest(self))
        return self->f280.z;
    else if (fn_80134870(self->f0))
        return fn_800B1724(*fn_80134870(self->f0))->z;
    return z;
}

extern "C" {
void fn_8014BA7C(Mover *self);
void *AI_GetActionQueue(void *ai);
int fn_801B6A44(void *list);
void *fn_801B5D3C(void *list, int i);
int AI_GetActionMoveKind(int b);
void fn_80138AE0(int h, int a, Vector *v, float f);
}

// Stop: drop the destination, clear the heading and the point ring, and zero every behavior's vector.
extern "C" void fn_8014B900(register Mover *self)
{
    fn_8014BA7C(self);
    fn_8042DC84(&self->f280, fn_800B1724(*AI_GetMoverEntity(self)));
    self->f27C = 0;
    self->f294 = 0;
    self->f278 = 0.0f;
    fn_80447C38(&self->fE0);
    int i;
    for (i = 0; i < 24; i++)
        fn_80447C38(&self->fF0[i]);
    void *list = AI_GetActionQueue(AI_GetMoverAI(self));
    int n = fn_801B6A44(list);
    int j;
    for (j = 0; j < n; j++) {
        int b = (int)fn_801B5D3C(list, j);
        if (!AI_GetActionMoveKind(b)) {
            Vector v;
            fn_80447C38(&v);
            fn_80138AE0(b, 0, &v, 0.0f);
        }
    }
}

extern "C" {
void fn_80463470(Mover *self, int v);
void AI_SetMoverSpotKind(Mover *self, int v);
}

// Clear the path: reset the path at +0x20 and zero +0x2B0 and +0xD0.
extern "C" void fn_8014BA7C(register Mover *self)
{
    fn_8014C660(&self->f20);
    fn_80463470(self, 0);
    AI_SetMoverSpotKind(self, 0);
}

extern "C" int fn_801368B8(void *ai);

extern "C" int fn_8014BAD0(register Mover *self)
{
    if (fn_800861EC(AI_GetEntity(self->f0)))
        return 1;
    if (!fn_801368B8(self->f0))
        return 0;
    return 0;
}

__asm__(".section .rodata\n\t.float 0.0\n\t.long 0x7F7FFFFF\n\t.float 5.0\n\t.text"); // 0x8049B410: linkonce pool words (matching_notes 23)

extern "C" {
Vector *AI_GetMoverWaypoint(Mover *self);
Vector *AI_GetMoverMoveDest(Mover *self);
}

// Where to head: the waypoint, else the move destination, else where we stand.
extern "C" void fn_8014BB4C(register Mover *self, Vector *out)
{
    float unused0 = 0.0f;
    int waypoint = 0;
    int dest = 0;
    int unused1 = 0;
    int found = 0;
    Vector v;
    fn_8042DC84(&v, fn_800B1724(*AI_GetEntity(self->f0)));
    if (AI_HasMoverWaypoint(self)) {
        fn_8042DC84(&v, AI_GetMoverWaypoint(self));
        found = 1;
        waypoint = 1;
    }
    if (!found && AI_HasMoverMoveDest(self)) {
        fn_8042DC84(&v, AI_GetMoverMoveDest(self));
        found = 1;
        dest = 1;
    }
    fn_8042DC84(out, &v);
}

// 0x8049B420-0x8049B468: linkonce pool words, then the header's "invalid" that closes the file's .rodata (docs/ai.md section 2).
__asm__(".section .rodata\n\t.float 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.2, 0.8, 2.0, 0.5, 0.8, 0.8, 1.0, 1.25, 0.75\n\t.long 2000\n\t.asciz \"invalid\"\n\t.text");
