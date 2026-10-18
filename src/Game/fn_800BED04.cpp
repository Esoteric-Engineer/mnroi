// Starts or stops the PLAYER effect handles (tuning fields 0x62, 0x63) and clips 0x1B/0x1C/0x1D as the entity enters or leaves a state; docs/versus.md row 20.

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
    char pad0[0x18];
    unsigned int f18;
    char pad1C[0x390 - 0x1C];
    Handle *h; // +0x390
    char pad394[0x3AC - 0x394];
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5(int mode); // vtable +0x30
};

extern char lbl_80572130[];

extern "C" {
PEnt *Entity_GetActor(void *self);
Target *Entity_GetActorT(void *self) __asm__("Entity_GetActor");
int fn_800CDA20(void *self);
void *fn_800CD9B0(void *self);
void *fn_800B1478(void *c);
int fn_800A4130(void *p);
int fn_8009AFC8(Ent &actor);
int fn_8009B04C(Ent &actor);
void fn_800BEB28(void *self);
void fn_800BEC14(void *self);
int fn_800CCA88(void *self);
int fn_800ACD20(Ent &actor, int id);
Handle *fn_80393D0C(Ent &actor, int id, int a, int b);
void fn_800CD55C(void *self, int v);
int fn_800B13D8(Ent &actor);
void *fn_80114950(int a, int id);
int fn_800CC60C(void *self);
void *fn_80085980(void *actor);
int fn_80446E8C(void *p);
int fn_80086B1C(void *actor);
int fn_800CC6DC(void *self);
void fn_8009DF60(void *actor, int v);
void fn_80066604(Ent &actor);
int fn_80097CE8(Ent &actor, int a, int mode, float speed, void *set, float blend, float f);
void fn_800CD7A8(void *self);
void fn_800BD2D0(void *self, int handle);
void fn_800BD3A8(void *self, int handle);
void *fn_800CE5B0(void *self);
int fn_8008582C(void *actor);
int fn_8043B31C(void *p);
void fn_80428EEC(void *p, int v);
void fn_800BE9AC(void *actor, int v);
void fn_8001C258(void *actor, int enable);
Handle *fn_80393B28(Ent &actor, Handle *h);
void fn_80393798(Ent &actor, int id);
void fn_800C05BC(void *self);
}

extern "C" int fn_800BED04(register Obj *self, int a, int b)
{
    int ret = 0;
    if (fn_800CDA20(self)) {
        if (fn_800A4130(fn_800B1478(fn_800CD9B0(self))))
            a = 0;
    }
    if (a && fn_8009AFC8(*Entity_GetActor(self)) == 0x1D && !fn_8009B04C(*Entity_GetActor(self))) {
        if (!(self->f18 & 0x40000000))
            fn_800BEB28(self);
    } else if (self->f18 & 0x40000000) {
        fn_800BEC14(self);
    }
    if (a && !fn_800CCA88(self)) {
        self->h = fn_80393D0C(*Entity_GetActor(self), fn_800ACD20(*Entity_GetActor(self), 0x62), 0xFF, 0xFF);
        fn_80393D0C(*Entity_GetActor(self), fn_800ACD20(*Entity_GetActor(self), 0x63), 0xFF, 0xFF);
        if (self->h)
            self->h->s56();
        fn_800CD55C(self, 1);
        fn_80114950(fn_800B13D8(*Entity_GetActor(self)), 0x37);
        int start = b;
        if (fn_800CC60C(self) && !fn_80446E8C(fn_80085980(Entity_GetActor(self))))
            start = 1;
        int h;
        if (!start && a && !fn_800CD9B0(self) && fn_80086B1C(Entity_GetActor(self))
            && (fn_800CC6DC(self) == 2 || fn_800CC6DC(self) == 3 || fn_800CC6DC(self) == 4)) {
            if (Entity_GetActorT(self)->s57(0.15f)) {
                self->s5(2);
                fn_8009DF60(Entity_GetActor(self), 0);
                fn_80066604(*Entity_GetActor(self));
                h = fn_80097CE8(*Entity_GetActor(self), 0x1B, 0, 30.0f, 0, 7.5f, -1.0f);
                if (h > 0) {
                    fn_800CD7A8(self);
                    fn_800BD2D0(self, h);
                    fn_800BD3A8(self, h);
                }
                fn_80097CE8(*Entity_GetActor(self), 0x1D, 1, 30.0f, 0, 7.5f, -1.0f);
                ret = 1;
                goto done;
            }
        }
        if (fn_800CC6DC(self) == 2 && !fn_800CD9B0(self)) {
            h = fn_80097CE8(*Entity_GetActor(self), 0x1B, 0, 30.0f, 0, 7.5f, -1.0f);
            if (h > 0)
                fn_800BD2D0(self, h);
            fn_80097CE8(*Entity_GetActor(self), 0x1D, 1, 30.0f, 0, 7.5f, -1.0f);
        } else if (fn_80086B1C(Entity_GetActor(self)) && fn_800CE5B0(self) && !fn_8008582C(Entity_GetActor(self))) {
            fn_80428EEC(lbl_80572130, fn_8043B31C(fn_800CE5B0(self)));
        }
    done:
        fn_800BE9AC(Entity_GetActor(self), 1);
        fn_8001C258(Entity_GetActor(self), 1);
    } else if (!a && fn_800CCA88(self)) {
        self->h = fn_80393B28(*Entity_GetActor(self), self->h);
        if (self->h)
            self->h->s54();
        fn_80393798(*Entity_GetActor(self), fn_800ACD20(*Entity_GetActor(self), 0x63));
        fn_800CD55C(self, 0);
        int h;
        if (fn_800CC6DC(self) == 2 && !fn_800CD9B0(self)) {
            h = fn_80097CE8(*Entity_GetActor(self), 0x1C, 0, 30.0f, 0, 7.5f, -1.0f);
            if (h > 0)
                fn_800BD2D0(self, h);
            fn_80097CE8(*Entity_GetActor(self), 4, 1, 30.0f, 0, 7.5f, -1.0f);
        }
        fn_800BE9AC(Entity_GetActor(self), 0);
        fn_8001C258(Entity_GetActor(self), 0);
    }
    fn_800C05BC(self);
    return ret;
}
