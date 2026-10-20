// fn_800DA884 sets up the hit a motion deals (strength, reaction, energy costs: the PLAYER fields it reads are in tools/nvbtool.py);
// fn_800DBC90 swaps the entity's PLAYER effect handle (tuning fields 0xAF+n) for the one its current animation kind picks.

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
    char pad0[0x10];
    unsigned int f10;
    char pad14[0x394 - 0x14];
    Handle *h; // +0x394
    char pad398[0x3EF - 0x398];
    char b3EF;
    char pad3F0[0x3F4 - 0x3F0];
    unsigned int f3F4; // hit flags
    float f3F8; // hit strength
    int f3FC; // hit reaction
    int f400;
    float f404;
    char b408;
    char pad409[0x414 - 0x409];
    float f414; // energy cost
    float f418;
};

extern "C" {
PEnt *Entity_GetActor(void *self);
char *fn_8009AF80(Ent &actor);
Table *fn_804355C0(void *p);
int fn_800ACD20(Ent &actor, int id);
Handle *fn_80393D0C(Ent &actor, int id, int a, int b);
int fn_800B18EC(Ent &actor, int id);
float fn_800B1884(Ent &actor, int id);
void *fn_800CD9B0(void *self);
int fn_800B0CC0(void *c);
void *fn_800B1478(void *c);
float fn_800A4620(void *p);
int fn_800CC148(void *self, int id);
int fn_80086B6C(void *actor);
int fn_80084A60(void *actor, float f);
int fn_80085D3C(void *actor);
int fn_80095608(Ent &actor);
void fn_800D9538(void *actor, int motion, float strength, unsigned int flags, int reaction);
void fn_800DA254(void *self, int on, unsigned char a, unsigned char b, unsigned char c, unsigned char d);
}

extern "C" void fn_800DA884(register Obj *self, int motion)
{
    int attack = 0;
    self->f400 = 0;
    self->f3F4 = 0x50;
    self->f404 = 1.0f;
    self->b408 = 0;
    self->b3EF = fn_800B18EC(*Entity_GetActor(self), 0xA9);
    self->f414 = 0.0f;
    self->f418 = 0.0f;
    self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x17);
    switch (motion) {
    case 0x2F:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x18);
        self->f3FC = 0x6C;
        self->f400 = 0x28;
        attack = 1;
        break;
    case 0x30:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x18);
        self->f3FC = 0x6F;
        self->f400 = 0x29;
        attack = 1;
        break;
    case 0x31:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x19);
        self->f3FC = 0x6F;
        self->f400 = 0x2A;
        self->f3F4 |= 0x2000;
        attack = 1;
        break;
    case 0x32:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x19);
        self->f3FC = 0x6F;
        self->f3F4 |= 0x2000;
        attack = 1;
        break;
    case 0x35:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x18);
        self->f3FC = 0x76;
        self->f400 = 0x28;
        attack = 1;
        self->f414 = fn_800B1884(*Entity_GetActor(self), 0x24);
        self->f418 = fn_800B1884(*Entity_GetActor(self), 0xBF);
        break;
    case 0x40:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x18);
        self->f3FC = 0x6C;
        attack = 1;
        break;
    case 0x33:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x19);
        self->f3FC = 0x6F;
        self->f400 = 0x28;
        attack = 1;
        break;
    case 0x3B:
        self->f414 = fn_800B1884(*Entity_GetActor(self), 0x23);
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x19);
        self->f3FC = 0x7F;
        attack = 1;
        break;
    case 0x34:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x1A);
        self->f3FC = 0x7E;
        self->f414 = fn_800B1884(*Entity_GetActor(self), 0xBB);
        attack = 1;
        break;
    case 0x36:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x1A);
        self->f3FC = 0x84;
        attack = 1;
        self->f414 = fn_800B1884(*Entity_GetActor(self), 0xE3);
        break;
    case 0xA2:
    case 0xA3:
    case 0xA4:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x19);
        self->f3FC = 0;
        attack = 1;
        break;
    case 0x9F:
    case 0xA0:
    case 0xA1:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x18);
        self->f3FC = 0;
        break;
    case 0xAC:
    case 0xAD:
    case 0xAE:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x17);
        self->f3FC = 0;
        break;
    case 0xB3:
    case 0xB4:
    case 0xB5:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x19);
        self->f3FC = 0;
        attack = 1;
        self->f414 = fn_800B1884(*Entity_GetActor(self), 0xE5);
        break;
    case 0x27:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x17);
        self->f3FC = 0x6C;
        self->f400 = 0x28;
        break;
    case 0x28:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x17);
        self->f3FC = 0x6F;
        self->f400 = 0x29;
        break;
    case 0x29:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x17);
        self->f3FC = 0x7F;
        self->f400 = 0x2A;
        break;
    case 0x2A:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x17);
        self->f3FC = 0x7F;
        break;
    case 0x3E:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x17);
        self->f3FC = 0x6C;
        self->f3F4 |= 0x8;
        break;
    case 0x4F:
    case 0x50:
    case 0x5E:
    case 0x5F:
        self->f3F8 = 0.0f;
        self->f3FC = 0;
        break;
    case 0x37:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x18);
        self->f3FC = 0x6C;
        self->f400 = 0x38;
        break;
    case 0x42:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x19);
        self->f3FC = 0x7F;
        self->f404 = 0.75f;
        self->f3F4 |= 0x8;
        break;
    case 0x39:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x17);
        self->f3FC = 0x7F;
        self->f404 = 0.75f;
        self->f3F4 |= 0x8;
        break;
    case 0x48:
    case 0x4A:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x18);
        self->f3FC = 0x7F;
        self->f404 = 0.75f;
        self->f3F4 |= 0x8;
        break;
    case 0x45:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x1A);
        self->f3FC = 0x7F;
        self->f404 = 1.5f;
        attack = 1;
        self->f3F4 |= 0x8;
        self->f418 = fn_800B1884(*Entity_GetActor(self), 0xBF);
        self->f414 = fn_800B1884(*Entity_GetActor(self), 0xE2);
        self->f3F4 |= 0x2000;
        break;
    case 0x3C:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x18);
        self->f3FC = 0x7F;
        self->f404 = 1.5f;
        attack = 1;
        self->f414 = fn_800B1884(*Entity_GetActor(self), 0xE1);
        break;
    case 0x49:
    case 0x4B:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x19);
        self->f3FC = 0x7F;
        self->f404 = 1.5f;
        attack = 1;
        self->f414 = fn_800B1884(*Entity_GetActor(self), 0xE6);
        break;
    case 0x2D:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x16);
        self->f3FC = 0x75;
        self->f400 = 0x28;
        self->f418 = fn_800B1884(*Entity_GetActor(self), 0xBF);
        break;
    case 0x5C:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x18);
        self->f3FC = 0x72;
        break;
    case 0x5D:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x19);
        self->f3FC = 0x72;
        attack = 1;
        self->f414 = fn_800B1884(*Entity_GetActor(self), 0xE4);
        self->f3F4 |= 0x2000;
        break;
    case 0x38:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x18);
        self->f3FC = 0x80;
        break;
    case 0x2C:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x19);
        self->f3FC = 0x7D;
        break;
    case 0x2E:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x18);
        self->f3FC = 0x72;
        break;
    case 0x2B:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x17);
        self->f3FC = 0x6F;
        self->f400 = 0x28;
        self->f3F4 |= 0x8;
        break;
    case 0x3F:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x18);
        self->f3FC = 0x6F;
        self->f3F4 |= 0x8;
        break;
    case 0xF0:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x18);
        self->f3FC = 0x7F;
        self->f418 = fn_800B1884(*Entity_GetActor(self), 0xBE);
        if (fn_800CD9B0(self) && fn_800B0CC0(fn_800CD9B0(self)))
            self->f3F8 = fn_800A4620(fn_800B1478(fn_800CD9B0(self)));
        break;
    case 0xEC:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x19);
        self->f3FC = 0x7F;
        self->f400 = 0xED;
        self->f418 = fn_800B1884(*Entity_GetActor(self), 0xBE);
        if (fn_800CD9B0(self) && fn_800B0CC0(fn_800CD9B0(self)))
            self->f3F8 = fn_800A4620(fn_800B1478(fn_800CD9B0(self)));
        break;
    case 0xF7:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x19);
        self->f3FC = 0x7F;
        self->f418 = fn_800B1884(*Entity_GetActor(self), 0xBE);
        if (fn_800CD9B0(self) && fn_800B0CC0(fn_800CD9B0(self)))
            self->f3F8 = fn_800A4620(fn_800B1478(fn_800CD9B0(self)));
        break;
    case 0xED:
        self->f400 = 0xEC;
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x19);
        self->f3FC = 0x7F;
        self->f418 = fn_800B1884(*Entity_GetActor(self), 0xBE);
        if (fn_800CD9B0(self) && fn_800B0CC0(fn_800CD9B0(self)))
            self->f3F8 = fn_800A4620(fn_800B1478(fn_800CD9B0(self)));
        break;
    case 0xF1:
        self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x18);
        self->f3FC = 0x7E;
        self->f418 = fn_800B1884(*Entity_GetActor(self), 0xBE);
        if (fn_800CD9B0(self) && fn_800B0CC0(fn_800CD9B0(self)))
            self->f3F8 = fn_800A4620(fn_800B1478(fn_800CD9B0(self)));
        break;
    case 0xE3:
        self->f3F8 = 0.0f;
        break;
    case 0x3A:
        break;

    default:
        if (fn_800CC148(self, 7))
            attack = 1;
        break;
    }
    if (attack) {
        self->f10 &= ~0x1000;
        self->f10 |= 0x80;
        if (self->f414 == 0.0f)
            self->f414 = fn_800B1884(*Entity_GetActor(self), 0x1F);
        if (self->f418 == 0.0f)
            self->f418 = fn_800B1884(*Entity_GetActor(self), 0xBD);
        if (fn_80086B6C(Entity_GetActor(self)))
            self->f414 = 0.0f;
        if (self->f3F4 & 8) {
            fn_80084A60(Entity_GetActor(self), self->f414);
            self->f414 = 0.0f;
        }
    } else {
        if (fn_80085D3C(Entity_GetActor(self)) || fn_80095608(*Entity_GetActor(self)))
            self->f3F4 |= 1;
        self->f10 &= ~0x80;
        if (self->f418 == 0.0f)
            self->f418 = fn_800B1884(*Entity_GetActor(self), 0xBC);
    }
    fn_800D9538(Entity_GetActor(self), motion, self->f3F8, self->f3F4, self->f3FC);
    fn_800DA254(self, attack, 0xFF, 0xFF, 0xFF, 0xFF);
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
