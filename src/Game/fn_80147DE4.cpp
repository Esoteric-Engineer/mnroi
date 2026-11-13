// Methods of the 0xDC-byte encounter record (AiObj): reset, lookups, the nearby scan, the engaged-list
// rotation (fn_80148B08), its debug draw, and the spot search around a target (fn_80148D30). docs/ai.md row 10.
// Float and string pool 0x8049B204-0x8049B258 (extern_pool).

inline int sn_return_decl(int a) { return a; }

struct Ent {
    int pad;
};
struct PEnt : Ent { // matching_notes 44
    int x;
};

struct Actor {
    int pad;
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

struct Tgt : Ent {
    char d[0x194];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(Vector *v, int z); // +0x30
};

struct CtlBase {
    char d[0x3AC];
};
struct Ctl : CtlBase { // vptr +0x3AC
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual int busy();
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

struct AiObj {
    int nNear; // +0x0
    int nearId[8]; // +0x4, AIs within radius of the owner
    unsigned int seenAt[8]; // +0x24, clock + tuning 183 / 2 when first seen
    int engagedAt[8]; // +0x44, last time engaged; the oldest is engaged next
    int f64; // +0x64
    int nEngaged; // +0x68, at most lbl_8066BF50
    int engaged[8]; // +0x6c
    int engagedSince[8]; // +0x8c, dropped after tuning 183
    unsigned int nHistory; // +0xac
    int history[8]; // +0xb0, disengaged ids, newest first
    int owner; // +0xD0
    int fD4; // +0xD4
    float radius; // +0xD8
};

extern "C" {
void fn_8004E9C8(Query *q);
void fn_80434C88(Query *q);
void fn_80434CDC(Query *q, int bit);
void fn_80434D18(Query *q, void *ignore);
void fn_8004E4B4(Query *q, void *a, float r, void *b);
Actor *fn_800ACFA8(int handle);
void *fn_800B1724(void *e);
void *fn_800B1CC8(void *e);
int fn_80434C2C(Slot *s);
void *fn_800B14A0(void *e);
void *fn_80085928(void *e);
int fn_800CC60C(void *e);
void *fn_80085980(void *e);
int fn_80463204(void *e);
int fn_80085EEC(void *e);
int fn_800B13D8(void *e);
int fn_800B18EC(Ent &e, int id);
PEnt *fn_800B14A0p(void *e) __asm__("fn_800B14A0");
int fn_8042EFF8(void *g);
void fn_8008656C(void *e, int v);
void *fn_80085954(void *e);
void *fn_800C9FD0(void *e);
float fn_800B1884(void *e, int id);
void fn_800E89B0(void *e, float a, float b, int c, int d, int e2);
float fn_804290F8(void *a, void *b);
Ctl *fn_80085954c(void *e) __asm__("fn_80085954");
int fn_800B18ECv(void *e, int id) __asm__("fn_800B18EC");
int fn_8015F384(void *a);
int sprintf(char *dst, const char *fmt, ...);
int fn_800FE284(int index);
int fn_80426E88(void *text, int font);
void fn_80100C50(void *text, int a);
void fn_8042AC7C(void *text, unsigned int color);
int fn_800B92DC(void **text, const char *s, float x, float y);
void *fn_80134870(void *a);
char *fn_800AFF88(void *thing);
Vector *fn_800B1750(Ent &actor);
Vector *fn_800B1724v(Ent &actor) __asm__("fn_800B1724");
void fn_8042DC84(Vector *dst, Vector *src);
void *fn_804304CC(void *p);
void fn_804354B8(void *dst, void *src);
void fn_80428FA8(Vector *v, float x, float y, float z);
int fn_804427FC(char *g);
void *fn_8046315C(char *g);
float fn_804631B8(void *cam);
float *fn_8042FB28(Vector *v);
float fn_801BDA3C(float a);
void fn_801BEC2C(Vector *v, Vector *rot);
void fn_80435530(Vector *v, float s);
void fn_8042D854(Vector *dst, Vector *src);
void fn_80429038(Vector *out, Vector *a, Vector *b);
float fn_8042EC54(Vector *v);
float fn_8042FE6C(Vector *v);
int fn_800B24AC(Ent &e);
int fn_800B1CC8i(Ent &e) __asm__("fn_800B1CC8");
Tgt *fn_80442080(void *ai);
Tgt *fn_80134870t(void *ai) __asm__("fn_80134870");
AiObj *fn_801332C0(Tgt *actor);
int fn_800B13D8r(Ent &e) __asm__("fn_800B13D8");
int fn_8004A9CC(Vector *from, Vector *dir, float len, unsigned int mask, void *hit, int a, int b, int c, int d);
}

extern char lbl_80593BE8[];
extern int lbl_8066BF50;
extern void *lbl_8066D6DC;
extern char lbl_80552110[];
extern char lbl_80593DD0[];

extern "C" void fn_80147DE4(register AiObj *self)
{
    int i;
    for (i = 0; i < 8; i++) {
        self->nearId[i] = 0;
        self->history[i] = 0;
        self->seenAt[i] = 0;
        self->engagedAt[i] = 0;
    }
    int j;
    for (j = 0; j < 8; j++) {
        self->engaged[j] = 0;
        self->engagedSince[j] = 0;
    }
    self->fD4 = -1;
    self->owner = 0;
    self->radius = 0.0f;
    self->f64 = 0;
    self->nNear = 0;
    self->nEngaged = 0;
    self->nHistory = 0;
}

extern "C" int fn_80147F20(register AiObj *self, int id)
{
    int i;
    for (i = 0; i < self->nNear; i++) {
        if (self->nearId[i] == id)
            return i;
    }
    return -1;
}

extern "C" int fn_80147FA4(register AiObj *self, int id)
{
    int i;
    for (i = 0; i < self->nNear; i++) {
        if (self->nearId[i] == id)
            return 1;
    }
    return 0;
}

extern "C" int fn_80148024(register AiObj *self)
{
    return self->nNear;
}

extern "C" int fn_80148050(register AiObj *self, int id)
{
    int i;
    for (i = 0; i < self->nEngaged; i++) {
        if (self->engaged[i] == id)
            return 1;
    }
    return 0;
}

extern "C" void fn_801480D0(register AiObj *self, void *e)
{
    if (e) {
        if (fn_800CC60C(fn_80085928(e)))
            self->fD4 = 1;
        else
            self->fD4 = 0;
        self->owner = fn_800B13D8(e);
        self->nNear = 0;
        self->nEngaged = 0;
        self->radius = 60.0f;
        self->f64 = 3000;
    }
}

extern "C" void fn_80148178(register AiObj *self)
{
    Query q;
    void *e58;

    fn_8004E9C8(&q);
    e58 = 0;
    fn_80434C88(&q);
    fn_80434CDC(&q, 0);
    fn_80434CDC(&q, 7);
    Actor &owner = *fn_800ACFA8(self->owner);
    if (!&owner)
        return;
    Slot *slot;
    int r;
    float f68;
    unsigned int i;
    int id;
    unsigned int t;
    fn_80434D18(&q, &owner);
    fn_8004E4B4(&q, fn_800B1724(&owner), self->radius, fn_800B1CC8(&owner));
    f68 = 3.4028235e38f;
    for (i = 0; i < q.count; i++) {
        slot = &q.slot[i];
        r = fn_80434C2C(slot);
        if (!r)
            continue;
        e58 = fn_800B14A0((void *)r);
        if (!fn_800CC60C(fn_80085928(e58)))
            continue;
        if (fn_80463204(fn_80085980(e58)) == 0x1d)
            continue;
        if (fn_80085EEC(e58))
            continue;
        id = fn_800B13D8(e58);
        if (fn_80147FA4(self, id))
            continue;
        if (self->nNear < sizeof self->nearId / sizeof self->nearId[0]) {
            t = fn_800B18EC(*fn_800B14A0p(fn_800ACFA8(id)), 0xB7);
            self->nearId[self->nNear] = id;
            self->seenAt[self->nNear] = fn_8042EFF8(lbl_80593BE8) + (t >> 1);
            fn_8008656C(e58, 1);
            self->nNear++;
        }
        if (!fn_800C9FD0(fn_80085954(e58))) {
            register void *v27 = fn_80085954(e58);
            register float f31 = fn_800B1884(e58, 0xDF);
            fn_800E89B0(v27, f31, fn_800B1884(e58, 2), 0, 0, 0);
        }
    }
}

extern "C" void fn_80148440(register AiObj *self)
{
    int i;
    for (i = 0; i < self->nNear; i++) {
        Actor &e = *fn_800ACFA8(self->nearId[i]);
        int gone = 0;
        if (!&e)
            gone = 1;
        else if (&e && fn_80085EEC(&e))
            gone = 1;
        else {
            Actor &owner = *fn_800ACFA8(self->owner);
            if (&owner && fn_804290F8(fn_800B1724(&e), fn_800B1724(&owner)) > self->radius)
                gone = 1;
            else
                gone = 0;
        }
        if (gone) {
            if (self->nNear == 1)
                self->nNear = 0;
            else if (i == self->nNear - 1)
                self->nNear--;
            else {
                self->nearId[i] = self->nearId[self->nNear - 1];
                self->engagedAt[i] = self->engagedAt[self->nNear - 1];
                self->seenAt[i] = self->seenAt[self->nNear - 1];
                self->nNear--;
            }
        }
    }
}

extern "C" void fn_80148644(register AiObj *self)
{
    int i;
    for (i = 0; i < self->nEngaged; i++) {
        int drop = 0;
        int id = self->engaged[i];
        Actor &e = *fn_800ACFA8(id);
        if (!&e)
            drop = 1;
        if (!fn_80147FA4(self, id))
            drop = 1;
        int dt = fn_8042EFF8(lbl_80593BE8) - self->engagedSince[i];
        if (&e && dt > fn_800B18ECv(&e, 0xB7) && !fn_80085954c(&e)->busy())
            drop = 1;
        if (drop) {
            int j;
            for (j = 7; j > 0; j--)
                self->history[j] = self->history[j - 1];
            self->history[0] = id;
            if (self->nHistory < 8)
                self->nHistory++;
            if (self->nEngaged == 1)
                self->engaged[i] = 0;
            else if (i == self->nEngaged - 1)
                self->engaged[i] = 0;
            else {
                self->engaged[i] = self->engaged[self->nEngaged - 1];
                self->engagedSince[i] = self->engagedSince[self->nEngaged - 1];
            }
            self->nEngaged--;
        }
    }
    if (self->nEngaged == lbl_8066BF50)
        return;
    for (i = self->nEngaged; i < lbl_8066BF50; i++) {
        int best = -1;
        int flag = 1;
        unsigned int min;
        if (flag) {
            min = 9999999;
            int k;
            for (k = 0; k < self->nNear; k++) {
                Actor &e = *fn_800ACFA8(self->nearId[k]);
                if (&e) {
                    if (fn_80085980(&e) && fn_8015F384(fn_80085980(&e)))
                        continue;
                    if (!fn_80148050(self, self->nearId[k]) && self->engagedAt[k] < min) {
                        best = k;
                        min = self->engagedAt[k];
                    }
                }
            }
        }
        if (best != -1) {
            min = fn_800B18EC(*fn_800B14A0p(fn_800ACFA8(self->nearId[best])), 0xB7);
            self->engaged[self->nEngaged] = self->nearId[best];
            self->engagedSince[self->nEngaged] = fn_8042EFF8(lbl_80593BE8);
            self->engagedAt[best] = fn_8042EFF8(lbl_80593BE8);
            self->nEngaged++;
        }
    }
}

extern "C" void fn_80148B08(register AiObj *self)
{
    fn_80148440(self);
    fn_80148178(self);
    fn_80148644(self);
}

extern "C" void fn_80148B50(register AiObj *self, float x, float y)
{
    char buf[0x80];
    fn_80426E88(lbl_8066D6DC, fn_800FE284(6));
    fn_80100C50(lbl_8066D6DC, 0);
    fn_8042AC7C(lbl_8066D6DC, 0xFFB0B020);
    int i;
    for (i = 0; i < self->nNear; i++) {
        int id = self->nearId[i];
        Actor &e = *fn_800ACFA8(id);
        if (&e) {
            char mark = '-';
            if (fn_80148050(self, id))
                mark = '>';
            void *t = 0;
            if (fn_80085980(&e))
                t = fn_80134870(fn_80085980(&e));
            const char *tname = "NONE";
            int tid = 0;
            if (t) {
                tname = fn_800AFF88(t);
                tid = fn_800B13D8(t);
            }
            sprintf(buf, "%c %s (%d) T:%s (%d)", mark, fn_800AFF88(&e), fn_800B13D8(&e), tname, tid);
            fn_800B92DC(&lbl_8066D6DC, buf, x, y);
            y += 13.0f;
        }
    }
}

// Finds a spot dist from center, in sight of it, at self's height: tries slots from start, by camera spread or evenly.
extern "C" int fn_80148D30(Tgt *self, Tgt *center, float dist, int start, int count, Vector *out, int byCamera,
                           int useFwd)
{
    float two = 2.0f;
    Vector pos;
    float d = dist;
    Vector fwd;
    fn_8042DC84(&fwd, fn_800B1750(*center));
    if (useFwd)
        fn_804354B8(&fwd, fn_804304CC(lbl_80593DD0));
    Vector rot;
    int done = 0;
    int i = start;
    while (!done) {
        fn_80428FA8(&pos, 0.0f, 1.0f, 0.0f);
        if (byCamera) {
            void *cam = 0;
            if (fn_804427FC(lbl_80552110))
                cam = fn_8046315C(lbl_80552110);
            if (cam) {
                float spread = 30.0f;
                float ang = fn_804631B8(cam) - spread / 2.0f - count * spread / 2.0f + (i + 1) * spread;
                *fn_8042FB28(&rot) = 0.0f;
                fn_8042FB28(&rot)[2] = fn_801BDA3C(ang);
                fn_8042FB28(&rot)[1] = 0.0f;
                fn_801BEC2C(&pos, &rot);
            }
        } else {
            float step = 360.0f / count;
            *fn_8042FB28(&rot) = 0.0f;
            fn_8042FB28(&rot)[2] = fn_801BDA3C(i * step + fn_8042FE6C(&fwd));
            fn_8042FB28(&rot)[1] = 0.0f;
            fn_801BEC2C(&pos, &rot);
        }
        fn_80435530(&pos, d);
        fn_8042D854(&pos, fn_800B1724v(*center));
        pos.z = fn_800B1724v(*self)->z;
        Vector from;
        Vector dir;
        center->s5(&from, 0);
        fn_80429038(&dir, &pos, &from);
        float len = fn_8042EC54(&dir);
        int clear = !fn_8004A9CC(&from, &dir, len, 0x8000, 0, fn_800B24AC(*center), fn_800B1CC8i(*center), 0, 3);
        if (clear)
            done = 1;
        if (++i > 7)
            i = 0;
        if (i == start) {
            done = 1;
            fn_8042DC84(&pos, fn_800B1724v(*center));
        }
    }
    *out = pos;
    return 1;
}

// Finds a spot dist from the AI's target for the AI's slot in its encounter record.
extern "C" int fn_80149270(void *ai, float dist, Vector *out)
{
    if (!ai)
        return 0;
    Tgt &t = *fn_80134870t(ai);
    if (!&t)
        return 0;
    AiObj *rec = fn_801332C0(fn_80442080(ai));
    if (!rec)
        return 0;
    int n = fn_80148024(rec);
    int slot = fn_80147F20(rec, fn_800B13D8r(*fn_80442080(ai)));
    return fn_80148D30(fn_80442080(ai), &t, dist, slot, n, out, 0, 0);
}

// Same around the target's facing, 8 slots; out falls back to the target's position.
extern "C" int fn_80149388(void *ai, float dist, Vector *out, int byCamera)
{
    if (!ai)
        return 0;
    Tgt &t = *fn_80134870t(ai);
    if (!&t)
        return 0;
    AiObj *rec = fn_801332C0(fn_80442080(ai));
    if (!rec)
        return 0;
    int n = 8;
    int slot = fn_80147F20(rec, fn_800B13D8r(*fn_80442080(ai)));
    Vector best;
    float bestDist = 3.4028235e38f;
    fn_8042DC84(&best, fn_800B1724v(t));
    Vector spot;
    if (fn_80148D30(fn_80442080(ai), &t, dist, slot, n, &spot, byCamera, 1)) {
        float d = fn_804290F8(&spot, fn_800B1724v(*fn_80442080(ai)));
        if (d < bestDist) {
            bestDist = d;
            fn_8042DC84(&best, &spot);
        }
    }
    fn_8042DC84(out, &best);
    return 1;
}
