// Starts a dash attack.

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

struct Act : Ent {
    int x;
};

struct Obj {
    char pad0[0x10];
    unsigned int f10;
    char pad14[0x18 - 0x14];
    unsigned int f18;
    char pad1C[0x3C - 0x1C];
    int f3C;
    char pad40[0x414 - 0x40];
    float f414; // energy cost of the motion
};

extern char lbl_8057217C[];

extern "C" {
Act *Entity_GetActor(void *self);
float fn_800B1884(Ent &actor, int id);
int fn_800BEAC0(void *self, int v);
void fn_800C05BC(void *self);
int fn_800CCA88(void *self);
int fn_800CC6DC(Obj &c);
int fn_8009AFC8(Ent &a);
int fn_80084B68(void *actor, float f);
void fn_800CD55C(void *self, int v);
int fn_8008582C(void *actor);
void *fn_800CE5B0(void *self);
int fn_8043B31C(void *p);
void fn_80428EEC(void *p, int v);
float fn_800CC1D4(void *self, int id, Vector *v);
int fn_800CC60C(void *self);
void fn_8042DC84(Vector *dst, Vector *src);
void *fn_80085980(void *actor);
Ent *fn_80134870(void *a);
int fn_800B0C58(void *actor);
Vector *fn_800B1724(Ent &actor);
Vector *fn_800B1750(Ent &actor);
float fn_8015F538(void *a, Vector *pos, Vector *dir);
int fn_80086374(void *actor);
Ent *fn_800E9AF8(void *self, float a, float b, float c, int d, Vector *dir);
Ent *fn_800E906C(void *self, int a, int b);
void fn_800B16D8(Ent *e, Vector *out);
void fn_80429038(Vector *out, Vector *a, Vector *b);
float fn_8042EC54(Vector *v);
void fn_8005A828(Ent &actor, Vector *p);
void *fn_800B14A0(void *c);
Ent *fn_80085928(void *p);
void fn_800B9CE8(void *a, int b, int c, void *d);
void *fn_8009AE00(Ent &actor);
float fn_8008FD58(void *set, int motion);
void fn_80429090(Vector *out, Vector *a, Vector *b, float s);
void fn_800C7FF4(Obj &c, Vector *v, float f);
void fn_800C98BC(void *self, void *e, int b);
void fn_80065AF8(Ent &actor, int a, int b);
int fn_800DDCB4(void *self, int motion, int retarget);
}

extern "C" int fn_800E2970(register Obj *self, int a)
{
    int air = (self->f10 & 0x40) || a;
    int motion;
    float f14 = fn_800B1884(*Entity_GetActor(self), 1);
    int f18 = 0;
    int f1C = 0;
    if (self->f18 & 0x80)
        return 0;
    fn_800BEAC0(self, 1);
    fn_800C05BC(self);
    self->f3C = 0;
    if (fn_800CCA88(self)) {
        if (fn_800CC6DC(*self) == 0x1E || fn_8009AFC8(*Entity_GetActor(self)) == 0x119) {
            motion = 0x49;
            air = 1;
            f18 = 1;
            if (!fn_80084B68(Entity_GetActor(self), fn_800B1884(*Entity_GetActor(self), 0xE6))) {
                f1C = 1;
                fn_800CD55C(self, 0);
            }
        } else if (fn_800CC6DC(*self) == 0x21) {
            motion = 0x4B;
            f14 = fn_800B1884(*Entity_GetActor(self), 2);
            air = 1;
            f18 = 1;
            if (!fn_80084B68(Entity_GetActor(self), fn_800B1884(*Entity_GetActor(self), 0xE6))) {
                f1C = 1;
                fn_800CD55C(self, 0);
            }
        } else if (air) {
            motion = 0x3C;
            if (!fn_80084B68(Entity_GetActor(self), fn_800B1884(*Entity_GetActor(self), 0xE1))) {
                f1C = 1;
                fn_800CD55C(self, 0);
            }
        } else {
            if (!(self->f10 & 0x20))
                return 0;
            motion = 0x3B;
            if (!fn_80084B68(Entity_GetActor(self), fn_800B1884(*Entity_GetActor(self), 0x23))) {
                f1C = 1;
                fn_800CD55C(self, 0);
            }
        }
    }
    if (!fn_800CCA88(self) || f1C) {
        if (fn_800CC6DC(*self) == 0x1E || fn_8009AFC8(*Entity_GetActor(self)) == 0x119) {
            motion = 0x48;
            air = 1;
            f18 = 1;
        } else if (fn_800CC6DC(*self) == 0x21) {
            motion = 0x4A;
            f14 = fn_800B1884(*Entity_GetActor(self), 2);
            air = 1;
            f18 = 1;
        } else if (air) {
            motion = 0x39;
        } else {
            if (!(self->f10 & 0x20))
                return 0;
            motion = 0x37;
        }
        if (f1C) {
            self->f414 = 0.0f;
            if (!fn_8008582C(Entity_GetActor(self)))
                fn_80428EEC(lbl_8057217C, fn_8043B31C(fn_800CE5B0(self)));
        }
    }
    Vector v20;
    Vector v30;
    float f40 = fn_800CC1D4(self, 0, &v20);
    Ent *target;
    float dist;
    if (f40 > 0.2f && !fn_800CC60C(self)) {
        fn_8042DC84(&v30, &v20);
    } else if (fn_800CC60C(self)) {
        target = fn_80134870(fn_80085980(Entity_GetActor(self)));
        if (target && fn_800B0C58(target))
            dist = fn_8015F538(fn_80085980(Entity_GetActor(self)), fn_800B1724(*target), &v30);
        else
            fn_8042DC84(&v30, fn_800B1750(*Entity_GetActor(self)));
    } else {
        fn_8042DC84(&v30, fn_800B1750(*Entity_GetActor(self)));
    }
    if ((motion == 0x3B || motion == 0x3C) && fn_80086374(Entity_GetActor(self)))
        target = fn_800E9AF8(self, fn_800B1884(*Entity_GetActor(self), 0xA), fn_800B1884(*Entity_GetActor(self), 9),
                             fn_800B1884(*Entity_GetActor(self), 0x14), 0, &v30);
    else
        target = fn_800E906C(self, air, f18);
    if (!target && fn_800CC60C(self) && fn_80134870(fn_80085980(Entity_GetActor(self)))
        && fn_800B0C58(fn_80134870(fn_80085980(Entity_GetActor(self)))))
        target = fn_80134870(fn_80085980(Entity_GetActor(self)));
    if (target) {
        Vector v50;
        Vector v60;
        fn_800B16D8(target, &v50);
        fn_80429038(&v60, &v50, fn_800B1724(*Entity_GetActor(self)));
        v60.z = 0.0f;
        dist = fn_8042EC54(&v60);
        fn_8005A828(*Entity_GetActor(self), &v50);
        if (fn_800B0C58(target) && fn_80085928(fn_800B14A0(target)))
            fn_800B9CE8(fn_80085928(fn_800B14A0(target)), 4, 0, Entity_GetActor(self));
        float reach = fn_8008FD58(fn_8009AE00(*Entity_GetActor(self)), motion);
        if ((reach - dist < 0.0f ? -(reach - dist) : reach - dist) < 0.5f) {
            Vector v78;
            fn_80429090(&v78, fn_800B1724(*Entity_GetActor(self)), &v60, dist - reach);
            v78.z = fn_800B1724(*Entity_GetActor(self))->z;
            fn_800C7FF4(*self, &v78, 0.1f);
        }
        fn_800C98BC(self, target, 1);
    } else {
        fn_800C98BC(self, 0, 1);
    }
    self->f18 |= 0x80;
    if (air)
        fn_80065AF8(*Entity_GetActor(self), 1, 0);
    else
        fn_80065AF8(*Entity_GetActor(self), 0, 0);
    fn_800DDCB4(self, motion, 1);
    return 1;
}
