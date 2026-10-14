// Starts or stops the entity's two PLAYER effect handles (tuning fields 0x43, 0x44, 0x4A, 0x4B); docs/versus.md row 20.

struct Ent {
    int pad;
};

struct PEnt : Ent { // the accessor returns the derived class; each conversion saves the pointer
    int x;
};

struct Handle {
    char d[0xC8];
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
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual void s39();
    virtual void s40();
    virtual void s41();
    virtual void s42();
    virtual void s43();
    virtual void s44();
    virtual void s45();
    virtual void s46();
    virtual void s47();
    virtual void s48(int a, int b);
    virtual void s49();
    virtual void s50();
    virtual void s51();
    virtual void s52();
    virtual void s53(int a, int b);
    virtual void s54();
    virtual void s55();
    virtual void s56();
    virtual void s57();
    virtual void s58();
};

struct Obj {
    char pad0[0x10];
    unsigned int flags; // +0x10
    char pad14[0x384];
    Handle *h0; // +0x398
    Handle *h1; // +0x39C
};

extern "C" {
PEnt *Entity_GetActor(void *self);
void fn_800DA134(void *self);
int fn_800ACD20(Ent &actor, int id);
Handle *fn_80393D0C(Ent &actor, int id, int a, int b);
}

extern "C" void fn_800DA254(register Obj *self, int on, unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
    if (on) {
        fn_800DA134(self);
        int p = fn_800ACD20(*Entity_GetActor(self), 0x4A);
        int q = fn_800ACD20(*Entity_GetActor(self), 0x4B);
        self->h0 = fn_80393D0C(*Entity_GetActor(self), p, 0xFF, 0xFF);
        if (self->h0)
            self->h0->s58();
        self->h1 = fn_80393D0C(*Entity_GetActor(self), q, 0xFF, 0xFF);
        if (self->h1)
            self->h1->s58();
        self->flags |= 0x80;
    } else if (!on) {
        fn_800DA134(self);
        int q = fn_800ACD20(*Entity_GetActor(self), 0x43);
        int p = fn_800ACD20(*Entity_GetActor(self), 0x44);
        self->h0 = fn_80393D0C(*Entity_GetActor(self), q, 0xFF, 0xFF);
        if (self->h0)
            self->h0->s58();
        self->h1 = fn_80393D0C(*Entity_GetActor(self), p, 0xFF, 0xFF);
        if (self->h1)
            self->h1->s58();
        self->flags &= ~0x80;
    }
    if (a != 0xFF && b != 0xFF && c != 0xFF && d != 0xFF && self->h1) {
        self->h1->s48(a, b);
        self->h1->s53(c, d);
    }
}
