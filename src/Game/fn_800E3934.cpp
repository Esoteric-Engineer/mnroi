// Per-frame step of a PLAYER state machine: picks the clip by the actor's type and ends the state (tuning fields 0xA0, 0xA1).

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
    char pad440[0x55C - 0x440];
    unsigned int f55C;
};

extern char lbl_80593BE8[];

extern "C" {
PEnt *Entity_GetActor(void *self);
float fn_800B1884(Ent &actor, int id);
int fn_8009B04C(Ent &actor);
void fn_80067050(Ent &actor, Vector *v);
float fn_80440EDC(Vector *v);
unsigned int fn_8042EFF8(void *g);
void fn_8009AEC8(Ent &actor, int v);
int fn_800CC2E0(void *self);
void fn_800BDF20(void *self);
int fn_800C4D70(void *self, int a, float f, int b);
int fn_80097CE8(Ent &actor, int a, int mode, float speed, void *set, float blend, float f);
int fn_800419AC(void);
int fn_800B13D8(Ent &actor);
int fn_80041F00(int v);
void fn_80040CE0(void *actor, Vector *v, float f, int z);
void *fn_800B1724(Ent &actor);
Vector *fn_800B1750(Ent &actor);
void fn_80429038(Vector *out, Vector *a, void *b);
void fn_8042DC84(Vector *dst, void *src);
float fn_80434040(Vector *v);
float fn_800B2670(Ent &actor);
void fn_8042F76C(Vector *v);
float fn_8042EBF4(Vector *a, Vector *b);
void fn_80435530(Vector *v, float s);
void fn_80065CB0(Ent &actor, Vector *v);
void fn_8005A828(Ent &actor, Vector *p);
int fn_800E8884(void *self);
void fn_800BD2D0(void *self, int handle);
}

extern "C" void fn_800E3934(register Obj *self)
{
    int f8 = 0;
    int type = fn_8009B04C(*Entity_GetActor(self));
    int isFlag = type == 0x45;
    int f14 = 0;
    Vector v18;
    fn_80067050(*Entity_GetActor(self), &v18);
    if (fn_80440EDC(&v18) < 1.0f) {
        if (self->f55C == 0)
            self->f55C = fn_8042EFF8(lbl_80593BE8);
    } else {
        self->f55C = 0;
    }
    if (self->f55C != 0 && self->f55C + 3000 < fn_8042EFF8(lbl_80593BE8)) {
        fn_8009AEC8(*Entity_GetActor(self), 0);
        self->s5(6);
        return;
    }
    if (fn_800CC2E0(self)) {
        fn_800BDF20(self);
        switch (type) {
        case 0x42:
        case 0x45:
            f14 = fn_800C4D70(self, 1, 0.0f, 0);
            break;
        }
    }
    if (!fn_800CC2E0(self)) {
        switch (type) {
        case 0x45:
            fn_80097CE8(*Entity_GetActor(self), 0x47, 0, 30.0f, 0, 7.5f, -1.0f);
            if (fn_800419AC()) {
                if (fn_80041F00(fn_800B13D8(*Entity_GetActor(self)))) {
                    float f28;
                    if (isFlag)
                        f28 = fn_800B1884(*Entity_GetActor(self), 0xA1);
                    else
                        f28 = fn_800B1884(*Entity_GetActor(self), 0xA0);
                    fn_80040CE0(Entity_GetActor(self), &self->v430, f28, 0);
                }
            }
            break;
        case 0x42:
            fn_80097CE8(*Entity_GetActor(self), 0x44, 0, 30.0f, 0, 7.5f, -1.0f);
            break;
        case 0x43:
        case 0x46:
            fn_8009AEC8(*Entity_GetActor(self), 0);
            self->s5(2);
            return;
        }
        f14 = fn_800C4D70(self, 1, 0.0f, 1);
        Vector v30;
        fn_80429038(&v30, &self->v430, fn_800B1724(*Entity_GetActor(self)));
        Vector v40;
        fn_8042DC84(&v40, &v30);
        v40.z = 0.0f;
        float f28 = fn_80434040(&v40);
        f28 = f28 - fn_800B2670(*Entity_GetActor(self));
        fn_8042F76C(&v30);
        if (f28 > 0.1f && fn_8042EBF4(&v30, fn_800B1750(*Entity_GetActor(self))) > 0.0f) {
            if (isFlag)
                fn_80435530(&v30, fn_800B1884(*Entity_GetActor(self), 0xA1));
            else
                fn_80435530(&v30, fn_800B1884(*Entity_GetActor(self), 0xA0));
            fn_80065CB0(*Entity_GetActor(self), &v30);
            fn_8005A828(*Entity_GetActor(self), &self->v430);
        } else {
            f14 = 1;
        }
    }
    f8 = fn_800E8884(self);
    if (f14) {
        int handle;
        fn_800BD2D0(self, 0);
        if (type == 0x47)
            handle = fn_80097CE8(*Entity_GetActor(self), 0x46, 0, 30.0f, 0, 7.5f, -1.0f);
        else
            handle = fn_80097CE8(*Entity_GetActor(self), 0x43, 0, 30.0f, 0, 7.5f, -1.0f);
        fn_800BD2D0(self, handle);
        self->f18 |= 0x80;
        return;
    } else if (f8) {
        fn_8009AEC8(*Entity_GetActor(self), 0);
        self->s5(5);
    }
}
