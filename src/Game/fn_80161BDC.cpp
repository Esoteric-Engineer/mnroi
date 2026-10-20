// A vtable method that resets one actor's state (guess) and starts a timer of PLAYER field 184.

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
extern "C" int fn_80134870(void *a);
extern "C" char *fn_804420AC(void *a);
extern "C" int fn_800B13D8(int v);
extern "C" void fn_8014B63C(char *p, int a, int b);
extern "C" PlayerEnt *fn_80442080(void *a);
extern "C" int fn_800B18EC(Ent &e, int id);
extern "C" void fn_801513D8(Timer *t, int v);
extern "C" void *fn_80151C8C(Timer *t);
extern "C" void fn_8044243C(void *p, unsigned int bit);

extern "C" int fn_80161BDC(register Machine *self)
{
    fn_80463B20(self);
    fn_804618B0(fn_80462780(self->actor));
    fn_80442130(self->actor, 0x18);
    int t = fn_80134870(self->actor);
    if (t)
        fn_8014B63C(fn_804420AC(self->actor), fn_800B13D8(t), 0);
    fn_801513D8(self->timer, fn_800B18EC(*fn_80442080(self->actor), 0xB8));
    fn_8044243C(fn_80151C8C(self->timer), 1);
    fn_80442130(self->actor, 9);
    fn_80442130(self->actor, 0x1E);
    return 1;
}
