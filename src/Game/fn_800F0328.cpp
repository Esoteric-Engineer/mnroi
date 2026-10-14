// Starts a PLAYER clip on the entity's actor (tuning fields 9, 10, 16, 20, 32); docs/versus.md row 20.

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

struct PEnt : Ent { // the accessor returns the derived class; each conversion saves the pointer
    int x;
};

struct EObj {
    char d[0x3AC];
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
    char pad3B0[0x44];
    int f3F4;
    char pad3F8[0x11];
    char b409;
    char b40a;
    char b40b;
    char b40c;
    int f410;
    float f414;
};

extern "C" {
PEnt *Entity_GetActor(void *self);
void *fn_800C9FD0(void *self);
int fn_80085D3C(void *actor);
int fn_800CCA88(void *self);
int fn_80084B68(void *actor, float f);
float fn_800B1884(Ent &actor, int id);
float fn_800CC1D4(void *self, int a, Vector *out);
int fn_800CC60C(void *self);
void fn_8042DC84(Vector *dst, Vector *src);
Vector *fn_800B1750(Ent &actor);
void *fn_800E9AF8(void *self, float a, float b, float c, int d, Vector *e);
void *fn_800B1724(void *node);
void fn_8005A828(Ent &actor, void *p);
int fn_800B0C58(void *node);
void *fn_800B14A0(void *node);
void *fn_80085928(void *p);
void fn_800B9CE8(void *a, int b, int c, void *d);
int fn_80097CE8(Ent &actor, int a, int mode, float speed, void *set, float blend, float f);
void fn_800C98BC(void *self, void *node, int v);
void fn_800D9538(void *actor, int anim, float f, int a, int b);
void fn_800BD2D0(void *self, int handle);
}

extern "C" int fn_800F0328(register Obj *self)
{
    int handle = -1;
    int anim = 0x60;
    float speed = 0.0f;
    Vector v18;
    int zero = 0;
    unsigned int cnt;
    void *node = fn_800C9FD0(self);

    if (fn_80085D3C(Entity_GetActor(self))) {
        if (!fn_800CCA88(self))
            return 0;
        if (!fn_80084B68(Entity_GetActor(self), fn_800B1884(*Entity_GetActor(self), 0x20)))
            return 0;
    }
    Vector v38;
    Vector v48;
    float f58 = fn_800CC1D4(self, 0, &v38);
    if (f58 > 0.2f && !fn_800CC60C(self))
        fn_8042DC84(&v48, &v38);
    else
        fn_8042DC84(&v48, fn_800B1750(*Entity_GetActor(self)));
    register float a = fn_800B1884(*Entity_GetActor(self), 10);
    register float b = fn_800B1884(*Entity_GetActor(self), 9);
    node = fn_800E9AF8(self, a, b, fn_800B1884(*Entity_GetActor(self), 0x14), 0, &v48);
    cnt = (unsigned int)fn_800B1884(*Entity_GetActor(self), 0x10);
    cnt = cnt;
    anim = 0x61;
    self->f414 = fn_800B1884(*Entity_GetActor(self), 0x20);
    if (node) {
        fn_8005A828(*Entity_GetActor(self), fn_800B1724(node));
        if (fn_800B0C58(node) && fn_80085928(fn_800B14A0(node))) {
            fn_800B9CE8(fn_80085928(fn_800B14A0(node)), 1, 0, Entity_GetActor(self));
        }
    }
    handle = fn_80097CE8(*Entity_GetActor(self), anim, 0, 30.0f, 0, 7.5f, -1.0f);
    if (handle < 0)
        return 0;
    fn_800C98BC(self, node, 1);
    self->b40a = 0;
    self->b409 = 0;
    self->b40b = 1;
    self->b40c = 0x15;
    self->f410 = 0xCA;
    self->s5(0x18);
    fn_800D9538(Entity_GetActor(self), anim, 0.0f, self->f3F4, 0);
    fn_800BD2D0(self, handle);
    return 1;
}
