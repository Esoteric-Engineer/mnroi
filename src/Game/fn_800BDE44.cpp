// Root-motion appliers called from state updates, and attachment effect helpers.

class Vector
{
public:
    float x, y, z, w;
    Vector();
};

struct Mat4 {
    float m[4][4];
};

struct Animator;

struct Ent {
    int pad;
};

struct PEnt : Ent {
    char pad4[0x74];
    float mat[16];         // +0x78
};

struct Effect {
    char d[0x58];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21();
    virtual void s22(float a, float b);
};

struct EffectEntry {
    char character[0x20];  // +0x00
    char attachment[0x20]; // +0x20
    float on[2];           // +0x40
    float off[2];          // +0x48
};

struct Obj {
    char pad0[0x18];
    unsigned int f18;      // +0x18
};

class Actor
{
public:
    void apply(const void *turn);
};

extern "C" {
extern char lbl_80593BE8[];
extern char lbl_80593DD0[];
extern char lbl_80552110[];
extern char lbl_805720C4[];
extern EffectEntry lbl_804CC578[8];
int stricmp(const char *a, const char *b);
void *fn_8009AD80(Ent &actor);
Effect *fn_801A4190(void *model, const char *name, unsigned short start, unsigned short *index);
int fn_800CC148(void *self, int id);
int fn_800BED04(void *self, int a, int b);
void fn_800869AC(void *actor, float v);
float fn_800869D4(void *actor);
float fn_800B1884(Ent &actor, int id);
void *fn_800CE5B0(void *self);
int fn_8043B31C(void *p);
int fn_80085D3C(void *actor);
void fn_8042D1E8(void *p, int a, int b);
int fn_80095B74(char *g);
void fn_80095B9C(char *g, int a, int b);
PEnt *Entity_GetActor(void *self);
Animator *fn_8009AF80(Ent &actor);
Vector *fn_800B1724(Ent &actor);
Actor *fn_800B1668(Ent &actor);
void fn_80065E10(Ent &actor, Vector *pos);
void fn_80065CB0(Ent &actor, Vector *vel);
int fn_8019E2CC(Animator *anim);
void fn_8019C3AC(Animator *anim, Vector *out, int noTargets);
void fn_8019C48C(Animator *anim, Vector *out);
void fn_8019C4D0(Animator *anim, Vector *out);
void fn_80434368(float *out, void *v, void *m);
void fn_8042D854(Vector *a, Vector *b);
float fn_8043B3B0(char *clock);
void fn_80435530(Vector *v, float s);
void fn_8042D7B0(Mat4 *m);
void fn_80433FFC(Vector *v);
void fn_804342EC(Mat4 *m, Vector *rot);
void fn_80435754(Vector *v, Mat4 *m);
int fn_80067050(Ent &actor, Vector *vel);
void fn_8042DCC0(Mat4 *m);
void fn_8042DC84(float *dst, Vector *src);
void fn_8042F984(float *dst, void *a, void *b);
void fn_8042F76C(float *v);
float fn_8042EBF4(Vector *a, float *b);
void fn_8042FE08(Vector *v, float *axis, float t);

void fn_800BDE44(register void *self)
{
    Vector step;
    Vector pos;
    fn_8019C3AC(fn_8009AF80(*Entity_GetActor(self)), &step, 0);
    fn_80434368(&pos.x, &step, Entity_GetActor(self)->mat);
    fn_8042D854(&pos, fn_800B1724(*Entity_GetActor(self)));
    fn_80065E10(*Entity_GetActor(self), &pos);
}

void fn_800BDF20(register void *self)
{
    Vector step;
    Vector vel;
    fn_8019C3AC(fn_8009AF80(*Entity_GetActor(self)), &step, 0);
    fn_80434368(&vel.x, &step, fn_800B1668(*Entity_GetActor(self)));
    fn_80435530(&vel, fn_8043B3B0(lbl_80593BE8));
    fn_80065CB0(*Entity_GetActor(self), &vel);
}

void fn_800BDFFC(register void *self)
{
    Vector step;
    Vector turn;
    Vector vel;
    Vector rot;
    fn_8019C3AC(fn_8009AF80(*Entity_GetActor(self)), &step, 0);
    fn_8019C48C(fn_8009AF80(*Entity_GetActor(self)), &turn);
    fn_8019C4D0(fn_8009AF80(*Entity_GetActor(self)), &rot);
    if (fn_8019E2CC(fn_8009AF80(*Entity_GetActor(self))))
        return;
    if (turn.z != 0.0f)
        fn_800B1668(*Entity_GetActor(self))->apply(&turn);
    if (rot.x != 0.0f || rot.y != 0.0f || rot.z != 0.0f) {
        Mat4 m;
        fn_8042D7B0(&m);
        fn_80433FFC(&rot);
        fn_804342EC(&m, &rot);
        fn_80435754(&step, &m);
    }
    fn_80434368(&vel.x, &step, fn_800B1668(*Entity_GetActor(self)));
    fn_80435530(&vel, fn_8043B3B0(lbl_80593BE8));
    fn_80065CB0(*Entity_GetActor(self), &vel);
}

void fn_800BE228(register void *self)
{
    Vector turn;
    Vector rot;
    fn_8019C48C(fn_8009AF80(*Entity_GetActor(self)), &turn);
    fn_8019C4D0(fn_8009AF80(*Entity_GetActor(self)), &rot);
    if (turn.z != 0.0f)
        fn_800B1668(*Entity_GetActor(self))->apply(&turn);
}

// Unreferenced literal in the original pool.
__asm__(".section .rodata\n\t.float 0.0\n\t.text");

void fn_800BE2F8(register void *self, Vector *up)
{
    Vector step;
    Vector turn;
    Vector vel;
    Vector rot;
    fn_8019C3AC(fn_8009AF80(*Entity_GetActor(self)), &step, 0);
    fn_8019C48C(fn_8009AF80(*Entity_GetActor(self)), &turn);
    fn_8019C4D0(fn_8009AF80(*Entity_GetActor(self)), &rot);
    if (turn.z != 0.0f)
        fn_800B1668(*Entity_GetActor(self))->apply(&turn);
    if (rot.x != 0.0f || rot.y != 0.0f || rot.z != 0.0f) {
        Mat4 m;
        fn_8042D7B0(&m);
        fn_80433FFC(&rot);
        fn_804342EC(&m, &rot);
        fn_80435754(&step, &m);
    }
    Vector cur;
    fn_80067050(*Entity_GetActor(self), &cur);
    fn_80434368(&vel.x, &step.x, fn_800B1668(*Entity_GetActor(self)));
    fn_80435530(&vel, fn_8043B3B0(lbl_80593BE8));
    vel.z = 0.0f;
    Mat4 basis;
    fn_8042D7B0(&basis);
    fn_8042DCC0(&basis);
    fn_8042DC84(basis.m[2], up);
    fn_8042F984(basis.m[0], lbl_80593DD0, up);
    fn_8042F76C(basis.m[0]);
    fn_8042F984(basis.m[1], basis.m[2], basis.m[0]);
    fn_8042F76C(basis.m[1]);
    fn_80435754(&vel, &basis);
    float t = fn_8042EBF4(&cur, basis.m[2]);
    t = t < 1.0f ? t : 1.0f;
    fn_8042FE08(&vel, basis.m[2], t);
    fn_80065CB0(*Entity_GetActor(self), &vel);
}

void fn_800BE638(register void *self)
{
    Vector cur;
    Vector step;
    Vector vel;
    fn_8019C3AC(fn_8009AF80(*Entity_GetActor(self)), &step, 0);
    fn_80067050(*Entity_GetActor(self), &cur);
    fn_80434368(&vel.x, &step.x, Entity_GetActor(self)->mat);
    fn_80435530(&vel, fn_8043B3B0(lbl_80593BE8));
    vel.z = cur.z;
    fn_80065CB0(*Entity_GetActor(self), &vel);
}

void fn_800BE740(register void *self)
{
    Vector vel;
    Vector step;
    fn_8019C3AC(fn_8009AF80(*Entity_GetActor(self)), &step, 0);
    fn_80067050(*Entity_GetActor(self), &vel);
    vel.z = step.z * fn_8043B3B0(lbl_80593BE8);
    fn_80065CB0(*Entity_GetActor(self), &vel);
}

void fn_800BE804(register void *self, int a, int on)
{
    if (on)
        fn_80095B9C(lbl_80552110, 2, a);
    else
        fn_80095B9C(lbl_80552110, 1, a);
}

int fn_800BE87C(register void *self)
{
    return fn_80095B74(lbl_80552110);
}

void fn_800BE8CC(void *model, const char *name, float a, float b)
{
    unsigned short index;
    Effect *e = fn_801A4190(model, name, 0, &index);
    while (e) {
        e->s22(a, b);
        e = fn_801A4190(model, name, index + 1, &index);
    }
}

void fn_800BE9AC(Ent &actor, int on)
{
    EffectEntry *e;
    for (unsigned int i = 0; i < 8; i++) {
        e = &lbl_804CC578[i];
        if (stricmp(e->character, (char *)&actor + 0xDC))
            continue;
        if (on)
            fn_800BE8CC(fn_8009AD80(actor), e->attachment, e->on[0], e->on[1]);
        else
            fn_800BE8CC(fn_8009AD80(actor), e->attachment, e->off[0], e->off[1]);
        break;
    }
}

int fn_800BEAC0(register void *self, int b)
{
    return fn_800BED04(self, fn_800CC148(self, 7), b);
}

void fn_800BEB28(register Obj *self)
{
    self->f18 |= 0x40000000;
    fn_800869AC(Entity_GetActor(self), fn_800869D4(Entity_GetActor(self)));
    if (fn_800CE5B0(self))
        fn_8042D1E8(lbl_805720C4, fn_8043B31C(fn_800CE5B0(self)), 1);
    else if (fn_80085D3C(Entity_GetActor(self)))
        fn_8042D1E8(lbl_805720C4, 1, 1);
}

void fn_800BEC14(register Obj *self)
{
    fn_800869AC(Entity_GetActor(self), fn_800B1884(*Entity_GetActor(self), 0x2D));
    if (fn_800CE5B0(self))
        fn_8042D1E8(lbl_805720C4, fn_8043B31C(fn_800CE5B0(self)), 0);
    else if (fn_80085D3C(Entity_GetActor(self)))
        fn_8042D1E8(lbl_805720C4, 1, 0);
    self->f18 &= ~0x40000000;
}
}
