// fn_800E89B0 and fn_800E906C pick the best target near the entity: within a radius, ahead of a facing (fn_800E89B0's arguments, fn_800E906C's tuning fields 1, 2, 0xDF, 0xE7), scored on distance and facing.

inline int sn_return_decl(int a) { return a; }

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

struct Target {
    char pad0[0x198];
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5(Vector *out, int a); // vtable +0x30
};

struct TSub : Target {
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

extern "C" {
PEnt *Entity_GetActor(void *self);
TSub *Entity_GetActorT(void *self) __asm__("Entity_GetActor");
void *fn_800C9FD0(void *self);
void fn_8004E9C8(Query *q);
void fn_80434C88(Query *q);
void fn_80434CDC(Query *q, int bit);
void fn_80434CB0(Query *q);
void fn_80447490(Query *q);
void fn_80434D18(Query *q, void *ignore);
void fn_804474BC(Query *q, int on);
void fn_80446A2C(Query *q, int on);
void fn_8004E4B4(Query *q, void *pos, float r, void *world);
int fn_8008582C(void *actor);
float fn_800B1884(Ent &actor, int id);
void *fn_800B1CC8(Ent &actor);
int fn_80434C2CT(Slot *s) __asm__("fn_80434C2C");
int fn_800B0F0C(void *c);
void *fn_800CD9F4(void *self);
int fn_800B13D8(void *c);
void fn_80429038(Vector *out, Vector *a, Vector *b);
float fn_8042EC54(Vector *v);
Vector *fn_800B1750(Ent &actor);
float fn_8042EBF4(Vector *a, Vector *b);
int fn_800B0CC0(void *c);
void *fn_800B1478(void *c);
PEnt *fn_800B1478P(void *c) __asm__("fn_800B1478");
int fn_800B11F8(Ent &e);
int fn_800B1258(void *c);
int fn_80085D3C(void *c);
void fn_8042DC84(Vector *dst, Vector *src);
void *fn_80434C2CV(Slot *s) __asm__("fn_80434C2C");
void *fn_800B14A0(void *c);
int fn_800B0FB8(void *c);
int fn_800B0C58(void *c);
int fn_80085EEC(void *c);
int fn_80085D9C(void *c);
void *fn_80085928(void *c);
int fn_800CCC28(void *c);
void fn_800C98BC(void *self, void *node, int v);
}

extern "C" Target *fn_800E89B0(register void *self, float minDot, float radius, int useOwner, Vector *dir, int all)
{
    void *owner = 0;
    Vector pos;
    Vector fwd;
    Query q;
    Target *cand;
    if (useOwner)
        owner = fn_800C9FD0(self);
    if (dir)
        fn_8042DC84(&fwd, dir);
    else
        fn_8042DC84(&fwd, fn_800B1750(*Entity_GetActor(self)));
    fn_8004E9C8(&q);
    fn_80434C88(&q);
    fn_80434CDC(&q, 0);
    fn_80434CDC(&q, 7);
    if (!all)
        fn_80434CDC(&q, 2);
    fn_80434CB0(&q);
    fn_80447490(&q);
    fn_80434D18(&q, Entity_GetActor(self));
    fn_804474BC(&q, 1);
    if (fn_8008582C(Entity_GetActor(self)))
        fn_80446A2C(&q, 1);
    Entity_GetActorT(self)->s5(&pos, 0);
    fn_8004E4B4(&q, &pos, radius, fn_800B1CC8(*Entity_GetActor(self)));
    Target *best = 0;
    float bestScore = 99999.9f;
    float score;
    Vector v1;
    Vector v2;
    float dot;
    float dist;
    float dz = 0.0f;
    for (unsigned int i = 0; i < q.count; i++) {
        cand = (Target *)(TSub *)fn_80434C2CT(&q.slot[i]);
        if (!cand || !fn_800B0F0C(cand))
            continue;
        if (fn_800CD9F4(self) == (void *)fn_800B13D8(cand))
            continue;
        if (fn_800B0CC0(cand) && fn_800B11F8(*fn_800B1478P(cand)))
            continue;
        cand->s5(&v2, 0);
        fn_80429038(&v1, &v2, &pos);
        dz = v1.z < 0.0f ? -v1.z : v1.z;
        v1.z = 0.0f;
        if (dz > 10.0f)
            continue;
        dist = fn_8042EC54(&v1) * 0.2f;
        dot = fn_8042EBF4(&fwd, &v1);
        if (dot < minDot)
            continue;
        score = dist * 10.0f;
        score = score - dot * 100.0f;
        if (dz > 2.0f)
            score = score + 30.0f;
        if ((void *)cand == owner) {
            if (fn_800B0C58(cand) && !fn_80085D3C(fn_800B14A0(cand)))
                score = score - 10.0f;
            else
                score = score - 20.0f;
        }
        void *node;
        if (fn_800B0CC0(fn_80434C2CV(&q.slot[i]))) {
            node = fn_800B1478(fn_80434C2CV(&q.slot[i]));
            if (fn_8008582C(Entity_GetActor(self)) || !fn_800B1258(node))
                continue;
            if (!fn_800B0FB8(node) && (dot < 0.8f || dist > 1.0f)) {
                score = score + 200.0f;
            } else {
            }
        } else {
            node = (Target *)(TSub *)fn_80434C2CT(&q.slot[i]);
            if (!fn_800B0C58(node) || fn_80085EEC(node) || fn_80085D9C(node))
                continue;
            if (fn_8008582C(node) && fn_800CCC28(fn_80085928(node)))
                score = score + 10.0f;
        }
        if (score < bestScore) {
            best = cand;
            bestScore = score;
        }
    }
    fn_800C98BC(self, best, 0);
    return best;
}

extern "C" void *fn_800E906C(register void *self, int a, int b)
{
    void *owner = fn_800C9FD0(self);
    Query q;
    Target *best;
    float bestScore;
    float score;
    fn_8004E9C8(&q);
    best = 0;
    bestScore = 99999.9f;
    Vector v1;
    Target *cand;
    float f188c = 0.0f;
    float f1890;
    float f1894;
    float f1898;
    float f189c;
    Vector v2;
    Vector v3;
    unsigned int i;
    void *node;
    fn_80434C88(&q);
    fn_80434CDC(&q, 0);
    fn_80434CDC(&q, 7);
    fn_80434CDC(&q, 2);
    fn_80434CB0(&q);
    fn_80447490(&q);
    fn_80434D18(&q, Entity_GetActor(self));
    fn_804474BC(&q, 1);
    if (fn_8008582C(Entity_GetActor(self)))
        fn_80446A2C(&q, 1);
    if (b) {
        f1898 = 20.0f;
        f189c = fn_800B1884(*Entity_GetActor(self), 0xE7);
    } else {
        f1898 = fn_800B1884(*Entity_GetActor(self), 1);
        f189c = fn_800B1884(*Entity_GetActor(self), 0xDF);
    }
    Entity_GetActorT(self)->s5(&v3, 0);
    fn_8004E4B4(&q, &v3, fn_800B1884(*Entity_GetActor(self), 2), fn_800B1CC8(*Entity_GetActor(self)));
    for (i = 0; i < q.count; i++) {
        cand = (Target *)(TSub *)fn_80434C2CT(&q.slot[i]);
        if (!cand || !fn_800B0F0C(cand))
            continue;
        if (fn_800CD9F4(self) == (void *)fn_800B13D8(cand))
            continue;
        cand->s5(&v2, 0);
        fn_80429038(&v1, &v2, &v3);
        f188c = v1.z;
        v1.z = 0.0f;
        if (a && f188c > 1.0f)
            continue;
        else if (!a && f188c < -1.0f)
            continue;
        f1890 = fn_8042EC54(&v1) * 0.2f;
        f1894 = fn_8042EBF4(fn_800B1750(*Entity_GetActor(self)), &v1);
        if (f1894 < f189c)
            continue;
        score = f1890 * 10.0f;
        score = score - f1894 * 100.0f;
        if (fn_800B0CC0(cand)) {
            node = fn_800B1478(cand);
            if (fn_8008582C(Entity_GetActor(self)))
                continue;
            if (!fn_800B0FB8(node))
                score = score + 200.0f;
        } else {
            node = fn_800B14A0(cand);
            if (!fn_800B0C58(node) || fn_80085EEC(node) || fn_80085D9C(node))
                continue;
            if (fn_8008582C(node) && fn_800CCC28(fn_80085928(node)))
                score = score + 10.0f;
            if ((void *)cand == owner)
                score = score - 20.0f;
        }
        if (score < bestScore) {
            best = cand;
            bestScore = score;
        }
    }
    fn_800C98BC(self, best, 0);
    return best;
}
