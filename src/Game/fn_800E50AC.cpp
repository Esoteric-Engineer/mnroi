// Starts the entity's two PLAYER effect handles (tuning fields 0xCB, 0xCC) after its 0x55 animation; docs/versus.md row 20.

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
    char pad14[0xB0];
    int fC4;
    int fC8;
    char padCC[0x3A4 - 0xCC];
    Handle *h; // +0x3A4
    char pad3A8[0x534 - 0x3A8];
    void *p534;
};

extern "C" {
PEnt *Entity_GetActor(void *self);
int fn_80097CE8(Ent &actor, int a, int mode, float speed, void *set, float blend, float f);
void fn_80066604(Ent &actor);
void fn_8006645C(Ent &actor, int a);
void fn_800BED04(void *self, int a, int b);
void fn_800C05BC(void *self);
int fn_800ACD20(Ent &actor, int id);
Handle *fn_80393D0C(Ent &actor, int id, int a, int b);
int fn_800B13D8(Ent &actor);
void *fn_80114950(int a, int id);
void fn_80114D70(void *p, int v);
}

extern "C" int fn_800E50AC(register Obj *self, int unused)
{
    self->fC8 = 1;
    self->fC4 = 0;
    fn_80097CE8(*Entity_GetActor(self), 0x55, 0, 30.0f, 0, 7.5f, -1.0f);
    fn_80097CE8(*Entity_GetActor(self), 0x55, 1, 30.0f, 0, 7.5f, -1.0f);
    self->flags = 0x80;
    fn_80066604(*Entity_GetActor(self));
    fn_8006645C(*Entity_GetActor(self), 1);
    self->flags |= 0x80;
    fn_800BED04(self, 1, 1);
    fn_800C05BC(self);
    self->h = fn_80393D0C(*Entity_GetActor(self), fn_800ACD20(*Entity_GetActor(self), 0xCB), 0xFF, 0xFF);
    if (self->h)
        self->h->s56();
    self->p534 = fn_80114950(fn_800B13D8(*Entity_GetActor(self)), 0x35);
    fn_80114D70(self->p534, 1000);
    Handle *h = fn_80393D0C(*Entity_GetActor(self), fn_800ACD20(*Entity_GetActor(self), 0xCC), 0xFF, 0xFF);
    if (h)
        h->s56();
    return 1;
}
