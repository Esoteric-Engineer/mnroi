// A vtable method like fn_80161BDC that sets an actor up and calls fn_800E9AF8 (PLAYER field 185). docs/versus.md row 20.

inline int sn_return_decl(int a) { return a; }

struct Ent {
    int pad;
};
struct PlayerEnt : Ent { // matching_notes 44
    int x;
};

struct Timer {
    char pad0[0x18];
    int len; // +0x18
};

struct Machine {
    void *actor; // +0
    Timer *timer; // +4
};

extern "C" void fn_80463B20(Machine *m);
extern "C" void *fn_80462780(void *a);
extern "C" void fn_804618B0(void *p);
extern "C" void fn_80442130(void *a, unsigned int bit);
extern "C" void fn_8046412C(void *a, unsigned int bit);
extern "C" void *fn_80151C8C(Timer *t);
extern "C" PlayerEnt *fn_80442080(void *a);
extern "C" int fn_800B18EC(Ent &e, int id);
extern "C" void fn_801513D8(Timer *t, int v);
extern "C" void *fn_8044203C(void *a);
extern "C" void *fn_800E9AF8(void *self, float a, float b, float c, int d, void *e);

extern "C" int fn_8016216C(register Machine *self)
{
    fn_80463B20(self);
    fn_804618B0(fn_80462780(self->actor));
    fn_80442130(self->actor, 0x18);
    fn_80442130(self->actor, 0x1A);
    fn_80442130(self->actor, 0x1C);
    fn_80442130(self->actor, 0x28);
    fn_80442130(self->actor, 0x1E);
    fn_80442130(self->actor, 4);
    fn_8046412C(self->actor, 0);
    fn_8046412C(self->actor, 6);
    fn_8046412C(self->actor, 5);
    fn_804618B0(fn_80151C8C(self->timer));
    fn_801513D8(self->timer, fn_800B18EC(*fn_80442080(self->actor), 0xB9));
    fn_800E9AF8(fn_8044203C(self->actor), 15.0f, 4.0f, 0.5f, 0, 0);
    return 1;
}
