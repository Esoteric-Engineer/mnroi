// The per-profile brains, each one's task factory (its vtable's one method) and constructor, and the special tasks of BRUTE3, FLYER1 and HUMAN3 (docs/ai.md row 4, section 4.2).
// Its float pool from 0x8049BB48 stays in dtk's .rodata (extern_pool); the orph words are linkonce entries.

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
    char d4[0x4C];
    float f50; // +0x50
    float f54; // +0x54
    char d58[8];
    float f60; // +0x60
    float f64; // +0x64
};
struct PEnt : Ent { // matching_notes 44
    int x;
};

struct Base {
    int pad;
};
struct Body : Base { // fn_80085954's result
    char d[0x3A8];
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
    virtual int v42(); // +0x158
};

struct BrainSelf {
    void *ai; // +0x0
    char d[0x26C];
    void *vtable; // +0x270
};

struct Task28 {
    char d[0x28];
    Task28(void *ai) __asm__("fn_801611C8");
};
struct Flyer1Task1 {
    char d[0x28];
    Flyer1Task1(void *ai) __asm__("fn_801627B8");
};
struct Flyer1Task3 {
    char d[0x28];
    Flyer1Task3(void *ai) __asm__("fn_80162810");
};
struct Human3Task {
    char d[0x28];
    Human3Task(void *ai) __asm__("fn_801638E0");
};
struct Flyer1Task9 {
    char d[0x28];
    Flyer1Task9(void *ai) __asm__("fn_80162868");
};

extern "C" void *fn_80150AA8(BrainSelf *self, int id);
extern "C" BrainSelf *fn_801507C0(BrainSelf *self, void *ai);
extern "C" void *fn_801641FC(BrainSelf *self, int id);
extern "C" BrainSelf *fn_80164274(BrainSelf *self, void *ai);

extern "C" void *AI_GetBehaviorSet(void *ai);
extern "C" void BitSet_ClearAll(void *p);
extern "C" void AI_EnableBehavior(void *ai, unsigned int bit);
extern "C" void AI_DisableBehavior(void *ai, unsigned int bit);
extern "C" void fn_8046412C(void *ai, unsigned int bit);
extern "C" void *fn_80151C8C(BrainSelf *brain);
extern "C" void BitSet_Set(void *timer, int v);

extern "C" {
int fn_80151B90(BrainSelf *brain, void *task);
int fn_80151430(BrainSelf *brain);
void fn_801513D8(BrainSelf *brain, int len);
void AI_SetTaskDone(void *task, int done);
int AI_TestCondition(void *ai, int bit);
int fn_801369B0(void *ai);
int fn_80085D3C(void *ent);
Ent *fn_80134870(void *ai);
int fn_8015F008(void *ai);
float fn_8015E4E8(void *ai);
PEnt *AI_GetEntity(void *ai);
float fn_800B1884(Ent &e, int id);
int fn_800B18EC(Ent &e, int id);
char *AI_GetMover(void *ai);
int fn_800B13D8(Ent &e);
void fn_8014B63C(char *p, int a, int b);
int BitSet_Test(void *set, int bit);
void BitSet_Clear(void *set, int v);
float fn_80461F68(void *ai);
float fn_80461EE4(void *ai);
int fn_8015EC1C(float f);
float fn_80464318(void *ai);
float fn_80462A30(void *ai);
float fn_80464344(void *ai);
unsigned int fn_8015EA6C(int n, float *w);
void *fn_800B1724(Ent &e);
void fn_8042DC84(Vector *dst, void *src);
void fn_80429038(Vector *out, void *a, Vector *b);
float fn_8042EC54(Vector *v);
float fn_800B2670(Ent &e);
void *fn_800B24AC(Ent &e);
void *fn_800B1CC8(Ent &e);
void AI_SaveTaskBehaviors(void *task);
void AI_RestoreTaskBehaviors(void *task);
void *AI_GetActor(void *ai);
void *fn_800E9AF8(void *actor, float a, float b, float c, int d, void *e);
int fn_800B0C58(Ent &e);
void *AI_GetTargetList(void *ai);
void fn_8014F7B0(void *rec, int v);
void fn_8042D8A8(Vector *dst, void *src);
void *AI_GetMoverMoveDest(char *p);
float fn_8015E580(void *a, void *b);
void *fn_800B1750(Ent &e);
float fn_8042EBF4(Vector *v, void *w);
int fn_801600DC(void *ai, int kind, float f);
void fn_8015105C(BrainSelf *brain, int id);
int fn_8009B04C(Ent &e);
void fn_80136214(void *ai, int bit);
void *fn_800B14A0(Ent &e);
Body *fn_80085954(void *p);
int fn_800CCBD8(Base &b);
int fn_800B0CC0(Ent &e);
void *fn_800B1478(Ent &e);
float fn_800A4054(void *p);
float fn_80086614(void *p);
float fn_8015E64C(void *ai);
int fn_8008606C(void *ent);
int fn_801368B8(void *ai);
int AI_HasMoverPath(char *p);
int fn_800CCA08(Base &b);
int fn_8004A9CC(Vector *from, Vector *dir, float len, unsigned int mask, void *hit, void *a, void *b, int c, int d);
}

extern char lbl_804F6320[];
extern char lbl_804F6338[];
extern char lbl_804F6350[];
extern char lbl_804F6368[];
extern char lbl_804F6380[];
extern char lbl_804F63B8[];
extern char lbl_804F63D0[];
extern char lbl_804F63E8[];
extern char lbl_804F6400[];
extern char lbl_804F6418[];
extern char lbl_804F6450[];
extern char lbl_804F6488[];
extern char lbl_804F64C0[];
extern char lbl_804F64D8[];
extern char lbl_804F64F0[];
extern char lbl_804F6508[];
extern char lbl_804F6520[];
extern char lbl_804F6538[];
extern char lbl_804F6550[];
extern char lbl_804F6568[];
extern char lbl_804F65A0[];
extern char lbl_804F65B8[];
extern char lbl_804F65D0[];
extern char lbl_804F65E8[];
extern char lbl_804F6600[];
extern char lbl_804F6618[];
extern char lbl_804F6630[];
extern char lbl_804F6648[];
extern char lbl_804F6660[];
extern char lbl_804F6678[];
extern char lbl_804F6690[];
extern char lbl_804F66A8[];
extern char lbl_804F66C0[];
extern char lbl_804F66D8[];
extern char lbl_804F66F0[];

extern "C" void *fn_80161484(BrainSelf *self, int id);
extern "C" BrainSelf *fn_80162764(BrainSelf *self, void *ai);

// AI_AFTERSHOCK
extern "C" void *fn_80160428(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case -1:
        break;
    default:
        return fn_801641FC(self, id);
    }
    return task;
}

extern "C" BrainSelf *fn_801604A0(register BrainSelf *self, register void *ai)
{
    fn_80164274(self, ai);
    self->vtable = (void *)lbl_804F6320;
    return self;
}

// AI_BIOHAZARD
extern "C" void *fn_801604F4(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case -1:
        break;
    default:
        return fn_801641FC(self, id);
    }
    return task;
}

extern "C" BrainSelf *fn_8016056C(register BrainSelf *self, register void *ai)
{
    fn_80164274(self, ai);
    self->vtable = (void *)lbl_804F6338;
    return self;
}

// AI_BRUTE1
extern "C" void *fn_801605C0(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case -1:
        break;
    default:
        return fn_80150AA8(self, id);
    }
    return task;
}

extern "C" BrainSelf *fn_80160638(register BrainSelf *self, register void *ai)
{
    fn_801507C0(self, ai);
    self->vtable = (void *)lbl_804F6350;
    return self;
}

// AI_BRUTE2
extern "C" void *fn_8016068C(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case -1:
        break;
    default:
        return fn_80150AA8(self, id);
    }
    return task;
}

extern "C" BrainSelf *fn_80160704(register BrainSelf *self, register void *ai)
{
    fn_801507C0(self, ai);
    self->vtable = (void *)lbl_804F6368;
    return self;
}

// AI_BRUTE3: task 3 is its special task (vtable lbl_804F6380)
extern "C" void *fn_80160758(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case -1:
        break;
    case 3:
        task = new Task28(self->ai);
        break;
    default:
        return fn_80150AA8(self, id);
    }
    return task;
}

struct TaskSelf {
    void *ai; // +0x0
    BrainSelf *brain; // +0x4
    char d[0x1C];
    void *vtable; // +0x24
};

extern "C" TaskSelf *fn_8015294C(TaskSelf *self, void *ai, int id);

// BRUTE3's special task (vtable lbl_804F6380): enter, exit, update
extern "C" int fn_801607FC(register TaskSelf *self)
{
    BitSet_ClearAll(AI_GetBehaviorSet(self->ai));
    fn_8046412C(self->ai, 0);
    fn_8046412C(self->ai, 3);
    fn_8046412C(self->ai, 5);
    AI_EnableBehavior(self->ai, 0);
    AI_DisableBehavior(self->ai, 1);
    AI_EnableBehavior(self->ai, 2);
    AI_EnableBehavior(self->ai, 4);
    AI_DisableBehavior(self->ai, 8);
    AI_DisableBehavior(self->ai, 9);
    fn_8046412C(self->ai, 6);
    AI_EnableBehavior(self->ai, 0x1A);
    AI_EnableBehavior(self->ai, 0x1C);
    AI_EnableBehavior(self->ai, 0x15);
    AI_EnableBehavior(self->ai, 0x16);
    AI_EnableBehavior(self->ai, 0x17);
    BitSet_ClearAll(fn_80151C8C(self->brain));
    BitSet_Set(fn_80151C8C(self->brain), 1);
    return 1;
}

extern "C" int fn_80160928(register void *self)
{
    return 1;
}

extern "C" int fn_80160950(register TaskSelf *self)
{
    if (fn_80151B90(self->brain, self)) {
        if (!AI_TestCondition(self->ai, 2)) {
            AI_SetTaskDone(self, 1);
            return 1;
        }
        if (!fn_801369B0(self->ai) && fn_80085D3C(AI_GetEntity(self->ai))) {
            AI_SetTaskDone(self, 1);
            return 0;
        }
        if (!fn_80134870(self->ai)) {
            AI_SetTaskDone(self, 1);
            return 0;
        }
        if (!fn_8015F008(self->ai)) {
            if (!AI_TestCondition(self->ai, 4) && AI_TestCondition(self->ai, 0x2B)) {
            } else {
                AI_SetTaskDone(self, 1);
            }
        } else {
            if (AI_TestCondition(self->ai, 3) && !AI_TestCondition(self->ai, 0x2B)) {
                if (fn_8015E4E8(self->ai) > fn_800B1884(*AI_GetEntity(self->ai), 0xD4) + 2.0f) {
                    AI_EnableBehavior(self->ai, 1);
                    AI_DisableBehavior(self->ai, 2);
                    if (fn_80134870(self->ai))
                        fn_8014B63C(AI_GetMover(self->ai), fn_800B13D8(*fn_80134870(self->ai)), 0);
                    return 0;
                }
            }
            if (BitSet_Test(fn_80151C8C(self->brain), 1)) {
                if (!fn_80151430(self->brain)) {
                    AI_DisableBehavior(self->ai, 9);
                    fn_801513D8(self->brain, fn_800B18EC(*AI_GetEntity(self->ai), 0xB9));
                    BitSet_Clear(fn_80151C8C(self->brain), 1);
                    BitSet_Set(fn_80151C8C(self->brain), 0);
                    if (AI_TestCondition(self->ai, 0x2B) && fn_8015EC1C(fn_80461F68(self->ai))) {
                        AI_EnableBehavior(self->ai, 9);
                        return 1;
                    }
                    AI_DisableBehavior(self->ai, 9);
                    AI_DisableBehavior(self->ai, 0x19);
                    AI_DisableBehavior(self->ai, 0xA);
                    AI_DisableBehavior(self->ai, 2);
                    AI_DisableBehavior(self->ai, 0xD);
                    AI_DisableBehavior(self->ai, 7);
                    AI_DisableBehavior(self->ai, 1);
                    AI_DisableBehavior(self->ai, 0x13);
                    float a = 0.0f;
                    if (AI_TestCondition(self->ai, 0x25))
                        a = 1.0f;
                    float b = 0.0f;
                    if (!AI_TestCondition(self->ai, 0x28))
                        b = 1.0f;
                    float w[7];
                    w[0] = 0.0f;
                    w[1] = fn_80464318(self->ai) * fn_80462A30(self->ai);
                    w[2] = fn_80464318(self->ai) * fn_80464344(self->ai) * a;
                    w[3] = fn_80464318(self->ai) * fn_80462A30(self->ai);
                    w[4] = (100.0f - fn_80461EE4(self->ai)) * 5.0f * (100.0f - fn_80461F68(self->ai));
                    w[5] = 0.0f;
                    w[6] = 0.0f;
                    if (AI_TestCondition(self->ai, 3) && !AI_TestCondition(self->ai, 4) && AI_TestCondition(self->ai, 0x2B)) {
                        w[2] = 0.0f;
                        w[4] = 0.0f;
                        w[5] = 0.0f;
                        w[1] = 0.0f;
                    }
                    unsigned int pick = fn_8015EA6C(7, w);
                    switch (pick) {
                    case 0:
                        AI_EnableBehavior(self->ai, 9);
                        break;
                    case 1:
                        AI_EnableBehavior(self->ai, 0x19);
                        AI_DisableBehavior(self->ai, 7);
                        break;
                    case 2:
                        AI_EnableBehavior(self->ai, 7);
                        break;
                    case 3:
                        AI_EnableBehavior(self->ai, 0xD);
                        break;
                    case 4:
                        AI_DisableBehavior(self->ai, 2);
                        break;
                    case 5:
                        AI_SetTaskDone(self, 1);
                        break;
                    case 6:
                        AI_EnableBehavior(self->ai, 0x13);
                        break;
                    }
                }
            } else if (BitSet_Test(fn_80151C8C(self->brain), 0) && !fn_80151430(self->brain)) {
                if (fn_80134870(self->ai)) {
                    Vector from;
                    Vector dir;
                    fn_8042DC84(&from, fn_800B1724(*AI_GetEntity(self->ai)));
                    from.z += 1.0f;
                    fn_80429038(&dir, fn_800B1724(*fn_80134870(self->ai)), &from);
                    float len = fn_8042EC54(&dir);
                    len -= fn_800B2670(*fn_80134870(self->ai));
                    if (!fn_8004A9CC(&from, &dir, len, 0x8000, 0, fn_800B24AC(*AI_GetEntity(self->ai)),
                                     fn_800B1CC8(*AI_GetEntity(self->ai)), 0, 3))
                        AI_EnableBehavior(self->ai, 9);
                    else
                        AI_DisableBehavior(self->ai, 9);
                }
                fn_801513D8(self->brain, fn_800B18EC(*AI_GetEntity(self->ai), 0xB8));
                BitSet_Set(fn_80151C8C(self->brain), 1);
            }
        }
        if (AI_TestCondition(self->ai, 0x2D) || AI_TestCondition(self->ai, 0x2C) || AI_TestCondition(self->ai, 0x24))
            AI_EnableBehavior(self->ai, 7);
    } else {
    }
    return 1;
}

extern "C" BrainSelf *fn_80161174(register BrainSelf *self, register void *ai)
{
    fn_801507C0(self, ai);
    self->vtable = (void *)lbl_804F63B8;
    return self;
}

extern "C" TaskSelf *fn_801611C8(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 3);
    self->vtable = (void *)lbl_804F6380;
    return self;
}

// AI_DAREDEVIL
extern "C" void *fn_80161220(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case -1:
        break;
    default:
        return fn_801641FC(self, id);
    }
    return task;
}

extern "C" BrainSelf *fn_80161298(register BrainSelf *self, register void *ai)
{
    fn_80164274(self, ai);
    self->vtable = (void *)lbl_804F63D0;
    return self;
}

// AI_DEFCON
extern "C" void *fn_801612EC(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case -1:
        break;
    default:
        return fn_801641FC(self, id);
    }
    return task;
}

extern "C" BrainSelf *fn_80161364(register BrainSelf *self, register void *ai)
{
    fn_80164274(self, ai);
    self->vtable = (void *)lbl_804F63E8;
    return self;
}

// AI_ELEKTRA
extern "C" void *fn_801613B8(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case -1:
        break;
    default:
        return fn_801641FC(self, id);
    }
    return task;
}

extern "C" BrainSelf *fn_80161430(register BrainSelf *self, register void *ai)
{
    fn_80164274(self, ai);
    self->vtable = (void *)lbl_804F6400;
    return self;
}

#define ABS(x) ((x) < 0.0f ? -(x) : (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// AI_FLYER1 (also used by FLYER2 and FLYER3)
extern "C" void *fn_80161484(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case 1:
        task = new Flyer1Task1(self->ai);
        break;
    case 3:
        task = new Flyer1Task3(self->ai);
        break;
    case 9:
        task = new Flyer1Task9(self->ai);
        break;
    default:
        return fn_80150AA8(self, id);
    }
    return task;
}

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.text"); // 0x8049BB5C-0x8049BB88, linkonce pool entries

// FLYER1's task 1 (vtable lbl_804F6488): enter, exit, update
extern "C" int fn_8016157C(register TaskSelf *self)
{
    fn_8046412C(self->ai, 0);
    fn_8046412C(self->ai, 6);
    fn_8046412C(self->ai, 5);
    AI_SaveTaskBehaviors(self);
    BitSet_ClearAll(AI_GetBehaviorSet(self->ai));
    AI_EnableBehavior(self->ai, 0x18);
    AI_EnableBehavior(self->ai, 0x28);
    AI_EnableBehavior(self->ai, 0x1E);
    AI_EnableBehavior(self->ai, 4);
    BitSet_ClearAll(fn_80151C8C(self->brain));
    fn_801513D8(self->brain, fn_800B18EC(*AI_GetEntity(self->ai), 0xB9));
    fn_800E9AF8(AI_GetActor(self->ai), 15.0f, 4.0f, 0.5f, 0, 0);
    if (fn_80134870(self->ai)) {
        if (!fn_800B0C58(*fn_80134870(self->ai)))
            fn_8014F7B0(AI_GetTargetList(self->ai), 0);
        fn_8014B63C(AI_GetMover(self->ai), fn_800B13D8(*fn_80134870(self->ai)), 0);
    }
    return 1;
}

extern "C" int fn_80161714(register TaskSelf *self)
{
    AI_RestoreTaskBehaviors(self);
    return 1;
}

extern "C" int fn_80161754(register TaskSelf *self)
{
    if (!fn_80151B90(self->brain, self))
        return 0;
    Ent *t = fn_80134870(self->ai);
    if (t) {
        Vector v;
        fn_8042DC84(&v, fn_800B1724(*t));
        fn_8042D8A8(&v, fn_800B1724(*AI_GetEntity(self->ai)));
        v.z = 0.0f;
        float dist = fn_8042EC54(&v);
        float d2 = fn_8015E580(fn_800B1724(*AI_GetEntity(self->ai)), AI_GetMoverMoveDest(AI_GetMover(self->ai)));
        if (!(dist > fn_800B1884(*AI_GetEntity(self->ai), 0xD4)) && !(dist < fn_800B1884(*AI_GetEntity(self->ai), 0xD2))) {
        } else {
            fn_8014B63C(AI_GetMover(self->ai), fn_800B13D8(*t), 0);
        }
        if (!fn_80151430(self->brain)) {
            float dot = fn_8042EBF4(&v, fn_800B1750(*AI_GetEntity(self->ai)));
            if (dot > 0.99f && dist <= fn_800B1884(*AI_GetEntity(self->ai), 0xD4) + 2.0f
                && dist >= fn_800B1884(*AI_GetEntity(self->ai), 0xD2)) {
                float len = dist - MAX(ABS(t->f60 - t->f50), ABS(t->f64 - t->f54));
                if (!AI_TestCondition(self->ai, 0x40) && fn_801600DC(self->ai, 1, 4.0f)
                    && !fn_8004A9CC((Vector *)fn_800B1724(*AI_GetEntity(self->ai)), &v, len, 0x1F, 0,
                                    fn_800B24AC(*AI_GetEntity(self->ai)), 0, 0, 0))
                    fn_8015105C(self->brain, 3);
            }
        }
        return 1;
    }
    return 1;
}

// FLYER1's task 3 (vtable lbl_804F6450): enter, exit, update
extern "C" int fn_80161BDC(register TaskSelf *self)
{
    AI_SaveTaskBehaviors(self);
    BitSet_ClearAll(AI_GetBehaviorSet(self->ai));
    AI_EnableBehavior(self->ai, 0x18);
    Ent *t = fn_80134870(self->ai);
    if (t)
        fn_8014B63C(AI_GetMover(self->ai), fn_800B13D8(*t), 0);
    fn_801513D8(self->brain, fn_800B18EC(*AI_GetEntity(self->ai), 0xB8));
    BitSet_Set(fn_80151C8C(self->brain), 1);
    AI_EnableBehavior(self->ai, 9);
    AI_EnableBehavior(self->ai, 0x1E);
    return 1;
}

extern "C" int fn_80161CD8(register TaskSelf *self)
{
    AI_RestoreTaskBehaviors(self);
    return 1;
}

extern "C" int fn_80161D18(register TaskSelf *self)
{
    if (!fn_80151B90(self->brain, self))
        return 0;
    Ent *t = fn_80134870(self->ai);
    if (!t) {
        AI_SetTaskDone(self, 1);
        return 0;
    }
    if (BitSet_Test(fn_80151C8C(self->brain), 1)) {
        if (!fn_80151430(self->brain) && fn_8009B04C(*AI_GetEntity(self->ai)) != 0x63) {
            if (!AI_TestCondition(self->ai, 0x35))
                AI_DisableBehavior(self->ai, 9);
            fn_80136214(self->ai, 9);
            fn_801513D8(self->brain, fn_800B18EC(*AI_GetEntity(self->ai), 0xB9));
            BitSet_Clear(fn_80151C8C(self->brain), 1);
        }
    } else if (!fn_80151430(self->brain)) {
        if (AI_TestCondition(self->ai, 0x35) && !AI_TestCondition(self->ai, 0x40) && fn_801600DC(self->ai, 1, 4.0f))
            AI_EnableBehavior(self->ai, 9);
        fn_801513D8(self->brain, fn_800B18EC(*AI_GetEntity(self->ai), 0xB8));
        BitSet_Set(fn_80151C8C(self->brain), 1);
    }
    if (fn_800B0C58(*t) && (fn_80085954(fn_800B14A0(*t))->v42() || fn_800CCBD8(*fn_80085954(fn_800B14A0(*t)))))
        AI_DisableBehavior(self->ai, 0x28);
    else
        AI_EnableBehavior(self->ai, 0x28);
    int done = 0;
    if (fn_800B0CC0(*t))
        done = fn_800A4054(fn_800B1478(*t)) < 0.1f;
    else if (fn_800B0C58(*t))
        done = fn_80086614(fn_800B14A0(*t)) < 0.1f;
    if (done) {
        AI_SetTaskDone(self, 1);
        return 1;
    }
    float range = fn_8015E64C(self->ai);
    if (!(range > fn_800B1884(*AI_GetEntity(self->ai), 0xD4)) && !(range < fn_800B1884(*AI_GetEntity(self->ai), 0xD3))) {
    } else {
        AI_SetTaskDone(self, 1);
    }
    float d = fn_8015E580(fn_800B1724(*AI_GetEntity(self->ai)), AI_GetMoverMoveDest(AI_GetMover(self->ai)));
    if (d > fn_800B1884(*AI_GetEntity(self->ai), 0xD2))
        AI_SetTaskDone(self, 1);
    return 1;
}

// FLYER1's task 9 (vtable lbl_804F6418): enter, exit, update
extern "C" int fn_8016216C(register TaskSelf *self)
{
    AI_SaveTaskBehaviors(self);
    BitSet_ClearAll(AI_GetBehaviorSet(self->ai));
    AI_EnableBehavior(self->ai, 0x18);
    AI_EnableBehavior(self->ai, 0x1A);
    AI_EnableBehavior(self->ai, 0x1C);
    AI_EnableBehavior(self->ai, 0x28);
    AI_EnableBehavior(self->ai, 0x1E);
    AI_EnableBehavior(self->ai, 4);
    fn_8046412C(self->ai, 0);
    fn_8046412C(self->ai, 6);
    fn_8046412C(self->ai, 5);
    BitSet_ClearAll(fn_80151C8C(self->brain));
    fn_801513D8(self->brain, fn_800B18EC(*AI_GetEntity(self->ai), 0xB9));
    fn_800E9AF8(AI_GetActor(self->ai), 15.0f, 4.0f, 0.5f, 0, 0);
    return 1;
}

extern "C" int fn_8016229C(register TaskSelf *self)
{
    AI_RestoreTaskBehaviors(self);
    return 1;
}

extern "C" int fn_801622DC(register TaskSelf *self)
{
    if (!fn_80151B90(self->brain, self))
        return 0;
    Ent *t = fn_80134870(self->ai);
    if (t) {
        int done = 0;
        if (fn_800B0CC0(*t))
            done = fn_800A4054(fn_800B1478(*t)) < 0.1f;
        else if (fn_800B0C58(*t))
            done = fn_80086614(fn_800B14A0(*t)) < 0.1f;
        if (done) {
            AI_SetTaskDone(self, 1);
            return 1;
        }
        Vector v;
        fn_8042DC84(&v, fn_800B1724(*t));
        fn_8042D8A8(&v, fn_800B1724(*AI_GetEntity(self->ai)));
        v.z = 0.0f;
        float dist = fn_8042EC54(&v);
        if (!(dist > fn_800B1884(*AI_GetEntity(self->ai), 0xD4)) && !(dist < fn_800B1884(*AI_GetEntity(self->ai), 0xD2))) {
        } else {
            fn_8014B63C(AI_GetMover(self->ai), fn_800B13D8(*t), 0);
        }
        if (!fn_80151430(self->brain)) {
            float dot = fn_8042EBF4(&v, fn_800B1750(*AI_GetEntity(self->ai)));
            if (dot > 0.95f && dist <= fn_800B1884(*AI_GetEntity(self->ai), 0xD4)) {
                float len = dist - MAX(ABS(t->f60 - t->f50), ABS(t->f64 - t->f54));
                if (!fn_8004A9CC((Vector *)fn_800B1724(*AI_GetEntity(self->ai)), &v, len, 0x1F, 0,
                                 fn_800B24AC(*AI_GetEntity(self->ai)), 0, 0, 0))
                    fn_8015105C(self->brain, 3);
            }
        }
        return 1;
    }
    return 0;
}

extern "C" BrainSelf *fn_80162764(register BrainSelf *self, register void *ai)
{
    fn_801507C0(self, ai);
    self->vtable = (void *)lbl_804F64C0;
    return self;
}

extern "C" TaskSelf *fn_801627B8(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 1);
    self->vtable = (void *)lbl_804F6488;
    return self;
}

extern "C" TaskSelf *fn_80162810(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 3);
    self->vtable = (void *)lbl_804F6450;
    return self;
}

extern "C" TaskSelf *fn_80162868(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 9);
    self->vtable = (void *)lbl_804F6418;
    return self;
}

// AI_FLYER2
extern "C" void *fn_801628C0(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case -1:
        break;
    default:
        return fn_80161484(self, id);
    }
    return task;
}

extern "C" BrainSelf *fn_80162938(register BrainSelf *self, register void *ai)
{
    fn_80162764(self, ai);
    self->vtable = (void *)lbl_804F64D8;
    return self;
}

// AI_FLYER3
extern "C" void *fn_8016298C(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case -1:
        break;
    default:
        return fn_80161484(self, id);
    }
    return task;
}

extern "C" BrainSelf *fn_80162A04(register BrainSelf *self, register void *ai)
{
    fn_80162764(self, ai);
    self->vtable = (void *)lbl_804F64F0;
    return self;
}

// AI_FOOTBALLGUY
extern "C" void *fn_80162A58(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case -1:
        break;
    default:
        return fn_801641FC(self, id);
    }
    return task;
}

extern "C" BrainSelf *fn_80162AD0(register BrainSelf *self, register void *ai)
{
    fn_80164274(self, ai);
    self->vtable = (void *)lbl_804F6508;
    return self;
}

// AI_HEATWAVE
extern "C" void *fn_80162B24(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case -1:
        break;
    default:
        return fn_801641FC(self, id);
    }
    return task;
}

extern "C" BrainSelf *fn_80162B9C(register BrainSelf *self, register void *ai)
{
    fn_80164274(self, ai);
    self->vtable = (void *)lbl_804F6520;
    return self;
}

// AI_HUMAN1
extern "C" void *fn_80162BF0(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case -1:
        break;
    default:
        return fn_80150AA8(self, id);
    }
    return task;
}

extern "C" BrainSelf *fn_80162C68(register BrainSelf *self, register void *ai)
{
    fn_801507C0(self, ai);
    self->vtable = (void *)lbl_804F6538;
    return self;
}

// AI_HUMAN2
extern "C" void *fn_80162CBC(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case -1:
        break;
    default:
        return fn_80150AA8(self, id);
    }
    return task;
}

extern "C" BrainSelf *fn_80162D34(register BrainSelf *self, register void *ai)
{
    fn_801507C0(self, ai);
    self->vtable = (void *)lbl_804F6550;
    return self;
}

// AI_HUMAN3: task 3 is its special task (vtable lbl_804F6568)
extern "C" void *fn_80162D88(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case -1:
        break;
    case 3:
        task = new Human3Task(self->ai);
        break;
    default:
        return fn_80150AA8(self, id);
    }
    return task;
}

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.text"); // 0x8049BBC4-0x8049BC08, linkonce pool entries

// HUMAN3's special task (vtable lbl_804F6568): enter, exit, update
extern "C" int fn_80162E2C(register TaskSelf *self)
{
    BitSet_ClearAll(AI_GetBehaviorSet(self->ai));
    fn_8046412C(self->ai, 0);
    fn_8046412C(self->ai, 3);
    fn_8046412C(self->ai, 5);
    AI_EnableBehavior(self->ai, 0);
    AI_DisableBehavior(self->ai, 1);
    AI_EnableBehavior(self->ai, 2);
    AI_EnableBehavior(self->ai, 4);
    AI_DisableBehavior(self->ai, 8);
    AI_DisableBehavior(self->ai, 9);
    fn_8046412C(self->ai, 6);
    AI_EnableBehavior(self->ai, 0x1A);
    AI_EnableBehavior(self->ai, 0x1C);
    AI_EnableBehavior(self->ai, 0x15);
    AI_EnableBehavior(self->ai, 0x16);
    AI_EnableBehavior(self->ai, 0x17);
    BitSet_ClearAll(fn_80151C8C(self->brain));
    BitSet_Set(fn_80151C8C(self->brain), 1);
    return 1;
}

extern "C" int fn_80162F58(register void *self)
{
    return 1;
}

extern "C" int fn_80162F80(register TaskSelf *self)
{
    if (fn_80151B90(self->brain, self)) {
        if (!AI_TestCondition(self->ai, 2)) {
            AI_SetTaskDone(self, 1);
            return 1;
        }
        if (!fn_801369B0(self->ai) && fn_80085D3C(AI_GetEntity(self->ai))) {
            AI_SetTaskDone(self, 1);
            return 0;
        }
        if (!fn_80134870(self->ai)) {
            AI_SetTaskDone(self, 1);
            return 0;
        }
        if (!fn_8015F008(self->ai)) {
            if (!AI_TestCondition(self->ai, 4) && AI_TestCondition(self->ai, 0x2B)) {
            } else {
                AI_SetTaskDone(self, 1);
            }
        } else {
            if (!AI_TestCondition(self->ai, 0x2B)) {
                if (!fn_8008606C(AI_GetEntity(self->ai)) && !fn_801368B8(self->ai)) {
                } else {
                    AI_DisableBehavior(self->ai, 9);
                    AI_DisableBehavior(self->ai, 0x19);
                    AI_DisableBehavior(self->ai, 0xA);
                    AI_DisableBehavior(self->ai, 2);
                    AI_DisableBehavior(self->ai, 0xD);
                    AI_DisableBehavior(self->ai, 7);
                    AI_DisableBehavior(self->ai, 1);
                    AI_DisableBehavior(self->ai, 0x13);
                    AI_EnableBehavior(self->ai, 1);
                    AI_DisableBehavior(self->ai, 2);
                    if (!AI_HasMoverPath(AI_GetMover(self->ai)) && fn_80134870(self->ai))
                        fn_8014B63C(AI_GetMover(self->ai), fn_800B13D8(*fn_80134870(self->ai)), 0);
                }
            }
            if (BitSet_Test(fn_80151C8C(self->brain), 1)) {
                if (!fn_80151430(self->brain)) {
                    AI_DisableBehavior(self->ai, 9);
                    fn_801513D8(self->brain, fn_800B18EC(*AI_GetEntity(self->ai), 0xB9));
                    BitSet_Clear(fn_80151C8C(self->brain), 1);
                    BitSet_Set(fn_80151C8C(self->brain), 0);
                    if (AI_TestCondition(self->ai, 0x2B) && fn_8015EC1C(fn_80461F68(self->ai))) {
                        AI_EnableBehavior(self->ai, 9);
                        return 1;
                    }
                    AI_DisableBehavior(self->ai, 9);
                    AI_DisableBehavior(self->ai, 0x19);
                    AI_DisableBehavior(self->ai, 0xA);
                    AI_DisableBehavior(self->ai, 2);
                    AI_DisableBehavior(self->ai, 0xD);
                    AI_DisableBehavior(self->ai, 7);
                    AI_DisableBehavior(self->ai, 1);
                    AI_DisableBehavior(self->ai, 0x13);
                    float a = 0.0f;
                    if (AI_TestCondition(self->ai, 0x25))
                        a = 1.0f;
                    float b = 0.0f;
                    if (!AI_TestCondition(self->ai, 0x28))
                        b = 1.0f;
                    float w[7];
                    w[0] = 0.0f;
                    w[1] = fn_80464318(self->ai) * fn_80462A30(self->ai);
                    w[2] = fn_80464318(self->ai) * fn_80464344(self->ai) * a;
                    w[3] = fn_80464318(self->ai) * fn_80462A30(self->ai);
                    w[4] = (100.0f - fn_80461EE4(self->ai)) * 5.0f * (100.0f - fn_80461F68(self->ai));
                    w[5] = 0.0f;
                    w[6] = 0.0f;
                    if (AI_TestCondition(self->ai, 3) && !AI_TestCondition(self->ai, 4) && AI_TestCondition(self->ai, 0x2B)) {
                        w[2] = 0.0f;
                        w[4] = 0.0f;
                        w[5] = 0.0f;
                        w[1] = 0.0f;
                    }
                    unsigned int pick = fn_8015EA6C(7, w);
                    switch (pick) {
                    case 0:
                        AI_EnableBehavior(self->ai, 9);
                        break;
                    case 1:
                        AI_EnableBehavior(self->ai, 0x19);
                        AI_DisableBehavior(self->ai, 7);
                        break;
                    case 2:
                        AI_EnableBehavior(self->ai, 7);
                        break;
                    case 3:
                        AI_EnableBehavior(self->ai, 0xD);
                        break;
                    case 4:
                        AI_DisableBehavior(self->ai, 2);
                        break;
                    case 5:
                        AI_SetTaskDone(self, 1);
                        break;
                    case 6:
                        AI_EnableBehavior(self->ai, 0x13);
                        break;
                    }
                } else {
                }
            } else if (BitSet_Test(fn_80151C8C(self->brain), 0) && !fn_80151430(self->brain)) {
                if (fn_80134870(self->ai)) {
                    Vector from;
                    Vector dir;
                    fn_8042DC84(&from, fn_800B1724(*AI_GetEntity(self->ai)));
                    from.z += 1.0f;
                    fn_80429038(&dir, fn_800B1724(*fn_80134870(self->ai)), &from);
                    float len = fn_8042EC54(&dir);
                    len -= fn_800B2670(*fn_80134870(self->ai));
                    int clear = !fn_8004A9CC(&from, &dir, len, 0x8000, 0, fn_800B24AC(*AI_GetEntity(self->ai)),
                                             fn_800B1CC8(*AI_GetEntity(self->ai)), 0, 3);
                    int hidden = 0;
                    if (fn_800B0C58(*fn_80134870(self->ai))
                        && fn_800CCA08(*fn_80085954(fn_800B14A0(*fn_80134870(self->ai)))))
                        hidden = 1;
                    if (clear && !hidden)
                        AI_EnableBehavior(self->ai, 9);
                    else
                        AI_DisableBehavior(self->ai, 9);
                }
                fn_801513D8(self->brain, fn_800B18EC(*AI_GetEntity(self->ai), 0xB8));
                BitSet_Set(fn_80151C8C(self->brain), 1);
            }
        }
        if (AI_TestCondition(self->ai, 0x2D) || AI_TestCondition(self->ai, 0x2C) || AI_TestCondition(self->ai, 0x24))
            AI_EnableBehavior(self->ai, 7);
    } else {
    }
    return 1;
}

extern "C" BrainSelf *fn_8016388C(register BrainSelf *self, register void *ai)
{
    fn_801507C0(self, ai);
    self->vtable = (void *)lbl_804F65A0;
    return self;
}

extern "C" TaskSelf *fn_801638E0(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 3);
    self->vtable = (void *)lbl_804F6568;
    return self;
}

// AI_HUMANTORCH
extern "C" void *fn_80163938(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case -1:
        break;
    default:
        return fn_801641FC(self, id);
    }
    return task;
}

extern "C" BrainSelf *fn_801639B0(register BrainSelf *self, register void *ai)
{
    fn_80164274(self, ai);
    self->vtable = (void *)lbl_804F65B8;
    return self;
}

// AI_IRONMAN
extern "C" void *fn_80163A04(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case -1:
        break;
    default:
        return fn_801641FC(self, id);
    }
    return task;
}

extern "C" BrainSelf *fn_80163A7C(register BrainSelf *self, register void *ai)
{
    fn_80164274(self, ai);
    self->vtable = (void *)lbl_804F65D0;
    return self;
}

// AI_JOHNNYOHM
extern "C" void *fn_80163AD0(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case -1:
        break;
    default:
        return fn_801641FC(self, id);
    }
    return task;
}

extern "C" BrainSelf *fn_80163B48(register BrainSelf *self, register void *ai)
{
    fn_80164274(self, ai);
    self->vtable = (void *)lbl_804F65E8;
    return self;
}

// AI_MAGNETO
extern "C" void *fn_80163B9C(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case -1:
        break;
    default:
        return fn_801641FC(self, id);
    }
    return task;
}

extern "C" BrainSelf *fn_80163C14(register BrainSelf *self, register void *ai)
{
    fn_80164274(self, ai);
    self->vtable = (void *)lbl_804F6600;
    return self;
}

// AI_MEGALITH
extern "C" void *fn_80163C68(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case -1:
        break;
    default:
        return fn_801641FC(self, id);
    }
    return task;
}

extern "C" BrainSelf *fn_80163CE0(register BrainSelf *self, register void *ai)
{
    fn_80164274(self, ai);
    self->vtable = (void *)lbl_804F6618;
    return self;
}

// AI_PEON
extern "C" void *fn_80163D34(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case -1:
        break;
    default:
        return fn_80150AA8(self, id);
    }
    return task;
}

extern "C" BrainSelf *fn_80163DAC(register BrainSelf *self, register void *ai)
{
    fn_801507C0(self, ai);
    self->vtable = (void *)lbl_804F6630;
    return self;
}

// AI_ROEKEL
extern "C" void *fn_80163E00(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case -1:
        break;
    default:
        return fn_801641FC(self, id);
    }
    return task;
}

extern "C" BrainSelf *fn_80163E78(register BrainSelf *self, register void *ai)
{
    fn_80164274(self, ai);
    self->vtable = (void *)lbl_804F6648;
    return self;
}

// AI_SPIDERMAN
extern "C" void *fn_80163ECC(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case -1:
        break;
    default:
        return fn_801641FC(self, id);
    }
    return task;
}

extern "C" BrainSelf *fn_80163F44(register BrainSelf *self, register void *ai)
{
    fn_80164274(self, ai);
    self->vtable = (void *)lbl_804F6660;
    return self;
}

// AI_STORM
extern "C" void *fn_80163F98(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case -1:
        break;
    default:
        return fn_801641FC(self, id);
    }
    return task;
}

extern "C" BrainSelf *fn_80164010(register BrainSelf *self, register void *ai)
{
    fn_80164274(self, ai);
    self->vtable = (void *)lbl_804F6678;
    return self;
}

// AI_THING
extern "C" void *fn_80164064(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case -1:
        break;
    default:
        return fn_801641FC(self, id);
    }
    return task;
}

extern "C" BrainSelf *fn_801640DC(register BrainSelf *self, register void *ai)
{
    fn_80164274(self, ai);
    self->vtable = (void *)lbl_804F6690;
    return self;
}

// AI_VENOM
extern "C" void *fn_80164130(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case -1:
        break;
    default:
        return fn_801641FC(self, id);
    }
    return task;
}

extern "C" BrainSelf *fn_801641A8(register BrainSelf *self, register void *ai)
{
    fn_80164274(self, ai);
    self->vtable = (void *)lbl_804F66A8;
    return self;
}

// The base of most named-character brains (docs/ai.md section 4.2)
extern "C" void *fn_801641FC(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case -1:
        break;
    default:
        return fn_80150AA8(self, id);
    }
    return task;
}

extern "C" BrainSelf *fn_80164274(register BrainSelf *self, register void *ai)
{
    fn_801507C0(self, ai);
    self->vtable = (void *)lbl_804F66C0;
    return self;
}

// AI_PARADOX
extern "C" void *fn_801642C8(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case -1:
        break;
    default:
        return fn_801641FC(self, id);
    }
    return task;
}

extern "C" BrainSelf *fn_80164340(register BrainSelf *self, register void *ai)
{
    fn_80164274(self, ai);
    self->vtable = (void *)lbl_804F66D8;
    return self;
}

// AI_WOLVERINE
extern "C" void *fn_80164394(register BrainSelf *self, int id)
{
    void *task = 0;
    switch (id) {
    case -1:
        break;
    default:
        return fn_801641FC(self, id);
    }
    return task;
}

extern "C" BrainSelf *fn_8016440C(register BrainSelf *self, register void *ai)
{
    fn_80164274(self, ai);
    self->vtable = (void *)lbl_804F66F0;
    return self;
}
