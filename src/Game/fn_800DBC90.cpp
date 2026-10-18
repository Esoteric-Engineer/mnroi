// Swaps the entity's PLAYER effect handle (tuning fields 0xAF+n) for the one its current animation kind picks; docs/versus.md row 20.

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

struct Entry {
    int pad0;
    unsigned short kind; // +0x4
    char pad6[6];
};

struct Table {
    char pad0[0x3C];
    unsigned int count; // +0x3C
    Entry *entries;     // +0x40
};

struct Obj {
    char pad0[0x394];
    Handle *h; // +0x394
};

extern "C" {
PEnt *Entity_GetActor(void *self);
char *fn_8009AF80(Ent &actor);
Table *fn_804355C0(void *p);
int fn_800ACD20(Ent &actor, int id);
Handle *fn_80393D0C(Ent &actor, int id, int a, int b);
}

extern "C" void fn_800DBC90(register Obj *self, int flag)
{
    Table *t = fn_804355C0(fn_8009AF80(*Entity_GetActor(self)) + 0x2C);
    int idx = 0;
    if (self->h) {
        self->h->s54();
        self->h = 0;
    }
    if (!flag)
        return;
    if (!t)
        return;
    for (unsigned int i = 0; i < t->count; i++) {
        switch (t->entries[i].kind) {
        case 5:
        case 0x18:
            idx = 1;
            break;
        case 0x1F:
        case 0x39:
            idx = 2;
            break;
        case 0x20:
        case 0x3C:
            idx = 3;
            break;
        case 0x21:
        case 0x3E:
            idx = 4;
            break;
        case 0x22:
            idx = 5;
            break;
        case 0x56:
            idx = 7;
            break;
        }
        if (idx)
            break;
    }
    if (idx) {
        self->h = fn_80393D0C(*Entity_GetActor(self), fn_800ACD20(*Entity_GetActor(self), idx + 0xAF), 0xFF, 0xFF);
        if (self->h)
            self->h->s58();
    }
}
