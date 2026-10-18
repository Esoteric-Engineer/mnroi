// Starts a PLAYER clip (tuning field 196) and plays voice event 0x77; docs/versus.md row 20.

struct Ent {
    int pad;
};

struct PEnt : Ent { // matching_notes 44
    int x;
};

struct Obj {
    char pad0[0x10];
    int f10;
};

extern "C" {
PEnt *Entity_GetActor(void *self);
float fn_800B1884(Ent &actor, int id);
int fn_80097CE8(Ent &actor, int a, int mode, float speed, void *set, float blend, float f);
void fn_80084A60(void *actor, float f);
void fn_800BD2D0(void *self, int handle);
void fn_800CD7A8(void *self);
int fn_8010CDCC(Ent &self, int event, void *target, int a3, int a4, int a5, int a6);
}

extern "C" int fn_800D579C(register Obj *self, int unused)
{
    int handle = fn_80097CE8(*Entity_GetActor(self), 0x112, 0, 30.0f, 0, 7.5f, -1.0f);
    self->f10 = 0;
    if (handle < 0)
        return 0;
    fn_80084A60(Entity_GetActor(self), fn_800B1884(*Entity_GetActor(self), 0xC4));
    fn_800BD2D0(self, 0x3E8);
    fn_800CD7A8(self);
    fn_8010CDCC(*Entity_GetActor(self), 0x77, 0, 0, 0, 0, 0);
    return 1;
}
