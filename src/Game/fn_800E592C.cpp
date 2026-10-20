// Clears the entity's effect handles and starts the PLAYER effect handles (tuning fields 0x51, 0xCD).

struct Ent {
    int pad;
};

struct PEnt : Ent { // matching_notes 44
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
    virtual void s48();
    virtual void s49();
    virtual void s50();
    virtual void s51();
    virtual void s52();
    virtual void s53();
    virtual void s54();
    virtual void s55();
    virtual void s56();
};

struct Obj {
    char pad0[0xC8];
    int c8; // +0xC8
    char padCC[0x2D8];
    Handle *h; // +0x3A4
    char pad3A8[0x18C];
    void *s534; // +0x534
};

extern "C" {
PEnt *Entity_GetActor(void *self);
void fn_8006645C(Ent &actor, int a);
Handle *fn_80393B28(Ent &actor, Handle *h);
int fn_800861BC(void *actor);
int fn_800ACD20(Ent &actor, int id);
Handle *fn_80393A60(Ent &actor, int id, int a);
Handle *fn_80393D0C(Ent &actor, int id, int a, int b);
void fn_80114D70(void *p, int a);
void fn_800CD484(void *self, int a);
}

extern "C" int fn_800E592C(register Obj *self, int unused)
{
    fn_8006645C(*Entity_GetActor(self), 0);
    self->c8 = 0;
    self->h = fn_80393B28(*Entity_GetActor(self), self->h);
    if (self->h)
        self->h->s54();
    if (fn_800861BC(Entity_GetActor(self))) {
        Handle *h = fn_80393A60(*Entity_GetActor(self), fn_800ACD20(*Entity_GetActor(self), 0x51), 0);
        if (h)
            h->s54();
    }
    fn_80114D70(self->s534, 0);
    Handle *g = fn_80393D0C(*Entity_GetActor(self), fn_800ACD20(*Entity_GetActor(self), 0xCD), 0xFF, 0xFF);
    if (g)
        g->s56();
    fn_800CD484(self, 0);
    return 1;
}
