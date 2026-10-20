// Chooses the next state of a PLAYER state machine from the entity's flags (tuning field 30).

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

class Actor60
{
public:
    char pad[0x60];
    float x; // +0x60
    void clearX();
};

struct Ent {
    int pad;
};

struct PEnt : Ent { // matching_notes 44
    int x;
};

struct EObj {
    char pad0[0x3AC];
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
    char pad3B0[0x904 - 0x3B0];
    int f904;
};

extern "C" {
PEnt *Entity_GetActor(void *self);
int fn_800CC76C(void *self);
void fn_800C8358(void *self);
void fn_800BEAC0(void *self, int v);
void fn_800BDF20(void *self);
int fn_800C4D70(void *self, int a, float f, int b);
Actor60 *fn_8009AF80(Ent &actor);
int fn_800CC8BC(void *self);
void fn_80061CFC(void *actor);
int fn_800CC0BC(void *self, int id);
int fn_800CF584(void *self, Vector *v);
void fn_800CF7E8(void *self, Vector *v, int mode);
void fn_800E2970(void *self, int v);
int fn_800E07A4(void *self, int v);
int fn_800CBF20(void *self);
int fn_800CC148(void *self, int id);
int fn_800D2CF8(void *self);
int fn_8008606C(void *actor);
float fn_800B1884(Ent &actor, int id);
int fn_80084B68(void *actor, float f);
int fn_800CC2E0(void *self);
}

extern "C" void fn_800CFD2C(register Obj *self)
{
    if (fn_800CC76C(self) != 0) {
        fn_800C8358(self);
    }
    fn_800BEAC0(self, 0);
    fn_800BDF20(self);
    if (fn_800C4D70(self, 0, 0.0f, 0) != 0) {
        if (self->f904 == 0) {
            fn_8009AF80(*Entity_GetActor(self))->clearX();
        }
        return;
    }
    if (fn_800CC8BC(self) != 0) {
        fn_80061CFC(Entity_GetActor(self));
        if (fn_800CC0BC(self, 5) != 0) {
            Vector v;
            if (fn_800CF584(self, &v) != 0) {
                fn_800CF7E8(self, &v, 3);
                return;
            }
        }
        if (fn_800CC0BC(self, 2) != 0) {
            fn_800E2970(self, 1);
            return;
        }
        if (fn_800CC0BC(self, 0x12) != 0 && fn_800E07A4(self, 0) != 0) {
            return;
        }
        if (fn_800CBF20(self) != 0 && fn_800CC148(self, 9) != 0 && fn_800D2CF8(self) != 0) {
            self->s5(0x17);
            return;
        }
        if (fn_8008606C(Entity_GetActor(self)) != 0 && fn_800CC148(self, 9) != 0) {
            if (fn_80084B68(Entity_GetActor(self), fn_800B1884(*Entity_GetActor(self), 0x1E)) != 0) {
                self->s5(0x1E);
                return;
            }
        }
    }
    if (fn_800CC2E0(self) != 0) {
        return;
    }
    self->s5(5);
}
