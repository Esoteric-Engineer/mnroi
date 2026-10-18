// Fires a projectile (template from PLAYER fields 90+/214+) with its muzzle effect (94+) toward the target; docs/versus.md row 20.

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

struct TObj {
    char d[0x198];
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5(Vector *out, int mode); // vtable +0x30
};

struct Obj {
    char pad0[0x409];
    unsigned char b409; // +0x409
    unsigned char b40a;
    unsigned char b40b;
    unsigned char b40c;
};

struct Mtx {
    char d[0x40];
};

extern Vector lbl_80593DE0;

extern "C" {
PEnt *Entity_GetActor(void *self);
int fn_800ACD20(Ent &actor, int id);
TObj *fn_800FD5FC(int name, int flag);
float fn_800B1884(Ent &actor, int id);
TObj *fn_800E9AF8(void *self, float a, float b, float c, int d, Vector *e);
int fn_800CC60C(void *self);
void *fn_80085980(void *actor);
TObj *fn_80134870(void *a);
int fn_800B0C58(void *actor);
void fn_80393D0C(Ent &actor, int id, int a, int b);
void *fn_8009AD80(Ent &actor);
int fn_800B1668(Ent &c);
int fn_801A5104(void *f, int kind, unsigned short a, void *vec, int e);
int fn_800B1318(Ent &actor);
void *fn_800B1724(Ent &actor);
void fn_8042DC84(void *dst, void *src);
float fn_800B2620(Ent &actor);
void fn_80429090(void *out, void *a, void *b, float s);
void fn_80429038(void *out, void *a, void *b);
float fn_8042EC54(void *v);
void *fn_800B14A0(void *actor);
void *fn_80085928(void *e);
int fn_800CCC28(void *e);
int fn_800CC6DC(void *e);
int fn_8008582C(void *actor);
int fn_80085D3C(void *actor);
void *fn_800B1750(Ent &actor);
void fn_8042F76C(void *v);
void fn_8042D7B0(void *p);
void fn_801BC080(void *m, void *v);
int fn_800B13D8(Ent &actor);
void *fn_800503B8(void *tpl, void *m, void *actor, int a, int b, int c, int d, int e);
void fn_800A1100(void *p, void *target, int a);
void fn_800B9CE8(void *a, int b, void *c, void *d);
int fn_800B24AC(void *self);
void fn_8006683C(Ent &actor, void *p);
int fn_8009ABEC(void *actor);
void fn_8010D050(void *actor, int event, int bank, int a2, int a3, void *target, int a5);
}

extern "C" int fn_800F1644(register Obj *self)
{
    TObj *tpl = 0;
    Vector a;
    Vector b;
    int voice;
    TObj *tgt;
    switch (self->b409) {
    case 4:
    case 5:
        tpl = fn_800FD5FC(fn_800ACD20(*Entity_GetActor(self), self->b409 + 0xD6), 0);
        break;
    default:
        tpl = fn_800FD5FC(fn_800ACD20(*Entity_GetActor(self), self->b409 + 0x5A), 0);
        break;
    }
    if (!tpl)
        return 0;
    tgt = fn_800E9AF8(self, fn_800B1884(*Entity_GetActor(self), 10), fn_800B1884(*Entity_GetActor(self), 9),
                      fn_800B1884(*Entity_GetActor(self), 0x15), 0, 0);
    if (fn_800CC60C(self) && fn_80134870(fn_80085980(Entity_GetActor(self)))
        && fn_800B0C58(fn_80134870(fn_80085980(Entity_GetActor(self)))))
        tgt = fn_80134870(fn_80085980(Entity_GetActor(self)));
    fn_80393D0C(*Entity_GetActor(self), fn_800ACD20(*Entity_GetActor(self), self->b40a + 0x5E), self->b40c,
                self->b40b);
    if (!fn_801A5104(fn_8009AD80(*Entity_GetActor(self)), self->b40c, self->b40b, &b,
                     fn_800B1668(*Entity_GetActor(self)))) {
        if (fn_800B1318(*Entity_GetActor(self)) == 1)
            fn_8042DC84(&b, fn_800B1724(*Entity_GetActor(self)));
        else
            fn_80429090(&b, fn_800B1724(*Entity_GetActor(self)), &lbl_80593DE0,
                        fn_800B2620(*Entity_GetActor(self)) * 0.9f);
    }
    if (tgt) {
        Vector tv;
        float len;
        tgt->s5(&tv, 0);
        fn_80429038(&a, &tv, &b);
        len = fn_8042EC54(&a);
        if (fn_800B0C58(tgt)
            && (fn_800CCC28(fn_80085928(fn_800B14A0(tgt))) || fn_800CC6DC(fn_80085928(fn_800B14A0(tgt))) == 0xD))
            a.z += 0.1f;
        if (fn_8008582C(Entity_GetActor(self)) && !fn_80085D3C(Entity_GetActor(self))) {
            fn_8042DC84(&a, fn_800B1750(*Entity_GetActor(self)));
            a.z -= 0.6f;
            fn_8042F76C(&a);
            tgt = 0;
        }
    } else {
        fn_8042DC84(&a, fn_800B1750(*Entity_GetActor(self)));
        a.z -= 0.6f;
        fn_8042F76C(&a);
    }
    Mtx m;
    fn_8042D7B0(&m);
    fn_801BC080(&m, &a);
    fn_8042DC84((char *)&m + 0x30, &b);
    void *proj = fn_800503B8(tpl, &m, Entity_GetActor(self), fn_800B13D8(*Entity_GetActor(self)), 0, 0, 0, 1);
    if (proj) {
        fn_800A1100(proj, tgt, 0);
        if (tgt && fn_800B0C58(tgt) && fn_80085928(fn_800B14A0(tgt)))
            fn_800B9CE8(fn_80085928(fn_800B14A0(tgt)), 6, proj, Entity_GetActor(self));
        if (fn_800B24AC(proj))
            fn_8006683C(*Entity_GetActor(self), proj);
        voice = fn_8009ABEC(proj);
    } else {
        voice = 0;
    }
    if (voice)
        fn_8010D050(Entity_GetActor(self), 0xC, voice, 500, 0, 0, 0);
    return 1;
}
