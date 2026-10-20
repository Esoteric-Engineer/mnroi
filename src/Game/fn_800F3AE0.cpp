// State entry that arms a timer from tuning field 60 and clears two state bits.

struct Ent {
    int pad;
};

struct PEnt : Ent { // matching_notes 44
    int x;
};

struct Actor {
    char pad0[0x30];
    unsigned int f30; // +0x30
};

struct Obj {
    char pad0[0x18];
    unsigned int f18; // +0x18
    char pad1C[0xD4 - 0x1C];
    unsigned int fD4; // +0xD4
};

extern char lbl_80593BE8[];

extern "C" {
PEnt *Entity_GetActor(void *self);
unsigned int fn_8042EFF8(void *g);
int fn_800B18EC(Ent &actor, int id);
void fn_80065AF8(Ent &actor, int a, int b);
void fn_800CD484(void *self, int a);
int fn_800CC60C(void *self);
void *fn_80085980(void *actor);
void fn_80136214(void *p, int a);
void fn_80442174(void *p, unsigned int bit);
}

extern "C" int fn_800F3AE0(register Obj *self, int unused)
{
    register unsigned int now = fn_8042EFF8(lbl_80593BE8);
    self->fD4 = now + fn_800B18EC(*Entity_GetActor(self), 60);
    self->f18 &= 0xFFD7FFFF;
    ((Actor *)Entity_GetActor(self))->f30 &= ~2;
    fn_80065AF8(*Entity_GetActor(self), 1, 0);
    fn_800CD484(self, 0);
    if (fn_800CC60C(self) && fn_80085980(Entity_GetActor(self))) {
        fn_80136214(fn_80085980(Entity_GetActor(self)), 0x19);
        fn_80442174(fn_80085980(Entity_GetActor(self)), 0x19);
    }
    return 1;
}
