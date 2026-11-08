// Flying and wall-run states' event handler.

struct Clip;

struct Channel {
    char pad0[0x1C];
    Clip *clip;            // +0x1C
};

struct Ent {
    int pad;
};

struct PEnt : Ent {
    int x;
};

struct Handle {
    char d[0xC8];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44();
    virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49();
    virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53(); virtual void s54();
    virtual void s55(); virtual void s56();
};

struct Obj {
    char pad0[0x10];
    unsigned int flags;    // +0x10
    char pad14[0x4];
    unsigned int f18;      // +0x18
    char pad1C[0x3A0 - 0x1C];
    Handle *h3A0;          // +0x3A0
    char pad3A4[0x409 - 0x3A4];
    unsigned char b409;    // +0x409
    unsigned char b40A;    // +0x40A
    unsigned char b40B;    // +0x40B
    unsigned char b40C;    // +0x40C
};

extern "C" {
PEnt *Entity_GetActor(void *self);
void fn_80066604(Ent &actor);
int fn_8009B04C(Ent &actor);
int fn_800CC148(void *self, int id);
int fn_800CC2E0(void *self);
float fn_80199F24(Clip *clip, int tag);
void fn_8019DB24(Channel *ch, float time);
float fn_804442BC(Clip *clip, float frame);
void fn_800BD3A8(void *self, unsigned int ms);
void fn_800BD2D0(void *self, unsigned int ms);
void fn_800F1644(void *self);
int fn_800ACD20(Ent &actor, int id);
Handle *fn_80393D0C(Ent &actor, int id, int a, int b);
void fn_800E8768(void *self, int index);
void fn_800E880C(void *self, int index);
void fn_800CD77C(void *self);

int fn_800D4970(register Obj *self, Channel *ch, int type, int value, int extra)
{
    if ((self->flags & 1) && type == 0x14) {
        self->flags &= ~1;
        fn_80066604(*Entity_GetActor(self));
        return 1;
    }
    switch (type) {
    case 0x10:
        if (fn_8009B04C(*Entity_GetActor(self)) == 0x63) {
            if (fn_800CC148(self, 1) && !fn_800CC2E0(self)) {
                fn_8019DB24(ch, fn_80199F24(ch->clip, 0x11));
                fn_800BD3A8(self, (unsigned int)fn_804442BC(ch->clip, 30.0f));
                fn_800BD2D0(self, (unsigned int)fn_804442BC(ch->clip, 30.0f));
            }
        } else {
            fn_8019DB24(ch, fn_80199F24(ch->clip, 0x11));
        }
        break;
    case 0x4:
        if (fn_8009B04C(*Entity_GetActor(self)) == 0x63) {
            fn_800F1644(self);
            self->h3A0 = fn_80393D0C(*Entity_GetActor(self), fn_800ACD20(*Entity_GetActor(self), 0x65), 0xFF, 0xFF);
            if (self->h3A0)
                self->h3A0->s56();
        }
        break;
    case 0x4E:
        self->b409 = (unsigned int)(value - 1) < 3 ? (unsigned int)(value - 1) : 3;
        break;
    case 0x4F:
        self->b40B = value;
        if (extra)
            self->b40C = extra;
        else
            self->b40C = 0x15;
        break;
    case 0x50:
        self->b40A = (unsigned int)(value - 1) < 3 ? (unsigned int)(value - 1) : 3;
        break;
    case 0x18:
        if (self->f18 & 0x1000)
            fn_800E8768(self, 0);
        else
            fn_800E8768(self, 2);
        break;
    case 0x39:
        if (self->f18 & 0x1000)
            fn_800E8768(self, 1);
        else
            fn_800E8768(self, 3);
        break;
    case 0x19:
        if (self->f18 & 0x1000)
            fn_800E880C(self, 0);
        else
            fn_800E880C(self, 2);
        break;
    case 0x3A:
        if (self->f18 & 0x1000)
            fn_800E880C(self, 1);
        else
            fn_800E880C(self, 3);
        break;
    case 0x12:
        fn_800CD77C(self);
        break;
    default:
        return 0;
    }
    return 1;
}
}
