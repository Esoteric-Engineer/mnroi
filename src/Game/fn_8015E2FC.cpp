// Shared AI helpers called from the behaviors and tasks (docs/ai.md row 9).
// Owns the .rodata pool 0x8049BA18-0x8049BAC0; dtk's lbl_8049BA38, lbl_8049BA8C and lbl_8049BABC were split to end it.

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

struct Slot {
    char d[0x30];
};

struct Query { // as in Game/fn_800F43D4.cpp
    char pad0[0x40];
    Slot slot[0x80];    // +0x40
    unsigned int count; // +0x1840
    char pad1844[0xC];
};

class Placement
{
public:
    Vector d[4];
    Placement();
};

struct Ent {
    int pad;
};
struct PlayerEnt : Ent { // matching_notes 48
    int x;
};

extern "C" {
void *AI_GetEntity(void *ai);
PlayerEnt *fn_80442080P(void *ai) __asm__("AI_GetEntity");
Vector *fn_800B1724(Ent &e);
void fn_8042DC84(Vector *dst, Vector *src);
void fn_8043539C(Placement *p);
void *fn_800B24AC(void *e);
int fn_8004A758(Vector *a, Vector *b, float r, int c, Placement *p, void *d, int e, int f, int g);
Vector *fn_80437168(Placement *p);
float fn_8042EBF4(Vector *a, Vector *b);
Ent *fn_80134870(void *ai);
int fn_800489BC(Placement *p);
int fn_800B13D8(Ent *e);
float fn_804290F8(Vector *a, Vector *b);
float *fn_8042FB28(Vector *v);
void fn_80429038(Vector *out, Vector *a, Vector *b);
void fn_8042F76C(Vector *v);
Vector *fn_800B1750(Ent &e);
float fn_80426A84(void *p);
extern char lbl_80593BE8[];
float fn_80464448(float lo, float hi);
unsigned int fn_80435904(void);
unsigned int fn_80171F8C(void);
float fn_800B1884(void *e, int id);
void fn_8043CEE4(Vector *out, Vector *v);
int fn_800B0C1C(void *e);
void *fn_800B14C8(void *e);
int fn_8008582C(void *e);
int fn_8015F2D0(void *a, void *b);
void *AI_GetBrain(void *ai);
int fn_80151AF8(void *brain, int id);
float fn_80086730(void *e);
float fn_8008677C(void *e);
float fn_80086614(void *e);
float fn_80086640(void *e);
float fn_804340B8(void *o, Vector *v);
void fn_8004E9C8(Query *q);
void fn_80434C88(Query *q);
void fn_80434CDC(Query *q, int bit);
void fn_80434D18(Query *q, void *ignore);
void fn_8004E4B4(Query *q, Vector *pos, float r, void *world);
Ent *fn_80434C2C(Slot *s);
void *fn_800B1CC8(void *e);
int fn_800860FC(void *e);
void *fn_80085980(void *e);
int fn_800B0CC0(void *e);
void *fn_800B1478(void *e);
int fn_800A4538(void *p);
int fn_800B11F8(void *e);
int fn_800B1D48(void *e);
float fn_800A4054(void *p);
float fn_8042EC54(Vector *v);
int fn_800A4130(void *p);
void *fn_80085954(void *e);
int fn_800F5CC8(void *self, void *c, int a);
int fn_8008572C(void *a, void *b);
float fn_8042FE6C(Vector *v);
float fn_801BDB9C(float a);
float fn_80085A04(void *e);
void fn_8042F838(Vector *out, Vector *v, float angle);
void *AI_GetEvents(void *ai);
int fn_80442508(void *set, int bit);
int fn_800862DC(void *e);
int fn_8046441C(void *ai);
int AI_TestCondition(void *ai, int bit);
Vector *fn_800B17A8(Ent &e);
void fn_8042D80C(Vector *dst, Vector *src);
void fn_80447C38(Vector *v);
void fn_80429090(Vector *out, Vector *a, Vector *b, float t);
void *fn_8013726C(void *ai);
int fn_804622B4(void *list);
void *fn_804622FC(void *list, int i);
int fn_80146A88(void *o, Vector *a, Vector *b, Vector *hit);
extern Vector lbl_80593DE0;

// Casts a ray from the AI's actor, raised by 0.4 + height, to the point; *hit gets what it struck.
int fn_8015E2FC(void *ai, Vector *to, float r, int *hit, float height)
{
    if (ai == 0 || to == 0)
        return 0;
    void *actor = AI_GetEntity(ai);
    Vector from;
    fn_8042DC84(&from, fn_800B1724(*(Ent *)actor));
    from.z += 0.4f;
    from.z += height;
    Placement p;
    fn_8043539C(&p);
    int found = fn_8004A758(&from, to, r, 0x1F, &p, fn_800B24AC(actor), 0, 0, 6);
    if (found) {
        float d = fn_8042EBF4(fn_80437168(&p), &lbl_80593DE0);
        if (d > 0.8f)
            found = 0;
        if (fn_80134870(ai) && fn_800489BC(&p) == fn_800B13D8(fn_80134870(ai))) {
            *hit = 0;
            found = 0;
        } else {
            *hit = fn_800489BC(&p);
        }
    }
    return found;
}

float fn_8015E4E8(void *ai)
{
    if (!fn_80134870(ai))
        return 0.0f;
    return fn_804290F8(fn_800B1724(*fn_80442080P(ai)), fn_800B1724(*fn_80134870(ai)));
}

float fn_8015E580(Vector *a, Vector *b)
{
    if (a == 0 || b == 0)
        return 0.0f;
    Vector va;
    Vector vb;
    fn_8042DC84(&va, a);
    fn_8042DC84(&vb, b);
    va.z = 0.0f;
    vb.z = 0.0f;
    return fn_804290F8(&va, &vb);
}

float fn_8015E64C(void *ai)
{
    if (!fn_80134870(ai))
        return 0.0f;
    Vector a;
    Vector b;
    fn_8042DC84(&a, fn_800B1724(*fn_80442080P(ai)));
    fn_8042DC84(&b, fn_800B1724(*fn_80134870(ai)));
    fn_8042FB28(&a)[2] = 0.0f;
    fn_8042FB28(&b)[2] = 0.0f;
    return fn_804290F8(&a, &b);
}

// Whether the point is less than 60 degrees off the actor's facing.
int fn_8015E764(void *ai, Vector *p)
{
    Vector dir;
    fn_80429038(&dir, p, fn_800B1724(*fn_80442080P(ai)));
    fn_8042F76C(&dir);
    float d = fn_8042EBF4(&dir, fn_800B1750(*fn_80442080P(ai)));
    if (d > 0.5f)
        return 1;
    return 0;
}

int fn_8015E830(void *ai)
{
    Ent *target = fn_80134870(ai);
    if (target == 0)
        return 0;
    return fn_8015E764(ai, fn_800B1724(*target));
}

float fn_8015E8A8(void *ai, Vector *p)
{
    return p->z - fn_800B1724(*fn_80442080P(ai))->z < 0.0f
               ? -(p->z - fn_800B1724(*fn_80442080P(ai))->z)
               : p->z - fn_800B1724(*fn_80442080P(ai))->z;
}

// True on average once every `seconds`, called once a frame.
int fn_8015E97C(float seconds)
{
    float dt = fn_80426A84(lbl_80593BE8);
    float chance = 1.0f / seconds / dt;
    float roll = fn_80464448(0.0f, chance);
    return roll <= 1.0f;
}

int fn_8015EA18(unsigned int n)
{
    return fn_80435904() % n;
}

// Pool words of linkonce functions whose kept copies are elsewhere (matching_notes 23).
__asm__(".section .rodata\n\t.long 0x3D072B02\n\t.float 2.0\n\t.float 0.0\n\t.float 28.0\n\t.float 0.0\n\t.float 0.0\n\t.float 1.0\n\t.text");

// Picks an index below n with odds given by the weights w.
unsigned int fn_8015EA6C(unsigned int n, float *w)
{
    float sum = 0.0f;
    unsigned int i;
    for (i = 0; i < n; i++)
        sum += w[i];
    float roll = fn_80464448(0.0f, sum - 1.0f < 0.0f ? 0.0f : sum - 1.0f);
    sum = 0.0f;
    for (i = 0; i < n; i++) {
        if (roll >= sum && roll < sum + w[i])
            return i;
        sum += w[i];
    }
    return fn_80171F8C() % n;
}

// True with `percent` chance in 100.
int fn_8015EC1C(float percent)
{
    return fn_8015EA18(100) < (int)percent;
}

// fn_8015E97C with the period scaled by percent / 100.
int fn_8015EC80(float percent, float seconds)
{
    float dt = fn_80426A84(lbl_80593BE8);
    if (dt == 0.0f)
        return 0;
    seconds *= percent / 100.0f;
    float chance = 1.0f / seconds / dt;
    return fn_80464448(0.0f, chance) <= 1.0f;
}

// Whether the point's height is within -0.1..1.5 of the actor's.
int fn_8015ED50(void *ai, Vector *p)
{
    float dz = p->z - fn_800B1724(*fn_80442080P(ai))->z;
    if (dz > 0.0f) {
        if (dz < 1.5f)
            return 1;
        else
            return 0;
    }
    if (dz <= 0.0f) {
        if (dz < -0.1f)
            return 0;
        else
            return 1;
    }
    return 0;
}

int fn_8015EE34(void *ai, Ent *e)
{
    if (e == 0)
        return 0;
    return fn_8015ED50(ai, fn_800B1724(*e));
}

// Whether the target stands more than 1.5 above the actor.
int fn_8015EEA0(void *ai)
{
    if (!fn_80134870(ai))
        return 0;
    Ent *target = fn_80134870(ai);
    float dz = fn_800B1724(*target)->z - fn_800B1724(*fn_80442080P(ai))->z;
    if (dz > 1.5f)
        return 1;
    return 0;
}

// Whether the target stands more than 0.5 below the actor.
int fn_8015EF54(void *ai)
{
    if (!fn_80134870(ai))
        return 0;
    Ent *target = fn_80134870(ai);
    float dz = fn_800B1724(*target)->z - fn_800B1724(*fn_80442080P(ai))->z;
    if (dz < -0.5f)
        return 1;
    return 0;
}

// Whether the flat distance to the target is beyond tuning field 211.
int fn_8015F008(void *self)
{
    register float v = fn_8015E64C(self);
    register void *p = AI_GetEntity(self);

    return v > fn_800B1884(p, 0xD3);
}

// Whether it is within tuning field 212.
int fn_8015F07C(void *self)
{
    register float v = fn_8015E64C(self);
    register void *p = AI_GetEntity(self);

    return v < fn_800B1884(p, 0xD4);
}

// Whether the actor faces the target's direction, measured on its own level.
int fn_8015F0F0(void *ai, Ent *target)
{
    if (target == 0)
        return 0;
    Vector me;
    fn_8042DC84(&me, fn_800B1724(*fn_80442080P(ai)));
    Vector them;
    fn_8042DC84(&them, fn_800B1724(*target));
    Vector level;
    fn_8042DC84(&level, &them);
    level.z = me.z;
    Vector flat;
    fn_80429038(&flat, &me, &level);
    fn_8042F76C(&flat);
    Vector to;
    fn_80429038(&to, &me, &them);
    Vector dir;
    fn_8043CEE4(&dir, &to);
    float d = fn_8042EBF4(&dir, &flat);
    if (d > 0.25f)
        return 1;
    return 0;
}

int fn_8015F278(void *a, void *b)
{
    return !fn_8015F2D0(a, b);
}

int fn_8015F2D0(void *a, void *b)
{
    if (fn_800B0C1C(a) && fn_800B0C1C(b)) {
        int ka = fn_8008582C(fn_800B14C8(a));
        int kb = fn_8008582C(fn_800B14C8(b));
        if (ka != kb)
            return 1;
    }
    return 0;
}

// Whether the brain runs a POSSESS (6) or ENSLAVE (0xE) task.
int fn_8015F384(void *ai)
{
    if (fn_80151AF8(AI_GetBrain(ai), 6) || fn_80151AF8(AI_GetBrain(ai), 0xE))
        return 1;
    return 0;
}

int fn_8015F410(void *ai, float min)
{
    float frac = fn_80086730(AI_GetEntity(ai)) / fn_8008677C(AI_GetEntity(ai));
    return frac >= min;
}

int fn_8015F4A4(void *ai, float min)
{
    float frac = fn_80086614(AI_GetEntity(ai)) / fn_80086640(AI_GetEntity(ai));
    return frac >= min;
}

float fn_8015F538(void *ai, Vector *p, void *o)
{
    if (o == 0)
        return 0.0f;
    if (AI_GetEntity(ai) == 0)
        return 0.0f;
    Vector d;
    fn_80429038(&d, p, fn_800B1724(*fn_80442080P(ai)));
    d.z = 0.0f;
    return fn_804340B8(o, &d);
}

float fn_8015F608(void *ai, Vector *p, void *o)
{
    if (o == 0)
        return 0.0f;
    if (AI_GetEntity(ai) == 0)
        return 0.0f;
    Vector d;
    fn_80429038(&d, p, fn_800B1724(*fn_80442080P(ai)));
    return fn_804340B8(o, &d);
}

// Fills out with the flat direction from the actor to its target.
int fn_8015F6CC(void *ai, Vector *out)
{
    if (out == 0)
        return 0;
    if (!fn_80134870(ai))
        return 0;
    Vector d;
    fn_80429038(&d, fn_800B1724(*fn_80134870(ai)), fn_800B1724(*fn_80442080P(ai)));
    d.z = 0.0f;
    fn_8043CEE4(out, &d);
    return 1;
}

__asm__(".section .rodata\n\t.float 0.0\n\t.float 10.0\n\t.float -1.0\n\t.text");

// Picks the nearest actor within range for mode 0, 1 or 2; one outside the cone around dir counts range farther.
void *fn_8015F7A4(Ent *actor, float range, int mode, Vector *dir, float cosmin)
{
    Query q;
    fn_8004E9C8(&q);
    void *best = 0;
    Slot *s;
    Ent *e;
    fn_80434C88(&q);
    fn_80434CDC(&q, 2);
    fn_80434CDC(&q, 8);
    fn_80434D18(&q, actor);
    fn_8004E4B4(&q, fn_800B1724(*actor), range, fn_800B1CC8(actor));
    float bestDist = 3.4028235e38f;
    unsigned int i;
    for (i = 0; i < q.count; i++) {
        s = &q.slot[i];
        e = fn_80434C2C(s);
        if (e == 0)
            continue;
        if (!fn_800860FC(actor) && !fn_8015EE34(fn_80085980(actor), e))
            continue;
        if (!fn_800B0CC0(e))
            continue;
        if (fn_800A4538(fn_800B1478(e)))
            continue;
        if (fn_800B11F8(e))
            continue;
        if (!fn_800B1D48(e))
            continue;
        int unused = 0;
        switch (mode) {
        case 0:
            if (fn_800B0CC0(e) && fn_800A4054(fn_800B1478(e)) > 0.0f) {
                Vector d;
                fn_80429038(&d, fn_800B1724(*e), fn_800B1724(*actor));
                float dist = fn_8042EC54(&d);
                if (dir && fn_8042EBF4(&d, dir) < cosmin)
                    dist += range;
                if (dist < bestDist) {
                    best = fn_800B1478(e);
                    bestDist = dist;
                }
            }
            break;
        case 1:
            if (fn_800B0CC0(e) && fn_800A4130(fn_800B1478(e)) && fn_800F5CC8(fn_80085954(actor), fn_800B1478(e), 1)
                && fn_8008572C(actor, fn_800B1478(e))) {
                Vector d;
                fn_80429038(&d, fn_800B1724(*e), fn_800B1724(*actor));
                float dist = fn_8042EC54(&d);
                if (dir && fn_8042EBF4(&d, dir) < cosmin)
                    dist += range;
                if (dist < bestDist) {
                    best = fn_800B1478(e);
                    bestDist = dist;
                }
            }
            break;
        case 2:
            if (fn_800B0CC0(e) && !fn_800A4130(fn_800B1478(e)) && fn_800F5CC8(fn_80085954(actor), fn_800B1478(e), 1)
                && fn_8008572C(actor, fn_800B1478(e))) {
                Vector d;
                fn_80429038(&d, fn_800B1724(*e), fn_800B1724(*actor));
                float dist = fn_8042EC54(&d);
                if (dir && fn_8042EBF4(&d, dir) < cosmin)
                    dist += range;
                if (dist < bestDist) {
                    best = fn_800B1478(e);
                    bestDist = dist;
                }
            }
            break;
        }
    }
    return best;
}

// Turns the actor's facing toward dir, by at most its turn speed times rate this frame.
void fn_8015FD2C(void *ai, Vector *dir, float rate, Vector *out)
{
    float cur;
    float tgt;
    float diff;
    float step;
    Vector res;
    Vector want;
    fn_8042DC84(&want, dir);
    want.z = 0.0f;
    fn_8042F76C(&want);
    cur = fn_8042FE6C(fn_800B1750(*fn_80442080P(ai)));
    tgt = fn_8042FE6C(&want);
    diff = tgt - cur;
    diff = fn_801BDB9C(diff);
    step = (diff < 0.0f ? -diff : diff) * 0.011111111f;
    step = step >= 0.4f ? (step <= 1.0f ? step : 1.0f) : 0.4f;
    step *= fn_80085A04(AI_GetEntity(ai)) * rate * fn_80426A84(lbl_80593BE8);
    if ((diff < 0.0f ? -diff : diff) > step) {
        diff = diff >= -step ? (diff <= step ? diff : step) : -step;
        fn_8042F838(&res, fn_800B1750(*fn_80442080P(ai)), diff);
    } else {
        fn_8042DC84(&res, &want);
    }
    *out = res;
}

int fn_8015FFD4(void *ai)
{
    if (fn_80442508(AI_GetEvents(ai), 4)) {
        if (!fn_800862DC(AI_GetEntity(ai)) && fn_8046441C(ai) == 0x60)
            return 1;
        if (fn_8046441C(ai) == 0x3E || fn_8046441C(ai) == 0x40 || fn_8046441C(ai) == 0x3F || fn_8046441C(ai) == 0x41
            || fn_8046441C(ai) == 0x2D)
            return 1;
    }
    return 0;
}

// Whether 2.5 units on side 0-3 of the actor are clear of the encounter record's elements (fn_80146A88); dist is unused.
int fn_801600DC(void *ai, int side, float dist)
{
    Vector dir;
    switch (side) {
    case 0:
        if (AI_TestCondition(ai, 0x12))
            return 0;
        fn_8042D80C(&dir, fn_800B17A8(*fn_80442080P(ai)));
        break;
    case 1:
        if (AI_TestCondition(ai, 0x14))
            return 0;
        fn_8042DC84(&dir, fn_800B1750(*fn_80442080P(ai)));
        break;
    case 2:
        if (AI_TestCondition(ai, 0x13))
            return 0;
        fn_8042DC84(&dir, fn_800B17A8(*fn_80442080P(ai)));
        break;
    case 3:
        if (AI_TestCondition(ai, 0x15))
            return 0;
        fn_8042D80C(&dir, fn_800B1750(*fn_80442080P(ai)));
        break;
    }
    Vector from;
    Vector to;
    fn_8042DC84(&from, fn_800B1724(*fn_80442080P(ai)));
    fn_80447C38(&to);
    fn_80429090(&to, &from, &dir, 2.5f);
    from.z = 0.0f;
    to.z = 0.0f;
    for (int i = 0; i < fn_804622B4(fn_8013726C(ai)); i++) {
        void *o = fn_804622FC(fn_8013726C(ai), i);
        if (o == 0)
            continue;
        Vector hit;
        if (fn_80146A88(o, &from, &to, &hit))
            return 0;
    }
    return 1;
}

int fn_801603CC(void *ai, int side)
{
    return fn_801600DC(ai, side, 4.5f);
}
}
