// Enters a PLAYER state: plays clip 4, then steers by the first facing candidate in range (GLOBALS 0x34, 0x3C; PLAYER 0x19).

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

struct Ent {
    int pad;
};

struct PEnt : Ent { // matching_notes 44
    int x;
};

struct Slot {
    char d[0x30];
};

struct Query {
    char pad0[0x40];
    Slot slot[0x80]; // +0x40
    unsigned int count; // +0x1840
    int pad1844;
    unsigned int mask; // +0x1848
    int pad184c;
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
    char pad0[5];
    char b5;
    char pad6[0x10 - 6];
    unsigned int f10;
    char pad14[4];
    unsigned int f18;
    char pad1C[0x3F8 - 0x1C];
    float f3F8;
    char pad3FC[0x4E8 - 0x3FC];
    int f4E8;
};

extern void *lbl_8066C6C8; // the GLOBALS record

extern "C" {
PEnt *Entity_GetActor(void *self);
Target *Entity_GetActorT(void *self) __asm__("Entity_GetActor");
int fn_80097CE8(Ent &actor, int a, int mode, float speed, void *set, float blend, float f);
float fn_800B1884(Ent &actor, int id);
int fn_800CC6DC(void *e);
void fn_8004E9C8(Query *q);
void fn_80434C88(Query *q);
void fn_80434CDC(Query *q, int bit);
void fn_80434CB0(Query *q);
void fn_80447490(Query *q);
void fn_804474BC(Query *q, int on);
void fn_80434D18(Query *q, void *ignore);
void *fn_800B1724(Ent &actor);
void fn_8004E4B4(Query *q, void *pos, float r, void *world);
float fn_80433D20(void *record, int id, int slot);
void *fn_800B1CC8(Ent &actor);
Slot *fn_8004E334(Query *q);
void *fn_80434C2CT(Slot *s) __asm__("fn_80434C2C");
int fn_800B0CC0(void *c);
PEnt *fn_800B1478(void *c);
int fn_800B1258(Ent &c);
void fn_80429038(Vector *out, void *a, void *b);
void fn_8042F76C(Vector *v);
Vector *fn_800B1750(Ent &actor);
float fn_8042EBF4(Vector *a, Vector *b);
void fn_80433FFC(Vector *v);
void fn_8005AB90(Ent &actor, Vector *v);
void fn_80065AF8(Ent &actor, int a, int b);
void fn_8007DE08(void *actor);
}

extern "C" int fn_800ED448(register Obj *self, int unused)
{
    self->f18 &= ~0x4000;
    self->f18 &= ~0x2000000;
    self->f18 &= ~0x4000000;
    self->b5 = 2;
    fn_80097CE8(*Entity_GetActor(self), 4, 1, 30.0f, 0, 7.5f, -1.0f);
    self->f10 &= 0x70;
    self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x19);
    self->f4E8 = 0;
    if (Entity_GetActorT(self)->s57(0.15f) && fn_800CC6DC(self) != 0xD) {
        Query q;
        fn_8004E9C8(&q);
        fn_80434C88(&q);
        fn_80434CDC(&q, 0);
        fn_80434CDC(&q, 7);
        fn_80434CDC(&q, 2);
        fn_80434CB0(&q);
        fn_80447490(&q);
        fn_804474BC(&q, 1);
        fn_80434D18(&q, Entity_GetActor(self));
        fn_8004E4B4(&q, fn_800B1724(*Entity_GetActor(self)), fn_80433D20(lbl_8066C6C8, 0x34, 0), fn_800B1CC8(*Entity_GetActor(self)));
        unsigned int i;
        for (i = 0; i < q.count; i++) {
            Vector v;
            void *cand = fn_80434C2CT(fn_8004E334(&q));
            if (!cand)
                continue;
            if (fn_800B0CC0(cand) && !fn_800B1258(*fn_800B1478(cand)))
                continue;
            fn_80429038(&v, fn_800B1724(*Entity_GetActor(self)), fn_800B1724(*(Ent *)cand));
            fn_8042F76C(&v);
            if (fn_8042EBF4(&v, fn_800B1750(*Entity_GetActor(self))) < fn_80433D20(lbl_8066C6C8, 0x3C, 0))
                continue;
            fn_80433FFC(&v);
            fn_8005AB90(*Entity_GetActor(self), &v);
            break;
        }
        goto done;
    done:;
    }
    fn_80065AF8(*Entity_GetActor(self), 0, 0);
    fn_8007DE08(Entity_GetActor(self));
    return 1;
}
