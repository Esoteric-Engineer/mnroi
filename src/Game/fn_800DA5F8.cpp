// Melee state (0xB) enter: resets the state's flags, saves the actor's z in fD8/fDC and, in a grab, links the target (fn_8003EE24).

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

struct Act : PEnt {
    char pad8[0x30 - 8];
    unsigned int f30;
    char pad34[0x308 - 0x34];
    unsigned int f308;
};

struct Obj {
    char pad0[8];
    unsigned char state; // +0x8
    char pad9[0x10 - 9];
    unsigned int flags; // +0x10
    char pad14[0x18 - 0x14];
    unsigned int f18;
    char pad1C[0xD8 - 0x1C];
    float fD8;
    float fDC;
};

extern "C" {
PEnt *Entity_GetActor(void *self);
Act *Entity_GetActorA(void *self) __asm__("Entity_GetActor");
void fn_800CC578(void *self, int a, int b);
void fn_800CC3CC(void *self);
void fn_800CD3AC(void *self, int v);
void fn_800BB02C(void *self, int v);
void fn_8006668C(Ent &actor, float v);
void fn_80067050(Ent &actor, Vector *v);
Vector *fn_800B1724(Ent &actor);
PEnt *fn_800C9FD0(void *self);
int fn_80095608(void *actor);
int fn_80085D3C(void *actor);
int fn_800B0C58(void *c);
void *fn_800B14A0(void *c);
int fn_800B13D8(Ent &actor);
void fn_8003EE24(int id, int other, int a, int b);
}

extern "C" int fn_800DA5F8(register Obj *self, int unused)
{
    fn_800CC578(self, 0, 0);
    fn_800CC3CC(self);
    self->flags = 0;
    self->f18 &= ~0x4000;
    fn_800CD3AC(self, 1);
    fn_800BB02C(self, 1);
    fn_8006668C(*Entity_GetActor(self), 0.0f);
    self->flags |= 0x20;
    self->flags &= ~0x2080C;
    self->flags &= ~0x10;
    if (Entity_GetActorA(self)->f308 & 0x4000)
        Entity_GetActorA(self)->f30 |= 0x40000000;
    Vector v10;
    fn_80067050(*Entity_GetActor(self), &v10);
    self->fDC = v10.z;
    self->fD8 = fn_800B1724(*Entity_GetActor(self))->z;
    PEnt *f20 = Entity_GetActor(self);
    PEnt *f24 = fn_800C9FD0(self);
    if (fn_80095608(f20) || fn_80085D3C(f20)) {
        int f28 = 0;
        if (f24 && fn_800B0C58(f24)) {
            void *f2c = fn_800B14A0(f24);
            if (f2c && (fn_80085D3C(f2c) || fn_80095608(f2c)))
                f28 = fn_800B13D8(*f24);
        }
        if ((!f24 || (f24 && f28)) && self->state != 0xB)
            fn_8003EE24(fn_800B13D8(*Entity_GetActor(self)), f28, 0, 0);
    }
    return 1;
}
