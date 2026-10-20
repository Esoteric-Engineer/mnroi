// Plays clip 0xE0-0xE2 on the actor against `other` when within 2.0 or in state 0x22 (GLOBALS 7).
// Float pool 0x8048DAB4-0x8048DAC8 via extern_pool.

struct Ent {
    int pad;
};

struct PEnt : Ent { // matching_notes 44
    int x;
};

struct Target {
    char pad0[0x198];
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
    virtual int s57(float a); // vtable +0x1D0
};

struct Obj {
    char pad0[0x3AC];
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5(int a); // vtable +0x30
};

extern void *lbl_8066C6C8; // the GLOBALS record
extern char lbl_8064AA80[];

extern "C" {
PEnt *Entity_GetActor(void *self);
Target *Entity_GetActorT(void *self) __asm__("Entity_GetActor");
void *fn_800B1724(Ent &actor);
float fn_804290F8(void *a, void *b);
int fn_800CC60C(void *self);
void *fn_80085980(void *actor);
int fn_804421B8(void *o, unsigned int bit);
int fn_800CCF60(void *self);
int fn_800CC6DC(void *e);
int fn_800B0CC0(Ent *a);
int fn_8008572C(void *a, void *b);
int fn_8008615C(void *actor);
int fn_800CCA88(void *self);
int fn_800A4130(void *a);
int fn_8009AC94(void *self);
int fn_800B13D8(Ent &actor);
float fn_80433D20(void *record, int id, int slot);
void fn_80086818(void *actor, float v);
void fn_800CD894(void *self, int a, int b);
void fn_800F8190(void *self, void *other);
void fn_80066604(Ent &actor);
int fn_800A43A0(void *c);
int fn_80097CE8(Ent &actor, int a, int mode, float speed, void *set, float blend, float f);
void fn_800BD2D0(void *self, int handle);
void fn_803A0588(char *tbl, int a, int b, void *n1, void *n2, int d, void *e, unsigned char fl);
}

extern "C" int fn_800E5B2C(register Obj *self, Ent *other, int d, void *e, float f, int u1, int u2)
{
    int near = fn_804290F8(fn_800B1724(*other), fn_800B1724(*Entity_GetActor(self))) < 2.0f;
    if ((fn_800CC60C(self) && fn_804421B8(fn_80085980(Entity_GetActor(self)), 7) && near && fn_800CCF60(self))
        || fn_800CC6DC(self) == 0x22) {
        Ent *x = other;
        if (fn_800B0CC0(x)
            && (fn_8008572C(Entity_GetActor(self), x) || (fn_8008615C(Entity_GetActor(self)) && fn_800CCA88(self)))
            && !fn_800A4130(x)) {
            if (fn_8009AC94(x) != fn_800B13D8(*Entity_GetActor(self)))
                fn_80086818(Entity_GetActor(self), fn_80433D20(lbl_8066C6C8, 7, 0));
            fn_800CD894(self, fn_800B13D8(*x), 0);
            fn_800F8190(self, x);
            self->s5(0x13);
            fn_80066604(*x);
            int clip;
            if (!fn_800A43A0(x))
                clip = fn_80097CE8(*Entity_GetActor(self), 0xE1, 0, 30.0f, 0, 7.5f, -1.0f);
            else
                clip = fn_80097CE8(*Entity_GetActor(self), 0xE0, 0, 30.0f, 0, 7.5f, -1.0f);
            if (!Entity_GetActorT(self)->s57(0.15f))
                clip = fn_80097CE8(*Entity_GetActor(self), 0xE2, 0, 30.0f, 0, 7.5f, -1.0f);
            if (clip > 0)
                fn_800BD2D0(self, clip);
            fn_803A0588(lbl_8064AA80, 0, 0, 0, 0, d, e, 0);
            return 1;
        }
    }
    return 0;
}
