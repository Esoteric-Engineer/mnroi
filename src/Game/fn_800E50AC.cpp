// fn_800E50AC starts the entity's two PLAYER effect handles (tuning fields 0xCB, 0xCC).
// fn_800E5308 is a PLAYER state update (tuning field 0x26) that scans nearby targets. docs/versus.md row 20.

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

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

struct EObj {
    char pad0[0xC8];
    int fC8; // +0xC8
    char padCC[0x3AC - 0xCC];
};

struct EBase : EObj {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(int mode); // vtable +0x30
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void s35(); virtual void s36();
    virtual int s37(int id, void *pos, int a, float f, int b, int c, int d, int e); // vtable +0x130
};

struct ESub : EBase {
    int pad;
};

struct State : EBase {
    int pad;
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
float fn_800B1884(Ent &actor, int id);
int fn_800861BC(void *actor);
float fn_80426A84(void *g);
int fn_80084A60(void *actor, float f);
int fn_800C388C(void *self, int a, int b, float f, int c);
int fn_800CC148(void *self, int id);
int fn_800CC60C(void *self);
void fn_8009AEC8(Ent &actor, int v);
unsigned int fn_804324EC(void *g);
int fn_8008627C(void *actor);
void fn_8004E9C8(Query *q);
void fn_80434C88(Query *q);
void fn_80434CDC(Query *q, int bit);
void fn_80434D18(Query *q, void *actor);
void *fn_800B1724(Ent &actor);
void *fn_800B1724P(void *p) __asm__("fn_800B1724");
void *fn_800B1CC8(Ent &actor);
void fn_8004E4B4(Query *q, void *pos, float r, void *world);
void *fn_80434C2C(Slot *s);
int fn_800B0C58(void *c);
void *fn_800B14A0(void *c);
int fn_8003119C(void *p);
ESub *fn_80085954(void *p);
PEnt *fn_80085954P(void *p) __asm__("fn_80085954");
EBase *fn_80085954E(void *p) __asm__("fn_80085954");
int fn_800CD21C(void *e);
int fn_800CCC28(void *e);
void fn_800CD4CC(void *e, int v);
int fn_8010CDCC(Ent &actor, int event, void *target, int a3, int a4, int a5, int a6);
void fn_800CD484(void *self, int a);
void *fn_800C9FD0(void *self);
int fn_800B0C1C(void *c);
void *fn_800B14C8(void *c);
int fn_800CCCBC(Ent &e);
void fn_80429038(Vector *out, void *a, void *b);
void fn_8042F76C(Vector *v);
Vector *fn_800B1750(Ent &actor);
float fn_8042EBF4(Vector *a, Vector *b);
void fn_8005A828(Ent &actor, void *p);
}

extern char lbl_80593BE8[];
extern "C" unsigned int lbl_8066C7D8;
extern "C" int lbl_8066F060;

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

extern "C" void fn_800E5308(register State *self)
{
    float scale = fn_800B1884(*Entity_GetActor(self), 0x26);
    if (fn_800861BC(Entity_GetActor(self)))
        scale = 0.0f;
    if (!fn_80084A60(Entity_GetActor(self), fn_80426A84(lbl_80593BE8) * scale)) {
        self->s5(2);
        return;
    }
    if (!fn_800C388C(self, 0, 0, 0.7f, 0)) {
        self->s5(5);
        return;
    }
    int ok;
    ok = fn_800CC148(self, 0) && ((fn_800CC148(self, 7) && !fn_800CC60C(self)) || fn_800CC148(self, 0x17));
    if (fn_800861BC(Entity_GetActor(self)))
        ok = fn_800CC148(self, 0);
    if (!ok) {
        fn_8009AEC8(*Entity_GetActor(self), 0);
        self->s5(2);
        return;
    }
    self->fC8 += fn_804324EC(lbl_80593BE8);
    if (!(lbl_8066C7D8 & 3) && fn_8008627C(Entity_GetActor(self))) {
        Query q;
        void *e;
        unsigned int i;
        ESub *other;
        fn_8004E9C8(&q);
        fn_80434C88(&q);
        fn_80434CDC(&q, 0);
        fn_80434CDC(&q, 7);
        fn_80434CDC(&q, 4);
        fn_80434D18(&q, Entity_GetActor(self));
        fn_8004E4B4(&q, fn_800B1724(*Entity_GetActor(self)), 1.5f, fn_800B1CC8(*Entity_GetActor(self)));
        for (i = 0; i < q.count; i++) {
            e = fn_80434C2C(&q.slot[i]);
            if (fn_800B0C58(e) && fn_8003119C(fn_800B14A0(e)) && fn_80085954(fn_800B14A0(e))) {
                other = fn_80085954(fn_800B14A0(e));
                if (!fn_800CD21C(other)
                    && fn_80085954E(fn_800B14A0(e))->s37(0x6F, fn_800B1724(*Entity_GetActor(self)), 1, 1.0f, 0, 0, 0, 0)
                    && fn_800CCC28(other))
                    fn_800CD4CC(other, 0);
            }
            lbl_8066F060 = 3;
            fn_8010CDCC(*Entity_GetActor(self), 0xE, 0, 0, 100, 0, 0);
        }
    }
    fn_800CD484(self, 1);
    void *t = fn_800C9FD0(self);
    if (t && fn_800B0C1C(t) && !fn_800CCCBC(*fn_80085954P(fn_800B14C8(t)))) {
        Vector v;
        fn_80429038(&v, fn_800B1724P(t), fn_800B1724(*Entity_GetActor(self)));
        v.z = 0.0f;
        fn_8042F76C(&v);
        if (fn_8042EBF4(fn_800B1750(*Entity_GetActor(self)), &v) > 0.0f)
            fn_8005A828(*Entity_GetActor(self), fn_800B1724P(t));
    }
}
