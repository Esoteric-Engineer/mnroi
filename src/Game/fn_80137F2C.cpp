// AI behavior registry (the 42-entry table, the action pool, the "Behaviors" debug list), then the handlers. docs/ai.md rows 2 and 13.
// .rodata 0x8049AB14-0x8049AD94: the behavior names, the list title and the float pools (IDLE's from 0x8049AD88).

inline int sn_return_decl(int a) { return a; }

struct Vec4 {
    float x;
    float y;
    float z;
    float w;
};

class AIBehavior;
typedef void *(*BehaviorFn)(void *ai, AIBehavior *rec);

class AIBehavior // 0x1C bytes, lbl_80571814[id]
{
public:
    int id;                // +0x0
    int started;           // +0x4
    int pad8;              // +0x8
    const char *name;      // +0xC
    BehaviorFn update;     // +0x10
    BehaviorFn enter;      // +0x14
    BehaviorFn exit;       // +0x18
    void init(int id, const char *name, BehaviorFn update, BehaviorFn enter, BehaviorFn exit);
    void *run(void *ai);
    void *start(void *ai);
};

class AIAction // 0x70 bytes, lbl_8056A7F0[256], handed out by fn_80138738 (guess)
{
public:
    char pad0[0x2C];
    int kind;  // +0x2C
    Vec4 pos;  // +0x30
    float f;   // +0x40
    char pad44[0x2C];
    int setPos(int kind, Vec4 *pos, float f);
    void init(int a, int b, int c);
};

class AISmallSet // up to 8 ints (guess)
{
public:
    int pad0[2];
    unsigned int count; // +0x8
    int items[8];       // +0xC
    int add(int x);
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

struct Ent {
    int pad;
};

struct PEnt : Ent { // matching_notes 50
    int x;
};

extern AIBehavior lbl_80571814[];
extern AIAction lbl_8056A7F0[];
extern char lbl_805717F0[]; // pool of free Actions
extern char lbl_80593BE8[];
extern void *lbl_8066BF5C;
extern void *lbl_8066D6DC; // the overlay text object (docs/versus.md section 6)

extern "C" {
int sprintf(char *buf, const char *fmt, ...);
void fn_80138030(void);
void fn_8013866C(void);
AIAction *fn_80138E10(void *ai, AIBehavior *rec);
AIAction *fn_8013922C(void *ai, AIBehavior *rec);
AIAction *fn_80139258(void *ai, AIBehavior *rec);
void fn_801399CC(void);
void fn_80139284(void);
void fn_801397C8(void);
void fn_8013B0F4(void);
void fn_8013BCE8(void);
void fn_8013C1C8(void);
void fn_8013C3A4(void);
void fn_8013CD40(void);
void fn_8013D464(void);
void fn_8013DA7C(void);
void fn_8013E0C4(void);
void fn_8013E99C(void);
void fn_8013F08C(void);
void fn_8013F438(void);
void fn_8013F8D0(void);
void fn_8013F9F0(void);
void fn_801409D0(void);
void fn_80140C10(void);
void fn_80140E64(void);
void fn_80141394(void);
void fn_801414C8(void);
void fn_80141D78(void);
void fn_8014470C(void);
void fn_80144E30(void);
void fn_801420B4(void);
void fn_80142558(void);
void fn_80142B04(void);
void fn_801426A0(void);
void fn_80142F80(void);
void fn_801435F0(void);
void fn_8014379C(void);
void fn_80144038(void);
void fn_80144544(void);
void fn_80144628(void);
void fn_80144970(void);
void fn_80144CB4(void);
void fn_80144D3C(void);
void fn_80144DB8(void);
void fn_80145200(void);
void fn_80145AA8(void);

void fn_80137FBC(int id, const char *name, BehaviorFn update, BehaviorFn enter, BehaviorFn exit);
void fn_80138C04(AIBehavior *self, int id, const char *name, BehaviorFn update, BehaviorFn enter, BehaviorFn exit);
void *fn_80138D90(AIBehavior *self, void *ai);
void fn_80135D64(void *ai, void *action);
void *fn_80462780(void *ai);
int fn_80442508(void *set, int bit);
void fn_80462B38(AIAction *a);
void fn_801B60F4(void *pool);
void fn_801B6040(void *pool, AIAction *a);
int fn_801B6A44(void *pool);
void *fn_801B6130(void *pool, int idx);
void fn_80462C30(AIAction *a, int v);
void fn_80462CA8(AIAction *a, int v);
void fn_80462C58(AIAction *a, int v);
void fn_80462130(AIAction *a, int v);
void fn_80462C80(AIAction *a, int v);
int fn_8042EFF8(void *p);
void *fn_80462C04(void *a);
float fn_80434040(void *a);
void fn_804620A0(void *a, void *b);
int fn_800B92DC(void **text, const char *s, float x, float y);
void fn_80101188(void *text, float height);
int fn_804624B8(void *text);
void fn_8042AC7C(void *text, unsigned int color);
const char *fn_80462288(AIBehavior *b);
Ent *fn_80134870(void *ai);
PEnt *fn_80442080(void *ai);
int fn_800B0C58(Ent *e);
void *fn_800B14A0(Ent *e);
int fn_80085EEC(void *a);
Vector *fn_800B1724(Ent &e);
Vector &fn_800B1724R(Ent &e) __asm__("fn_800B1724");
Vector *fn_800B1750(Ent &e);
void fn_8042DC84(Vector *dst, Vector *src);
void fn_8042D8A8(Vector *dst, Vector *src);
void fn_8042F76C(Vector *v);
float fn_8042EBF4(Vector *a, Vector *b);
int fn_80138A24(AIAction *a, int bit);
int fn_80138AE0(AIAction *a, int kind, Vector *pos, float f);
void fn_80462BB4(AIAction *a, int v);
int fn_80446E8C(void *ai);
int fn_80086B1C(void *e);
void fn_801362DC(void *ai, int a);
void fn_80447C38(Vector *v);
void *fn_8044203C(void *ai);
int fn_800CE4D0(void *a);
int fn_804421B8(void *ai, int bit);
int fn_804628AC(void *ai);
void *fn_80461DD4(void *ai);
void fn_80442174(void *ai, int bit);
}

#define BH(f) ((BehaviorFn)f)

extern "C" void fn_80137F2C(void)
{
    int i;

    for (i = 0; i <= 0x29; i++) {
        fn_80138C04(&lbl_80571814[i], -1, "BEHAVIOR_NONE", 0, 0, 0);
    }
    fn_80138030();
    fn_8013866C();
}

extern "C" void fn_80137FBC(int id, const char *name, BehaviorFn update, BehaviorFn enter, BehaviorFn exit)
{
    AIBehavior *rec = &lbl_80571814[id];

    fn_80138C04(rec, id, name, update, enter, exit);
}

extern "C" void fn_80138030(void)
{
    fn_80137FBC(0, "IDLE", BH(fn_80138E10), BH(fn_8013922C), BH(fn_80139258));
    fn_80137FBC(1, "APPROACH", BH(fn_801399CC), 0, 0);
    fn_80137FBC(2, "APPROACH_RANGED", BH(fn_80139284), 0, 0);
    fn_80137FBC(3, "TOO_CLOSE", BH(fn_801397C8), 0, 0);
    fn_80137FBC(4, "PRONE", BH(fn_8013B0F4), 0, 0);
    fn_80137FBC(5, "MOVE_TO_WAYPOINT", BH(fn_8013BCE8), 0, 0);
    fn_80137FBC(6, "AVOID_OBSTACLES", BH(fn_8013C1C8), 0, 0);
    fn_80137FBC(7, "BLOCK", BH(fn_8013C3A4), 0, 0);
    fn_80137FBC(10, "JUMP_ATTACK", BH(fn_8013CD40), 0, 0);
    fn_80137FBC(11, "JUMP_ATTACK_PEAK", BH(fn_8013D464), 0, 0);
    fn_80137FBC(12, "JUMP_ATTACK_DESCEND", BH(fn_8013DA7C), 0, 0);
    fn_80137FBC(8, "ATTACK_MELEE", BH(fn_8013E0C4), 0, 0);
    fn_80137FBC(9, "ATTACK_RANGED", BH(fn_8013E99C), 0, 0);
    fn_80137FBC(13, "STRAFE", BH(fn_8013F08C), 0, 0);
    fn_80137FBC(14, "FLY", BH(fn_8013F438), 0, 0);
    fn_80137FBC(15, "SUSPENDED", BH(fn_8013F8D0), 0, 0);
    fn_80137FBC(16, "THROW_OBJECT", BH(fn_8013F9F0), 0, 0);
    fn_80137FBC(17, "BODY_THROW", BH(fn_801409D0), 0, 0);
    fn_80137FBC(18, "SWAT", BH(fn_80140C10), 0, 0);
    fn_80137FBC(19, "PICKUP", BH(fn_80140E64), 0, 0);
    fn_80137FBC(20, "SUPER_BLOCK_THROWN", BH(fn_80141394), 0, 0);
    fn_80137FBC(21, "AVOID_HAZARDS", BH(fn_801414C8), 0, 0);
    fn_80137FBC(22, "DEFEND_REGIONS", BH(fn_80141D78), 0, 0);
    fn_80137FBC(23, "ROOFTOP_REGIONS", BH(fn_8014470C), 0, 0);
    fn_80137FBC(24, "HOVER", BH(fn_80144E30), 0, 0);
    fn_80137FBC(25, "DODGE", BH(fn_801420B4), 0, 0);
    fn_80137FBC(26, "AVOID_ACTORS", BH(fn_80142558), 0, 0);
    fn_80137FBC(27, "JUMP", BH(fn_80142B04), 0, 0);
    fn_80137FBC(28, "AVOID_OBJECTS", BH(fn_801426A0), 0, 0);
    fn_80137FBC(29, "EVADE", BH(fn_80142F80), 0, 0);
    fn_80137FBC(30, "TURN_TOWARDS", BH(fn_801435F0), 0, 0);
    fn_80137FBC(32, "SWING", BH(fn_8014379C), 0, 0);
    fn_80137FBC(33, "WALL_CLIMB", BH(fn_80144038), 0, 0);
    fn_80137FBC(34, "WALL_CLIMB_MELEE_ATTACK", BH(fn_80144544), 0, 0);
    fn_80137FBC(35, "WALL_CLIMB_RANGED_ATTACK", BH(fn_80144628), 0, 0);
    fn_80137FBC(36, "APPROACH_MOBILITY", BH(fn_80144970), 0, 0);
    fn_80137FBC(37, "FORCE_SUPER_BLOCK", BH(fn_80144CB4), 0, 0);
    fn_80137FBC(38, "FORCE_POWER_STAND", BH(fn_80144D3C), 0, 0);
    fn_80137FBC(39, "FORCE_FLY", BH(fn_80144DB8), 0, 0);
    fn_80137FBC(40, "FLYER_MOVE", BH(fn_80145200), 0, 0);
    fn_80137FBC(41, "POWER_STAND", BH(fn_80145AA8), 0, 0);
}

extern "C" void fn_80138584(void)
{
}

extern "C" void fn_801385A0(void *ai)
{
    int i;

    lbl_8066BF5C = ai;
    for (i = 0; i <= 0x29; i++) {
        if (fn_80442508(fn_80462780(ai), i)) {
            void *t = lbl_80571814[i].run(ai);
            if (t) {
                fn_80135D64(ai, t);
            }
        }
    }
    lbl_8066BF5C = 0;
}

extern "C" void fn_8013866C(void)
{
    {
        int i;
        for (i = 0; i <= 0xFF; i++) {
            AIAction *a = &lbl_8056A7F0[i];
            fn_80462B38(a);
        }
    }
    fn_801B60F4(lbl_805717F0);
    {
        int j;
        for (j = 0; j <= 0xFF; j++) {
            fn_801B6040(lbl_805717F0, &lbl_8056A7F0[j]);
        }
    }
}

extern "C" AIAction *fn_80138738(int a, int b, int c)
{
    int n = fn_801B6A44(lbl_805717F0);
    if (n <= 0) {
        return 0;
    }
    AIAction *item = (AIAction *)fn_801B6130(lbl_805717F0, n - 1);
    fn_80462C30(item, b);
    fn_80462CA8(item, c);
    fn_80462C58(item, fn_8042EFF8(lbl_80593BE8));
    fn_80462130(item, 1);
    fn_80462C80(item, a);
    return item;
}

extern "C" void fn_8013880C(AIAction *a)
{
    if (a == 0) {
        return;
    }
    fn_80462B38(a);
    fn_801B6040(lbl_805717F0, a);
    return;
}

extern "C" float fn_80138868(void *ai, float x, float y)
{
    float dy = 0.0f;
    char buf[0x50];
    sprintf(buf, "Behaviors");
    fn_800B92DC(&lbl_8066D6DC, buf, x, y + dy);
    dy += 12.0f;
    fn_80101188(lbl_8066D6DC, 10.0f);
    unsigned int saved = fn_804624B8(lbl_8066D6DC);
    int i;
    for (i = 0; i <= 0x29; i++) {
        unsigned int color = 0xFFC04000;
        if (fn_80442508(fn_80462780(ai), i)) {
            color = 0xFF10C000;
        }
        fn_8042AC7C(lbl_8066D6DC, color);
        fn_800B92DC(&lbl_8066D6DC, fn_80462288(&lbl_80571814[i]), x, y + dy);
        dy += 9.0f;
        if (i == 0x23) {
            dy = 0.0f;
            x = 210.0f;
            y = 220.0f;
        }
    }
    fn_8042AC7C(lbl_8066D6DC, saved);
    return dy;
}

__asm__(".text\n\t.globl fn_80138A24\n\t.type fn_80138A24,@function\nfn_80138A24:");
int AISmallSet::add(int x)
{
    unsigned int i;

    for (i = 0; i < count; i++) {
        if (items[i] == x) {
            return 0;
        }
    }
    if (count > 7) {
        return 0;
    }
    items[count++] = x;
    return 1;
}
__asm__(".size fn_80138A24, 0xBC");

__asm__(".text\n\t.globl fn_80138AE0\n\t.type fn_80138AE0,@function\nfn_80138AE0:");
int AIAction::setPos(int k, Vec4 *p, float v)
{
    if (p == 0) {
        return 0;
    }
    kind = k;
    pos = *p;
    f = v;
    if (k != 7) {
        pos.z = 0.0f;
    }
    return 1;
}
__asm__(".size fn_80138AE0, 0x9C");

__asm__(".text\n\t.globl fn_80138B7C\n\t.type fn_80138B7C,@function\nfn_80138B7C:");
void AIAction::init(int a, int b, int c)
{
    fn_80462C30(this, b);
    fn_80462CA8(this, c);
    fn_80462C58(this, fn_8042EFF8(lbl_80593BE8));
    fn_80462130(this, 1);
    fn_80462C80(this, a);
}
__asm__(".size fn_80138B7C, 0x88");

__asm__(".text\n\t.globl fn_80138C04\n\t.type fn_80138C04,@function\nfn_80138C04:");
void AIBehavior::init(int i, const char *n, BehaviorFn u, BehaviorFn e, BehaviorFn x)
{
    id = i;
    name = n;
    update = u;
    enter = e;
    exit = x;
    started = 0;
    pad8 = 0;
}
__asm__(".size fn_80138C04, 0x6C");

__asm__(".text\n\t.globl fn_80138C70\n\t.type fn_80138C70,@function\nfn_80138C70:");
void *AIBehavior::run(void *ai)
{
    void *r = 0;

    if (started == 0) {
        r = fn_80138D90(this, ai);
        started = 1;
    }
    if (update) {
        void *t = 0;
        int n;
        t = update(ai, this);
        if (t) {
            if (fn_80434040(fn_80462C04(t)) > 0.0f) {
                n = 0;
                n++;
            }
        }
        if (r) {
            if (t) {
                fn_804620A0(r, t);
            }
        } else {
            r = t;
        }
    }
    return r;
}
__asm__(".size fn_80138C70, 0x120");

__asm__(".text\n\t.globl fn_80138D90\n\t.type fn_80138D90,@function\nfn_80138D90:");
void *AIBehavior::start(void *ai)
{
    void *r = 0;

    if (enter) {
        r = enter(ai, this);
    }
    started = 1;
    return r;
}
__asm__(".size fn_80138D90, 0x80");

// IDLE and its enter/exit (docs/ai.md section 4.3).
extern "C" AIAction *fn_80138E10(void *ai, AIBehavior *rec)
{
    Ent *t = fn_80134870(ai);
    AIAction *h;

    if (t) {
        if (fn_80134870(ai) && fn_800B0C58(fn_80134870(ai)) && fn_80085EEC(fn_800B14A0(fn_80134870(ai)))) {
            h = fn_80138738(0, 2000, 500);
            if (h) {
                Vector v;
                float f = 0.08f;
                fn_8042DC84(&v, fn_800B1724(*t));
                v.z = fn_800B1724R(*fn_80442080(ai)).z;
                fn_8042D8A8(&v, fn_800B1724(*fn_80442080(ai)));
                fn_8042F76C(&v);
                fn_80138AE0(h, 0, &v, f);
                fn_80138A24(h, 0x13);
                fn_80462BB4(h, 5);
                return h;
            }
        } else if (fn_80446E8C(ai) && fn_80086B1C(fn_80442080(ai))) {
            fn_801362DC(ai, 0);
            h = fn_80138738(0, 100, 300);
            if (h) {
                Vector v;
                fn_80447C38(&v);
                fn_80138A24(h, 7);
                fn_80138AE0(h, 0, &v, 1.0f);
            }
            return h;
        } else if (fn_800CE4D0(fn_8044203C(ai)) && fn_804421B8(ai, 0xe) && !fn_804628AC(ai) &&
                   (fn_80442508(fn_80461DD4(ai), 1) || fn_80442508(fn_80461DD4(ai), 2))) {
            fn_80442174(ai, 0xe);
        } else {
            h = fn_80138738(-1, 0, 0);
            if (h) {
                Vector v;
                float f = 0.08f;
                fn_8042DC84(&v, fn_800B1724(*t));
                v.z = fn_800B1724R(*fn_80442080(ai)).z;
                fn_8042D8A8(&v, fn_800B1724(*fn_80442080(ai)));
                fn_8042F76C(&v);
                float facing = fn_8042EBF4(fn_800B1750(*fn_80442080(ai)), &v);
                if (facing < 0.66f)
                    fn_80138AE0(h, 0, &v, f);
            }
            return h;
        }
    }
    return 0;
}

extern "C" AIAction *fn_8013922C(void *ai, AIBehavior *rec)
{
    return 0;
}

extern "C" AIAction *fn_80139258(void *ai, AIBehavior *rec)
{
    return 0;
}
