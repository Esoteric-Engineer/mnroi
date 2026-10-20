// Virtual method on a slot-owning object: runs virtual slot 35 unless flag 0x10000 is set, then returns 1 after a round reset (fn_80092550) or after fn_8005736C / fn_801AA328.

struct Obj {
    char pad0[0x18];
    unsigned flags; // +0x18
    char pad1C[0x390];
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
};

struct State {
    char pad[0x75C];
};

extern State lbl_80552110; // the game-state object G
extern char lbl_80593BE8[];
extern int lbl_8066B820;

inline int sn_return_decl(int a) { return a; }

extern "C" {
int fn_8042EFF8(void *g);
void *Entity_GetActor(void *self);
int fn_80085EEC(void *actor);
int fn_80432844(State *g);
int fn_80432870(State *g);
void fn_80092550(State *g, int unused);
int fn_80435878(State *g);
void *fn_800CDD30(void *self);
int fn_80432708(void *x);
void fn_8005736C(int a);
void fn_801AA328();

int fn_800BA4D8(register Obj *self)
{
    if ((self->flags & 0x10000) == 0) {
        self->s35();
    }
    if ((unsigned int)fn_8042EFF8(lbl_80593BE8) < (unsigned int)lbl_8066B820) {
        return 0;
    }
    if (fn_80085EEC(Entity_GetActor(self)) != 0) {
        if (fn_80432844(&lbl_80552110) != 0 || fn_80432870(&lbl_80552110) != 0) {
            fn_80092550(&lbl_80552110, 0);
            return 1;
        }
    }
    if (fn_80435878(&lbl_80552110) == 0 && fn_80432708(fn_800CDD30(self)) != 0) {
        fn_8005736C(0);
        fn_801AA328();
        return 1;
    }
    return 0;
}
}
