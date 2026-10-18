// Picks the nearest valid target in range (GLOBALS 3.0 radius, PLAYER 0xF4 facing floor); docs/versus.md row 20.

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

extern "C" {
PEnt *Entity_GetActor(void *self);
void fn_8004E9C8(Query *q);
void fn_80434C88(Query *q);
void fn_80434CDC(Query *q, int bit);
void fn_80434D18(Query *q, void *ignore);
void fn_8004E4B4(Query *q, void *pos, float r, void *world);
void *fn_800B1CC8(Ent &actor);
void *fn_800B1724(Ent &actor);
Vector *fn_800B1750(Ent &actor);
float fn_800B1884(Ent &actor, int id);
int fn_800CDA20(void *self);
void fn_800CE158(void *self, int a);
void *fn_80434C2CT(Slot *s) __asm__("fn_80434C2C");
int fn_800B0E54(void *c);
void *fn_800B1590(void *c);
int fn_800F5CC8(void *self, void *c, int a);
int fn_800B0CC0(void *c);
void *fn_800B1478(void *c);
int fn_8008572C(void *a, void *b);
int fn_8008582C(void *actor);
void *fn_800B24AC(void *c);
void *fn_80318E84(void *p);
void fn_80434BA4(Vector *out, void *v);
void fn_8042DC84(Vector *dst, void *src);
void fn_80429038(Vector *out, Vector *a, void *b);
void fn_8042F76C(Vector *v);
float fn_8042EBF4(Vector *a, Vector *b);
}

extern "C" void *fn_800C94C8(register void *self)
{
    register void *tmp;
    Query q;
    void *cand;
    void *best;
    fn_8004E9C8(&q);
    if (!Entity_GetActor(self) || !fn_800B1CC8(*Entity_GetActor(self)) || fn_800CDA20(self))
        return 0;
    fn_800CE158(self, 0);
    fn_80434C88(&q);
    fn_80434CDC(&q, 2);
    fn_80434CDC(&q, 8);
    fn_80434D18(&q, Entity_GetActor(self));
    fn_8004E4B4(&q, fn_800B1724(*Entity_GetActor(self)), 3.0f, fn_800B1CC8(*Entity_GetActor(self)));
    best = 0;
    Vector v0;
    float bestScore;
    float score;
    float f;
    unsigned int i;
    bestScore = 99999.9f;
    for (i = 0; i < q.count; i++) {
        tmp = fn_80434C2CT(&q.slot[i]);
        cand = tmp;
        if (!cand || !fn_800B0E54(cand) || !fn_800F5CC8(self, fn_800B1590(cand), 0))
            continue;
        score = q.slot[i].dist;
        if (fn_800B0CC0(cand) && !fn_8008572C(Entity_GetActor(self), fn_800B1478(cand))) {
            if (q.slot[i].dist > 1.0f || fn_8008582C(Entity_GetActor(self)))
                continue;
            score = score + 200.0f;
        }
        Vector v2;
        if (fn_800B24AC(cand))
            fn_80434BA4(&v2, fn_80318E84(fn_800B24AC(cand)));
        else
            fn_8042DC84(&v2, fn_800B1724(*(Ent *)cand));
        Vector v3;
        fn_80429038(&v3, &v2, fn_800B1724(*Entity_GetActor(self)));
        v3.z = 0.0f;
        fn_8042F76C(&v3);
        f = fn_8042EBF4(&v3, fn_800B1750(*Entity_GetActor(self)));
        if (f < fn_800B1884(*Entity_GetActor(self), 0xF4))
            continue;
        score = score - f * 100.0f;
        if (score < bestScore) {
            bestScore = score;
            best = cand;
        }
    }
    return best;
}
