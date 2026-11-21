// AI script API: resolve a script handle to an actor's AIObject (fn_8007A3A0) and forward one call to it; docs/ai.md row 8.
// Reads .rodata from 0x80487E88 (extern_pool); the orphan words are pool entries no function here loads.

extern "C" {

void *fn_800ACFA8(int handle);
int fn_800B0C58(void *actor);
void *fn_800B14A0(void *actor);
void *fn_80085980(void *x);
void *AI_GetBrain(void *ai);
void *fn_80151BCC(void *brain);
int AI_GetTaskId(void *task);
void *fn_8015105C(void *brain, int id);
int fn_8015123C(void *brain, int id);
void *AI_GetMover(void *ai);
void *AI_GetPath(void *mover);
void *AI_GetTargetList(void *ai);
void fn_8014B518(void *mover, void *pos, int index);
void fn_8014D034(void *x);
void fn_8042DC84(void *dst, void *src);
int fn_800B0CC0(void *actor);
int fn_800B13D8(void *actor);
void fn_801501AC(void *list, void *actor);
void fn_80152A10(void *task);
void fn_8014B63C(void *mover, int id, int b);

struct Waypoint { // 0x30
    char pad0[0x10];
    char pos[0x20]; // +0x10
};

struct WaypointOwner {
    char pad0[0x144];
    unsigned int count; // +0x144
    Waypoint *list; // +0x148
};

WaypointOwner *AI_GetEntity(void *ai);

int fn_80151AF8(void *brain, int id);
void fn_80442414(void *task, int v);
void *AI_GetActor(void *ai);
int fn_800F63DC(void *actor, int a, int b);

struct TaskData {
    char pad0[0x24];
};

struct AITask : TaskData {
    virtual void v0();
    virtual void v1();
    virtual void update(); // +0x18, guess
    virtual int enter(); // +0x20, guess
    virtual void exit(); // +0x28, guess
};

struct RangedOnlyTask : AITask { // id 0x14
    int f28; // +0x28
};

struct ThrowAtTask : AITask { // ids 0x11 and 0x1A
    int what; // +0x28, script handle
    int at; // +0x2C, script handle
};

class ScriptActor
{
public:
    char d[0x3ac];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(int v); // +0x30
    virtual void s6(int v); // +0x38
};
struct ScriptActorD : ScriptActor { // matching_notes 44
    int x;
};

RangedOnlyTask *fn_8015105CR(void *brain, int id) __asm__("fn_8015105C");
ScriptActorD *fn_8044203CA(void *ai) __asm__("AI_GetActor");

struct Ent {
    int pad;
};
struct PlayerEnt : Ent { // matching_notes 44
    int x;
};

PlayerEnt *fn_80442080P(void *ai) __asm__("AI_GetEntity");
void fn_8009AEC8(Ent &actor, int v);
void fn_8009AF28(Ent &actor);
int fn_80097CE8(Ent &actor, int a, int mode, float speed, int set, float blend, float f);
void fn_800BD2D0(void *actor, int clip);
void fn_80133878(int a, int b);
void fn_801338C0(int a, int b);
void fn_80133908(int a);
void fn_801343B0(void *ai);
void AI_EnableBehavior(void *ai, int v);
void fn_80442208(void *ai, float v);
void fn_80442230(void *ai, float v);
void fn_80442258(void *ai, float v);
void fn_80442280(void *ai, float v);
void fn_804422A8(void *ai, float v);
void fn_804422D0(void *ai, float v);
void fn_804422F8(void *ai, float v);
void fn_80442320(void *ai, float v);
void fn_80442348(void *ai, float v);
void fn_80442370(void *ai, float v);
void fn_80442398(void *ai, float v);
void fn_804423C0(void *ai, float v);

struct PlayAnimTask : AITask { // id 0x13
    int anim; // +0x28
    int f2c; // +0x2C
};

PlayAnimTask &fn_8015105CA(void *brain, int id) __asm__("fn_8015105C");

int fn_80086B6C(void *x);
void fn_80086BFC(void *x, int on);
void fn_8009DF60(void *x, int v);
void fn_8009E09C(void *x);
void fn_80086938(void *x, int v);
void fn_80133AE4(int v);
void fn_80133B94(void *x, int a, int b, int c);
void fn_80133B0C(float v);
void fn_80133B34(float v);
int fn_80085F7C(void *x);
int fn_8008606C(void *x);
void fn_80135668(void *ai, int on);

float fn_80086980(void *x);
void fn_800869AC(void *x, float v);
void fn_800B1950(Ent &actor, int v);

struct HoverTask : AITask { // id 0x18
    int f28; // +0x28
};

HoverTask &fn_8015105CH(void *brain, int id) __asm__("fn_8015105C");
void AI_DisableBehavior(void *ai, unsigned int bit);
void fn_80086490(void *x, int v);
void fn_800864C0(void *x, int v);
int fn_800ACFA8I(int handle) __asm__("fn_800ACFA8");
PlayerEnt *fn_80085954(void *actor);
int fn_800CCF90(Ent &x);
int fn_800B0C1C(void *actor);
void fn_800B9CE8(Ent &actor, int a, void *b, void *c);
PlayerEnt *fn_8044203CP(void *ai) __asm__("AI_GetActor");

struct MoveTask {
    char pad0[0x30];
    char dest[0x10]; // +0x30
};

void *fn_8007A3A0(int handle)
{
    void *actor = fn_800ACFA8(handle);
    if (actor == 0)
        return 0;
    if (!fn_800B0C58(actor))
        return 0;
    void *x = fn_800B14A0(actor);
    void *ai = fn_80085980(x);
    if (ai == 0) {
    }
    return ai;
}

void fn_8007A448(int handle)
{
    void *ai = fn_8007A3A0(handle);
    if (ai == 0)
        return;
    void *brain = AI_GetBrain(ai);
    void *task = fn_80151BCC(brain);
    if (task != 0 && AI_GetTaskId(task) == 6) {
        return;
    } else {
        if (fn_8015105C(brain, 6))
            return;
    }
}

void fn_8007A4FC(int handle)
{
    void *ai = fn_8007A3A0(handle);
    if (ai == 0)
        return;
    void *brain = AI_GetBrain(ai);
    while (fn_80151BCC(brain) != 0 && AI_GetTaskId(fn_80151BCC(brain)) != 6) {
        if (fn_8015123C(brain, -1)) {
        } else {
            return;
        }
    }
    if (fn_80151BCC(brain))
        fn_8015123C(brain, -1);
}

void fn_8007A5DC(int handle)
{
    void *ai = fn_8007A3A0(handle);
    if (ai == 0)
        return;
    void *brain = AI_GetBrain(ai);
    if (fn_8015105C(brain, 14))
        return;
}

void fn_8007A658(int handle)
{
    void *ai = fn_8007A3A0(handle);
    if (ai == 0)
        return;
    void *brain = AI_GetBrain(ai);
    while (fn_80151BCC(brain) != 0 && AI_GetTaskId(fn_80151BCC(brain)) != 14) {
        if (fn_8015123C(brain, -1)) {
        } else {
            return;
        }
    }
    if (fn_80151BCC(brain))
        fn_8015123C(brain, -1);
}

void fn_8007A738(int handle, void *pos)
{
    void *ai = fn_8007A3A0(handle);
    if (ai == 0)
        return;
    void *brain = AI_GetBrain(ai);
    void *task = fn_8015105C(brain, 11);
    if (task) {
        MoveTask *t = (MoveTask *)task;
        fn_8014B518(AI_GetMover(ai), pos, -1);
        fn_8014D034(AI_GetPath(AI_GetMover(ai)));
        fn_8042DC84(t->dest, pos);
        return;
    }
}

void fn_8007A818(int handle, unsigned int index)
{
    void *ai = fn_8007A3A0(handle);
    if (ai == 0)
        return;
    if (index >= AI_GetEntity(ai)->count)
        return;
    Waypoint *w = &AI_GetEntity(ai)->list[index];
    if (w == 0)
        return;
    void *brain = AI_GetBrain(ai);
    void *task = fn_8015105C(brain, 11);
    if (task) {
        MoveTask *t = (MoveTask *)task;
        fn_8014B518(AI_GetMover(ai), w->pos, index);
        fn_8014D034(AI_GetPath(AI_GetMover(ai)));
        fn_8042DC84(t->dest, w->pos);
        return;
    }
}

void fn_8007A958(int handle, int target)
{
    void *ai = fn_8007A3A0(handle);
    if (ai == 0)
        return;
    void *other = fn_800ACFA8(target);
    if (other == 0)
        return;
    if (!fn_800B0CC0(other) && !fn_800B0C58(other))
        return;
    fn_801501AC(AI_GetTargetList(ai), other);
    void *brain = AI_GetBrain(ai);
    void *task = fn_8015105C(brain, 9);
    if (task) {
        fn_801501AC(AI_GetTargetList(ai), other);
        fn_80152A10(task);
        fn_8014B63C(AI_GetMover(ai), fn_800B13D8(other), 0);
        return;
    }
}

void fn_8007AA8C(int handle, int v)
{
    void *ai = fn_8007A3A0(handle);
    if (ai == 0)
        return;
    RangedOnlyTask *task = fn_8015105CR(AI_GetBrain(ai), 0x14);
    if (task) {
        task->f28 = v;
        task->enter();
        return;
    }
}

inline void sn_label_decl() { clear:; } // the pair from fn_8007AB50 on (prodg.md)

void fn_8007AB50(int handle)
{
    void *ai = fn_8007A3A0(handle);
    if (ai)
        fn_8044203CA(ai)->s5(18);
}

void fn_8007ABE8(int handle, int target)
{
    void *ai = fn_8007A3A0(handle);
    if (ai == 0)
        return;
    fn_801501AC(AI_GetTargetList(ai), fn_800ACFA8(target));
}

int fn_8007AC68(int handle, int a, int b)
{
    void *ai = fn_8007A3A0(handle);
    if (ai == 0 || AI_GetActor(ai) == 0)
        return 0;
    return fn_800F63DC(AI_GetActor(ai), a, b);
}

int fn_8007AD0C(int handle, int what, int at)
{
    void *ai = fn_8007A3A0(handle);
    if (ai == 0)
        return 0;
    void *a = fn_800ACFA8(what);
    if (a == 0)
        return 0;
    void *b = fn_800ACFA8(at);
    if (b == 0)
        return 0;
    void *brain = AI_GetBrain(ai);
    if (fn_80151AF8(AI_GetBrain(ai), 0x11) == 0) {
        void *task = fn_8015105C(brain, 0x11);
        if (task) {
            fn_801501AC(AI_GetTargetList(ai), a);
            fn_8014B63C(AI_GetMover(ai), fn_800B13D8(a), 0);
            ThrowAtTask *t = (ThrowAtTask *)task;
            t->what = what;
            t->at = at;
            fn_80442414(t, 0);
            return 1;
        } else {
            return 0;
        }
    }
    return 1;
}

int fn_8007AE94(int handle, int what, int at)
{
    void *ai = fn_8007A3A0(handle);
    if (ai == 0)
        return 0;
    void *a = fn_800ACFA8(what);
    if (a == 0)
        return 0;
    void *b = fn_800ACFA8(at);
    if (b == 0)
        return 0;
    void *brain = AI_GetBrain(ai);
    if (fn_80151AF8(AI_GetBrain(ai), 0x1A) == 0) {
        void *task = fn_8015105C(brain, 0x1A);
        if (task) {
            fn_801501AC(AI_GetTargetList(ai), a);
            fn_8014B63C(AI_GetMover(ai), fn_800B13D8(a), 0);
            ThrowAtTask *t = (ThrowAtTask *)task;
            t->what = what;
            t->at = at;
            fn_80442414(t, 0);
            return 1;
        } else {
            return 0;
        }
    }
    return 1;
}

void fn_8007B01C(int a, int b)
{
    fn_80133878(a, b);
}

void fn_8007B064(int a, int b)
{
    fn_801338C0(a, b);
}

void fn_8007B0AC(int a)
{
    fn_80133908(a);
}

void fn_8007B0EC(int handle, int anim, int b, int mode)
{
    void *ai = fn_8007A3A0(handle);
    if (ai == 0)
        return;
    void *brain = AI_GetBrain(ai);
    if (fn_80151AF8(brain, 0x13))
        return;
    PlayAnimTask &task = fn_8015105CA(brain, 0x13);
    if (&task) {
        task.anim = anim;
        task.f2c = b;
        fn_8044203CA(ai)->s6(0x24);
        fn_8009AEC8(*fn_80442080P(ai), 0);
        if (mode == 1)
            fn_8009AF28(*fn_80442080P(ai));
        unsigned int clip = fn_80097CE8(*fn_80442080P(ai), anim, mode, 30.0f, 0, 7.5f, -1.0f);
        fn_800BD2D0(AI_GetActor(ai), clip);
    } else {
    }
}

void fn_8007B288(int handle)
{
    void *ai = fn_8007A3A0(handle);
    if (ai == 0)
        return;
    fn_801343B0(ai);
}

void fn_8007B2E8(int handle, int which, float v)
{
    void *ai = fn_8007A3A0(handle);
    if (ai == 0)
        return;
    if (v < 0.0f)
        v = 0.0f;
    if (v > 100.0f)
        v = 100.0f;
    switch (which) {
    case 0:
        fn_80442230(ai, v);
        break;
    case 1:
        fn_80442208(ai, v);
        break;
    case 2:
        fn_80442258(ai, v);
        break;
    case 3:
        fn_80442280(ai, v);
        break;
    case 4:
        fn_804422A8(ai, v);
        break;
    case 5:
        fn_804422D0(ai, v);
        break;
    case 6:
        fn_80442320(ai, v);
        break;
    case 7:
        fn_80442348(ai, v);
        break;
    case 8:
        fn_80442370(ai, v);
        break;
    case 9:
        fn_80442398(ai, v);
        break;
    case 10:
        fn_804423C0(ai, v);
        break;
    case 11:
        fn_804422F8(ai, v);
        break;
    default:
        break;
    }
}

void fn_8007B4D8(int handle, int v)
{
    void *ai = fn_8007A3A0(handle);
    if (ai == 0)
        return;
    AI_EnableBehavior(ai, v);
}

void fn_8007B540(int handle, int on, int b)
{
    void *actor = fn_800ACFA8(handle);
    if (actor == 0)
        return;
    if (fn_800B0C58(actor)) {
        void *x = fn_800B14A0(actor);
        if (fn_80086B6C(x) && on == 1)
            return;
        fn_80086BFC(x, on);
        if (on)
            fn_8009DF60(x, b);
        else
            fn_8009E09C(x);
    }
}

void fn_8007B618(int handle, int v)
{
    void *actor = fn_800ACFA8(handle);
    if (actor == 0)
        return;
    if (fn_800B0C58(actor)) {
        void *x = fn_800B14A0(actor);
        fn_80086938(x, v);
    }
}

void fn_8007B6A4(int v)
{
    fn_80133AE4(v);
}

void fn_8007B6E4(int handle, int a, int b, int c)
{
    void *actor = fn_800ACFA8(handle);
    if (actor && fn_800B0C58(actor)) {
        void *x = fn_800B14A0(actor);
        fn_80133B94(x, a, b, c);
    }
}

void fn_8007B77C(float v)
{
    fn_80133B0C(v);
}

void fn_8007B7BC(float v)
{
    fn_80133B34(v);
}

void fn_8007B7FC(int handle, int v)
{
    void *actor = fn_800ACFA8(handle);
    if (actor && fn_800B0C58(actor)) {
        void *x = fn_800B14A0(actor);
        if (!fn_80085F7C(x) && !fn_8008606C(x))
            return;
        void *ai = fn_80085980(x);
        if (ai)
            fn_80135668(ai, 1);
    }
}

void fn_8007B8CC(int a, int b)
{
}

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.text"); // 0x80487E9C-0x80487EA8, pool entries no function in the unit loads

float fn_8007B8F8(int handle)
{
    void *actor = fn_800ACFA8(handle);
    if (actor == 0)
        return 0.0f;
    if (!fn_800B0C58(actor))
        return 0.0f;
    return fn_80086980(fn_800B14A0(actor));
}

void fn_8007B998(int handle, float v)
{
    void *actor = fn_800ACFA8(handle);
    if (actor == 0)
        return;
    if (!fn_800B0C58(actor))
        return;
    fn_800869AC(fn_800B14A0(actor), v);
}

void fn_8007BA24(int handle, int v)
{
    void *ai = fn_8007A3A0(handle);
    if (ai == 0)
        return;
    fn_800B1950(*fn_80442080P(ai), v);
    fn_801343B0(ai);
}

void fn_8007BAA0(int handle)
{
    void *ai = fn_8007A3A0(handle);
    if (ai == 0)
        return;
    void *brain = AI_GetBrain(ai);
    if (fn_8015105C(brain, 0x16)) {
    } else {
    }
}

void fn_8007BB24(int handle)
{
    void *ai = fn_8007A3A0(handle);
    if (ai == 0)
        return;
    void *brain = AI_GetBrain(ai);
    if (fn_80151AF8(brain, 0x16)) {
        fn_8015123C(brain, 0x16);
    } else {
    }
}

void fn_8007BBB4(int handle)
{
    void *ai = fn_8007A3A0(handle);
    if (ai == 0)
        return;
    void *brain = AI_GetBrain(ai);
    if (fn_8015105C(brain, 0x17)) {
    } else {
    }
}

void fn_8007BC38(int handle)
{
    void *ai = fn_8007A3A0(handle);
    if (ai == 0)
        return;
    void *brain = AI_GetBrain(ai);
    if (fn_80151AF8(brain, 0x17)) {
        fn_8015123C(brain, 0x17);
    } else {
    }
}

void fn_8007BCC8(int handle, int keep)
{
    void *ai = fn_8007A3A0(handle);
    if (ai == 0)
        return;
    void *brain = AI_GetBrain(ai);
    HoverTask &task = fn_8015105CH(brain, 0x18);
    if (&task) {
        task.f28 = 1;
        if (keep == 0)
            AI_DisableBehavior(ai, 9);
    } else {
    }
}

void fn_8007BD7C(int handle)
{
    void *ai = fn_8007A3A0(handle);
    if (ai == 0)
        return;
    void *brain = AI_GetBrain(ai);
    if (fn_80151AF8(brain, 0x18)) {
        fn_8015123C(brain, 0x18);
    } else {
    }
}

void fn_8007BE0C(int handle, int on)
{
    void *ai = fn_8007A3A0(handle);
    if (ai == 0)
        return;
    if (on)
        fn_80086490(AI_GetEntity(ai), 1);
    else
        fn_800864C0(AI_GetEntity(ai), 1);
}

int fn_8007BEA8(int handle)
{
    Ent *actor = (Ent *)(PlayerEnt *)fn_800ACFA8I(handle);
    if (actor == 0)
        return 0;
    if (!fn_800B0C58(actor))
        return 0;
    return fn_800CCF90(*fn_80085954(actor));
}

int fn_8007BF40(int handle, int a, int hb, int hc)
{
    void *ai = fn_8007A3A0(handle);
    if (ai == 0)
        return 0;
    if (AI_GetActor(ai) == 0)
        return 0;
    void *b = fn_800ACFA8(hb);
    Ent *c = (Ent *)(PlayerEnt *)fn_800ACFA8I(hc);
    if (c && !fn_800B0C1C(c))
        c = 0;
    fn_800B9CE8(*fn_8044203CP(ai), a, b, c);
    return 1;
}

}

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.text"); // 0x80487EAC-0x80487EC8, five zeros and "invalid"

extern "C" {

struct ScriptHActor { // the actor behind a script handle
    char pad[0x31C];
    float health; // +0x31C
    float f320;   // +0x320
    float f324;   // +0x324
    float f328;   // +0x328
    float f32c;   // +0x32C
};

class ScriptObj
{
public:
    char d[0x3ac];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void s35(); virtual void s36();
    virtual int s37(int a, int b, int c, float f, int d, int e, int g, int h); // +0x130
};

ScriptHActor *fn_80081E6C(int handle);
void fn_80030930(void *a, int b, int c, int d, float f1, int e, int f, int g, int h, float f2);
float fn_80086640(void *a);
float fn_80086614(void *a);
float fn_8008677C(void *a);
void *fn_800B14C8(void *a);
void *fn_80085954V(void *a) __asm__("fn_80085954");
ScriptObj *fn_80085954O(void *a) __asm__("fn_80085954");
unsigned int fn_800CC514(void *a);
float fn_8002FD50(void *self, void *src, int kind, int type, float dmg, int p20, int p24, unsigned int flags, int p2C,
                  float f30, int *blocked, int pBC, int pC0, int pC4);
int fn_80030894(void *a, float v);

ScriptHActor *fn_8007C034(register int handle)
{
    ScriptHActor *actor = fn_80081E6C(handle);
    if (!actor || !fn_800B0C58(actor))
        return 0;
    return actor;
}

float fn_8007C0AC(register int handle)
{
    ScriptHActor *actor = fn_8007C034(handle);
    if (actor == 0)
        return -1.0f;
    return actor->health;
}

float fn_8007C114(register int handle, float v)
{
    ScriptHActor *actor = fn_8007C034(handle);
    if (actor == 0)
        return -1.0f;
    float old = actor->health;
    if (v < 1.0) {
        fn_80030930(actor, 0, 0, 0, 0.0f, 0, 0, 0, 1, 0.0f);
        return old;
    }
    actor->health = v >= 1.0f ? (v <= fn_80086640(actor) ? v : fn_80086640(actor)) : 1.0f;
    return old;
}

float fn_8007C244(register int handle)
{
    ScriptHActor *actor = fn_8007C034(handle);
    if (actor == 0)
        return -1.0f;
    return actor->f320;
}

}

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.text");

extern "C" {

float fn_8007C2AC(register int handle)
{
    ScriptHActor *actor = fn_8007C034(handle);
    if (actor == 0)
        return -1.0f;
    return actor->f32c;
}

float fn_8007C314(register int handle, float v)
{
    ScriptHActor *actor = fn_8007C034(handle);
    if (actor == 0)
        return -1.0f;
    float old = actor->f32c;
    actor->f32c = v >= 1.0f ? (v <= fn_80086614(actor) ? v : fn_80086614(actor)) : 1.0f;
    return old;
}

float fn_8007C3EC(register int handle)
{
    ScriptHActor *actor = fn_8007C034(handle);
    if (actor == 0)
        return -1.0f;
    return actor->f324;
}

float fn_8007C454(register int handle, float v)
{
    ScriptHActor *actor = fn_8007C034(handle);
    if (actor == 0)
        return -1.0f;
    float old = actor->f324;
    actor->f324 = v >= 1.0f ? (v <= fn_8008677C(actor) ? v : fn_8008677C(actor)) : 1.0f;
    return old;
}

float fn_8007C52C(register int handle)
{
    ScriptHActor *actor = fn_8007C034(handle);
    if (actor == 0)
        return -1.0f;
    return actor->f328;
}

}

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.text");

extern "C" {

float fn_8007C594(register int handle, float dmg, int type, int kind, int src, unsigned int flags)
{
    ScriptHActor *actor;
    void *act;
    void *obj;

    actor = fn_8007C034(handle);
    if (actor == 0)
        return -1.0f;
    if (fn_800B0C1C(actor)) {
        act = fn_800B14C8(actor);
        obj = fn_80085954V(act);
        if (obj && (fn_800CC514(obj) & 0x20000000))
            return -1.0f;
    }
    obj = fn_800ACFA8(src);
    return fn_8002FD50(actor, obj, kind, type, dmg, 0, 0, flags, 1, 0.0f, 0, 0, 0xFF, 0xFF);
}

int fn_8007C6D0(register int handle, float v)
{
    ScriptHActor *actor = fn_8007C034(handle);
    if (actor == 0)
        return 0;
    return fn_80030894(actor, v);
}

int fn_8007C740(register int handle, int a, int b, int c, float f, int d)
{
    ScriptHActor *actor = fn_8007C034(handle);
    if (!actor || !fn_80085954V(actor))
        return 0;
    int ret = fn_80085954O(actor)->s37(a, c, b, f, 0, 0, d, 0);
    return ret;
}

float fn_80433D20(void *record, int id, int slot);
extern void *lbl_8066C6C8;
extern float lbl_8066D5C0;

void fn_8007C830(float f)
{
    if (f > fn_80433D20(lbl_8066C6C8, 0x10, 0) || f < fn_80433D20(lbl_8066C6C8, 0xF, 0))
        return;
    lbl_8066D5C0 = f;
}

}
