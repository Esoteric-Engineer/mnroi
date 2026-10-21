// The AIObject+0xD0 record's methods, the AI_NONE brain's factory and task, the base AIBrain. Its float pool (1.5f, 2.0f, 20.0f) stays in dtk's .rodata (extern_pool).

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

class Placement {
public:
    char d[0x40];
    Placement();
};

struct Ent {
    int pad;
};

struct PEnt : Ent { // matching_notes 44
    int x;
};

struct Finder {
    void *ai; // +0x0
    char pad0[0x44];
    int count; // +0x48
    int handles[16]; // +0x4C
    char pad1[0x58];
    int handle; // +0xE4
};

struct Task28 {
    char d[0x28];
    Task28(void *brain) __asm__("fn_80151D0C");
};

extern "C" {
Ent *fn_800ACFA8(int handle);
void *fn_800B14A0(Ent *node);
int fn_800B13D8(Ent *actor);
Vector *fn_80444688(void *a);
void fn_8042DC84(Vector *dst, Vector *src);
void *fn_800B1724(Ent &node);
void fn_80429038(Vector *out, Vector *a, Vector *b);
float fn_8042EC54(Vector *v);
Ent *fn_80134870(void *a);
PEnt *fn_80442080(void *a);
int fn_800B24AC(Ent &e);
int fn_800B1CC8(Ent &e);
int fn_80461714(void *a, int b);
int fn_8004A9CC(Vector *from, Vector *dir, float len, unsigned int mask, Placement *hit, int a, int b, int c, int d);
int fn_801370B0(void *a);
void *fn_8009C55C(void *a, int b, int c, float range, void *callback, void *user, int e);
int fn_80463BCC(void *a);
float fn_80463BF8(void *a);
void fn_80463A44(void *task, int flags);
void fn_804617F0(void *timer);
void fn_80461828(void *timer, int a);
void fn_804618B0(void *timer);
int fn_80085954(PEnt *e);
void fn_8015105C(void *brain, int id);
}
extern char lbl_804F5CB0[];
struct BrainSelf;
extern "C" void fn_80150820(BrainSelf *self, void *ai);
extern "C" void *fn_80150AA8(BrainSelf *self, int id);
extern "C" void fn_80150FFC(BrainSelf *self, void *task);

extern "C" int fn_801500C4(register Finder *self)
{
    return self->count;
}

extern "C" void *fn_801500F0(register Finder *self, int i)
{
    if (i < 0 && i >= self->count)
        return 0;
    int h = self->handles[i];
    if (!h)
        return 0;
    Ent *e = fn_800ACFA8(h);
    if (e)
        return fn_800B14A0(e);
    return 0;
}

extern "C" void fn_801501AC(register Finder *self, Ent *actor)
{
    if (!actor)
        return;
    self->handle = fn_800B13D8(actor);
}

extern "C" Ent *fn_80150200(register Finder *self)
{
    if (!self->handle)
        return 0;
    return fn_800ACFA8(self->handle);
}

extern "C" int fn_80150258(register Finder *self)
{
    if (!self->handle)
        return 0;
    if (fn_800ACFA8(self->handle)) {
        return 1;
    } else {
        self->handle = 0;
        return 0;
    }
}

extern "C" int fn_801502CC(void *a, void *b, short c, void *user)
{
    Vector from;
    Vector to;
    Ent *target = (Ent *)user;
    if (!target)
        return 0;
    Ent *t = fn_80134870(target);
    if (!t)
        return 0;
    fn_8042DC84(&from, fn_80444688(a));
    fn_8042DC84(&to, (Vector *)fn_800B1724(*t));
    from.z += 1.5f;
    to.z += 1.5f;
    Vector dir;
    fn_80429038(&dir, &to, &from);
    float len = fn_8042EC54(&dir);
    len -= 2.0f;
    Placement hit;
    int clear = !fn_8004A9CC(&from, &dir, len, 0x8000, 0, fn_800B24AC(*fn_80442080(target)), fn_80461714(a, 0), 0, 5);
    int color = 0xffff0000;
    if (clear)
        color = 0xff00ff00;
    return clear;
}

extern "C" int fn_801504BC(register Finder *self, Vector *out)
{
    void *found = fn_8009C55C(fn_800B1724(*fn_80442080(self->ai)), fn_800B1CC8(*fn_80442080(self->ai)),
                              fn_801370B0(self->ai), 20.0f, (void *)fn_801502CC, self->ai, -1);
    if (found) {
        fn_8042DC84(out, fn_80444688(found));
        return 1;
    }
    return 0;
}

extern "C" int fn_80150590(void *a, void *b)
{
    if (!a || !b)
        return 0;
    void *x = a;
    void *y = b;
    if (fn_80463BCC(x) < fn_80463BCC(y)) {
        return 1;
    } else if (fn_80463BCC(x) > fn_80463BCC(y)) {
        return -1;
    } else {
        if (fn_80463BF8(x) < fn_80463BF8(y)) {
            return 1;
        } else if (fn_80463BF8(x) > fn_80463BF8(y)) {
            return -1;
        }
        return 0;
    }
}

struct Slot {
    int a; // +0x0
    int b; // +0x4
};

struct BrainSelf {
    void *ai; // +0x0
    PEnt *entity; // +0x4
    int f8; // +0x8
    void *task; // +0xC
    int f10; // +0x10
    int f14; // +0x14
    char pad0[4];
    char timer[8]; // +0x1C
    unsigned int count; // +0x24
    void *tasks[16]; // +0x28
    int f68; // +0x68
    int f6C; // +0x6C
    Slot slots[64]; // +0x70
    void *vtable; // +0x270
};

extern "C" void *fn_801506B4(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case 1:
        task = new Task28(self->ai);
        break;
    default:
        return fn_80150AA8(self, id);
    }
    return task;
}

extern "C" int fn_80150748(register void *self)
{
    return 1;
}

extern "C" int fn_80150770(register void *self)
{
    return 1;
}

extern "C" int fn_80150798(register void *self)
{
    return 1;
}

extern "C" BrainSelf *fn_801507C0(register BrainSelf *self, void *ai)
{
    self->vtable = (void *)lbl_804F5CB0;
    fn_804617F0(self->timer);
    fn_80150820(self, ai);
    return self;
}

extern "C" void fn_80150820(register BrainSelf *self, void *ai)
{
    unsigned int i;
    self->ai = ai;
    self->entity = fn_80442080(self->ai);
    self->f8 = fn_80085954(self->entity);
    self->f10 = 0;
    self->count = 0;
    for (i = 0; i <= 15; i++)
        self->tasks[i] = 0;
    self->f14 = 0;
    self->task = 0;
    for (i = 0; i <= 63; i++) {
        self->slots[i].a = -1;
        self->slots[i].b = 0;
    }
    self->f68 = 0;
    self->f6C = 0;
    fn_80461828(self->timer, 2);
    fn_804618B0(self->timer);
}

extern "C" void fn_80150960(register BrainSelf *self)
{
    self->task = 0;
    fn_8015105C(self, 0);
    return;
}

extern "C" void fn_801509A8(register BrainSelf *self)
{
    for (unsigned int i = 0; i < self->count; i++) {
        if (self->tasks[i]) {
            fn_80150FFC(self, self->tasks[i]);
            self->tasks[i] = 0;
        }
    }
    self->count = 0;
}

extern "C" void fn_80150A5C(register BrainSelf *self)
{
    fn_801509A8(self);
    fn_80150820(self, self->ai);
    fn_80150960(self);
}

struct Task00 {
    char d[0x28];
    Task00(void *ai) __asm__("fn_8015D950");
};
struct Task01 {
    char d[0x28];
    Task01(void *ai) __asm__("fn_8015D9A8");
};
struct Task02 {
    char d[0x28];
    Task02(void *ai) __asm__("fn_8015DA00");
};
struct Task03 {
    char d[0x2C];
    Task03(void *ai) __asm__("fn_8015DA58");
};
struct Task04 {
    char d[0x28];
    Task04(void *ai) __asm__("fn_8015DAB0");
};
struct Task05 {
    char d[0x28];
    Task05(void *ai) __asm__("fn_8015DB08");
};
struct Task06 {
    char d[0x28];
    Task06(void *ai) __asm__("fn_8015DB60");
};
struct Task07 {
    char d[0x28];
    Task07(void *ai) __asm__("fn_8015DBB8");
};
struct Task08 {
    char d[0x28];
    Task08(void *ai) __asm__("fn_8015DC10");
};
struct Task09 {
    char d[0x28];
    Task09(void *ai) __asm__("fn_8015DC68");
};
struct Task0A {
    char d[0x28];
    Task0A(void *ai) __asm__("fn_8015DCC0");
};
struct Task0B {
    char d[0x40];
    Task0B(void *ai) __asm__("fn_8015DD18");
};
struct Task0C {
    char d[0x28];
    Task0C(void *ai) __asm__("fn_8015DD7C");
};
struct Task0D {
    char d[0x28];
    Task0D(void *ai) __asm__("fn_8015DDD4");
};
struct Task0E {
    char d[0x28];
    Task0E(void *ai) __asm__("fn_8015DE2C");
};
struct Task0F {
    char d[0x28];
    Task0F(void *ai) __asm__("fn_8015DE84");
};
struct Task10 {
    char d[0x28];
    Task10(void *ai) __asm__("fn_8015DEDC");
};
struct Task11 {
    char d[0x30];
    Task11(void *ai) __asm__("fn_8015DF34");
};
struct Task12 {
    char d[0x28];
    Task12(void *ai) __asm__("fn_8015DF8C");
};
struct Task13 {
    char d[0x30];
    Task13(void *ai) __asm__("fn_8015DFE4");
};
struct Task14 {
    char d[0x2C];
    Task14(void *ai) __asm__("fn_8015E03C");
};
struct Task15 {
    char d[0x28];
    Task15(void *ai) __asm__("fn_8015E094");
};
struct Task16 {
    char d[0x28];
    Task16(void *ai) __asm__("fn_8015E0EC");
};
struct Task17 {
    char d[0x28];
    Task17(void *ai) __asm__("fn_8015E144");
};
struct Task18 {
    char d[0x2C];
    Task18(void *ai) __asm__("fn_8015E19C");
};
struct Task19 {
    char d[0x28];
    Task19(void *ai) __asm__("fn_8015E1F4");
};
struct Task1A {
    char d[0x30];
    Task1A(void *ai) __asm__("fn_8015E24C");
};
struct Task1B {
    char d[0x28];
    Task1B(void *ai) __asm__("fn_8015E2A4");
};

extern "C" void *fn_80150AA8(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case 0:
        task = new Task00(self->ai);
        break;
    case 1:
        task = new Task01(self->ai);
        break;
    case 2:
        task = new Task02(self->ai);
        break;
    case 3:
        task = new Task03(self->ai);
        break;
    case 4:
        task = new Task04(self->ai);
        break;
    case 5:
        task = new Task05(self->ai);
        break;
    case 6:
        task = new Task06(self->ai);
        break;
    case 7:
        task = new Task07(self->ai);
        break;
    case 8:
        task = new Task08(self->ai);
        break;
    case 9:
        task = new Task09(self->ai);
        break;
    case 10:
        task = new Task0A(self->ai);
        break;
    case 11:
        task = new Task0B(self->ai);
        break;
    case 12:
        task = new Task0C(self->ai);
        break;
    case 13:
        task = new Task0D(self->ai);
        break;
    case 14:
        task = new Task0E(self->ai);
        break;
    case 15:
        task = new Task0F(self->ai);
        break;
    case 16:
        task = new Task10(self->ai);
        break;
    case 17:
        task = new Task11(self->ai);
        break;
    case 18:
        task = new Task12(self->ai);
        break;
    case 19:
        task = new Task13(self->ai);
        break;
    case 20:
        task = new Task14(self->ai);
        break;
    case 21:
        task = new Task15(self->ai);
        break;
    case 22:
        task = new Task16(self->ai);
        break;
    case 23:
        task = new Task17(self->ai);
        break;
    case 24:
        task = new Task18(self->ai);
        break;
    case 25:
        task = new Task19(self->ai);
        break;
    case 26:
        task = new Task1A(self->ai);
        break;
    case 27:
        task = new Task1B(self->ai);
        break;
    }
    return task;
}

extern "C" void fn_80150FFC(register BrainSelf *self, void *task)
{
    if (!task)
        return;
    if (task) {
        fn_80463A44(task, 3);
        return;
    }
}
