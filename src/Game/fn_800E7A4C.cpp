// fn_800E7A4C lands a hit on an entity. With no attacker it only plays the hit sound and effect.
// An attacker whose fn_800B0C1C holds is a multi-slot hit (fn_800E6D54); any other is a plain hit.

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
    char pad[0x80];
};

struct Self : Ent {
    char pad4[0x10 - 0x4];
    unsigned int f10; // +0x10
    char pad14[0x18 - 0x14];
    unsigned int f18; // +0x18
    char pad1C[0xE4 - 0x1C];
    void *fE4; // +0xE4
    char padE8[0x3F4 - 0xE8];
    unsigned int f3F4; // +0x3F4
    float f3F8; // +0x3F8
    int f3FC; // +0x3FC
    char pad400[0x580 - 0x400];
    Slot slots[7]; // +0x580
};

struct Anim {
    char pad0[0x4];
    float f4; // +0x4
};

struct Table;

extern char lbl_8064AA80[];

extern "C" {
void *memset(void *p, int c, unsigned long n);
PEnt *Entity_GetActor(void *self);
void *fn_80085AF0(void *p);
int fn_8043B2C8(void *p);
int fn_80442624(void *slot);
void fn_801AA414(int id, float a, float b, int c, int d);
PEnt *fn_80085954(void *p);
void *fn_800CD9B0(Ent &e);
int fn_800B0F0C(void *c);
void *fn_800B1568(void *c);
int fn_8009ABEC(void *c);
void fn_8010D050(void *actor, int event, int bank, int a2, int a3, void *target, int a5);
void fn_800E673C(void *self, int a, void *b, void *c, void *d, void *e, unsigned char flags, unsigned char f2);
void *fn_800B24AC(void *self);
void *fn_80318E84(void *p);
void fn_80434BA4(Vector *out, void *v);
void fn_8004BBA8(void *rope, Vector *v, void *b, float f, float g, int z, Vector *o1, Vector *o2);
int fn_800B0C1C(void *c);
int fn_804476F0(void *slot);
int fn_800B13D8(void *c);
void fn_804477D8(void *slot, int x);
void *fn_800B14A0(void *c);
void *fn_800B1750(void *c);
void fn_800E6D54(void *self, void *a, void *b, void *c, void *d, unsigned char e, int f, int g, int h);
int fn_800CDA20(void *self);
PEnt *fn_800B1478(void *c);
int fn_800A4130(void *p);
unsigned int fn_8009ABECr(Ent &e) __asm__("fn_8009ABEC");
int fn_800E82C0(void *self, int x);
int fn_800B0CC0(void *c);
int fn_8009B04C(Ent &actor);
int fn_800B0FB8(void *c);
void fn_800A2F94(void *a, void *b, int c, void *d, float f, void *g, void *h, float k, int l);
int fn_800E5F04(void *self, void *other);
int fn_800E6094(void *self, void *other);
void fn_803A0588(char *tbl, int a, int b, void *n1, void *n2, void *d, void *e, unsigned char fl);
void fn_80066DC4(void *a, Vector *v, int b, int c, int d);
void fn_80066F74(void *a, Vector *v, int b);
void fn_8042D80C(Vector *v, void *e);
void fn_800A140C(void *a, void *b, void *c, Vector *d, float f);
int fn_80086344(void *actor);
char *fn_8009AF80(Ent &actor);
Table *fn_804355C0(void *p);
float fn_80199F24(Table *t, int id);
void fn_8019DB24(void *anim, float t);
}

extern "C" void fn_800E7A4C(register Self *self, void *a, void *b, void *c, void *d, unsigned char e, int f, int g, int h, int i)
{
    unsigned char fl = 0;
    self->f18 &= ~0x100000;
    if (!e && fn_80085AF0(Entity_GetActor(self)) && fn_8043B2C8(fn_80085AF0(Entity_GetActor(self)))) {
        float t = (self->f10 & 0x80) ? 0.5f : 0.3f;
        int n = 50;
        if (h == 1)
            fn_801AA414(fn_80442624(fn_80085AF0(self->fE4)), 0.0f, t, n, 2);
        else
            fn_801AA414(fn_80442624(fn_80085AF0(self->fE4)), t, 0.0f, n, 2);
    }
    if (!a) {
        if (!e) {
            if (fn_800CD9B0(*fn_80085954(Entity_GetActor(self)))) {
                if (fn_800B0F0C(fn_800CD9B0(*fn_80085954(Entity_GetActor(self)))))
                    fn_8010D050(Entity_GetActor(self), 9, fn_8009ABEC(fn_800B1568(fn_800CD9B0(*fn_80085954(Entity_GetActor(self))))), 500, i, 0, 0);
                else
                    fn_8010D050(Entity_GetActor(self), 9, 200, 500, i, 0, 0);
            } else
                fn_8010D050(Entity_GetActor(self), 9, 200, 500, i, 0, 0);
        }
        fn_800E673C(self, 1, d, a, b, c, fl, e);
        return;
    }
    Vector v38;
    Vector v48;
    if (fn_800B24AC(a)) {
        Vector v58;
        fn_80434BA4(&v58, fn_80318E84(fn_800B24AC(a)));
        fn_8004BBA8(fn_800B24AC(a), &v58, b, 3.0f, 300.0f, 0, &v38, &v48);
    } else {
        memset(&v38, 0, sizeof(Vector));
        memset(&v48, 0, sizeof(Vector));
    }
    if (fn_800B0C1C(a)) {
        for (int k = 0; k < sizeof(self->slots) / sizeof(Slot); k++) {
            Slot *s = &self->slots[k];
            if (fn_804476F0(s) && k != h)
                fn_804477D8(s, fn_800B13D8(a));
        }
        fn_800E6D54(self, fn_800B14A0(a), b, fn_800B1750(self->fE4), d, e, f, g, h);
        self->f10 |= 0x8000;
        self->f3F4 &= ~0x8;
        return;
    }
    fn_800E673C(self, 1, d, a, b, c, fl, e);
    int id = 200;
    if (fn_800CDA20(self) && fn_800CD9B0(*self) && fn_800A4130(fn_800B1478(fn_800CD9B0(*self))))
        id = fn_8009ABECr(*fn_800B1478(fn_800CD9B0(*self)));
    else if ((g == 0x28 || g == 0x2A) && (h == 1 || h == 2))
        id = 210;
    else if (self->f18 & 0x1000)
        id = 201;
    int x = fn_800E82C0(self, self->f3FC);
    fn_8010D050(Entity_GetActor(self), 9, id, x, i, a, 0);
    if (fn_800B0CC0(a)) {
        PEnt *node = fn_800B1478(a);
        if (fn_8009B04C(*Entity_GetActor(self)) != 0x2B || (fn_8009B04C(*Entity_GetActor(self)) == 0x2B && fn_800B0FB8(node)))
            fn_800A2F94(node, Entity_GetActor(self), 1, d, self->f3F8, b, 0, 0.0f, 0);
        int r = 0;
        if (fn_800E5F04(self, node)) {
            r = fn_800E6094(self, node);
            fn_803A0588(lbl_8064AA80, 0, 0, 0, 0, b, c, 0);
        }
        if (!r) {
            fn_80066DC4(node, &v38, 0, 0, 0);
            fn_80066F74(node, &v48, 0);
        }
        Vector v58;
        fn_8042D80C(&v58, c);
        fn_800A140C(node, Entity_GetActor(self), b, &v58, self->f3F8);
        if (fn_80086344(Entity_GetActor(self))) {
            if (fn_8009B04C(*Entity_GetActor(self)) == 0x33 || fn_8009B04C(*Entity_GetActor(self)) == 0x36) {
                Anim *anim = (Anim *)(fn_8009AF80(*Entity_GetActor(self)) + 0x2C);
                Table *tbl = fn_804355C0(anim);
                if (tbl) {
                    float at = fn_80199F24(tbl, 0x53);
                    if (at >= anim->f4)
                        fn_8019DB24(anim, at);
                }
            }
        }
    }
}
