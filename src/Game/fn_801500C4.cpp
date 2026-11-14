// The AIObject+0xD0 record's methods, the base AIBrain and its task stack, the AI_NONE brain and its null task,
// two steering helpers and the base task (docs/ai.md row 3, section 4.4).
// Its float pool (0x8049B574-0x8049B604, orphan words where linkonce entries and lbl_8049B5D8 sit) stays in dtk's .rodata (extern_pool).

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

struct AITask;
struct BrainSelf;
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
PEnt *AI_GetEntity(void *a);
int fn_800B24AC(Ent &e);
int fn_800B1CC8(Ent &e);
int fn_80461714(void *a, int b);
int fn_8004A9CC(Vector *from, Vector *dir, float len, unsigned int mask, Placement *hit, int a, int b, int c, int d);
int fn_801370B0(void *a);
void *fn_8009C55C(void *a, int b, int c, float range, void *callback, void *user, int e);
int AI_GetActionPriority(void *a);
float AI_GetActionWeight(void *a);
void Task_Base_Destroy(void *task, int flags);
void BitSet_Init(void *timer);
void BitSet_Resize(void *timer, int a);
void BitSet_ClearAll(void *timer);
int fn_80085954(PEnt *e);
AITask *fn_8015105C(struct BrainSelf *brain, int id);
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
    int clear = !fn_8004A9CC(&from, &dir, len, 0x8000, 0, fn_800B24AC(*AI_GetEntity(target)), fn_80461714(a, 0), 0, 5);
    int color = 0xffff0000;
    if (clear)
        color = 0xff00ff00;
    return clear;
}

extern "C" int fn_801504BC(register Finder *self, Vector *out)
{
    void *found = fn_8009C55C(fn_800B1724(*AI_GetEntity(self->ai)), fn_800B1CC8(*AI_GetEntity(self->ai)),
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
    if (AI_GetActionPriority(x) < AI_GetActionPriority(y)) {
        return 1;
    } else if (AI_GetActionPriority(x) > AI_GetActionPriority(y)) {
        return -1;
    } else {
        if (AI_GetActionWeight(x) < AI_GetActionWeight(y)) {
            return 1;
        } else if (AI_GetActionWeight(x) > AI_GetActionWeight(y)) {
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
    struct AITask *cur; // +0x10
    unsigned int f14; // +0x14, task timer end
    int f18; // +0x18, task timer length
    char timer[8]; // +0x1C
    unsigned int count; // +0x24
    void *tasks[16]; // +0x28
    int f68; // +0x68, slots used
    int f6C; // +0x6C, next slot
    Slot slots[64]; // +0x70
    void *vtable; // +0x270
};

struct TaskData {
    void *ai; // +0x0
    void *brain; // +0x4, AI_GetBrain
    int target; // +0x8, target handle while covered
    char *name; // +0xC, lbl_804CFB58[id]
    char timer[8]; // +0x10
    int id; // +0x18
    int f1C; // +0x1C
    int f20; // +0x20
};

struct AITask : TaskData {
    virtual void v0();
    virtual void v1();
    virtual void update(); // +0x18, guess
    virtual int enter(); // +0x20, guess
    virtual void exit(); // +0x28, guess
};

struct BrainV {
    char d[0x270];
    virtual AITask *create(int id);
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
    BitSet_Init(self->timer);
    fn_80150820(self, ai);
    return self;
}

extern "C" void fn_80150820(register BrainSelf *self, void *ai)
{
    unsigned int i;
    self->ai = ai;
    self->entity = AI_GetEntity(self->ai);
    self->f8 = fn_80085954(self->entity);
    self->cur = 0;
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
    BitSet_Resize(self->timer, 2);
    BitSet_ClearAll(self->timer);
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
        Task_Base_Destroy(task, 3);
        return;
    }
}

extern "C" {
int AI_GetTaskDone(AITask *t);
void AI_RestoreTaskBehaviors(AITask *t);
void AI_SaveTaskBehaviors(AITask *t);
void fn_80152A78(TaskData *t);
void fn_80152A10(TaskData *t);
void fn_801515C4(BrainSelf *self, AITask *t);
void AI_DeferTaskDelete(BrainSelf *self, AITask *t);
void fn_801513D8(BrainSelf *self, int len);
int fn_80133A08(void);
void *fn_80133A30(void);
int fn_8015123C(BrainSelf *self, int id);
void *fn_80151BF8(BrainSelf *self);
}

extern "C" AITask *fn_8015105C(register BrainSelf *self, int id)
{
    while (self->cur && AI_GetTaskDone(self->cur))
        fn_8015123C(self, -1);
    if (self->count > 15)
        return 0;
    AITask *t = ((BrainV *)self)->create(id);
    if (!t)
        return 0;
    if (self->cur) {
        self->cur->exit();
        AI_RestoreTaskBehaviors(self->cur);
        fn_80152A78(self->cur);
        fn_801515C4(self, self->cur);
    }
    self->tasks[self->count++] = t;
    self->cur = t;
    AI_SaveTaskBehaviors(self->cur);
    fn_80152A10(self->cur);
    fn_801513D8(self, 0);
    int r = self->cur->enter();
    if (fn_80133A08()) {
        if (fn_80133A30() == self->ai) {
        }
    }
    return self->cur;
}

extern "C" int fn_8015123C(register BrainSelf *self, int id)
{
    if (self->count <= 1)
        return 0;
    AITask *t = (AITask *)self->tasks[self->count - 1];
    if (!t)
        return 0;
    t->exit();
    fn_80152A78(t);
    AI_RestoreTaskBehaviors(t);
    fn_801515C4(self, t);
    AI_DeferTaskDelete(self, t);
    self->tasks[--self->count] = 0;
    t = (AITask *)self->tasks[self->count - 1];
    self->cur = t;
    fn_80152A10(self->cur);
    AI_SaveTaskBehaviors(self->cur);
    fn_801513D8(self, 0);
    self->cur->enter();
    if (fn_80133A08()) {
        if (fn_80133A30() == self->ai) {
        }
    }
    return 1;
}

extern char lbl_80593BE8[];
extern "C" int fn_8042EFF8(void *p);
extern "C" int AI_GetTaskId(AITask *t);

extern "C" void fn_801513D8(register BrainSelf *self, int len)
{
    self->f18 = len;
    self->f14 = fn_8042EFF8(lbl_80593BE8) + len;
}

extern "C" int fn_80151430(register BrainSelf *self)
{
    if (self->f14)
        return 1;
    else
        return 0;
}

extern "C" int fn_80151470(register BrainSelf *self)
{
    return fn_8042EFF8(lbl_80593BE8) - self->f18;
}

extern "C" int fn_801514C0(register BrainSelf *self, int id)
{
    int i = self->f6C - 1;
    if (i < 0)
        i = self->f68 - 1;
    for (int n = 0; n < self->f68; n++) {
        if (self->slots[i].a == id)
            return fn_8042EFF8(lbl_80593BE8) - self->slots[i].b;
        if (--i < 0)
            i = self->f68 - 1;
    }
    return 100000;
}

extern "C" void fn_801515C4(register BrainSelf *self, AITask *t)
{
    Slot *s = &self->slots[self->f6C];
    s->a = AI_GetTaskId(t);
    s->b = fn_8042EFF8(lbl_80593BE8);
    if (++self->f6C >= sizeof(self->slots) / sizeof(Slot))
        self->f6C = 0;
    if (self->f68 < sizeof(self->slots) / sizeof(Slot))
        self->f68++;
}

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.text"); // 0x8049B580-0x8049B598, pool entries no function in the unit loads

extern "C" {
void *AI_GetActionQueue(void *ai);
void fn_801B6A98(void *list, void *compare);
void fn_801B67D8(void *list, int a);
int fn_801B6A44(void *list);
struct Goal *fn_801B5D3C(void *list, int i);
int AI_IsActionActive(void *e);
float AI_GetActionSpeed(void *e);
Vector *AI_GetActionMove(void *e);
unsigned int AI_GetActionControlCount(void *e);
int AI_GetActionControl(void *e, unsigned int i);
void AI_SetControllerAction(void *ai, int x);
int AI_GetActionMoveKind(void *e);
void fn_8042FE08(Vector *dst, Vector *src, float w);
void fn_80447C38(Vector *v);
void fn_80435530(Vector *v, float f);
void *AI_GetMover(void *ai);
void fn_8014B420(void *a, Vector *v);
void AI_FlushTaskDeletes(BrainSelf *self);
}

extern "C" int fn_80151674(register BrainSelf *self)
{
    void *list = AI_GetActionQueue(fn_80151BF8(self));
    fn_801B6A98(list, (void *)fn_80150590);
    fn_801B67D8(list, 0);
    Vector v;
    fn_80447C38(&v);
    float best = -99999.0f;
    for (int i = 0; i < fn_801B6A44(list); i++) {
        void *e = fn_801B5D3C(list, i);
        if (!e)
            continue;
        if (!AI_IsActionActive(e)) {
            if (AI_GetActionPriority(e) == 5) {
                best = AI_GetActionSpeed(e);
                fn_8042DC84(&v, AI_GetActionMove(e));
                break;
            }
            continue;
        }
        if (AI_GetActionSpeed(e) > best)
            best = AI_GetActionSpeed(e);
        if (AI_GetActionControlCount(e)) {
            for (unsigned int j = 0; j < AI_GetActionControlCount(e); j++) {
                int x = AI_GetActionControl(e, j);
                AI_SetControllerAction(fn_80151BF8(self), x);
            }
        }
        if (!AI_GetActionMoveKind(e) || AI_GetActionMoveKind(e) == 7) {
            float w = AI_GetActionWeight(e) + AI_GetActionSpeed(e);
            fn_8042FE08(&v, AI_GetActionMove(e), w);
        }
        if (AI_GetActionPriority(e) == 5) {
            fn_8042DC84(&v, AI_GetActionMove(e));
            break;
        }
    }
    fn_80435530(&v, best);
    fn_8014B420(AI_GetMover(fn_80151BF8(self)), &v);
    return 1;
}

extern "C" void fn_80151934(register BrainSelf *self)
{
    if (self->cur)
        self->cur->update();
    for (int i = self->count - 2; i >= 0; i--)
        ((AITask *)self->tasks[i])->update();
    if (self->f14 && fn_8042EFF8(lbl_80593BE8) >= self->f14)
        self->f14 = 0;
    if (self->cur) {
        while (AI_GetTaskDone(self->cur))
            fn_8015123C(self, AI_GetTaskId(self->cur));
    }
    AI_FlushTaskDeletes(self);
}

extern "C" int fn_80151A9C(register BrainSelf *self)
{
    if (!fn_80151674(self))
        return 0;
    fn_80151934(self);
    return 1;
}

extern "C" int fn_80151AF8(register BrainSelf *self, int id)
{
    for (int i = self->count - 1; i >= 0; i--) {
        if (AI_GetTaskId((AITask *)self->tasks[i]) == id)
            return 1;
    }
    return 0;
}

extern "C" int fn_80151B90(register BrainSelf *self, register AITask *t)
{
    return self->cur == t;
}

extern "C" AITask *fn_80151BCC(register BrainSelf *self)
{
    return self->cur;
}

extern "C" void *fn_80151BF8(register BrainSelf *self)
{
    return self->ai;
}

extern "C" unsigned int fn_80151C24(register BrainSelf *self)
{
    return self->count;
}

extern "C" void *fn_80151C50(register BrainSelf *self, register int i)
{
    return self->tasks[i];
}

extern "C" void *fn_80151C8C(register BrainSelf *self)
{
    return self->timer;
}

extern char lbl_804F5C98[];

extern "C" BrainSelf *fn_80151CB8(register BrainSelf *self, register void *ai)
{
    fn_801507C0(self, ai);
    self->vtable = (void *)lbl_804F5C98;
    return self;
}

struct TaskSelf : TaskData {
    void *vtable; // +0x24
};
extern char lbl_804F5C60[];
extern "C" TaskSelf *fn_8015294C(TaskSelf *self, void *ai, int id);

extern "C" TaskSelf *fn_80151D0C(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 1);
    self->vtable = (void *)lbl_804F5C60;
    return self;
}

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.text"); // 0x8049B5A0-0x8049B5B8, pool entries no function in the unit loads

extern "C" {
void *AI_GetTargetList(void *ai);
int fn_8014FCAC(void *a);
Ent *fn_8014FCD8(void *a, int i);
int fn_80085D3C(void *actor);
void *fn_80085980(Ent *e);
float fn_80426A84(void *p);
void fn_80067050(Ent &actor, Vector *out);
Vector *AI_GetMoverLookAhead(void *a);
void fn_80463F3C(void *a, int b);
void fn_8042D8A8(Vector *v, Vector *b);
void fn_8042F76C(Vector *v);
float fn_8042EBF4(Vector *a, Vector *b);
void fn_8042D854(Vector *v, Vector *b);
float fn_804290F8(Vector *a, Vector *b);
float *fn_8042FB28(Vector *v);
void fn_801BEC2C(Vector *v, Vector *rot);
float fn_8042CE28(int n);
void fn_8042FDBC(Vector *out, Vector *v, float f);
void fn_80463EF0(void *a, Vector *v);
}

inline void sn_label_decl() { clear:; } // clears the return flag fn_80151D0C set (prodg.md)

extern "C" int fn_80151D64(void *ai, Vector *out, float *weight)
{
    int n = fn_8014FCAC(AI_GetTargetList(ai));
    float radius = 1.2f;
    if (!fn_80085D3C(AI_GetEntity(ai)))
        radius = 2.0f;
    int hits = 0;
    fn_80447C38(out);
    *weight = 0.0f;
    PEnt *self = AI_GetEntity(ai);
    if (!self)
        return 0;
    float dt = fn_80426A84(lbl_80593BE8);
    Vector pos;
    Vector fwd;
    Vector vel;
    fn_8042DC84(&pos, (Vector *)fn_800B1724(*self));
    fn_80067050(*self, &fwd);
    fn_8042DC84(&vel, AI_GetMoverLookAhead(AI_GetMover(ai)));
    Vector from;
    Vector to;
    for (int i = 0; i < n; i++) {
        Ent *other = fn_8014FCD8(AI_GetTargetList(ai), i);
        if (!other)
            continue;
        if (other == fn_80134870(ai))
            continue;
        if (other == self)
            continue;
        if (!fn_80085980(other))
            continue;
        Vector opos;
        Vector ofwd;
        Vector ovel;
        fn_8042DC84(&opos, (Vector *)fn_800B1724(*other));
        fn_80067050(*other, &ofwd);
        fn_8042DC84(&ovel, AI_GetMoverLookAhead(AI_GetMover(fn_80085980(other))));
        Vector d;
        fn_80429038(&d, &opos, &pos);
        float dist = fn_8042EC54(&d);
        dist = dist > 0.1f ? dist : 0.1f;
        if (dist < 2.0f * radius) {
            float s = 1.0f - dist / (2.0f * radius);
            fn_80463F3C(AI_GetMover(ai), 1);
            Vector push;
            fn_8042DC84(&push, &pos);
            fn_8042D8A8(&push, &opos);
            fn_8042F76C(&push);
            float w = s;
            float dot = fn_8042EBF4(&push, &d);
            if (dot < -0.5f)
                w = 1.0f;
            fn_8042DC84(&from, &opos);
            fn_8042DC84(&to, &pos);
            from.z += 0.06f;
            to.z += 0.06f;
            fn_8042D854(out, &push);
            *weight += w;
            hits++;
        }
        float vdist = fn_804290F8(&vel, &opos);
        if (vdist < 2.0f * radius) {
            fn_80463F3C(AI_GetMover(ai), 1);
            Vector push;
            fn_8042DC84(&push, &d);
            fn_8042F76C(&push);
            float w = 1.0f - vdist / (2.0f * radius);
            Vector rot;
            fn_8042FB28(&rot)[2] = w * 90.0f;
            fn_8042FB28(&rot)[0] = 0.0f;
            fn_8042FB28(&rot)[1] = 0.0f;
            fn_801BEC2C(&push, &rot);
            fn_8042D854(out, &push);
            *weight += w;
            hits++;
            fn_8042DC84(&from, &opos);
            fn_8042DC84(&to, &vel);
            from.z += 0.06f;
            to.z += 0.06f;
        }
    }
    if (hits > 0) {
        fn_80435530(out, 1.0f / fn_8042CE28(hits));
        *weight /= fn_8042CE28(hits);
        Vector target;
        fn_8042FDBC(&target, out, *weight);
        fn_8042D854(&target, (Vector *)fn_800B1724(*self));
        fn_80463EF0(AI_GetMover(ai), &target);
        return 1;
    }
    return 0;
}

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.text"); // 0x8049B5D8-0x8049B5F0, the angles fn_8015243C copies from lbl_8049B5D8

struct Angles {
    float a[6];
};
extern const Angles lbl_8049B5D8; // 0, 90, 270, 120, 240, 360

struct Rec20 {
    int w[8];
};

struct Obstacle : Ent {
    char pad0[0x4C];
    Rec20 box; // +0x50
    char pad1[0x8];
    char f78[4]; // +0x78
};

extern "C" {
Vector *fn_800B1750(Ent &actor);
float fn_800B2670(Ent &actor);
int fn_801BA328(Vector *pos, Vector *dir, float range, void *a, Rec20 *box, float *t);
void fn_80429090(Vector *out, Vector *a, Vector *b, float t);
void fn_8042F838(Vector *out, Vector *v, float angle);
}

extern "C" int fn_8015243C(Ent *a, Obstacle *b, Vector *out)
{
    float dt = fn_80426A84(lbl_80593BE8);
    Vector pos;
    Vector v28;
    Vector fwd;
    fn_8042DC84(&pos, (Vector *)fn_800B1724(*a));
    fn_8042DC84(&fwd, fn_800B1750(*a));
    pos.z += 0.5f;
    Vector bpos;
    fn_8042DC84(&bpos, (Vector *)fn_800B1724(*b));
    Rec20 box = b->box;
    float size = fn_800B2670(*a);
    float t;
    fn_8042DC84(out, &fwd);
    float range = 2.0f * size;
    range = 3.0f;
    Angles angles = lbl_8049B5D8;
    int i = 0;
    int found = 0;
    while (fn_801BA328(&pos, out, range, b->f78, &box, &t)) {
        float angle = angles.a[i++];
        if (angle > 350.0f)
            break;
        found = 1;
        Vector hit;
        fn_80429090(&hit, &pos, out, t);
        fn_8042F838(out, &fwd, angle);
    }
    return found;
}

extern "C" {
void *AI_GetAvoidObject(void *ai);
int fn_800B0CC0(Ent *e);
int AI_GetMoverDestThing(void *a);
void AI_SetAvoidObject(void *ai, int a);
}

extern "C" Ent *fn_801526E4(void *ai, Vector *out, float *weight)
{
    int n = fn_801500C4((Finder *)AI_GetTargetList(ai));
    int unused = 0;
    fn_80447C38(out);
    *weight = 0.0f;
    PEnt *self = AI_GetEntity(ai);
    if (!self)
        return 0;
    Ent *e;
    if (AI_GetAvoidObject(ai)) {
        e = fn_800ACFA8((int)AI_GetAvoidObject(ai));
        if (e) {
            Vector v;
            int r = fn_8015243C(self, (Obstacle *)e, &v);
            if (r) {
                fn_8042DC84(out, &v);
                *weight = 1.0f;
                return e;
            }
        } else {
            AI_SetAvoidObject(ai, 0);
        }
    }
    for (int i = 0; i < n; i++) {
        e = (Ent *)fn_801500F0((Finder *)AI_GetTargetList(ai), i);
        if (!e)
            continue;
        if (!fn_800B0CC0(e))
            continue;
        if (fn_800B13D8(e) == AI_GetMoverDestThing(AI_GetMover(ai)))
            continue;
        if (e == fn_80134870(ai))
            continue;
        Vector v;
        int r = fn_8015243C(self, (Obstacle *)e, &v);
        if (r) {
            fn_8042DC84(out, &v);
            *weight = 1.0f;
            return e;
        }
    }
    return 0;
}

extern char lbl_804F5CC8[];
extern char *lbl_804CFB58[]; // task names by id, "TASK_SLEEP"...
extern "C" {
void *AI_GetBrain(void *ai);
void fn_80463AB4(TaskSelf *self);
}

extern "C" TaskSelf *fn_8015294C(register TaskSelf *self, void *ai, int id)
{
    self->vtable = (void *)lbl_804F5CC8;
    BitSet_Init(self->timer);
    if (!ai) {
        goto done;
        return self;
    }
    self->ai = ai;
    self->brain = AI_GetBrain(self->ai);
    self->id = id;
    self->f1C = 0;
    self->f20 = 0;
    self->name = lbl_804CFB58[id];
    fn_80463AB4(self);
done:
    return self;
}

extern "C" void fn_80152A10(register TaskData *self)
{
    Ent *t = fn_80134870(self->ai);
    if (t)
        self->target = fn_800B13D8(t);
    else
        self->target = 0;
}

extern "C" void fn_80152A78(register TaskData *self)
{
    if (self->target) {
        Ent *t = fn_800ACFA8(self->target);
        if (t)
            fn_801501AC((Finder *)AI_GetTargetList(self->ai), t);
    }
}
