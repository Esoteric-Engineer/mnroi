// Builds a frame's input flags from the pad, the button word and the target handle; reads GLOBALS 0x50.
// Float pool at 0x80485FB8 (extern_pool).

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

struct Actor;

struct Obj {
    char pad0[0xB0];
    Vector vB0; // +0xB0
    Vector vC0; // +0xC0
    char padD0[0x100 - 0xD0];
    Vector v100; // +0x100
    int f110; // +0x110
    char pad114[0x150 - 0x114];
    Vector v150; // +0x150
    Vector v160; // +0x160
    char pad170[0x1B0 - 0x170];
    unsigned int u1B0; // +0x1B0
    char pad1B4[0x1C8 - 0x1B4];
    unsigned int u1C8; // +0x1C8
    char pad1CC[0x1F4 - 0x1CC];
    Actor *p1F4; // +0x1F4
    char pad1F8[0x1FC - 0x1F8];
    int h1FC; // +0x1FC
    Vector v200; // +0x200
};

extern "C" {
float fn_8043489C(int a, int b);
Vector *fn_800B1750(Actor &actor);
float fn_8042EBF4(Vector *a, Vector *b);
void fn_8042DC84(Vector *dst, Vector *src);
unsigned int fn_8042E96C(char *g);
unsigned int fn_8042EFF8(char *g);
Actor *fn_800ACFA8(int handle);
int fn_800B1138(Actor *actor);
Vector *fn_800B1724(Actor &actor);
int fn_800B0C58(Actor *actor);
void *fn_800B14A0(Actor *actor);
void *fn_80132F00(void *p);
int fn_80148024(void *p);
int fn_80433D70(void *record, int id, int slot);
extern void *lbl_8066C6C8;  // the GLOBALS record
extern char lbl_80593BE8[]; // the globals object of Game/fn_80443908.cpp
extern int lbl_8066B598;
}

#define ABS(x) ((x) < 0.0f ? -(x) : (x))

extern "C" unsigned int fn_80034894(register Obj *self, unsigned int a, unsigned int *b)
{
    unsigned int flags = 0;
    if (a & 0x40000)
        flags |= 0x80;
    if (ABS(fn_8043489C(1, 0)) > 0.1f || ABS(fn_8043489C(1, 1)) > 0.1f || (a & 0x4000)) {
        flags |= 0x10;
        self->f110 = 0;
        *b = *b & ~1;
    } else if (self->f110 == 0) {
        self->f110 = flags & 0x80;
    }
    if (a & 0x20)
        flags |= 0x200;
    if (fn_8042EBF4(&self->v100, fn_800B1750(*self->p1F4)) < 0.9f)
        flags |= 0x100;
    if (fn_8042E96C(lbl_80593BE8) > self->u1B0) {
        fn_8042DC84(&self->v100, fn_800B1750(*self->p1F4));
        self->u1B0 = fn_8042E96C(lbl_80593BE8) + 50;
    }
    if (*b & 0x2000) {
        flags |= 0x2000;
        if (*b & 0x4000)
            flags |= 0x4000;
        if (*b & 0x8000)
            flags |= 0x8000;
    }
    Actor *target = fn_800ACFA8(self->h1FC);
    if (target == 0) {
        target = fn_800ACFA8(lbl_8066B598);
        if (target != 0 && !fn_800B1138(target))
            self->h1FC = lbl_8066B598;
        else
            target = 0;
    }
    if (target)
        fn_8042DC84(&self->v200, fn_800B1724(*target));
    else
        self->h1FC = 0;
    if ((*b & 0x800000) && self->f110)
        flags |= 0x800000;
    if (fn_800B0C58(self->p1F4)) {
        void *t = fn_80132F00(fn_800B14A0(self->p1F4));
        if (t && fn_80148024(t)) {
            flags |= 0x1000000;
            self->u1C8 = fn_8042EFF8(lbl_80593BE8) + fn_80433D70(lbl_8066C6C8, 0x50, 0);
        } else if ((*b & 0x1000000) && fn_8042EFF8(lbl_80593BE8) < self->u1C8) {
            flags |= 0x1000000;
        }
    }
    fn_8042DC84(&self->v150, &self->vB0);
    fn_8042DC84(&self->v160, &self->vC0);
    return flags;
}
