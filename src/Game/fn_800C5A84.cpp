// Per-frame update of the player controller's second air state. Once fn_800C5818's checks pass, it may switch to another state. Starts the wire swing (0x1E) when:
// - the actor can swing (fn_8008606C),
// - action 9 is on,
// - motion 0x119 isn't playing,
// - and the energy covers tuning field 30.

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
    char pad0[0x10];
    unsigned int f10;
    char pad14[0x3AC - 0x14];
};

struct Obj : EObj {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(int state); // +0x30
};

extern char lbl_80593BE8[];

extern "C" {
PEnt *Entity_GetActor(void *self);
int fn_804439A4(void *g);
int fn_800CC76C(void *self);
void fn_800C8098(void *self);
int fn_8009AFC8(Ent &actor);
int fn_800C5818(void *self);
int fn_800861EC(void *actor);
void fn_80065AF8(Ent &actor, int a, int b);
void fn_800BDFFC(void *self);
void fn_800BE740(void *self);
void fn_800C7C8C(void *self, float f, int a);
void fn_800C7BEC(void *self);
int fn_800BEAC0(void *self, int v);
void fn_80061CFC(void *actor);
int fn_800CC2E0(void *self);
int fn_800C4D70(void *self, int a, float f, int b);
int fn_800CC0BC(void *self, int id);
int fn_800CF584(void *self, Vector *v);
void fn_800CF7E8(void *self, Vector *v, int mode);
int fn_800CDA20(void *self);
Ent *fn_800CD9B0(void *self);
int fn_800B0CC0(void *c);
void *fn_800B1478(void *c);
int fn_800A4130(void *p);
int fn_800DDCB4(void *self, int a, int b);
void fn_800F8B90(void *self);
int fn_800E07A4(void *self, int v);
int fn_800CC8BC(void *self);
int fn_8008606C(void *actor);
float fn_800B1884(Ent &actor, int id);
int fn_80084B68(void *actor, float f);
int fn_800E2970(void *self, int v);
int fn_800CBF20(void *self);
int fn_800CC148(void *self, int id);
int fn_800D2CF8(void *self);
int fn_800D01A4(void *self);
void fn_800C05BC(void *self);
int fn_8008612C(void *actor);
int fn_800D14F0(void *self);
}

extern "C" void fn_800C5A84(register Obj *self)
{
    if (fn_804439A4(lbl_80593BE8))
        return;
    fn_800C7BEC(self);
    if (fn_800CC76C(self))
        fn_800C8098(self);
    if (!fn_800C5818(self))
        return;
    if (fn_800CBF20(self) && fn_800CC148(self, 9) && fn_800D2CF8(self)) {
        if (fn_800861EC(Entity_GetActor(self)))
            self->s5(0x25);
        else
            self->s5(0x17);
        return;
    }
    if (fn_800CDA20(self) && fn_800CD9B0(self) && fn_800B0CC0(fn_800CD9B0(self))) {
        if (fn_800CC0BC(self, 2) && fn_800A4130(fn_800B1478(fn_800CD9B0(self)))) {
            fn_800DDCB4(self, 0xF0, 0);
            return;
        }
        if (fn_800CC0BC(self, 1) || fn_800CC0BC(self, 6)) {
            fn_800F8B90(self);
            return;
        }
        return;
    }
    if (fn_8008606C(Entity_GetActor(self)) && fn_800CC0BC(self, 9) && fn_8009AFC8(*Entity_GetActor(self)) != 0x119
        && fn_80084B68(Entity_GetActor(self), fn_800B1884(*Entity_GetActor(self), 0x1E))) {
        self->s5(0x1E);
        return;
    }
    if (fn_800CC0BC(self, 2)) {
        self->f10 |= 0x40;
        fn_800E2970(self, 0);
        fn_80065AF8(*Entity_GetActor(self), 1, 1);
        return;
    }
    if (fn_800D01A4(self)) {
        fn_800BEAC0(self, 1);
        fn_800C05BC(self);
        self->s5(8);
        return;
    }
    if (fn_800CC148(self, 8) && fn_8008612C(Entity_GetActor(self))) {
        switch (fn_800D14F0(self)) {
        case 1:
            self->s5(0x19);
            return;
            break;
        case 2:
            self->s5(0x1A);
            return;
            break;
        case 0:
        default:
            break;
        }
    }
}
