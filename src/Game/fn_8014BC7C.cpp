// The Mover's path (Mover+0x20): build to an actor or point, cost, rebuild, update, waypoint arrival and spot steps (docs/ai.md row 11).
// .rodata 0x8049B468-0x8049B520, the whole file's. AI_GetEntity returns Sub * so Ent & arguments convert (matching_notes 50).

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

struct Sub : Ent { // matching_notes 44
    int x;
};

struct Nav {
    unsigned int f0;       // +0x0: spot count
    void *f4[18];          // +0x4: spots
    int f4C;               // +0x4C
    void *f50;             // +0x50: next spot
    unsigned short f54;    // +0x54: flags
    short f56;
    void *f58;             // +0x58
    void *f5C;             // +0x5C: AIObject
    Vector f60;            // +0x60: destination point
    int f70;
    void *f74;             // +0x74: destination's world
    char pad2[0x8];
    Vector f80;            // +0x80: goal point
    void *f90;             // +0x90: current waypoint
    unsigned int f94;      // +0x94: deadline
    int f98;
    unsigned int f9C;      // +0x9C: spot search mask (fn_801370B0)
};

extern "C" {
Sub *AI_GetEntity(void *ai);
Vector *fn_800B1724(Ent &actor);
void *fn_800B1CC8(Ent &actor);
unsigned int fn_801370B0(void *ai);
int fn_80463204(void *ai);
int fn_804623BC(Nav *nav);
int fn_8009BB7C(Nav *nav, Vector *from, Vector *to, void *fromWorld, void *toWorld, unsigned int mask, float range);
void fn_8014BF9C(Nav *nav, void *ai, Ent *dest, void *world, Vector *pos, int b, int a, int c, int d);
int fn_8014C5C4(Nav *nav);
void *fn_80430050(void *level);
void *fn_8004DD38(void *level, Vector *pos);
int fn_800B13D8(Ent *actor);
void fn_8042DC84(Vector *dst, Vector *src);
unsigned int fn_8042EFF8(void *clock);
extern char lbl_8052F060[];
extern char lbl_80593BE8[];
void fn_8014C660(Nav *nav);
}

struct Query {             // the path query fn_8009C004 fills, 0x58 bytes (guess)
    char pad0[0x48];
    float f48;             // +0x48: route length
    char pad1[0xC];
} __attribute__((aligned(8)));

struct Way {
    void *f0;
};

extern "C" {
void *fn_8009C55C(Vector *pos, void *world, unsigned int mask, float r, void *test, void *b, int c);
void fn_804623F0(Query *q);
Vector *fn_80444688(void *spot);
float fn_804290F8(Vector *a, Vector *b);
int fn_8009C004(Query *q, Vector *from, Vector *to, void *fromSpot, void *toSpot, unsigned int mask, float range);
void fn_8014DD30(Nav *nav);
Way *fn_80463714(Nav *nav);
Ent *fn_800ACFA8(int handle);
void *fn_80444904(void *wp, int i);
int fn_8009BD7C(Nav *nav, void *fromSpot, Vector *to, void *toWorld, unsigned int mask, float range);
int fn_804636AC(Nav *nav);
int fn_80463550(void *p);
int fn_80444CD0(void *p);
void *AI_GetMover(void *ai);
void AI_SetMoverSpotKind(void *p, int a);
Sub *AI_GetActor(void *ai);
Vector *fn_8044460C(void *wp);
Vector *fn_800B1750(Ent &actor);
void fn_8042D80C(Vector *dst, Vector *src);
int fn_80444570(void *wp);
int fn_804445D8(void *wp);
int fn_804445A4(void *wp);
int fn_80444D04(void *wp);
unsigned int fn_800CC6DC(Ent &c);
void *fn_80444984(void *wp, int i);
float fn_801BABC8(Vector *p, Vector *a, Vector *b, Vector *out);
int fn_80444E14(void *spot);
int fn_800CCA58(Ent &c);
int fn_800861EC(void *actor);
float fn_800B1884(Ent &actor, int id);
int fn_8015ED50(void *ai, Vector *v);
void fn_80429090(Vector *out, Vector *a, Vector *b, float t);
void fn_8042F984(Vector *out, Vector *a, Vector *b);
extern Vector lbl_80593DE0;
void fn_8042FE08(Vector *v, Vector *dir, float s);
float fn_8015E580(Vector *a, Vector *b);
int fn_801BA090(Vector *a, Vector *b, float r, Vector *c, Vector *d, float *t);
Vector *AI_GetMoverWaypoint(void *p);
double __ieee754_sqrt(double x);
float fn_804341BC(Vector *a, Vector *b);
int fn_80463644(Nav *nav);
void *fn_804635B8(Nav *nav);
int fn_8014D8C0(Nav *nav);
int fn_804636E0(Nav *nav);
void fn_8014D890(Nav *nav);
void fn_80429038(Vector *out, Vector *a, Vector *b);
float fn_8042EC54(Vector *v);
void *fn_800B24AC(Ent &actor);
int fn_8004A9CC(Vector *from, Vector *dir, float len, unsigned int mask, void *hit, void *body, void *world, int c, int d);
void fn_8042F76C(Vector *v);
float fn_8042EBF4(Vector *a, Vector *b);
void AI_SetMoverWaypoint(void *p, Vector *v);
void fn_8014D928(Nav *nav, void *spot);
int fn_8014D744(Nav *nav);
int fn_80463678(Nav *nav);
void fn_804637BC(Nav *nav, Vector *v, void *spot, int a);
int fn_80463770(Nav *nav);
int fn_80463584(Nav *nav);
Vector *fn_80444A04(void *p, int i);
Vector *fn_804635EC(void *spot, int i);
int fn_8014BAD0(void *mover);
int fn_80444D38(void *wp);
void fn_8014D7B0(Nav *nav);
void fn_80461CC0(void *ai, int id);
int fn_801368B8(void *ai);
void *fn_8044734C(void *mover);
int fn_80444D6C(void *spot);
}

extern "C" int fn_8014BC7C(register Nav *self, void *ai, Ent *dest, int a, int b, int c)
{
    int r;

    if (fn_804623BC(self)) {
        if (!fn_8014C5C4(self))
            return 0;
        fn_8014C660(self);
    }
    self->f9C = fn_801370B0(ai);
    self->f4C = fn_80463204(ai);
    r = fn_8009BB7C(self, fn_800B1724(*AI_GetEntity(ai)), fn_800B1724(*dest), fn_800B1CC8(*AI_GetEntity(ai)),
                    fn_800B1CC8(*dest), self->f9C, 5000.0f);
    if (!r)
        return 0;
    fn_8014BF9C(self, ai, dest, fn_800B1CC8(*dest), fn_800B1724(*dest), b, a, c, 0);
    if (r == 1)
        self->f54 |= 0x20;
    return 1;
}

extern "C" int fn_8014BE08(register Nav *self, void *ai, Vector *to, int a, int b, int c)
{
    int r;

    if (fn_804623BC(self)) {
        if (!fn_8014C5C4(self))
            return 0;
        fn_8014C660(self);
    }
    self->f74 = fn_8004DD38(fn_80430050(lbl_8052F060), to);
    if (!self->f74)
        return 0;
    self->f9C = fn_801370B0(ai);
    self->f4C = fn_80463204(ai);
    r = fn_8009BB7C(self, fn_800B1724(*AI_GetEntity(ai)), to, fn_800B1CC8(*AI_GetEntity(ai)), self->f74,
                    self->f9C, 5000.0f);
    if (!r)
        return 0;
    fn_8014BF9C(self, ai, 0, self->f74, to, b, a, c, 0);
    if (r == 1)
        self->f54 |= 0x20;
    return 1;
}

extern "C" void fn_8014BF9C(register Nav *self, void *ai, Ent *dest, void *world, Vector *pos, int b, int a, int c,
                            int d)
{
    self->f5C = ai;
    self->f4C = fn_80463204(self->f5C);
    self->f70 = dest ? fn_800B13D8(dest) : 0;
    if (pos && &self->f60 != pos)
        fn_8042DC84(&self->f60, pos);
    self->f74 = world;
    self->f56 = 0;
    self->f58 = 0;
    self->f94 = fn_8042EFF8(lbl_80593BE8) + 5000;
    self->f54 = 3;
    if (!d) {
    }
    if (b)
        self->f54 |= 8;
    self->f90 = 0;
}

__asm__(".section .rodata\n\t.float 5000\n\t.float 5000\n\t.text"); // two unloaded pool words (matching_notes 23)

extern "C" float fn_8014C0B8(register Nav *self, void *ai, Vector *from, Vector *to)
{
    void *toWorld = fn_8004DD38(fn_80430050(lbl_8052F060), to);
    void *fromWorld = fn_8004DD38(fn_80430050(lbl_8052F060), from);
    void *fromSpot;
    void *toSpot;
    Query q;
    float d;
    int r;

    if (!toWorld || !fromWorld)
        return 0.0f;
    fromSpot = fn_8009C55C(from, fromWorld, fn_801370B0(ai), 20.0f, 0, 0, -1);
    toSpot = fn_8009C55C(to, toWorld, fn_801370B0(ai), 20.0f, 0, 0, -1);
    if (!fromSpot || !toSpot)
        return 0.0f;
    fn_804623F0(&q);
    d = fn_804290F8(from, fn_80444688(fromSpot)) + fn_804290F8(to, fn_80444688(toSpot));
    r = fn_8009C004(&q, from, to, fromSpot, toSpot, fn_801370B0(ai) | 0x2000000, 5000.0f);
    switch (r) {
    case 0:
        return 0.0f;
        break;
    case 1:
        return fn_804290F8(from, to);
        break;
    case 2:
        return d + q.f48;
        fn_8014DD30(self);
        break;
    }
    return 0.0f;
}

extern "C" int fn_8014C31C(register Nav *self)
{
    Way *way = fn_80463714(self);
    int r;
    Ent *dest = self->f70 ? fn_800ACFA8(self->f70) : 0;

    if (dest) {
        if (way)
            r = fn_8009BD7C(self, fn_80444904(way->f0, 0), fn_800B1724(*dest), fn_800B1CC8(*dest),
                            fn_801370B0(self->f5C), 5000.0f);
        else
            r = fn_8009BB7C(self, fn_800B1724(*AI_GetEntity(self->f5C)), fn_800B1724(*dest),
                            fn_800B1CC8(*AI_GetEntity(self->f5C)), fn_800B1CC8(*dest), fn_801370B0(self->f5C), 5000.0f);
    } else {
        if (way)
            r = fn_8009BD7C(self, fn_80444904(way->f0, 0), &self->f60, self->f74, fn_801370B0(self->f5C), 5000.0f);
        else
            r = fn_8009BB7C(self, fn_800B1724(*AI_GetEntity(self->f5C)), &self->f60,
                            fn_800B1CC8(*AI_GetEntity(self->f5C)), self->f74, fn_801370B0(self->f5C), 5000.0f);
    }
    if (!r)
        return 0;
    fn_8014BF9C(self, self->f5C, dest, self->f74, &self->f60, fn_804636AC(self), 0, 0, 1);
    if (r == 1)
        self->f54 |= 0x20;
    return 1;
}

extern "C" int fn_8014C5C4(register Nav *self)
{
    if (!fn_804623BC(self))
        return 1;
    if (self->f58 && (fn_80463550(self->f58) || fn_80444CD0(self->f58)))
        return 0;
    return 1;
}

extern "C" void fn_8014C660(register Nav *self)
{
    if (!fn_804623BC(self))
        return;
    AI_SetMoverSpotKind(AI_GetMover(self->f5C), 0);
    self->f54 &= ~1;
}

extern "C" int fn_8014C6D8(register Nav *self)
{
    int ret = 0;
    void *wp = self->f90;

    if (wp) {
        Vector a;
        fn_8042DC84(&a, fn_8044460C(wp));
        Vector b;
        fn_8042D80C(&b, &a);
        Vector c;
        void *spot = 0;
        Vector d;
        if (self->f98) {
            if (fn_80444570(wp) || fn_804445D8(wp) || fn_804445A4(wp)) {
                switch (fn_800CC6DC(*AI_GetActor(self->f5C))) {
                case 2:
                case 3:
                case 4:
                case 0x25:
                    break;
                default:
                    return 0;
                }
            }
            spot = fn_80444984(wp, 0);
        } else {
            if (fn_80444570(wp) || fn_80444D04(wp) || fn_804445A4(wp)) {
                switch (fn_800CC6DC(*AI_GetActor(self->f5C))) {
                case 2:
                case 3:
                case 4:
                case 0x17:
                case 0x25:
                    break;
                default:
                    return 0;
                }
            }
            fn_8042DC84(&a, fn_800B1750(*AI_GetEntity(self->f5C)));
            fn_8042D80C(&b, &a);
            spot = fn_80444904(wp, 0);
            fn_801BABC8(fn_800B1724(*AI_GetEntity(self->f5C)), fn_80444688(fn_80444904(wp, 0)),
                        fn_80444688(fn_80444984(wp, 0)), &d);
        }
        fn_8042DC84(&c, fn_80444688(spot));
        int flag = 0;
        if (!fn_80444E14(spot) && fn_800CCA58(*AI_GetActor(self->f5C))) {
            flag = 1;
        } else if (fn_800861EC(AI_GetEntity(self->f5C))) {
            if (fn_800B1724(*AI_GetEntity(self->f5C))->z >= c.z - 1.0f) {
                if (fn_800B1724(*AI_GetEntity(self->f5C))->z < fn_800B1884(*AI_GetEntity(self->f5C), 214) + c.z)
                    flag = 1;
            }
        } else if (fn_8015ED50(self->f5C, &c)) {
            flag = 1;
        }
        Vector e;
        fn_80429090(&e, &c, &b, 1.0f);
        {
            Vector f;
            fn_8042F984(&f, &b, &lbl_80593DE0);
            Vector g;
            Vector h;
            fn_80429090(&g, &e, &f, 2.0f);
            fn_80429090(&h, &e, &f, -2.0f);
            g.z += 0.05f;
            h.z += 0.05f;
        }
        Vector p;
        fn_8042DC84(&p, fn_800B1724(*AI_GetEntity(self->f5C)));
        Vector q;
        fn_8042DC84(&q, &a);
        fn_8042FE08(&p, &b, 0.5f);
        float d1 = fn_8015E580(fn_800B1724(*AI_GetEntity(self->f5C)), &c);
        float d2 = fn_8015E580(&p, &c);
        float d3 = 2.0f;
        if (!flag)
            return 0;
        if (!self->f98)
            d3 = fn_8015E580(fn_800B1724(*AI_GetEntity(self->f5C)), &d);
        if (d1 <= 1.0f || d2 <= 1.0f || d3 <= 1.0f) {
            ret = 1;
        } else {
            float r = 1.0f;
            float t = 0.0f;
            int hit = fn_801BA090(&p, &q, r, &b, &e, &t);
            if (hit && flag) {
                ret = 1;
                Vector v;
                fn_80429090(&v, &p, &q, t);
                v.z += 0.05f;
            }
        }
    } else {
        float dist = __ieee754_sqrt(
            (fn_800B1724(*AI_GetEntity(self->f5C))->x - AI_GetMoverWaypoint(AI_GetMover(self->f5C))->x)
                * (fn_800B1724(*AI_GetEntity(self->f5C))->x - AI_GetMoverWaypoint(AI_GetMover(self->f5C))->x)
            + (fn_800B1724(*AI_GetEntity(self->f5C))->y - AI_GetMoverWaypoint(AI_GetMover(self->f5C))->y)
                * (fn_800B1724(*AI_GetEntity(self->f5C))->y - AI_GetMoverWaypoint(AI_GetMover(self->f5C))->y));
        if (dist < 1.0f) {
            float dz = fn_800B1724(*AI_GetEntity(self->f5C))->z - self->f80.z < 0.0f
                           ? -(fn_800B1724(*AI_GetEntity(self->f5C))->z - self->f80.z)
                           : fn_800B1724(*AI_GetEntity(self->f5C))->z - self->f80.z;
            ret = 1;
            if (fn_800CCA58(*AI_GetActor(self->f5C)) && dz > 3.0f)
                ret = 0;
        } else {
            ret = fn_804341BC(fn_800B1724(*AI_GetEntity(self->f5C)), &self->f80) < 1.0f;
        }
    }
    return ret;
}

extern "C" int fn_8014D034(register Nav *self)
{
    Way *way;
    void *x;
    int hit;

    if (!fn_804623BC(self))
        return 0;
    fn_8014DD30(self);
    if (!fn_804636AC(self) && !fn_80463644(self) && !fn_804635B8(self) && fn_8014D8C0(self)
        && self->f94 < fn_8042EFF8(lbl_80593BE8)) {
        if (!fn_804636E0(self))
            fn_8014D890(self);
        if (!fn_8014C31C(self)) {
            fn_8014C660(self);
            return 0;
        }
        self->f94 = fn_8042EFF8(lbl_80593BE8) + 5000;
    }
    way = fn_80463714(self);
    if (fn_80463644(self)) {
        x = fn_804635B8(self);
        hit = 0;
        if (x) {
            Vector a;
            Vector b;
            Vector c;
            fn_8042DC84(&a, fn_800B1724(*AI_GetEntity(self->f5C)));
            fn_8042DC84(&b, fn_80444688(self->f50));
            fn_80429038(&c, &b, &a);
            float len = fn_8042EC54(&c);
            hit = fn_8004A9CC(&a, &c, len, 0x8000, 0, fn_800B24AC(*AI_GetEntity(self->f5C)),
                              fn_800B1CC8(*AI_GetEntity(self->f5C)), 0, 3);
        }
        if (x && !hit) {
            Vector a;
            Vector b;
            fn_80429038(&a, &self->f60, fn_800B1724(*AI_GetEntity(self->f5C)));
            fn_8042F76C(&a);
            fn_80429038(&b, fn_80444688(self->f50), fn_800B1724(*AI_GetEntity(self->f5C)));
            fn_8042F76C(&b);
            if (fn_8042EBF4(&a, &b) < 0.4f) {
                self->f54 |= 0x8000;
                AI_SetMoverWaypoint(AI_GetMover(self->f5C), 0);
            } else {
                AI_SetMoverWaypoint(AI_GetMover(self->f5C), fn_80444688(self->f50));
            }
            self->f54 &= ~2;
            return 0;
        } else if (way) {
            fn_8014D928(self, way->f0);
            if (fn_8014D744(self))
                self->f54 &= ~2;
            else
                return 0;
        }
    }
    hit = fn_8014C6D8(self);
    if (hit) {
        if (!way) {
            if (fn_80463678(self)) {
                fn_8014C660(self);
                return 1;
            } else {
                self->f54 |= 0x8000;
                fn_804637BC(self, &self->f60, 0, 0);
                return 0;
            }
        }
        if (!fn_804636E0(self))
            fn_8014D890(self);
        self->f58 = way->f0;
        if (!fn_80463770(self) && fn_80463584(self)) {
            if (fn_8014C31C(self))
                fn_8014D034(self);
            else
                fn_8014C660(self);
            return 0;
        }
        self->f54 &= ~0xC0;
        if (fn_8014D744(self)) {
            way = fn_80463714(self);
            if (way)
                fn_804637BC(self, fn_80444A04(way->f0, 0), self->f58, 1);
            else
                fn_804637BC(self, fn_804635EC(self->f58, 0), self->f58, 1);
            if (self->f58) {
                if (fn_80444570(self->f58))
                    AI_SetMoverSpotKind(AI_GetMover(self->f5C), 1);
                else if (fn_80444CD0(self->f58))
                    AI_SetMoverSpotKind(AI_GetMover(self->f5C), 2);
                else if (fn_80444D04(self->f58)) {
                    if (fn_8014BAD0(AI_GetMover(self->f5C)))
                        AI_SetMoverSpotKind(AI_GetMover(self->f5C), 3);
                } else if (fn_804445A4(self->f58))
                    AI_SetMoverSpotKind(AI_GetMover(self->f5C), 4);
                else if (fn_804445D8(self->f58))
                    AI_SetMoverSpotKind(AI_GetMover(self->f5C), 2);
                else if (fn_80444D38(self->f58))
                    AI_SetMoverSpotKind(AI_GetMover(self->f5C), 5);
                else
                    AI_SetMoverSpotKind(AI_GetMover(self->f5C), 0);
            }
        } else {
            self->f54 |= 0x80;
        }
    } else {
        fn_8014D7B0(self);
    }
    return 0;
}

extern "C" int fn_8014D744(register Nav *self)
{
    if (!self->f58)
        return 1;
    if (fn_80444570(self->f58))
        fn_80461CC0(self->f5C, 0x1D);
    return 1;
}

extern "C" void fn_8014D7B0(register Nav *self)
{
    if (fn_80463714(self) && fn_80444D04(fn_80463714(self)->f0)) {
        if (!fn_801368B8(self->f5C)) {
            fn_8014C660(self);
            return;
        }
        fn_80461CC0(self->f5C, 0x1C);
    }
    if (fn_80463714(self) && fn_80444570(fn_80463714(self)->f0))
        fn_80461CC0(self->f5C, 0x1D);
    if (!self->f58)
        return;
}

extern "C" void fn_8014D890(register Nav *self)
{
    if (!self->f58)
        return;
}

extern "C" int fn_8014D8C0(register Nav *self)
{
    if (!self->f58)
        return 1;
    if (fn_80444570(self->f58))
        return 0;
    return 1;
}

extern "C" void fn_8014D928(register Nav *self, void *spot)
{
    if (fn_8044734C(AI_GetMover(self->f5C))
        && fn_80444A04(spot, 0)->x == fn_804635EC(fn_8044734C(AI_GetMover(self->f5C)), 0)->x
        && fn_80444A04(spot, 0)->y == fn_804635EC(fn_8044734C(AI_GetMover(self->f5C)), 0)->y
        && fn_80444A04(spot, 0)->z == fn_804635EC(fn_8044734C(AI_GetMover(self->f5C)), 0)->z) {
        fn_804637BC(self, fn_804635EC(spot, 0), spot, 1);
        return;
    }
    if (!fn_80444D04(spot)) {
        Vector a;
        if (fn_801BABC8(fn_800B1724(*AI_GetEntity(self->f5C)), fn_80444A04(spot, 0), fn_804635EC(spot, 0), &a) > 0.0f) {
            Vector b;
            Vector c;
            fn_8042DC84(&b, fn_800B1724(*AI_GetEntity(self->f5C)));
            b.z = a.z;
            fn_80429038(&c, &a, &b);
            float len = fn_8042EC54(&c);
            if (!fn_8004A9CC(&b, &c, len, 0x8000, 0, fn_800B24AC(*AI_GetEntity(self->f5C)),
                             fn_800B1CC8(*AI_GetEntity(self->f5C)), 0, 3)) {
                if (AI_GetMoverWaypoint(AI_GetMover(self->f5C))->x == fn_80444688(fn_80444984(spot, 0))->x
                    && AI_GetMoverWaypoint(AI_GetMover(self->f5C))->y == fn_80444688(fn_80444984(spot, 0))->y
                    && AI_GetMoverWaypoint(AI_GetMover(self->f5C))->z == fn_80444688(fn_80444984(spot, 0))->z)
                    fn_804637BC(self, fn_80444688(fn_80444984(spot, 0)), spot, 1);
                else
                    fn_804637BC(self, &a, spot, 0);
                self->f58 = spot;
                return;
            }
        }
    }
    fn_804637BC(self, fn_80444A04(spot, 0), spot, 0);
}

extern "C" void fn_8014DD30(register Nav *self)
{
    unsigned int i;

    for (i = 0; i < self->f0; i++) {
        void *spot = self->f4[i];
        if (spot) {
            unsigned int color = 0xFFFF8000;
            if (fn_80444D6C(spot))
                color = 0xFFFF0000;
        }
    }
}

// 0x8049B4AC-0x8049B520: linkonce pool words, then the header's "invalid" that closes the file's .rodata (docs/ai.md section 2).
__asm__(".section .rodata\n\t.long 0x41A00000, 0x43300000, 0x80000000, 0x30000000, 0x42C80000, 0x42480000\n\t"
        ".long 0x497423FE, 0xC97423FE, 0xC97423FE, 0xC97423FE, 0x497423FE\n\t"
        ".float 1.0, 0.0, 1.0, 0.0, 1.0, 1.2, 0.8, 2.0, 0.5, 0.8, 0.8, 1.0, 1.25, 0.75\n\t"
        ".long 2000\n\t.balign 8\n\t.asciz \"invalid\"\n\t.text");
