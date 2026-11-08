// Prone state's enter. Clears controller bits 0x2A0000; ability 0x100 also clears flag 0x8 on the actor's fn_8009AD80 object.

struct Ent {
    int pad;
};

struct PEnt : Ent { // matching_notes 44
    int x;
};

struct Obj {
    char pad0[0x18];
    unsigned int f18; // +0x18
};

extern "C" {
PEnt *Entity_GetActor(void *self);
void fn_800CD4CC(void *self, int v);
void fn_800CD7A8(void *self);
int fn_800862AC(void *actor);
void *fn_8009AD80(Ent &actor);
void fn_80446784(void *p);
void fn_8006668C(Ent &actor, float v);
void fn_800CD484(void *self, int a);
}

extern "C" int fn_800F30E8(register Obj *self, int prev)
{
    fn_800CD4CC(self, 0);
    fn_800CD7A8(self);
    self->f18 &= 0xFFD5FFFF;
    if (fn_800862AC(Entity_GetActor(self)))
        fn_80446784(fn_8009AD80(*Entity_GetActor(self)));
    fn_8006668C(*Entity_GetActor(self), 4.0f);
    fn_800CD484(self, 0);
    return 1;
}
