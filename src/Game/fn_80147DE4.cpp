// Methods of the 0xDC-byte encounter record (AiObj): reset, lookups, init and the nearby-entity scan.
// docs/ai.md row 10. Float pool 0x8049B204 (extern_pool).

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
    int n; // +0x0
    int id[8]; // +0x4
    unsigned int time[8]; // +0x24
    int f44[8]; // +0x44
    int f64; // +0x64
    int n68; // +0x68
    int list[8]; // +0x6c
    int list8c[8]; // +0x8c
    int fAC; // +0xac
    int fB0[8]; // +0xb0
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
}

extern char lbl_80593BE8[];

extern "C" void fn_80147DE4(register AiObj *self)
{
    int i;
    for (i = 0; i < 8; i++) {
        self->id[i] = 0;
        self->fB0[i] = 0;
        self->time[i] = 0;
        self->f44[i] = 0;
    }
    int j;
    for (j = 0; j < 8; j++) {
        self->list[j] = 0;
        self->list8c[j] = 0;
    }
    self->fD4 = -1;
    self->owner = 0;
    self->radius = 0.0f;
    self->f64 = 0;
    self->n = 0;
    self->n68 = 0;
    self->fAC = 0;
}

extern "C" int fn_80147F20(register AiObj *self, int id)
{
    int i;
    for (i = 0; i < self->n; i++) {
        if (self->id[i] == id)
            return i;
    }
    return -1;
}

extern "C" int fn_80147FA4(register AiObj *self, int id)
{
    int i;
    for (i = 0; i < self->n; i++) {
        if (self->id[i] == id)
            return 1;
    }
    return 0;
}

extern "C" int fn_80148024(register AiObj *self)
{
    return self->n;
}

extern "C" int fn_80148050(register AiObj *self, int id)
{
    int i;
    for (i = 0; i < self->n68; i++) {
        if (self->list[i] == id)
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
        self->n = 0;
        self->n68 = 0;
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
        if (self->n < sizeof self->id / sizeof self->id[0]) {
            t = fn_800B18EC(*fn_800B14A0p(fn_800ACFA8(id)), 0xB7);
            self->id[self->n] = id;
            self->time[self->n] = fn_8042EFF8(lbl_80593BE8) + (t >> 1);
            fn_8008656C(e58, 1);
            self->n++;
        }
        if (!fn_800C9FD0(fn_80085954(e58))) {
            register void *v27 = fn_80085954(e58);
            register float f31 = fn_800B1884(e58, 0xDF);
            fn_800E89B0(v27, f31, fn_800B1884(e58, 2), 0, 0, 0);
        }
    }
}
