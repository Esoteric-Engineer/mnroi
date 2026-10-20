// Entry state of a PLAYER state machine: steers the entity to its target and starts a clip (tuning fields 0x4C, 0x23, 0xEC).

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

struct EObj {
    char pad0[0x18];
    unsigned int f18;
    char pad1C[0x3AC - 0x1C];
};

struct EBase : EObj {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5(int mode); // vtable +0x30
};

struct Obj : EBase {
    char pad3B0[0x430 - 0x3B0];
    Vector v430;
};

extern "C" {
PEnt *Entity_GetActor(void *self);
float fn_800B1884(Ent &actor, int id);
void *fn_800E89B0(void *self, float a, float b, int c, int d, int e);
void fn_800BEAC0(void *self, int v);
void fn_800C05BC(void *self);
void *fn_800B1724(Ent &actor);
Vector *fn_800B1750(Ent &actor);
void fn_8042DC84(Vector *dst, void *src);
void fn_8042FE08(Vector *a, Vector *b, float t);
void fn_800B16D8(void *node, Vector *out);
void fn_80429038(Vector *out, Vector *a, void *b);
float fn_8042EC54(Vector *v);
int fn_800B0C58(void *node);
void *fn_800B14A0(void *node);
void *fn_80085928(void *p);
void fn_800B9CE8(void *a, int b, int c, void *d);
void fn_8005A828(Ent &actor, Vector *p);
int fn_800CCA88(void *self);
int fn_80084B68(void *actor, float f);
int fn_80097CE8(Ent &actor, int a, int mode, float speed, void *set, float blend, float f);
void fn_800BD2D0(void *self, int handle);
void fn_800DA884(void *self, int state);
}

extern "C" int fn_800E339C(register Obj *self)
{
    void *node = fn_800E89B0(self, fn_800B1884(*Entity_GetActor(self), 0xEC), fn_800B1884(*Entity_GetActor(self), 0x4C), 0, 0, 1);
    if (self->f18 & 0x80)
        return 0;
    fn_800BEAC0(self, 0);
    fn_800C05BC(self);
    fn_8042DC84(&self->v430, fn_800B1724(*Entity_GetActor(self)));
    self->v430.z = self->v430.z - 40.0f;
    fn_8042FE08(&self->v430, fn_800B1750(*Entity_GetActor(self)), 40.0f);
    if (node) {
        Vector v10;
        Vector v20;
        fn_800B16D8(node, &v10);
        fn_80429038(&v20, &v10, fn_800B1724(*Entity_GetActor(self)));
        float f30;
        float f34 = v20.z;
        v20.z = 0.0f;
        f30 = fn_8042EC54(&v20);
        if (f34 < -2.0f && f30 > 2.0f) {
            if (fn_800B0C58(node) && fn_80085928(fn_800B14A0(node))) {
                fn_800B9CE8(fn_80085928(fn_800B14A0(node)), 4, 0, Entity_GetActor(self));
            }
            fn_8005A828(*Entity_GetActor(self), &v10);
            fn_8042DC84(&self->v430, &v10);
        }
    }
    int state = 0x42;
    if (fn_800CCA88(self)) {
        if (fn_80084B68(Entity_GetActor(self), fn_800B1884(*Entity_GetActor(self), 0x23)))
            state = 0x45;
    }
    self->s5(0x11);
    int handle = fn_80097CE8(*Entity_GetActor(self), state, 0, 30.0f, 0, 7.5f, -1.0f);
    if (handle > 0)
        fn_800BD2D0(self, handle);
    fn_800DA884(self, state);
    return 1;
}
