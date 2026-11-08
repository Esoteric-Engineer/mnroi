// Block and SuperBlock states' event handler.

struct Clip;

struct Channel {
    char pad0[0x1C];
    Clip *clip;            // +0x1C
};

struct Obj {
    char pad0[0x10];
    int f10;               // +0x10
};

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
float fn_80199F24(Clip *clip, int tag);
void fn_8019DB24(Channel *ch, float time);

int fn_800E4FCC(register Obj *self, Channel *ch, int type, int value, int extra)
{
    switch (type) {
    case 0x14:
        fn_8009AEC8(*Entity_GetActor(self), 0);
        break;
    case 0x10:
        fn_8019DB24(ch, fn_80199F24(ch->clip, 0x11));
        return 1;
    case 0x27:
        self->f10 = 0;
        break;
    case 0x12:
        fn_800CD77C(self);
        break;
    }
    return 0;
}
}
