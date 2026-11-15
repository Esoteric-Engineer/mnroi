// Prone state's event handler.

struct Ent {
    int pad;
};

struct PEnt : Ent {
    int x;
};

extern "C" {
PEnt *Entity_GetActor(void *self);
void fn_8009AEC8(Ent &actor, int v);
void fn_800CD77C(void *self);

int fn_800F31BC(register void *self, int ch, int type, int value, int extra)
{
    switch (type) {
    case 0x12:
        fn_800CD77C(self);
        break;
    case 0x14:
        fn_8009AEC8(*Entity_GetActor(self), 0);
        break;
    default:
        return 0;
    }
    return 1;
}
}
