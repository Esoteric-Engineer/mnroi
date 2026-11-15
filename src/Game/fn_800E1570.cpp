// Melee state (0xB) exit: undoes the enter's flags and releases the target unless the next state is Melee again.

struct Ent {
    int pad;
};

struct PEnt : Ent { // matching_notes 44
    int x;
};

struct Act : PEnt {
    char pad8[0x30 - 8];
    unsigned int f30;
};

struct Obj {
    char pad0[0x10];
    unsigned int flags; // +0x10
    char pad14[0x18 - 0x14];
    unsigned int f18;
    char pad1C[0x3F4 - 0x1C];
    unsigned int f3F4;
    char pad3F8[0x4E4 - 0x3F8];
    int h4E4;
};

extern "C" {
PEnt *Entity_GetActor(void *self);
Act *Entity_GetActorA(void *self) __asm__("Entity_GetActor");
void fn_800CD3AC(void *self, int v);
void fn_800BB02C(void *self, int v);
void fn_800DA134(void *self);
void *fn_800ACFA8(int handle);
void fn_80066A48(Ent &actor, void *p);
void fn_800CBE8C(void *self);
void fn_800E893C(void *self);
int fn_800862AC(void *actor);
void *fn_8009AD80(Ent &actor);
void fn_80446784(void *p);
int fn_800CD7D4(void *self);
void fn_80065AF8(Ent &actor, int a, int b);
void fn_800DBC90(void *self, int v);
int fn_800B13D8(Ent &actor);
void fn_80041E80(int id);
char *fn_8009AF80(Ent &actor);
int fn_8044667C(void *axis, void *owner, float v, float w, int mode);
}

extern "C" int fn_800E1570(register Obj *self, int next)
{
    fn_800CD3AC(self, 0);
    fn_800BB02C(self, 0);
    self->f18 &= ~0x80000000;
    self->f3F4 &= ~8;
    fn_800DA134(self);
    void *f0c = fn_800ACFA8(self->h4E4);
    if (f0c)
        fn_80066A48(*Entity_GetActor(self), f0c);
    fn_800CBE8C(self);
    fn_800E893C(self);
    if (fn_800862AC(Entity_GetActor(self)) && fn_8009AD80(*Entity_GetActor(self)))
        fn_80446784(fn_8009AD80(*Entity_GetActor(self)));
    if (self->flags & 2 && !fn_800CD7D4(self))
        fn_80065AF8(*Entity_GetActor(self), 1, 0);
    self->f18 &= ~0x380000;
    Entity_GetActorA(self)->f30 &= ~2;
    fn_800DBC90(self, 0);
    if (next != 0xB)
        fn_80041E80(fn_800B13D8(*Entity_GetActor(self)));
    fn_8044667C(fn_8009AF80(*Entity_GetActor(self)) + 0x104, 0, 0.0f, 0.0f, 0);
    Entity_GetActorA(self)->f30 &= ~0x40000000;
    return 1;
}
