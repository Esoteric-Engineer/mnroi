// Resets the entity's state and reads its PLAYER tuning fields 0x17, 0x18.

struct Ent {
    int pad;
};

struct PEnt : Ent { // matching_notes 44
    int x;
};

struct Obj {
    char pad0[0x10];
    unsigned int f10;
    char pad14[0x3F8 - 0x14];
    float f3F8;
    int f3FC;
    char pad400[0x55C - 0x400];
    int f55C;
};

extern "C" {
PEnt *Entity_GetActor(void *self);
float fn_800B1884(Ent &actor, int id);
void fn_800BEAC0(void *self, int v);
void fn_800C05BC(void *self);
void fn_800CC578(void *self, int a, int b);
void fn_800CC3CC(void *self);
void fn_800CD3AC(void *self, int v);
int fn_800CCA88(void *self);
void fn_800DA254(void *self, int on, unsigned char a, unsigned char b, unsigned char c, unsigned char d);
void *fn_800C9FD0(void *self);
int fn_80095608(void *actor);
int fn_80085D3C(void *actor);
int fn_800B0C58(void *node);
void *fn_800B14A0(void *node);
int fn_800B13D8(Ent &actor);
void fn_8003EE24(int a, int b, int c, int d);
}

extern "C" int fn_800E3720(register Obj *self, int unused)
{
    self->f55C = 0;
    fn_800BEAC0(self, 0);
    fn_800C05BC(self);
    fn_800CC578(self, 0, 0);
    fn_800CC3CC(self);
    self->f10 = 0;
    fn_800CD3AC(self, 1);
    fn_800DA254(self, fn_800CCA88(self), 255, 255, 255, 255);
    if (fn_800CCA88(self)) {
        self->f10 |= 0x80;
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x18);
        self->f3FC = 0x6F;
    } else {
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x17);
        self->f3FC = 0x6C;
    }
    PEnt *a = Entity_GetActor(self);
    void *c = fn_800C9FD0(self);
    if (fn_80095608(a) || fn_80085D3C(a)) {
        if (c && fn_800B0C58(c)) {
            void *d = fn_800B14A0(c);
            if (d && (fn_80085D3C(d) || fn_80095608(d)))
                fn_8003EE24(fn_800B13D8(*Entity_GetActor(self)), fn_800B13D8(*(Ent *)c), 0, 0);
        }
    }
    return 1;
}
