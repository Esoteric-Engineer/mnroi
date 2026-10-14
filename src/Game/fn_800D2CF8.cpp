// True if fn_800861EC or fn_80084B68 (with PLAYER tuning field 41) accepts the entity's actor; docs/versus.md row 20.

extern "C" {
void *Entity_GetActor(void *self);
int fn_800861EC(void *actor);
float fn_800B1884(void *actor, int id);
int fn_80084B68(void *actor, float f);
}

extern "C" int fn_800D2CF8(register void *self)
{
    if (fn_800861EC(Entity_GetActor(self)) != 0) {
        return 1;
    }
    register void *b;
    register void *a = Entity_GetActor(self);
    b = Entity_GetActor(self);
    if (fn_80084B68(a, fn_800B1884(b, 0x29)) == 0) {
        return 0;
    }
    return 1;
}
