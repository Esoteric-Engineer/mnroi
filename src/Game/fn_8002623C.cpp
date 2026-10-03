// fn_8002623C: per frame, gathers one actor's live effects into five parallel arrays for fn_8001DCE0, and reports the best node of the world's list through Actor's vtable slot 11.
// The last of fn_80020E60's three callers.
//
// Names are guesses. The unit owns the float pool at 0x80484E58.


// __6Vector is 0x80428F74; the 8-byte alignment is load-bearing (docs/prodg.md).
class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

// One record in the table EffectManager+0x3C points at.
typedef struct Rec
{
    char unk0[0x4C];
} Rec;

// One live effect; +0x30 and +0x34 are as Game/fn_8001C258.cpp has them.
typedef struct Effect
{
    char unk0[0x10];
    Vector pos;  // +0x10
    char unk20[0x8];
    int unk28;   // +0x28
    char unk2C[0x4];
    int type;    // +0x30
    void *owner; // +0x34 the actor the effect is attached to
    char unk38[0x8];
    float unk40; // +0x40
    char unk44[0xC];
} Effect;

typedef struct EffectManager
{
    int unk0;           // +0x00
    char unk4[0x38];
    Rec *records;       // +0x3C
    char unk40[0x350];
    Effect effects[64]; // +0x390
    int numEffects;     // +0x1790
    char unk1794[0x19C];
} EffectManager; // 0x1930

// lbl_80515030, one global of 0xB050: `extra` is reached as an offset from its start.
typedef struct EffectSystem
{
    EffectManager managers[6]; // +0x0000
    char unk9630[0xF0];
    EffectManager extra;       // +0x9720
} EffectSystem;

// The 0xA0 state object fn_80430128 constructs and fn_8001DCE0 / fn_8001F374 take.
typedef struct AimState
{
    char unk0[0xA0];
} AimState;

// The vtable pointer goes after the data members, so the data fills exactly 0x198 bytes.
class Actor
{
public:
    char unk0[0x120];
    int unk120;    // +0x120
    int unk124[4]; // +0x124
    int unk134[4]; // +0x134
    char unk144[0x54];
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
    virtual void v11(Vector *target, float f, int a, int b);
};

class SceneObj
{
public:
    char unk0[0xC8];
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
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void v65();
    virtual void v66();
    virtual void v67();
    virtual int v68();
};

typedef struct Node
{
    struct Node *next; // +0x00
    SceneObj *obj;     // +0x04
    char unk8[0x48];
    Vector pos;        // +0x50
    float unk60;       // +0x60
} Node;

typedef struct World
{
    char unk0[0x28];
    Node *nodes; // +0x28
    char unk2C[0xB8];
    int unkE4;   // +0xE4
} World;

extern "C" {
extern Actor *fn_800B1568(void *entity);
extern World *fn_800B1CC8(void *entity);
extern Vector *fn_800B1724(void *actor);
extern float fn_800B2620(Actor *actor);
extern float fn_800B2670(Actor *actor);
extern void fn_8042DC84(Vector *dst, Vector *src);
extern float fn_8002851C(Vector *a, Vector *b, float r);
extern void fn_80430128(AimState *state);
extern int fn_8001C744(Actor *actor);
extern int fn_80392510(SceneObj *obj);
extern Actor *fn_8039C918(SceneObj *obj);
extern int fn_8042FEFC(void *obj);
extern int fn_80020E60(Actor *actor);
extern void fn_8001DCE0(Rec *rec, AimState *state, Vector *pos, int a, int count, Rec **recs,
                        Vector *offsets, int *ids, float *scales, int *flags, int type);
extern void fn_8001F374(AimState *state, Actor *actor);
extern void *memset(void *dst, int c, unsigned int n);
}

extern AimState lbl_80514EF0; // the live state
extern AimState lbl_80514F90; // the defaults it is reset from
extern EffectSystem lbl_80515030;
extern char lbl_8057E430[];
extern int lbl_8066B5EC; // which manager in lbl_80515030.managers is current
extern int lbl_8066B600;

extern "C" void fn_8002623C(void *entity)
{
    Actor *x = fn_800B1568(entity);
    World *w;
    Vector pos;
    Vector *best = 0;
    float bestVal = 0.0f;

    w = fn_800B1CC8(entity);
    if (w == 0) {
        return;
    }

    x->v10();

    fn_8042DC84(&pos, fn_800B1724(x));

    if (w->unkE4 == lbl_8066B600) {
        Node *node;

        for (node = w->nodes; node != 0; node = node->next) {
            if (node->obj != 0
                && (!node->obj->v68()
                    || (fn_80392510(node->obj) && fn_8039C918(node->obj) != x))) {
                continue;
            }
            if (node->unk60 > 0.0f) {
                float d;

                d = fn_8002851C(&pos, &node->pos, fn_800B2670(x));
                if (d > bestVal) {
                    best = &node->pos;
                    bestVal = d;
                }
            }
        }
    }

    if (lbl_80515030.managers[lbl_8066B5EC].unk0 == 0) {
        lbl_80514EF0 = lbl_80514F90;
    } else {
        AimState scratch;

        fn_80430128(&scratch);
        if (fn_8001C744(x) == 0) {
            lbl_80514EF0 = lbl_80514F90;
        } else {
            pos.z += fn_800B2620(x) * 0.5f;

            Rec *recs[5];
            Vector offsets[5];
            int ids[5];
            int flags[5];
            float scales[5];
            int count = 0;
            int i;

            for (i = 0; i <= 3; i++) {
                if (x->unk134[i] >= 0) {
                    void *owner;

                    ids[count] = lbl_80515030.managers[lbl_8066B5EC].effects[x->unk124[i]].unk28;
                    scales[count] = lbl_80515030.managers[lbl_8066B5EC].effects[x->unk124[i]].unk40;
                    flags[count] =
                        lbl_80515030.managers[lbl_8066B5EC].effects[x->unk124[i]].type != 0;
                    if (ids[count] != 0) {
                        recs[count] = &lbl_80515030.extra.records[x->unk134[i]];
                    } else {
                        recs[count] = &lbl_80515030.managers[lbl_8066B5EC].records[x->unk134[i]];
                    }
                    offsets[count] =
                        lbl_80515030.managers[lbl_8066B5EC].effects[x->unk124[i]].pos;
                    owner = lbl_80515030.managers[lbl_8066B5EC].effects[x->unk124[i]].owner;
                    if (owner != 0) {
                        offsets[count].x -= fn_800B1724(owner)->x;
                        offsets[count].y -= fn_800B1724(owner)->y;
                        offsets[count].z -= fn_800B1724(owner)->z;
                    }
                    count++;
                }
            }

            if (x->unk120 >= 0) {
                ids[count] = 0;
                scales[count] = 1.0f;
                flags[count] = 0;
                recs[count] = &lbl_80515030.managers[lbl_8066B5EC].records[x->unk120];
                memset(&offsets[count], 0, 0x10);
                count++;
            }

            if (count == 0) {
                lbl_80514EF0 = lbl_80514F90;
            } else {
                int type = fn_80020E60(x);

                fn_8001DCE0(recs[0], &lbl_80514EF0, &pos, 0, count, recs, offsets, ids, scales,
                            flags, type);
            }
        }
    }

    fn_8001F374(&lbl_80514EF0, x);
    if (best != 0) {
        x->v11(best, 1.0f, 0, fn_8042FEFC(lbl_8057E430));
    }
}
