// Picks the PLAYER animation for the entity's current state and plays it (tuning fields 0x68, 0x22, 0x9D, 0x6D, 0x69, 0x6B); docs/versus.md row 20.

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
    char pad3B0[0x514 - 0x3B0];
    float f514;
};

extern "C" {
PEnt *Entity_GetActor(void *self);
void *fn_800C9FD0(void *self);
int fn_800B0C58(void *node);
void *fn_800B14A0(void *node);
void *fn_80085928(void *p);
void fn_800B9CE8(void *a, int b, int c, void *d);
float fn_80086D54(void *actor);
int fn_800CC0BC(void *self, int id);
int fn_800CC60C(void *self);
void fn_80067050(Ent &actor, Vector *out);
float fn_8042EC54(Vector *v);
Vector *fn_800B1750(Ent &actor);
void fn_8042DC84(Vector *dst, Vector *src);
void fn_80435530(Vector *v, float s);
void fn_80065CB0(Ent &actor, Vector *v);
int fn_800CCA88(void *self);
void *fn_800CD9B0(void *self);
int fn_80084A60(void *actor, float f);
float fn_800B1884(Ent &actor, int id);
int fn_800CC6AC(void *self);
int fn_8009AFC8(Ent &actor);
void *fn_800B1478(void *c);
int fn_800A4130(void *p);
int fn_800A4468(void *p);
float fn_8042EBF4(Vector *a, Vector *b);
void fn_8042FDBC(Vector *out, Vector *v, float f);
int fn_80097CE8(Ent &actor, int a, int mode, float speed, void *set, float blend, float f);
void fn_8009AEC8(Ent &actor, int v);
void fn_800BD2D0(void *self, int handle);
}

extern "C" int fn_800C45B0(register Obj *self, int a)
{
    int handle;
    int moving = 0;
    int anim;
    int g = 200;
    void *node = fn_800C9FD0(self);
    if (node && fn_800B0C58(node) && fn_80085928(fn_800B14A0(node))) {
        fn_800B9CE8(fn_80085928(fn_800B14A0(node)), 10, 0, Entity_GetActor(self));
    }
    self->f514 = fn_80086D54(Entity_GetActor(self));
    if (fn_800CC0BC(self, 0x14)) {
        anim = 8;
        if (fn_800CC60C(self)) {
            moving = 1;
            Vector v;
            fn_80067050(*Entity_GetActor(self), &v);
            float len = fn_8042EC54(&v);
            if (len < fn_80086D54(Entity_GetActor(self))) {
                len = fn_80086D54(Entity_GetActor(self));
                fn_8042DC84(&v, fn_800B1750(*Entity_GetActor(self)));
            }
            fn_80435530(&v, len);
            fn_80065CB0(*Entity_GetActor(self), &v);
        }
    } else if (a) {
        anim = a;
    } else {
        if (fn_800CCA88(self) && !fn_800CD9B0(self)) {
            if (fn_80084A60(Entity_GetActor(self), fn_800B1884(*Entity_GetActor(self), 0x22)))
                moving = 1;
        }
        switch ((unsigned int)fn_800CC6AC(self)) {
        case 8:
            anim = 0x10F;
            g = 0;
            break;
        case 0x1E:
            anim = 0x119;
            g = 0;
            break;
        case 4:
            if (fn_8009AFC8(*Entity_GetActor(self)) == 3)
                self->f514 = fn_800B1884(*Entity_GetActor(self), 0x9D);
        case 3:
            g = 0x15E;
            if (fn_800CD9B0(self)) {
                if (fn_800A4130(fn_800B1478(fn_800CD9B0(self)))) {
                    anim = 0xEF;
                    self->f514 = fn_800B1884(*Entity_GetActor(self), 0x6D);
                } else if (fn_800A4468(fn_800B1478(fn_800CD9B0(self))) == 0) {
                    anim = 0xCC;
                    self->f514 = fn_800B1884(*Entity_GetActor(self), 0x69);
                } else {
                    anim = 0xD7;
                    self->f514 = fn_800B1884(*Entity_GetActor(self), 0x6B);
                }
            } else if (moving) {
                anim = 9;
            } else {
                anim = 7;
            }
            break;
        default:
            g = 300;
            if (fn_800CD9B0(self)) {
                if (fn_800A4130(fn_800B1478(fn_800CD9B0(self)))) {
                    anim = 0xEF;
                    self->f514 = fn_800B1884(*Entity_GetActor(self), 0x6D);
                } else if (fn_800A4468(fn_800B1478(fn_800CD9B0(self))) == 0) {
                    anim = 0xCB;
                    self->f514 = fn_800B1884(*Entity_GetActor(self), 0x69);
                } else {
                    anim = 0xD6;
                    self->f514 = fn_800B1884(*Entity_GetActor(self), 0x6B);
                }
            } else if (moving) {
                anim = 8;
            } else {
                anim = 6;
            }
            break;
        }
    }
    Vector v;
    fn_80067050(*Entity_GetActor(self), &v);
    float len = fn_8042EBF4(&v, fn_800B1750(*Entity_GetActor(self)));
    len = len > 0.0f ? len : 0.0f;
    fn_8042FDBC(&v, fn_800B1750(*Entity_GetActor(self)), len);
    fn_80065CB0(*Entity_GetActor(self), &v);
    handle = fn_80097CE8(*Entity_GetActor(self), anim, 1, 30.0f, 0, 7.5f, -1.0f);
    if (handle > 0) {
        fn_8009AEC8(*Entity_GetActor(self), 0);
        self->s5(7);
        fn_800BD2D0(self, g);
        return 1;
    }
    return 0;
}
