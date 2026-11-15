// Starts the WirePickup state (0x22). Owns .rodata 0x8048D1FC-0x8048D21C.
// With mode set it takes the controller's target (or the lock-on's).
// With mode unset, it picks the first prop within PLAYER field 240 that is reachable, inside the actor's height window (unless Flying) and in front of it (field 239), then enters the state and, when fn_800CCA58 holds, plays WirePullFly (0x116).

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

struct Act : PEnt {
    char pad8[0x380 - 8];
    void *f380;
};

struct Slot {
    char pad0[0x20];
    float dist; // +0x20
    char pad24[0xC];
} __attribute__((aligned(8)));

struct Query {
    char pad0[0x40];
    Slot slot[0x80]; // +0x40
    unsigned int count; // +0x1840
    int pad1844;
    unsigned int mask; // +0x1848
    int pad184c;
};

struct EObj {
    char pad0[0x10];
    unsigned int f10;
    char pad14[0x3AC - 0x14];
};

struct Obj : EObj {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(int state); // +0x30
};

extern "C" {
PEnt *Entity_GetActor(void *self);
Act *Entity_GetActorA(void *self) __asm__("Entity_GetActor");
void fn_8004E9C8(Query *q);
void fn_80434C88(Query *q);
void fn_80434CDC(Query *q, int bit);
void fn_8004E4B4(Query *q, void *pos, float r, void *world);
Slot *fn_8004E334(Query *q);
Ent *fn_80434C2C(Slot *s);
Ent *fn_8008529C(void *actor);
Ent *fn_8008588C(void *actor);
int fn_800CE0FC(void *self);
int fn_800CDA20(void *self);
int fn_800CC60C(void *self);
int fn_800B0CC0(void *c);
int fn_800B0E54(void *c);
void *fn_800B1590(void *c);
int fn_800F5CC8(void *self, void *c, int a);
Ent *fn_800B1478(void *c);
int fn_800A4130(void *p);
int fn_8008572C(void *a, void *b);
int fn_8008615C(void *actor);
Vector *fn_800B1724(Ent &actor);
Vector *fn_800B1750(Ent &actor);
void *fn_800B1CC8(Ent &actor);
float fn_800B1884(Ent &actor, int id);
int fn_800B13D8(Ent &actor);
void fn_8042DC84(Vector *dst, Vector *src);
int fn_8004AC84(Vector *a, Vector *b, int c, int d, int e);
int fn_800CC6DC(void *self);
void *fn_800B1668(void *p);
void fn_80447218(void *a, void *b, int x, int y, int z, float *lo, float *hi);
int fn_800664C0(Ent &actor);
float fn_800B2620(Ent &actor);
void fn_80429038(Vector *out, Vector *a, Vector *b);
void fn_8042F76C(Vector *v);
float fn_8042EBF4(Vector *a, Vector *b);
void fn_800CE158(void *self, void *p);
void fn_800C98BC(void *self, void *node, int v);
int fn_8009B234(void *p);
int fn_80084A60(void *actor, float f);
void fn_8005A828(Ent &actor, Vector *p);
void *AI_GetTargetList(void *p);
void fn_801501AC(void *a, void *b);
int fn_800CCA58(void *self);
int fn_80097CE8(Ent &actor, int a, int mode, float speed, void *set, float blend, float f);
}

extern "C" int fn_800D5FEC(register Obj *self, int mode)
{
    Query q;
    Slot *e;
    Ent *cand;
    fn_8004E9C8(&q);
    Vector v1868;
    Ent *f1878 = 0;
    Ent &me = *fn_8008529C(Entity_GetActor(self));
    if (fn_800CDA20(self))
        return 0;
    if (mode) {
        if (fn_800CC60C(self)) {
            Ent *f1880 = fn_8008588C(Entity_GetActor(self));
            if (!f1880 || !fn_800B0CC0(f1880))
                return 0;
            f1878 = f1880;
        } else {
            f1878 = (Ent *)(PEnt *)fn_800CE0FC(self);
            if (!f1878 || !fn_800B0CC0(f1878))
                return 0;
        }
    } else {
        fn_80434C88(&q);
        fn_80434CDC(&q, 2);
        fn_80434CDC(&q, 8);
        fn_8004E4B4(&q, fn_800B1724(*Entity_GetActor(self)), fn_800B1884(*Entity_GetActor(self), 0xF0), fn_800B1CC8(*Entity_GetActor(self)));
        while ((e = fn_8004E334(&q)) != 0) {
            cand = fn_80434C2C(e);
            if (!cand)
                continue;
            if (!fn_800B0CC0(cand) || !fn_800B0E54(cand) || !fn_800F5CC8(self, fn_800B1590(cand), 1))
                continue;
            if (fn_800A4130(fn_800B1478(cand)))
                continue;
            if (!fn_800F5CC8(self, fn_800B1590(cand), 1))
                continue;
            if (!fn_8008572C(Entity_GetActor(self), fn_800B1478(cand)) && !fn_8008615C(Entity_GetActor(self)))
                continue;
            if (cand == &me)
                continue;
            Vector v1888;
            Vector v1898;
            fn_8042DC84(&v1888, fn_800B1724(*Entity_GetActor(self)));
            fn_8042DC84(&v1898, fn_800B1724(*cand));
            v1888.z += 0.5f;
            v1898.z += 0.2f;
            if (fn_8004AC84(&v1888, &v1898, 0, fn_800B13D8(*cand), 0x55))
                continue;
            if (fn_800CC6DC(self) != 0x17) {
                float f18a8 = 3.4028235e38f;
                float f18ac = -3.4028235e38f;
                fn_80447218((char *)cand + 0x50, fn_800B1668(cand), 0, 0, 0, &f18a8, &f18ac);
                fn_80447218((char *)cand + 0x50, fn_800B1668(cand), 1, 1, 1, &f18a8, &f18ac);
                fn_80447218((char *)cand + 0x50, fn_800B1668(cand), 0, 0, 1, &f18a8, &f18ac);
                fn_80447218((char *)cand + 0x50, fn_800B1668(cand), 0, 1, 1, &f18a8, &f18ac);
                fn_80447218((char *)cand + 0x50, fn_800B1668(cand), 1, 1, 0, &f18a8, &f18ac);
                fn_80447218((char *)cand + 0x50, fn_800B1668(cand), 1, 0, 0, &f18a8, &f18ac);
                fn_80447218((char *)cand + 0x50, fn_800B1668(cand), 1, 0, 1, &f18a8, &f18ac);
                fn_80447218((char *)cand + 0x50, fn_800B1668(cand), 0, 1, 0, &f18a8, &f18ac);
                float f18b0 = (f18ac - f18a8) * 0.3f;
                f18b0 = f18b0 > 0.3f ? f18b0 : 0.3f;
                float f18b4 = f18a8 + f18b0;
                float f18b8 = fn_800664C0(*cand) ? f18a8 - fn_800B2620(*Entity_GetActor(self)) * 0.5f : f18a8 - f18b0;
                float f18bc = fn_800B1724(*Entity_GetActor(self))->z;
                if (!(f18bc >= f18b8 ? f18bc <= f18b4 : 0))
                    continue;
            }
            fn_80429038(&v1868, fn_800B1724(*cand), fn_800B1724(*Entity_GetActor(self)));
            fn_8042F76C(&v1868);
            if (fn_8042EBF4(&v1868, fn_800B1750(*Entity_GetActor(self))) < fn_800B1884(*Entity_GetActor(self), 0xEF))
                continue;
            f1878 = fn_800B1478(cand);
            break;
        }
        if (!f1878)
            return 0;
        fn_800CE158(self, f1878);
        fn_800C98BC(self, f1878, 1);
    }
    if (fn_8009B234(f1878))
        return 0;
    if (!mode) {
        if (!fn_80084A60(Entity_GetActor(self), fn_800B1884(*Entity_GetActor(self), 0xC4)))
            return 0;
    }
    fn_8005A828(*Entity_GetActor(self), fn_800B1724(*f1878));
    if (fn_800CC60C(self))
        fn_801501AC(AI_GetTargetList(Entity_GetActorA(self)->f380), f1878);
    if (fn_800CCA58(self)) {
        self->s5(0x22);
        self->f10 |= 1;
        fn_80097CE8(*Entity_GetActor(self), 0x116, 0, 30.0f, 0, 7.5f, -1.0f);
    } else {
        self->s5(0x22);
    }
    return 1;
}
