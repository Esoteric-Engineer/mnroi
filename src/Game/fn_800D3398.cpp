// Steers the float at +0xDC toward PLAYER field 0x27 or -0x28, sets the effect-handle value, then starts a clip (0x1E-0x20, 0xDB-0xF6); fields in tools/nvbtool.py.

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

struct Handle {
    char d[0xC8];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
    virtual void s17(float a, float b);
};

struct Obj {
    char pad0[0xDC];
    float fDC; // +0xDC
    char padE0[0x3A0 - 0xE0];
    Handle *h; // +0x3A0
    char pad3A4[0x534 - 0x3A4];
    void *p534; // +0x534
    char pad538[0x950 - 0x538];
    float f950; // +0x950
};

extern char lbl_80593BE8[];

extern "C" {
PEnt *Entity_GetActor(void *self);
float fn_800B1884(Ent &actor, int id);
void *fn_800B1724(Ent &actor);
int fn_800CC148(void *self, int id);
int fn_80085300(void *actor, void *node, float a, float b, float *out);
void fn_80067050(Ent &actor, Vector *v);
void fn_80084A60(void *actor, float f);
float fn_80426A84(void *p);
int fn_800861EC(void *actor);
int fn_800CDA20(void *self);
PEnt *fn_800CD9B0(void *self);
int fn_800B0CC0(void *c);
int fn_800A4438(void *c);
int fn_800A4408(void *c);
Handle *fn_80393B28(Ent &actor, Handle *h);
void fn_80114D70(void *p, int v);
int fn_800664C0(Ent &actor);
float fn_800D9308(float a, float b, float c);
void fn_80065CB0(Ent &actor, Vector *v);
void *fn_800B1478(void *c);
int fn_800A4130(void *c);
int fn_800A43A0(void *c);
int fn_80097CE8(Ent &actor, int a, int mode, float speed, void *set, float blend, float f);
}

extern "C" int fn_800D3398(register Obj *self)
{
    Vector v8;
    float f18 = 0.5f;
    Vector v20;
    float f30 = 0.0f;
    int f34;
    float f38 = -fn_800B1884(*Entity_GetActor(self), 0x28);
    float f3C = fn_800B1884(*Entity_GetActor(self), 0x27);
    float f40 = fn_800B1884(*Entity_GetActor(self), 0x2A);
    int f44 = 0;
    float f48;
    int f4C = fn_800CC148(self, 0x10);
    int f50 = fn_80085300(Entity_GetActor(self), fn_800B1724(*Entity_GetActor(self)), 0.7f, f40 + 1.0f, &f48);
    if (f50)
        self->f950 = f48;
    else
        self->f950 = -1.0f;
    fn_80067050(*Entity_GetActor(self), &v20);
    self->fDC = v20.z;
    if (f4C) {
        fn_80084A60(Entity_GetActor(self), fn_800B1884(*Entity_GetActor(self), 0x9E) * fn_80426A84(lbl_80593BE8));
        f18 = 1.0f;
    } else if (!fn_800861EC(Entity_GetActor(self))) {
        if (f50 && self->fDC < 1.0f) {
            if (f48 < f40) {
                f18 = 1.0f;
                f44 = 1;
            } else {
                f18 = 0.5f;
            }
            self->f950 = f48;
        } else {
            f18 = 0.0f;
        }
    } else {
        f18 = 0.0f;
    }
    if (fn_800CDA20(self)) {
        PEnt &f54 = *fn_800CD9B0(self);
        if (fn_800B0CC0(&f54)) {
            if (fn_800A4438(&f54)) {
                f3C = f3C * 0.25f;
                f38 = 2.0f * f38;
            } else if (fn_800A4408(&f54)) {
                f3C = f3C * 0.5f;
                f38 = f38 * 1.5f;
            }
        }
    }
    self->h = fn_80393B28(*Entity_GetActor(self), self->h);
    if (self->h) {
        float f58 = f18 * 0.7f + 0.3f;
        if (f48 < f40)
            f58 = 1.0f;
        self->h->s17(f58, -1.0f);
        fn_80114D70(self->p534, (int)(f58 * 1000.0f));
    }
    if (f18 >= 1.0f)
        f30 = f3C;
    else if (f18 < 0.5f)
        f30 = f38;
    if (fn_800664C0(*Entity_GetActor(self)))
        f30 = 0.0f;
    self->fDC = fn_800D9308(self->fDC, f30, fn_80426A84(lbl_80593BE8) * 10.0f);
    v20.z = self->fDC;
    if (!fn_800664C0(*Entity_GetActor(self)))
        fn_80065CB0(*Entity_GetActor(self), &v20);
    if (fn_800CD9B0(self)) {
        if (fn_800A4130(fn_800B1478(fn_800CD9B0(self))))
            f34 = 0xF6;
        else if (fn_800A43A0(fn_800B1478(fn_800CD9B0(self))))
            f34 = 0xDB;
        else
            f34 = 0xDE;
    } else if (f44) {
        f34 = 0x1F;
    } else if (f30 > 1.0f && !f44) {
        f34 = 0x1E;
    } else if (f30 < -1.0f) {
        f34 = 0x1F;
    } else {
        f34 = 0x20;
    }
    fn_80097CE8(*Entity_GetActor(self), f34, 1, 30.0f, 0, 7.5f, -1.0f);
    return 0;
}
