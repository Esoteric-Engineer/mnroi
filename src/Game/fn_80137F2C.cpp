// AI behavior registry (the 42-entry table, the action pool, the "Behaviors" debug list), then the handlers. docs/ai.md rows 2 and 13.
// .rodata 0x8049AB10-0x8049AE60: the behavior names, the list title, then each handler's float pool in .text order.
__asm__(".section .rodata\n\t.globl lbl_8049AB10\nlbl_8049AB10:\n\t.4byte 0x6C696400\n\t.text"); // 8-aligns the claim: the tail of the "invalid" string ahead of it, which no code reads

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
    char pad8[0x300];
    unsigned int f308; // +0x308
};

struct FEnt { // fn_80462734's result
    char pad[0x2A0];
    unsigned int f2a0; // +0x2A0
};

struct Base {
    int pad;
};

class Placement { // fn_8004A9CC's hit record
public:
    char d[0x40];
    Placement();
};

struct Target { // fn_80134870's result as ATTACK_RANGED reads it
    char pad0[0x50];
    float minX; // +0x50 (guess: bounds)
    float minY; // +0x54
    char pad58[0x8];
    float maxX; // +0x60
    float maxY; // +0x64
    char pad68[0x130];
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5(Vector *out, int a); // vtable +0x30
};

struct TSub : Target {
    int pad;
};

struct Actor {
    char pad0[0x308];
    unsigned int flags; // +0x308
};

#define ABS(x) ((x) < 0.0f ? -(x) : (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

struct SCtl : Base { // fn_8044203C's result, reference arguments convert (matching_notes 50)
    int x;
};

struct Body : Base { // fn_80085954's result, vptr +0x3AC
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

struct VEnt { // fn_80442080's result with its vptr, +0x198
    char d[0x198];
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
    virtual int v57(float f); // +0x1D0
};

struct Region { // a volume registry list 1 entry (docs/ai.md section 4.5)
    char pad0[0x10];
    Vector centre; // +0x10
    char pad20[0x310];
    int owner; // +0x330, actor id
};

extern AIBehavior lbl_80571814[];
extern AIAction lbl_8056A7F0[];
extern char lbl_805717F0[]; // pool of free Actions
extern char lbl_80593BE8[];
extern Vector lbl_80593E00;
extern Vector lbl_80593DD0;
extern Vector lbl_80593DE0;
extern void *lbl_8066BF5C;
extern float lbl_8066BF60;
extern void *lbl_8066D6DC; // the overlay text object (docs/versus.md section 6)

extern "C" {
int sprintf(char *buf, const char *fmt, ...);
void fn_80138030(void);
void fn_8013866C(void);
AIAction *fn_80138E10(void *ai, AIBehavior *rec);
AIAction *fn_8013922C(void *ai, AIBehavior *rec);
AIAction *fn_80139258(void *ai, AIBehavior *rec);
AIAction *fn_801399CC(void *ai, AIBehavior *rec);
AIAction *fn_80139284(void *ai, AIBehavior *rec);
AIAction *fn_801397C8(void *ai, AIBehavior *rec);
AIAction *fn_8013B0F4(void *ai, AIBehavior *rec);
AIAction *fn_8013BCE8(void *ai, AIBehavior *rec);
AIAction *fn_8013C1C8(void *ai, AIBehavior *rec);
AIAction *fn_8013C3A4(void *ai, AIBehavior *rec);
AIAction *fn_8013CD40(void *ai, AIBehavior *rec);
AIAction *fn_8013D464(void *ai, AIBehavior *rec);
AIAction *fn_8013DA7C(void *ai, AIBehavior *rec);
AIAction *fn_8013E0C4(void *ai, AIBehavior *rec);
AIAction *fn_8013E99C(void *ai, AIBehavior *rec);
AIAction *fn_8013F08C(void *ai, AIBehavior *rec);
AIAction *fn_8013F438(void *ai, AIBehavior *rec);
AIAction *fn_8013F8D0(void *ai, AIBehavior *rec);
AIAction *fn_8013F9F0(void *ai, AIBehavior *rec);
AIAction *fn_801409D0(void *ai, AIBehavior *rec);
AIAction *fn_80140C10(void *ai, AIBehavior *rec);
AIAction *fn_80140E64(void *ai, AIBehavior *rec);
AIAction *fn_80141394(void *ai, AIBehavior *rec);
AIAction *fn_801414C8(void *ai, AIBehavior *rec);
AIAction *fn_80141D78(void *ai, AIBehavior *rec);
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
SCtl *fn_8044203C(void *ai);
int fn_800CE4D0(void *a);
int fn_804421B8(void *ai, int bit);
int fn_804628AC(void *ai);
void *fn_80461DD4(void *ai);
void fn_80442174(void *ai, int bit);
int fn_80461D48(void *ai, int bit);
int fn_80133208(void *e);
char *fn_804420AC(void *ai);
int fn_80461BA0(void *p);
int fn_80461BCC(void *p);
Vector *fn_804625CC(void *p);
Vector *fn_804625F8(void *p);
float fn_8015E580(Vector *a, Vector *b);
float fn_800B1884(Ent &e, int id);
int fn_800861EC(void *e);
Body *fn_80085954(void *p);
int fn_800CCBD8(Base &b);
void fn_80433FFC(Vector *v);
int fn_8015F384(void *ai);
float fn_8015E64C(void *ai);
int fn_801600DC(void *ai, int side, float dist);
int fn_800CDA20(Base &c);
void *fn_8044734C(char *mover);
int fn_80444570(void *wp);
int fn_804445A4(void *wp);
void *fn_80444904(void *wp, int i);
void *fn_80444984(void *wp, int i);
Vector *fn_80444688(void *spot);
void fn_8014B900(char *mover);
int fn_8015F6CC(void *ai, Vector *out);
void *fn_800CD9B0(Base &c);
void *fn_800B1478(void *e);
int fn_800A4130(void *e);
int fn_8015ED50(void *ai, void *pos);
void fn_801363A4(void *ai, int a);
float fn_8015F608(void *ai, Vector *p, Vector *out);
float fn_804290F8(Vector *a, Vector *b);
int fn_80085D3C(void *e);
void fn_80138B7C(AIAction *a, int k, int b, int c);
void fn_80429038(Vector *out, Vector *a, Vector *b);
float fn_8042EC54(Vector *v);
void fn_80067050(Ent &e, Vector *out);
float fn_8015F538(void *ai, Vector *p, Vector *out);
int fn_801369B0(void *ai);
float fn_8015E8A8(void *ai, Vector *p);
int fn_804625A0(char *mover);
int fn_800B13D8(Ent &e);
void fn_8014B63C(char *mover, int id, int b);
int fn_8015F07C(void *ai);
int fn_8015EE34(void *ai, Ent *e);
int fn_8015E2FC(void *ai, Vector *to, float r, int *hit, float height);
int fn_800CC96C(Base &c);
int fn_800CC6DC(Base &c);
int fn_8008603C(void *e);
int fn_800860CC(void *e);
int fn_80085F7C(void *e);
int fn_80085FDC(void *e);
int fn_8008609C(void *e);
int fn_8015F410(void *ai, float min);
float fn_80461EE4(void *ai);
float fn_80461F3C(void *ai);
float fn_80461FC0(void *ai);
int fn_8015EC80(float percent, float seconds);
int fn_8015EC1C(float chance);
void *fn_804420D8(void *ai);
Ent *fn_804624EC(void *p);
int fn_800B0CC0(void *e);
int fn_800A4538(void *p);
int fn_800A3EE4(void *p);
int fn_800A3F44(void *p);
int fn_8015E764(void *ai, Vector *p);
int fn_800E5F04(Base &c, void *other);
int fn_801368B8(void *ai);
int fn_80461C94(char *mover);
int fn_800CCC28(Base &c);
int fn_80462624(char *mover);
int fn_8015F008(void *ai);
int fn_80462880(void *ai);
float fn_80462954(void *ai);
float fn_80462980(void *ai);
float fn_80462AB4(void *ai);
float fn_804629AC(void *ai);
float fn_804629D8(void *ai);
float fn_80462AE0(void *ai);
int fn_8015E97C(float f);
void fn_80136214(void *ai, int a);
Ent *fn_804626F0(void *ai);
SCtl *fn_800B14A0S(Ent *e) __asm__("fn_800B14A0");
int fn_8009B04C(Base &b);
int fn_801603CC(void *ai, int axis);
Vector *fn_800B17A8(Ent &e);
void fn_8042D80C(Vector *dst, Vector *src);
unsigned int fn_8015EA6C(int a, float *d);
int fn_8008618C(void *e);
float fn_80086730(void *e);
int fn_800CD0EC(Base &c);
void *fn_800ACFA8(int handle);
int fn_800860FC(void *e);
Ent *fn_80462530(void *brain);
int fn_8008615C(void *e);
float fn_80461F94(void *ai);
int fn_800CD174(Base &c);
int fn_800CD21C(Base &c);
int fn_80462928(void *ai);
void fn_804627AC(void *ai, int v);
void fn_80462800(void *ai, int v);
void fn_80462900(void *ai, int v);
unsigned int fn_804627D4(void *ai);
VEnt *fn_80442080V(void *ai) __asm__("fn_80442080");
Vector *fn_800CE230(SCtl &c);
void fn_80435530(Vector *v, float s);
int fn_800CCA58(Base &c);
int fn_800CCAE8(Base &c);
void fn_80462BDC(AIAction *a, float v);
void fn_8014F7B0(void *list, int mode);
Ent *fn_8046267C(void *ai);
int fn_8008572C(void *a, void *b);
float fn_80462A04(void *ai);
float fn_80462B0C(void *ai);
int fn_80086908(void *e);
float fn_80462A30(void *ai);
Vector *fn_800B1668(Ent &e);
int fn_8015EA18(unsigned int n);
int fn_8015FFD4(void *ai);
float fn_800867A8(void *e);
float fn_8008666C(void *e);
FEnt *fn_80462734(void *ai);
Body *fn_8044203CB(void *ai) __asm__("fn_8044203C");
unsigned int fn_800CC2B4(Base &c);
float fn_80462A5C(void *ai);
float fn_80462A88(void *ai);
void fn_80461E58(void *ai, Vector *v);
int fn_800CCC28(Base &c);
int fn_800B0C1C(Ent *e);
int fn_801500C4(void *list);
Ent *fn_801500F0(void *list, int i);
int fn_800866C0(void *e);
int fn_800CD2E8(Base &b);
float fn_80461F10(void *ai);
int fn_8015E830(void *ai);
int fn_8009B04CE(Ent &e) __asm__("fn_8009B04C");
Target *fn_80134870T(void *ai) __asm__("fn_80134870");
TSub *fn_80442080T(void *ai) __asm__("fn_80442080");
Actor *fn_80442080A(void *ai) __asm__("fn_80442080");
void *fn_800B24AC(Ent &actor);
void *fn_800B1CC8(Ent &actor);
unsigned int fn_800B18EC(Ent &e, int id);
int fn_8004A9CC(Vector *from, Vector *dir, float len, unsigned int mask, Placement *hit, void *a, void *b, int c, int d);
int fn_8015EEA0(void *ai);
int fn_800862DC(void *e);
float fn_8014B824(void *mover);
int fn_8015F0F0(void *ai, Ent *t);
int fn_80086B6C(void *e);
Target *fn_800CD9B0T(Base &c) __asm__("fn_800CD9B0");
void fn_8042F984(Vector *out, Vector *a, Vector *b);
void fn_80429090(Vector *out, Vector *a, Vector *b, float s);
void *fn_8013726C(void *ai);
int fn_80462D68(void *list);
void *fn_80462DB0(void *list, int i);
int fn_804622B4(void *list);
void *fn_804622FC(void *list, int i);
int fn_80462E98(void *list);
Ent *fn_80462EE0(void *list, int i);
int fn_801464E4(void *rec, Vector *pos);
void fn_80146604(void *rec, Vector *pos, Vector *out);
int fn_80146A88(void *rec, Vector *a, Vector *b, Vector *hit);
float fn_8042CE28(unsigned int n);
void fn_8042D854(Vector *dst, Vector *src);
int fn_8008606C(void *e);
int fn_80462CD0(void *list);
Region *fn_80462D18(void *list, int i);
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

// APPROACH_RANGED (docs/ai.md section 4.3).
extern "C" AIAction *fn_80139284(void *ai, AIBehavior *rec)
{
    if (fn_80461D48(ai, 2)) {
        Ent *t = fn_80134870(ai);
        if (!t) {
            return 0;
        }
        if (!fn_80133208(fn_80442080(ai))) {
            return 0;
        }
        Vector *me = fn_800B1724(*fn_80442080(ai));
        Vector goal;
        int found = 0;
        fn_8042DC84(&goal, me);
        if (fn_80461BA0(fn_804420AC(ai))) {
            fn_8042DC84(&goal, fn_804625CC(fn_804420AC(ai)));
            found = 1;
        }
        if (!found && fn_80461BCC(fn_804420AC(ai))) {
            fn_8042DC84(&goal, fn_804625F8(fn_804420AC(ai)));
            found = 1;
        }
        if (!found && fn_80134870(ai)) {
            fn_8042DC84(&goal, fn_800B1724(*fn_80134870(ai)));
            found = 1;
        }
        float toGoal = fn_8015E580(me, &goal);
        float toTarget = fn_8015E580(me, fn_800B1724(*t));
        float far = fn_800B1884(*fn_80442080(ai), 0xd4);
        float near = fn_800B1884(*fn_80442080(ai), 0xd3);
        if (fn_800861EC(fn_80442080(ai)) && fn_800B0C58(t)) {
            if (!fn_80085954(fn_800B14A0(t))->v42() && !fn_800CCBD8(*fn_80085954(fn_800B14A0(t)))) {
            } else {
                toTarget = near + 1.0f;
            }
        }
        if (fn_80442080(ai)->f308 & 0x4000) {
            far = near;
        }
        if (toGoal > far) {
            AIAction *h = fn_80138738(-1, 0, 0);
            if (h) {
                Vector v;
                fn_8042DC84(&v, fn_800B1724(*t));
                fn_8042D8A8(&v, fn_800B1724(*fn_80442080(ai)));
                v.z = 0.0f;
                fn_8042F76C(&v);
                float f = 1.0f;
                fn_80138AE0(h, 0, &v, f);
                return h;
            }
        } else if (toTarget < near) {
            if (fn_80461D48(ai, 0x34)) {
                return 0;
            }
            if (!fn_80461D48(ai, 4) && fn_80461D48(ai, 0x2b)) {
                return 0;
            }
            AIAction *h = fn_80138738(-1, 0, 0);
            if (h) {
                Vector v;
                fn_8042DC84(&v, fn_800B1724(*t));
                fn_8042D8A8(&v, fn_800B1724(*fn_80442080(ai)));
                v.z = 0.0f;
                fn_8042F76C(&v);
                fn_80433FFC(&v);
                float f = 1.0f;
                fn_80138AE0(h, 0, &v, f);
                return h;
            }
        }
    }
    return 0;
}

// TOO_CLOSE (docs/ai.md section 4.3).
extern "C" AIAction *fn_801397C8(void *ai, AIBehavior *rec)
{
    if (fn_804421B8(ai, 7) || fn_804421B8(ai, 8) || fn_804421B8(ai, 0x11)) {
        return 0;
    }
    if (fn_80461D48(ai, 4)) {
        return 0;
    }
    if (!fn_8015F384(ai) && fn_80461D48(ai, 0x35)) {
        return 0;
    }
    Ent *t = fn_80134870(ai);
    if (t) {
        float near = fn_800B1884(*fn_80442080(ai), 0xd3);
        Vector unused;
        float range = fn_8015E64C(ai);
        if (range < near) {
            Vector v;
            fn_8042DC84(&v, fn_800B1750(*fn_80442080(ai)));
            fn_80433FFC(&v);
            if (fn_801600DC(ai, 3, 2.5f)) {
                AIAction *h = fn_80138738(3, 500, 0);
                if (h) {
                    fn_80138AE0(h, 0, &v, 1.0f);
                    fn_80138A24(h, 0xb);
                }
                return h;
            }
        }
    }
    return 0;
}

// APPROACH (docs/ai.md section 4.3).
extern "C" AIAction *fn_801399CC(void *ai, AIBehavior *rec)
{
    Vector goal;
    int found = 0;

    if (fn_80461D48(ai, 4) || (fn_80461D48(ai, 0x2b) && !fn_800CDA20(*fn_8044203C(ai)))) {
        return 0;
    }
    void *wp = fn_8044734C(fn_804420AC(ai));
    if (wp && fn_80444570(wp)) {
        if (fn_800CDA20(*fn_8044203C(ai))) {
            fn_8014B900(fn_804420AC(ai));
            AIAction *h = fn_80138738(1, 100, 100);
            if (h) {
                Vector v;
                fn_8015F6CC(ai, &v);
                v.z = 0.0f;
                fn_8042F76C(&v);
                fn_80138AE0(h, 0, &v, 1.0f);
                if (fn_800CD9B0(*fn_8044203C(ai)) && !fn_800A4130(fn_800B1478(fn_800CD9B0(*fn_8044203C(ai))))) {
                    fn_80138A24(h, 10);
                } else {
                    fn_80138A24(h, 6);
                }
                return h;
            }
        } else {
            float dist = fn_8015E580(fn_800B1724(*fn_80442080(ai)), fn_80444688(fn_80444904(wp, 0)));
            if (dist < 2.0f && fn_8015ED50(ai, fn_80444688(fn_80444904(wp, 0)))) {
                fn_801363A4(ai, 0x16);
                AIAction *h = fn_80138738(1, 0x32, 0x1f4);
                if (h) {
                    Vector v;
                    fn_8015F608(ai, fn_80444688(fn_80444984(wp, 0)), &v);
                    float dz = fn_80444688(fn_80444984(wp, 0))->z - fn_800B1724(*fn_80442080(ai))->z;
                    float len = fn_804290F8(fn_80444688(fn_80444904(wp, 0)), fn_80444688(fn_80444984(wp, 0)));
                    v.z = 0.0f;
                    fn_8042F76C(&v);
                    fn_80138AE0(h, 0, &v, 1.0f);
                    if (dz > 0.25f || fn_80461D48(ai, 0x14)) {
                        fn_80138A24(h, 5);
                        if (fn_80085D3C(fn_80442080(ai))) {
                            if (len > 2.0f) {
                                fn_80138A24(h, 7);
                            }
                        } else if ((len >= 3.0f && dz > 0.0f) || (len >= 4.0f && (dz < 0.0f ? -dz : dz) < 2.0f)) {
                            fn_80138A24(h, 0x14);
                        }
                    } else {
                        fn_80138B7C(h, 1, 0x1f4, 0);
                    }
                    return h;
                }
            } else if (dist < 4.0f && fn_8015ED50(ai, fn_80444688(fn_80444904(wp, 0)))) {
                Vector v;
                fn_80429038(&v, fn_80444688(fn_80444904(wp, 0)), fn_800B1724(*fn_80442080(ai)));
                v.z = 0.0f;
                float len = fn_8042EC54(&v);
                AIAction *h = fn_80138738(1, 0x1f4, 0);
                if (h) {
                    fn_80138AE0(h, 0, &v, 1.0f);
                    return h;
                }
            }
        }
    } else if (wp && fn_804445A4(wp) && !fn_80461D48(ai, 0x3d)) {
        float dist = fn_8015E580(fn_800B1724(*fn_80442080(ai)), fn_80444688(fn_80444904(wp, 0)));
        if (dist < 2.0f && fn_8015ED50(ai, fn_80444688(fn_80444904(wp, 0)))) {
            AIAction *h = fn_80138738(1, 0x4b0, 0);
            if (h) {
                Vector v;
                Vector g;
                int have = 0;
                if (fn_80461BA0(fn_804420AC(ai))) {
                    fn_8042DC84(&g, fn_804625CC(fn_804420AC(ai)));
                    have = 1;
                }
                if (!have && fn_80461BCC(fn_804420AC(ai))) {
                    fn_8042DC84(&g, fn_804625F8(fn_804420AC(ai)));
                    have = 1;
                }
                if (!have) {
                    fn_80067050(*fn_80442080(ai), &v);
                    v.z = 0.0f;
                    float len = fn_8042EC54(&v);
                    if (len < 0.1f) {
                        fn_8042DC84(&v, fn_800B1750(*fn_80442080(ai)));
                    }
                } else {
                    fn_8015F538(ai, &g, &v);
                }
                fn_80138AE0(h, 0, &v, 1.0f);
                if (fn_801369B0(ai)) {
                    fn_80138A24(h, 8);
                }
                return h;
            }
        } else {
            Vector v;
            fn_80429038(&v, fn_80444688(fn_80444904(wp, 0)), fn_800B1724(*fn_80442080(ai)));
            v.z = 0.0f;
            float len = fn_8042EC54(&v);
            AIAction *h = fn_80138738(1, 0x1f4, 0);
            if (h) {
                fn_80138AE0(h, 0, &v, 1.0f);
                return h;
            }
        }
    }

    float dist = 3.40282347e+38f;
    int fromA = 0;
    int fromB = 0;
    int fromTarget = 0;
    if (fn_80134870(ai)) {
        if (fn_8015E64C(ai) > fn_800B1884(*fn_80442080(ai), 0xd3) ||
            fn_8015E8A8(ai, fn_800B1724(*fn_80134870(ai))) > 5.0f) {
            if (!fn_804625A0(fn_804420AC(ai))) {
                fn_8014B63C(fn_804420AC(ai), fn_800B13D8(*fn_80134870(ai)), 0);
            }
        }
    }
    if (fn_80461BA0(fn_804420AC(ai))) {
        fn_8042DC84(&goal, fn_804625CC(fn_804420AC(ai)));
        found = 1;
        fromA = 1;
    }
    if (!found && fn_80461BCC(fn_804420AC(ai))) {
        fn_8042DC84(&goal, fn_804625F8(fn_804420AC(ai)));
        found = 1;
        fromB = 1;
    }
    Vector from;
    float reach = fn_8015E64C(ai) * 0.9f;
    fn_8015F6CC(ai, &from);
    int hit = 0;
    if (fn_80134870(ai) && fn_8015F07C(ai) && fn_8015EE34(ai, fn_80134870(ai)) && fn_80461D48(ai, 0x35) &&
        !fn_8015E2FC(ai, &from, reach, &hit, 0.2f)) {
        fn_8042DC84(&goal, fn_800B1724(*fn_80134870(ai)));
        found = 1;
        fromTarget = 1;
    }
    float scale = 1.0f;
    if (fn_80134870(ai)) {
        float d = fn_804290F8(fn_800B1724(*fn_80442080(ai)), fn_800B1724(*fn_80134870(ai)));
        float far = fn_800B1884(*fn_80442080(ai), 0xd4);
        if (fn_80134870(ai) && d <= far) {
            scale = d / far;
            scale = scale > 0.7f ? scale : 0.7f;
        }
    }
    dist = fn_8015E580(fn_800B1724(*fn_80442080(ai)), &goal);
    if (!fromTarget && dist <= 1.0f) {
        return 0;
    }
    if (dist >= fn_800B1884(*fn_80442080(ai), 0xd5)) {
        return 0;
    }
    if (found) {
        int done = 0;
        Vector v;
        fn_8042DC84(&v, &goal);
        fn_8042D8A8(&v, fn_800B1724(*fn_80442080(ai)));
        v.z = 0.0f;
        float len = fn_8042EC54(&v);
        float range;
        if (fn_80461D48(ai, 0x35) && fn_80134870(ai) && fn_8015EE34(ai, fn_80134870(ai)) &&
            fn_8015E64C(ai) < fn_800B1884(*fn_80442080(ai), 0xd1)) {
            return 0;
        }
        if (fn_800CC96C(*fn_8044203C(ai)) && fn_800CC6DC(*fn_8044203C(ai)) == 0x1a && fn_8008603C(fn_80442080(ai))) {
            Vector w;
            fn_80429038(&w, fn_800B1724(*fn_80134870(ai)), fn_800B1724(*fn_80442080(ai)));
            w.z = 0.0f;
            range = fn_8042EC54(&w);
            AIAction *h = fn_80138738(0x24, 0x1f4, 0);
            if (h) {
                fn_80138AE0(h, 0, &w, 1.0f);
                if (fn_801369B0(ai)) {
                    fn_80138A24(h, 7);
                    fn_80138A24(h, 8);
                }
                return h;
            }
        }
        AIAction *h = fn_80138738(-1, 0, 0);
        if (h) {
            fn_80138AE0(h, 0, &v, scale);
            void *at = fn_8044734C(fn_804420AC(ai));
            if (at && fn_80444570(at)) {
            } else if (!fn_800860CC(fn_80442080(ai)) && !fn_80085F7C(fn_80442080(ai)) &&
                fn_80085FDC(fn_80442080(ai)) && fn_801369B0(ai) && fn_8015F410(ai, 0.2f) &&
                len > fn_800B1884(*fn_80442080(ai), 0xd4)) {
                fn_80138A24(h, 0xd);
            }
            range = len;
            if (fn_80134870(ai) && fn_800B0C58(fn_80134870(ai))) {
                range = fn_8015E64C(ai);
            }
            if (!fn_800CCBD8(*fn_8044203C(ai)) && fn_80461D48(ai, 0x33) && fn_80461D48(ai, 0x14) &&
                fn_80461D48(ai, 0x18) && fn_8015EC80(fn_80461EE4(ai), 2.0f)) {
                Ent *e = fn_804624EC(fn_804420D8(ai));
                if (e && fn_800B0CC0(e) &&
                    (fn_800A4538(fn_800B1478(e)) || !fn_800A3EE4(fn_800B1478(e)) || fn_800A3F44(fn_800B1478(e)) ||
                     !fn_8015E764(ai, fn_800B1724(*e)) || fn_800A4130(fn_800B1478(e)))) {
                } else if (!fn_80461D48(ai, 0x40)) {
                    fn_80138A24(h, 2);
                    if (fn_800E5F04(*fn_8044203C(ai), fn_800B1478(e))) {
                        fn_80138A24(h, 0x19);
                    }
                }
                if (fn_801369B0(ai) && fn_8015EC1C(fn_80461F3C(ai))) {
                    fn_80138A24(h, 7);
                }
                if (fn_8015EC1C(fn_80461FC0(ai)) && fn_801369B0(ai) && fn_80085D3C(fn_80442080(ai)) && fn_801368B8(ai)) {
                    fn_80138A24(h, 9);
                }
            } else if (fn_8008609C(fn_80442080(ai)) && range > fn_800B1884(*fn_80442080(ai), 0xd3) &&
                       range < fn_800B1884(*fn_80442080(ai), 0xd4) && fn_80134870(ai) && fn_800B0C58(fn_80134870(ai)) &&
                       fn_80461C94(fn_804420AC(ai)) == fn_800B13D8(*fn_80134870(ai)) &&
                       fn_8015EE34(ai, fn_80134870(ai))) {
                fn_80138A24(h, 0xc);
                fn_80138A24(h, 0x16);
                fn_80138B7C(h, 1, 0x1f4, 0);
                done = 1;
            } else if (!fn_80085D3C(fn_80442080(ai)) && !fn_800861EC(fn_80442080(ai)) && fn_80134870(ai) &&
                       fn_800B0C58(fn_80134870(ai)) && !fn_800CCC28(*fn_80085954(fn_800B14A0(fn_80134870(ai)))) &&
                       len < 4.0f && fn_8015F07C(ai)) {
                fn_80138A24(h, 0xb);
                fn_80138B7C(h, 1, 0x1f4, 0);
            }
        }
        if (!done) {
            switch (fn_80462624(fn_804420AC(ai))) {
            case 4:
                if (fn_801369B0(ai)) {
                    fn_80138A24(h, 8);
                }
                break;
            case 2:
                if (fn_801369B0(ai)) {
                    fn_80138A24(h, 8);
                    fn_80138A24(h, 7);
                }
                break;
            }
        }
        return h;
    }
    return 0;
}

// PRONE (docs/ai.md section 4.3).
extern "C" AIAction *fn_8013B0F4(void *ai, AIBehavior *rec)
{
    if (fn_800CCC28(*fn_8044203C(ai))) {
        unsigned int dt = fn_8042EFF8(lbl_80593BE8) - fn_80462880(ai);
        if ((float)dt <= fn_80462954(ai)) {
            fn_8014B900(fn_804420AC(ai));
            AIAction *h = fn_80138738(4, 250, 100);
            if (h) {
                Vector v;
                fn_80447C38(&v);
                fn_80138AE0(h, 0, &v, 1.0f);
                fn_80136214(ai, 4);
                fn_80136214(ai, 8);
                fn_80136214(ai, 10);
                return h;
            }
            return 0;
        }
        int targeted = fn_80134870(ai) && !fn_8015F008(ai);
        int flag25 = fn_80461D48(ai, 0x25);
        if (!targeted || !flag25) {
            if (!fn_8015E97C(fn_80462980(ai) / 1000.0f) && (float)dt < fn_80462980(ai)) {
                fn_8014B900(fn_804420AC(ai));
                AIAction *h = fn_80138738(4, 250, 100);
                if (h) {
                    Vector v;
                    fn_80447C38(&v);
                    fn_80138AE0(h, 0, &v, 1.0f);
                    return h;
                }
                return 0;
            }
        }
        float percent = fn_80462AB4(ai);
        if (targeted) {
        } else {
            percent = 0.0f;
        }
        if (fn_80461D48(ai, 0x29)) {
            percent = 0.0f;
        }
        if (!fn_80461D48(ai, 0x35)) {
            percent = 0.0f;
        }
        int positive = percent > 0.0f;
        int roll = fn_8015EC80(percent, 6.0f) || targeted;
        if (positive && roll) {
            AIAction *h = fn_80138738(4, 100, 100);
            if (h) {
                fn_80138A24(h, 2);
                if (fn_801369B0(ai)) {
                    fn_80138A24(h, 7);
                }
                fn_80462BB4(h, 5);
                return h;
            }
        } else {
            AIAction *h = fn_80138738(4, 100, 100);
            if (h) {
                fn_80138A24(h, 5);
                return h;
            }
        }
    } else {
        if (fn_80442508(fn_80461DD4(ai), 9)) {
            AIAction *h = fn_80138738(4, 1500, 0);
            fn_80138A24(h, 5);
            fn_80138AE0(h, 0, &lbl_80593E00, 1.0f);
            fn_80462BB4(h, 5);
            return h;
        }
        if (fn_80442508(fn_80461DD4(ai), 4)) {
            Ent *e = fn_804626F0(ai);
            if (e && fn_800B0C58(e) && fn_8009B04C(*fn_800B14A0S(e)) == 0x2e) {
                float axes[3] = {1.0f, 1.0f, 1.0f};
                if (!fn_801603CC(ai, 0)) {
                    axes[0] = 0.0f;
                }
                if (!fn_801603CC(ai, 2)) {
                    axes[1] = 0.0f;
                }
                if (!fn_801603CC(ai, 3)) {
                    axes[2] = 0.0f;
                }
                Vector dir;
                fn_8042D80C(&dir, fn_800B1750(*fn_80442080(ai)));
                unsigned int side = fn_8015EA6C(3, axes);
                switch (side) {
                case 0:
                    fn_8042D80C(&dir, fn_800B17A8(*fn_80442080(ai)));
                    break;
                case 1:
                    fn_8042DC84(&dir, fn_800B17A8(*fn_80442080(ai)));
                    break;
                case 2:
                    fn_8042D80C(&dir, fn_800B1750(*fn_80442080(ai)));
                    break;
                }
                AIAction *h = fn_80138738(4, 200, 0);
                fn_80138A24(h, 0xc);
                fn_80138AE0(h, 0, &dir, 1.0f);
                fn_80462BB4(h, 5);
                return h;
            }
        }
    }
    if (fn_80085D3C(fn_80442080(ai)) && (fn_80461D48(ai, 0x1e) || fn_80461D48(ai, 0x1f))) {
        if (fn_801369B0(ai) && fn_80461D48(ai, 0x1e) && fn_8015EC80(fn_804629AC(ai), 8.0f)) {
            AIAction *h = fn_80138738(4, 500, 10);
            if (h) {
                fn_80138A24(h, 7);
                fn_80138A24(h, 8);
                fn_80138A24(h, 9);
                return h;
            }
        } else if (fn_801369B0(ai) && fn_80461D48(ai, 0x1f) && fn_801369B0(ai) && fn_8008603C(fn_80442080(ai))) {
            AIAction *h = fn_80138738(4, 3000, 10);
            if (h) {
                fn_80138A24(h, 7);
                fn_80138A24(h, 8);
                return h;
            }
        }
    }
    if (fn_8008618C(fn_80442080(ai)) && fn_80086730(fn_80442080(ai)) < fn_800B1884(*fn_80442080(ai), 0xde)) {
    } else if (fn_800CD0EC(*fn_8044203C(ai)) && !fn_800861EC(fn_80442080(ai)) && !fn_8015F384(ai)) {
        if (!fn_80462928(ai)) {
            fn_804627AC(ai, 200);
            if (fn_800CD174(*fn_8044203C(ai))) {
                fn_804627AC(ai, 400);
            }
            fn_80462800(ai, 0);
            fn_80462900(ai, 1);
        } else if (fn_804627D4(ai) < 50 && fn_8015EC80(fn_80462AE0(ai), 35.0f)) {
            fn_80136214(ai, 7);
            AIAction *h = fn_80138738(0x11, 0x23, 1);
            fn_80138A24(h, 0x12);
            return h;
        }
    } else {
        fn_80462900(ai, 0);
    }
    if (fn_800CD21C(*fn_8044203C(ai))) {
        int go = 0;
        if (fn_80442080V(ai)->v57(0.15f)) {
            if (fn_801369B0(ai) && fn_8015EC80(fn_804629AC(ai), 8.0f)) {
                go = 1;
            }
        } else if (fn_801369B0(ai) && fn_8015EC80(fn_804629D8(ai), 8.0f)) {
            go = 1;
        }
        if (fn_804628AC(ai) || fn_80461D48(ai, 0x3c)) {
            go = 1;
        }
        if (go) {
            AIAction *h = fn_80138738(4, 500, 0);
            if (h) {
                fn_80138A24(h, 7);
                fn_80138A24(h, 8);
                fn_80138A24(h, 9);
                return h;
            }
        }
    }
    return 0;
}

// MOVE_TO_WAYPOINT (docs/ai.md section 4.3).
extern "C" AIAction *fn_8013BCE8(void *ai, AIBehavior *rec)
{
    Vector goal;
    int found = 0;
    if (fn_801369B0(ai) && fn_80462624(fn_804420AC(ai)) == 4) {
        AIAction *h = fn_80138738(-1, 0, 0);
        if (h) {
            Vector v;
            fn_80067050(*fn_80442080(ai), &v);
            v.z = 0.0f;
            fn_8042F76C(&v);
            fn_8042D8A8(&v, fn_800CE230(*fn_8044203C(ai)));
            fn_80435530(&v, 0.5f);
            fn_80138AE0(h, 0, &v, 1.0f);
            fn_80138A24(h, 8);
            return h;
        }
    }
    float dist = 3.40282347e+38f;
    if (fn_80461BA0(fn_804420AC(ai))) {
        fn_8042DC84(&goal, fn_804625CC(fn_804420AC(ai)));
        found = 1;
        dist = fn_8015E580(fn_800B1724(*fn_80442080(ai)), &goal);
    }
    if (!found && fn_80461BCC(fn_804420AC(ai))) {
        fn_8042DC84(&goal, fn_804625F8(fn_804420AC(ai)));
        found = 1;
        dist = fn_8015E580(fn_800B1724(*fn_80442080(ai)), &goal);
    }
    float reach = 2.0f;
    if (fn_800CCA58(*fn_8044203C(ai))) {
        reach = 4.0f;
    } else if (fn_800CCAE8(*fn_8044203C(ai))) {
        reach = 8.0f;
    }
    if (dist < reach) {
        return 0;
    } else if (found) {
        Vector v;
        fn_8042DC84(&v, &goal);
        fn_8042D8A8(&v, fn_800B1724(*fn_80442080(ai)));
        float len = fn_8042EC54(&v);
        AIAction *h = fn_80138738(-1, 0, 0);
        if (h) {
            fn_80138AE0(h, 0, &v, 1.0f);
        }
        switch (fn_80462624(fn_804420AC(ai))) {
        case 1:
            if (!fn_80461D48(ai, 0x3d)) {
                fn_80138A24(h, 5);
                if (goal.z - fn_800B1724(*fn_80442080(ai))->z > 2.0f && fn_801369B0(ai)) {
                    fn_80138A24(h, 7);
                }
                if (!fn_80085D3C(fn_80442080(ai))) {
                    fn_80138A24(h, 0x14);
                }
            }
            break;
        case 4:
            if (fn_801369B0(ai)) {
                fn_80138A24(h, 8);
            }
            break;
        case 2:
            if (fn_801369B0(ai)) {
                fn_80138A24(h, 8);
            }
            break;
        }
        return h;
    }
    return 0;
}

// AVOID_OBSTACLES (docs/ai.md section 4.3).
extern "C" AIAction *fn_8013C1C8(void *ai, AIBehavior *rec)
{
    if (fn_80461D48(ai, 0x14)) {
        Vector v;
        int a = fn_80461D48(ai, 0x12);
        int b = fn_80461D48(ai, 0x13);
        if (a && !b) {
            fn_8042DC84(&v, fn_800B17A8(*fn_80442080(ai)));
        } else if (!a && b) {
            fn_8042D80C(&v, fn_800B17A8(*fn_80442080(ai)));
        } else if (a) {
            fn_8042D80C(&v, fn_800B1750(*fn_80442080(ai)));
        } else {
            fn_8042D80C(&v, fn_800B17A8(*fn_80442080(ai)));
        }
        AIAction *h = fn_80138738(-1, 0, 0);
        if (h) {
            fn_80138AE0(h, 0, &v, 1.0f);
            fn_80462BDC(h, lbl_8066BF60);
        }
        return h;
    } else {
        AIAction *h = 0;
    }
    return 0;
}

// BLOCK (docs/ai.md section 4.3).
extern "C" AIAction *fn_8013C3A4(void *ai, AIBehavior *rec)
{
    fn_8014F7B0(fn_804420D8(ai), 0);
    if (fn_80461D48(ai, 0x2c) || fn_80442508(fn_80461DD4(ai), 2)) {
        Ent *t = fn_8046267C(ai);
        float dist = t ? fn_804290F8(fn_800B1724(*t), fn_800B1724(*fn_80442080(ai))) : 0.0f;
        int far = t && dist > 12.0f;
        if (far) {
            return 0;
        }
        int facing = t && fn_8008572C(fn_80442080(ai), t);
        int near = t && dist < 9.0f;
        int a = fn_8015EC1C(fn_80462A04(ai));
        int b = fn_8015EC1C(fn_80462B0C(ai) * 0.7f + 30.0f);
        if (fn_80462B0C(ai) <= 0.0f) {
            b = 0;
        }
        if (facing && (a || b) && near) {
            fn_80136214(ai, 0x11);
            fn_80136214(ai, 0x13);
            if (b) {
                AIAction *h = fn_80138738(-1, 0, 0);
                if (h) {
                    fn_80138A24(h, 0x12);
                    fn_80138AE0(h, 0, &lbl_80593E00, 1.0f);
                    return h;
                }
            }
            if (a) {
                AIAction *h = fn_80138738(7, 250, 10);
                if (h) {
                    fn_80138A24(h, 2);
                    fn_80138AE0(h, 0, &lbl_80593E00, 1.0f);
                    return h;
                }
            }
        } else {
            int close = t && dist < 5.0f;
            if ((fn_801369B0(ai) && !close) || fn_80086908(fn_80442080(ai))) {
                AIAction *h = fn_80138738(7, 1500, 1500);
                if (h) {
                    fn_80138A24(h, 0);
                    fn_80138AE0(h, 0, &lbl_80593E00, 1.0f);
                    fn_80138A24(h, 0x17);
                    return h;
                }
            } else {
                int c = fn_8015EC1C(fn_80462A30(ai));
                int side = fn_80461D48(ai, 0x12) || fn_80461D48(ai, 0x13);
                if (c && !side) {
                    Vector v;
                    fn_8042DC84(&v, fn_800B1668(*fn_80442080(ai)));
                    int r = fn_8015EA18(2);
                    if (r == 1) {
                        fn_80433FFC(&v);
                    }
                    AIAction *h = fn_80138738(7, 1000, 1000);
                    if (h) {
                        fn_80138A24(h, 0xc);
                        fn_80138AE0(h, 0, &v, 1.0f);
                        fn_80462BDC(h, 5.0f);
                        return h;
                    }
                } else {
                    AIAction *h = fn_80138738(7, 1000, 1000);
                    if (h) {
                        fn_80138A24(h, 0x17);
                        fn_80138A24(h, 0);
                        fn_80138AE0(h, 0, &lbl_80593E00, 1.0f);
                        return h;
                    }
                }
            }
        }
    }
    if (!fn_80461D48(ai, 0x2d) && !fn_80442508(fn_80461DD4(ai), 1) && !fn_80461D48(ai, 0x35) && fn_8015E97C(5.0f) &&
        !fn_80461D48(ai, 5) && !fn_80461D48(ai, 6)) {
        AIAction *h = fn_80138738(-1, 0, 0);
        if (h) {
            fn_80138A24(h, 0x13);
            return h;
        }
    }
    AIAction *h = fn_80138738(7, 500, 10);
    if (h) {
        int x = fn_80442508(fn_80461DD4(ai), 1);
        int y = fn_8015FFD4(ai);
        if (x && !fn_801369B0(ai)) {
            Vector v;
            fn_8042DC84(&v, fn_800B1668(*fn_80442080(ai)));
            int r = fn_8015EA18(2);
            if (r == 1) {
                fn_80433FFC(&v);
            }
            fn_80138B7C(h, 7, 1000, 1000);
            fn_80138A24(h, 0xc);
            fn_80138AE0(h, 0, &v, 1.0f);
            fn_80462BDC(h, 5.0f);
            return h;
        } else {
            if (y) {
                fn_80138B7C(h, 7, 2000, 1000);
                fn_80138A24(h, 0x17);
            } else if (fn_80461D48(ai, 0x25)) {
                fn_80136214(ai, 7);
                fn_80138B7C(h, 7, 1500, 10);
            } else {
                fn_80138B7C(h, 7, 500, 1000);
            }
            fn_80138A24(h, 0);
            fn_80138AE0(h, 0, &lbl_80593E00, 1.0f);
        }
        int hi = fn_800867A8(fn_80442080(ai)) > 0.75f;
        int lo = fn_8008666C(fn_80442080(ai)) < 0.4f;
        int z = 0;
        if (x) {
            fn_80462C30(h, 1000);
        }
        if (fn_80442508(fn_80461DD4(ai), 6) && fn_80462734(ai) && (fn_80462734(ai)->f2a0 & 2)) {
            z = 1;
        }
        int w = z;
        if ((w && fn_801369B0(ai)) || fn_80086908(fn_80442080(ai))) {
            fn_80138A24(h, 0x17);
            fn_80462C30(h, 1500);
        }
    }
    return h;
}

// JUMP_ATTACK (docs/ai.md section 4.3).
extern "C" AIAction *fn_8013CD40(void *ai, AIBehavior *rec)
{
    if (!(fn_80462A5C(ai) > 0.0f)) {
        return 0;
    }
    if (fn_80461D48(ai, 0x29)) {
        return 0;
    }
    if (fn_80461D48(ai, 0x40)) {
        return 0;
    }
    if (fn_80134870(ai)) {
        if (fn_8015E8A8(ai, fn_800B1724(*fn_80134870(ai))) > fn_800B1884(*fn_80442080(ai), 0xd8)) {
            return 0;
        }
    }
    Vector v;
    AIAction *none = 0;
    if (fn_800CCBD8(*fn_8044203C(ai)) || fn_800CC6DC(*fn_8044203C(ai)) == 5 || fn_8044203CB(ai)->v42()) {
        unsigned int dt = fn_800CC2B4(*fn_8044203C(ai)) - fn_8042EFF8(lbl_80593BE8);
        if (!fn_8015E97C(5.0f) && !fn_8015EE34(ai, fn_80134870(ai))) {
            return 0;
        }
        if (dt < 500 && dt > 150) {
            fn_80067050(*fn_80442080(ai), &v);
            int below = 0;
            int above = 0;
            int level = 0;
            if (fn_800B1724(*fn_80134870(ai))->z < fn_800B1724(*fn_80442080(ai))->z - 1.0f) {
                below = 1;
            } else if (fn_800B1724(*fn_80134870(ai))->z > fn_800B1724(*fn_80442080(ai))->z + 1.0f) {
                above = 1;
            } else {
                level = 1;
            }
            AIAction *h = fn_80138738(-1, 0, 0);
            if (h) {
                Vector p;
                fn_8015F6CC(ai, &p);
                fn_80138AE0(h, 0, &p, 1.0f);
                if (v.z < -0.5f) {
                    if (fn_801369B0(ai) && fn_8015EC1C(fn_80461F3C(ai))) {
                        fn_80138A24(h, 2);
                        if (fn_801369B0(ai) && fn_8015EC1C(fn_80461F3C(ai))) {
                            fn_80138A24(h, 7);
                        }
                        if (fn_801369B0(ai) && fn_8015EC1C(fn_80461FC0(ai))) {
                            fn_80138A24(h, 0xd);
                        }
                    }
                } else if (v.z > 0.5f) {
                    fn_80138A24(h, 2);
                    if (fn_801369B0(ai) && fn_8015EC1C(fn_80461F3C(ai))) {
                        fn_80138A24(h, 7);
                    }
                } else {
                    if (fn_8015EC1C(fn_80462A88(ai))) {
                        fn_80138A24(h, 0x12);
                    } else {
                        fn_80138A24(h, 2);
                    }
                    if (fn_801369B0(ai) && fn_8015EC1C(fn_80461F3C(ai))) {
                        fn_80138A24(h, 7);
                    }
                    if (fn_801369B0(ai) && fn_8015EC1C(fn_80461FC0(ai))) {
                        fn_80138A24(h, 0xd);
                    }
                }
                return h;
            }
        }
    }
    int dur = 2000;
    int jitter = fn_8015EA18(500) - 250;
    dur += jitter;
    if (!fn_80461D48(ai, 0x3d)) {
        AIAction *h = fn_80138738(10, dur, 10);
        if (h) {
            Vector p;
            float dist = fn_8015E64C(ai);
            float range = fn_800B1884(*fn_80442080(ai), 0xd3);
            float s = dist / range < 1.0f ? dist / range : 1.0f;
            fn_8015F6CC(ai, &p);
            fn_80138AE0(h, 0, &p, s);
            fn_80462BDC(h, 10.0f);
            fn_80138A24(h, 5);
            fn_80461E58(ai, &p);
            if (fn_801369B0(ai) && fn_80085D3C(fn_80442080(ai)) && fn_8015EC1C(fn_80461F3C(ai))) {
                fn_80138A24(h, 7);
            }
            return h;
        }
    }
    return 0;
}

// JUMP_ATTACK_PEAK (docs/ai.md section 4.3).
extern "C" AIAction *fn_8013D464(void *ai, AIBehavior *rec)
{
    if (!(fn_80462A5C(ai) > 0.0f)) {
        return 0;
    }
    if (fn_80461D48(ai, 0x29)) {
        return 0;
    }
    if (fn_80461D48(ai, 0x40)) {
        return 0;
    }
    if (fn_80134870(ai)) {
        if (fn_8015E8A8(ai, fn_800B1724(*fn_80134870(ai))) > fn_800B1884(*fn_80442080(ai), 0xd8)) {
            return 0;
        }
    }
    Vector v;
    AIAction *none = 0;
    if (fn_800CCBD8(*fn_8044203C(ai)) || fn_800CC6DC(*fn_8044203C(ai)) == 5 || fn_8044203CB(ai)->v42()) {
        unsigned int dt = fn_800CC2B4(*fn_8044203C(ai)) - fn_8042EFF8(lbl_80593BE8);
        if (!fn_8015E97C(5.0f)) {
            return 0;
        }
        if (dt) {
            fn_80067050(*fn_80442080(ai), &v);
            int below = 0;
            int above = 0;
            int level = 0;
            if (fn_800B1724(*fn_80134870(ai))->z < fn_800B1724(*fn_80442080(ai))->z - 1.0f) {
                below = 1;
            } else if (fn_800B1724(*fn_80134870(ai))->z > fn_800B1724(*fn_80442080(ai))->z + 1.0f) {
                above = 1;
            } else {
                level = 1;
            }
            AIAction *h = fn_80138738(-1, 0, 0);
            if (h) {
                Vector p;
                fn_8015F6CC(ai, &p);
                fn_80138AE0(h, 0, &p, 1.0f);
                if (v.z > 0.5f) {
                    fn_80138A24(h, 2);
                    if (fn_801369B0(ai) && fn_8015EC1C(fn_80461F3C(ai))) {
                        fn_80138A24(h, 7);
                    }
                    if (fn_801369B0(ai) && fn_8015EC1C(fn_80461FC0(ai))) {
                        fn_80138A24(h, 0xd);
                    }
                } else {
                    if (fn_8015EC1C(fn_80462A88(ai))) {
                        fn_80138A24(h, 0x12);
                        if (fn_801369B0(ai) && fn_8015EC1C(fn_80461F3C(ai))) {
                            fn_80138A24(h, 7);
                        }
                    }
                }
                return h;
            }
        }
    }
    int dur = 1250;
    int jitter = fn_8015EA18(500) - 250;
    dur += jitter;
    if (!fn_80461D48(ai, 0x3d)) {
        AIAction *h = fn_80138738(10, dur, 10);
        if (h) {
            Vector p;
            float dist = fn_8015E64C(ai);
            float range = fn_800B1884(*fn_80442080(ai), 0xd3);
            float s = dist / range < 1.0f ? dist / range : 1.0f;
            s = 1.0f;
            fn_8015F6CC(ai, &p);
            fn_80138AE0(h, 0, &p, s);
            fn_80462BDC(h, 10.0f);
            fn_80138A24(h, 5);
            fn_80461E58(ai, &p);
            if (fn_801369B0(ai) && fn_80085D3C(fn_80442080(ai)) && fn_8015EC1C(fn_80461F3C(ai))) {
                fn_80138A24(h, 7);
            }
            return h;
        }
    }
    return 0;
}

// JUMP_ATTACK_DESCEND (docs/ai.md section 4.3).
extern "C" AIAction *fn_8013DA7C(void *ai, AIBehavior *rec)
{
    if (!(fn_80462A5C(ai) > 0.0f)) {
        return 0;
    }
    if (fn_80461D48(ai, 0x29)) {
        return 0;
    }
    if (fn_80461D48(ai, 0x40)) {
        return 0;
    }
    if (fn_80134870(ai)) {
        if (fn_8015E8A8(ai, fn_800B1724(*fn_80134870(ai))) > fn_800B1884(*fn_80442080(ai), 0xd8)) {
            return 0;
        }
    }
    Vector v;
    AIAction *none = 0;
    if (fn_800CCBD8(*fn_8044203C(ai)) || fn_800CC6DC(*fn_8044203C(ai)) == 5 || fn_8044203CB(ai)->v42()) {
        unsigned int dt = fn_800CC2B4(*fn_8044203C(ai)) - fn_8042EFF8(lbl_80593BE8);
        if (!fn_8015E97C(2.0f)) {
            return 0;
        }
        if (fn_800CC6DC(*fn_8044203C(ai)) == 5 || dt < 150) {
            fn_80067050(*fn_80442080(ai), &v);
            AIAction *h = fn_80138738(-1, 0, 0);
            if (h) {
                Vector p;
                fn_8015F6CC(ai, &p);
                fn_80138AE0(h, 0, &p, 1.0f);
                if (v.z < -0.5f) {
                    if (fn_801369B0(ai) && fn_8015EC1C(fn_80461F3C(ai))) {
                        fn_80138A24(h, 2);
                        if (fn_801369B0(ai) && fn_8015EC1C(fn_80461F3C(ai))) {
                            fn_80138A24(h, 7);
                        }
                    }
                    if (fn_801369B0(ai) && fn_8015EC1C(fn_80461FC0(ai))) {
                        fn_80138A24(h, 0xd);
                    }
                } else if (v.z > 0.5f) {
                    fn_80138A24(h, 2);
                    if (fn_801369B0(ai) && fn_8015EC1C(fn_80461F3C(ai))) {
                        fn_80138A24(h, 7);
                    }
                } else {
                    if (fn_8015EC1C(fn_80462A88(ai))) {
                        fn_80138A24(h, 0x12);
                    } else {
                        fn_80138A24(h, 2);
                    }
                    if (fn_801369B0(ai) && fn_8015EC1C(fn_80461F3C(ai))) {
                        fn_80138A24(h, 7);
                    }
                    if (fn_801369B0(ai) && fn_8015EC1C(fn_80461FC0(ai))) {
                        fn_80138A24(h, 0xd);
                    }
                }
                return h;
            }
        }
    }
    int dur = 2000;
    int jitter = fn_8015EA18(500) - 250;
    dur += jitter;
    if (!fn_80461D48(ai, 0x3d)) {
        AIAction *h = fn_80138738(10, dur, 10);
        if (h) {
            Vector p;
            float dist = fn_8015E64C(ai);
            float range = fn_800B1884(*fn_80442080(ai), 0xd3);
            float s = dist / range < 1.0f ? dist / range : 1.0f;
            fn_8015F6CC(ai, &p);
            fn_80138AE0(h, 0, &p, s);
            fn_80462BDC(h, 10.0f);
            fn_80138A24(h, 5);
            fn_80461E58(ai, &p);
            if (fn_801369B0(ai) && fn_80085D3C(fn_80442080(ai)) && fn_8015EC1C(fn_80461F3C(ai))) {
                fn_80138A24(h, 7);
            }
            return h;
        }
    }
    return 0;
}

// ATTACK_MELEE (docs/ai.md section 4.3).
extern "C" AIAction *fn_8013E0C4(void *ai, AIBehavior *rec)
{
    if (fn_800CCC28(*fn_8044203C(ai))) {
        return 0;
    }
    if ((!fn_8015F384(ai) && !fn_80461D48(ai, 0x35) && fn_80134870(ai) && fn_800B0C1C(fn_80134870(ai))) ||
        fn_80461D48(ai, 0x40)) {
        if (fn_8015E97C(5.0f) && fn_8015F07C(ai) &&
            ((!fn_80461D48(ai, 5) && !fn_80461D48(ai, 6)) || fn_80461D48(ai, 0x40))) {
            AIAction *h = fn_80138738(-1, 0, 0);
            if (h) {
                fn_80138A24(h, 0x13);
                return h;
            }
        }
        return 0;
    }
    if (fn_80461D48(ai, 0x29)) {
        return 0;
    }
    if (fn_80461D48(ai, 0x40)) {
        return 0;
    }
    for (int i = 0; i < fn_801500C4(fn_804420D8(ai)); i++) {
        void *t = fn_801500F0(fn_804420D8(ai), i);
        if (t && fn_800B0CC0(t) && fn_800A3F44(fn_800B1478(t))) {
            return 0;
        }
    }
    if (fn_80085D3C(fn_80442080(ai)) && fn_80134870(ai) && fn_800B0C58(fn_80134870(ai)) && !fn_80461D48(ai, 0x28)) {
        void *e = fn_800B14A0(fn_80134870(ai));
        if (fn_800866C0(e)) {
            AIAction *h = fn_80138738(8, 50, 500);
            fn_80138A24(h, 7);
            fn_80138A24(h, 0x12);
            fn_80136214(ai, 8);
            fn_801363A4(ai, 0x12);
            fn_801362DC(ai, 8);
            return h;
        }
    }
    if (fn_80134870(ai) && fn_800B0C58(fn_80134870(ai)) && fn_800CD2E8(*fn_80085954(fn_800B14A0(fn_80134870(ai))))) {
        fn_801362DC(ai, 8);
        fn_801363A4(ai, 2);
        AIAction *h = fn_80138738(8, 50, 20);
        fn_80138A24(h, 2);
        return h;
    }
    int ok = fn_8015EC1C(fn_80461F3C(ai)) && fn_8015EC1C(fn_80461EE4(ai)) && fn_8015EC1C(fn_80461F10(ai));
    if (fn_8015EE34(ai, fn_80134870(ai)) && fn_8015E830(ai)) {
        if (fn_8044734C(fn_804420AC(ai)) && fn_80444570(fn_8044734C(fn_804420AC(ai))) && fn_800CCBD8(*fn_8044203C(ai))) {
        } else {
            AIAction *h = fn_80138738(8, 250, 50);
            if (h) {
                if (fn_80134870(ai)) {
                    Vector p;
                    fn_8015F6CC(ai, &p);
                    fn_80138AE0(h, 0, &p, 1.0f);
                }
                if (ok && fn_8009B04CE(*fn_80442080(ai)) != 0x28) {
                    fn_80138A24(h, 7);
                }
                fn_80138A24(h, 2);
                if (fn_8015EC80(fn_80461FC0(ai), 1.0f) &&
                    (!fn_800860CC(fn_80442080(ai)) || fn_800CCAE8(*fn_8044203C(ai)) || fn_800CE4D0(fn_8044203C(ai))) &&
                    fn_801600DC(ai, 1, 5.0f)) {
                    fn_80138A24(h, 0xd);
                }
                return h;
            }
        }
    } else {
    }
    if (fn_800CC96C(*fn_8044203C(ai))) {
        int low = 1;
        if (fn_800CC6DC(*fn_8044203C(ai)) == 0x19) {
            low = 0;
        }
        float z = fn_800B1724(*fn_80442080(ai))->z;
        float tz = fn_800B1724(*fn_80134870(ai))->z;
        if (z > tz) {
            if (!low) {
                Vector *d = fn_800CE230(*fn_8044203C(ai));
                if (d) {
                    Vector v;
                    fn_80429038(&v, fn_800B1724(*fn_80134870(ai)), fn_800B1724(*fn_80442080(ai)));
                    v.z = 0.0f;
                    fn_8042F76C(&v);
                    if (fn_8042EBF4(d, &v) > 0.2f) {
                        AIAction *h = fn_80138738(8, 50, 20);
                        fn_80138A24(h, 2);
                        if (ok) {
                            fn_80138A24(h, 7);
                        }
                        return h;
                    }
                }
            } else if (z > tz + 3.0f) {
                AIAction *h = fn_80138738(8, 50, 20);
                fn_80138A24(h, 2);
                if (ok) {
                    fn_80138A24(h, 7);
                }
                return h;
            }
        }
    }
    return 0;
}

// ATTACK_RANGED (docs/ai.md section 4.3): an attack toward the target, gated by a clear path and tuning field 200.
extern "C" AIAction *fn_8013E99C(void *self, AIBehavior *rec)
{
    if (!fn_8015F384(self) && !fn_80461D48(self, 0x35)) {
        if (fn_8015E97C(1.0f) && fn_8015F008(self) && !fn_80461D48(self, 5) && !fn_80461D48(self, 6)) {
            AIAction *e = fn_80138738(-1, 0, 0);
            if (e) {
                fn_80138A24(e, 0x13);
                return e;
            }
        }
        return 0;
    }
    Target *t = fn_80134870T(self);
    if (!t)
        return 0;
    if (fn_80461D48(self, 0x29))
        return 0;
    Vector dir;
    t->s5(&dir, 0);
    fn_8042D8A8(&dir, fn_800B1724(*fn_80442080(self)));
    float len = fn_8042EC54(&dir);
    float facing = fn_8042EBF4(&dir, fn_800B1750(*fn_80442080(self)));
    float size = MAX(ABS(fn_80134870T(self)->maxX - fn_80134870T(self)->minX),
                     ABS(fn_80134870T(self)->maxY - fn_80134870T(self)->minY));
    len -= size;
    Vector from;
    fn_80442080T(self)->s5(&from, 0);
    if (facing > 0.5f) {
        Placement hit;
        int clear = !fn_8004A9CC(&from, &dir, len, 0x8000, &hit, fn_800B24AC(*fn_80442080(self)),
                                 fn_800B1CC8(*fn_80442080(self)), 0, 3);
        int color = 0xffff0000;
        if (clear)
            color = 0xff00ff00;
        if (clear) {
            int id = 200;
            int n = fn_800B18EC(*fn_80442080(self), 200);
            AIAction *h = fn_80138738(9, id, n);
            if (h) {
                if (fn_80442080A(self)->flags & 0x4000) {
                    fn_80138A24(h, 2);
                    fn_80138A24(h, 7);
                } else {
                    fn_80138A24(h, 1);
                    int a = fn_8015EEA0(self);
                    int b = fn_800862DC(fn_80442080(self));
                    if (fn_801369B0(self) && (b || (!b && !a)))
                        fn_80138A24(h, 7);
                    if (fn_801369B0(self) && fn_8015EC1C(fn_80461FC0(self)))
                        fn_80138A24(h, 0xd);
                }
                dir.z = 0.0f;
                fn_8042F76C(&dir);
                fn_80138AE0(h, 0, &dir, 0.08f);
            }
            return h;
        }
    }
    return 0;
}

// STRAFE (docs/ai.md section 4.3): weighs four directions, drops the blocked ones, picks one.
extern "C" AIAction *fn_8013F08C(void *ai, AIBehavior *rec)
{
    int dur = 500;
    int rest = 500;
    if (fn_800861EC(fn_80442080(ai))) {
        dur = 1000;
        rest = 0;
    }
    AIAction *h = fn_80138738(13, dur, rest);
    if (h) {
        fn_80138A24(h, 0xb);
        float w[4];
        w[0] = 3.0f;
        w[1] = 1.0f;
        w[2] = 3.0f;
        w[3] = 1.0f;
        if (fn_800861EC(fn_80442080(ai))) {
            w[1] = 0.0f;
            w[3] = 0.0f;
        }
        if (fn_8015E64C(ai) <= fn_800B1884(*fn_80442080(ai), 0xd3)) {
            w[1] = 0.0f;
        }
        if (fn_8015E64C(ai) < fn_800B1884(*fn_80442080(ai), 0xd2)) {
            w[0] = 0.0f;
            w[1] = 0.0f;
            w[2] = 0.0f;
        }
        if (fn_80461D48(ai, 0x40)) {
            w[1] = 0.0f;
        }
        for (int i = 0; i <= 3; i++) {
            if (w[i] == 0.0f) {
                continue;
            }
            if (!fn_801600DC(ai, i, 2.5f)) {
                w[i] = 0.0f;
            }
        }
        Vector v;
        unsigned int r = fn_8015EA6C(4, w);
        switch (r) {
        case 0:
            fn_8042D80C(&v, fn_800B17A8(*fn_80442080(ai)));
            break;
        case 1:
            fn_8042DC84(&v, fn_800B1750(*fn_80442080(ai)));
            break;
        case 2:
            fn_8042DC84(&v, fn_800B17A8(*fn_80442080(ai)));
            break;
        case 3:
            fn_8042D80C(&v, fn_800B1750(*fn_80442080(ai)));
            break;
        }
        Vector p;
        fn_8042DC84(&p, &v);
        fn_80138AE0(h, 0, &p, 1.0f);
        return h;
    }
    return 0;
}

// FLY (docs/ai.md section 4.3).
extern "C" AIAction *fn_8013F438(void *ai, AIBehavior *rec)
{
    int a = fn_8015F008(ai);
    int b = fn_80461D48(ai, 0x27);
    int c = fn_80461D48(ai, 0x2a);
    int d = fn_80461D48(ai, 0x1c);
    int e = fn_80461D48(ai, 0xc) || fn_80461D48(ai, 0xe);
    if (!fn_801368B8(ai) && !fn_804628AC(ai)) {
        return 0;
    }
    AIAction *h = fn_80138738(0xe, 0, 0);
    if (h) {
        float z = fn_800B1724(*fn_80442080(ai))->z;
        float gz = fn_8014B824(fn_804420AC(ai));
        float dz = gz - z;
        if (fn_80461BA0(fn_804420AC(ai))) {
            gz = fn_804625CC(fn_804420AC(ai))->z;
        }
        if (fn_804628AC(ai)) {
            fn_80138A24(h, 9);
        }
        if (dz > -1.0f) {
            fn_80138A24(h, 0x10);
            fn_80138A24(h, 9);
        }
        if (fn_804628AC(ai) && z < gz + 2.5f &&
            fn_8015E580(fn_800B1724(*fn_80442080(ai)), fn_804625F8(fn_804420AC(ai))) > 2.0f) {
            fn_80138A24(h, 0x10);
        }
        Ent *t = fn_80134870(ai);
        if (t) {
            float dist = fn_8015E64C(ai);
            float tdist = fn_8015E8A8(ai, fn_800B1724(*fn_80134870(ai)));
            if (!fn_804628AC(ai) && fn_80085D3C(fn_80442080(ai)) && tdist > 0.0f && tdist < 5.0f &&
                dist < fn_800B1884(*fn_80442080(ai), 0xd3) && !fn_80461D48(ai, 0x14)) {
                fn_80138A24(h, 2);
            } else if (tdist < 5.0f) {
                fn_80138A24(h, 9);
            }
        } else {
            fn_80138A24(h, 9);
        }
        if (!fn_804628AC(ai) && fn_80134870(ai) && fn_8015EC1C(fn_80462A88(ai)) && fn_8015EE34(ai, fn_80134870(ai))) {
            Vector p;
            fn_8015F6CC(ai, &p);
            fn_80138AE0(h, 0, &p, 1.0f);
            fn_80138A24(h, 0x12);
            if (fn_801369B0(ai)) {
                fn_80138A24(h, 7);
            }
        }
        return h;
    }
    return 0;
}

// SUSPENDED (docs/ai.md section 4.3).
extern "C" AIAction *fn_8013F8D0(void *ai, AIBehavior *rec)
{
    if (fn_80461D48(ai, 0x32)) {
        AIAction *h = fn_80138738(-1, 0, 0);
        if (h) {
            if (fn_800B1724(*fn_80442080(ai))->z < fn_8014B824(fn_804420AC(ai)) - 1.0f) {
                Vector v;
                fn_8042DC84(&v, &lbl_80593DD0);
                fn_80138AE0(h, 0, &v, 1.0f);
            } else {
                fn_80138A24(h, 5);
            }
            return h;
        }
    }
    return 0;
}

// THROW_OBJECT (docs/ai.md section 4.3): throws when the path to the target is clear down the centre and both edges.
extern "C" AIAction *fn_8013F9F0(void *ai, AIBehavior *rec)
{
    if (fn_80461D48(ai, 0xc)) {
        AIAction *h = fn_80138738(0x10, 100, 500);
        if (h) {
            Vector v;
            if (fn_8015F6CC(ai, &v)) {
                if (!fn_8015F384(ai) || !fn_80085D3C(fn_80442080(ai))) {
                    fn_80138AE0(h, 0, &v, 1.0f);
                    fn_80462BDC(h, 10.0f);
                }
            } else {
                fn_8042DC84(&v, fn_800B1750(*fn_80442080(ai)));
                if (!fn_8015F384(ai) || !fn_80085D3C(fn_80442080(ai))) {
                    fn_80138AE0(h, 0, &v, 1.0f);
                }
            }
            float facing = fn_8042EBF4(&v, fn_800B1750(*fn_80442080(ai)));
            if (facing < 0.0f) {
                return h;
            }
            int seen = 1;
            if (fn_80134870(ai)) {
                seen = fn_8015F0F0(ai, fn_80134870(ai));
            }
            if (fn_80086B1C(fn_80442080(ai)) || fn_80086B6C(fn_80442080(ai))) {
                fn_80138A24(h, 6);
            }
            int clear = 1;
            if (fn_80134870(ai)) {
                Vector from, to, dir;
                fn_80442080T(ai)->s5(&from, 0);
                fn_80134870T(ai)->s5(&to, 0);
                fn_80429038(&dir, &to, &from);
                fn_8042F76C(&dir);
                float len = fn_804290F8(&from, &to);
                float size = MAX(ABS(fn_80134870T(ai)->maxX - fn_80134870T(ai)->minX),
                                 ABS(fn_80134870T(ai)->maxY - fn_80134870T(ai)->minY));
                len -= size;
                if (len > 10.0f) {
                    len = 10.0f;
                }
                Vector side;
                fn_8042F984(&side, &dir, &lbl_80593DE0);
                Vector left, right;
                Target *b = fn_800CD9B0T(*fn_8044203C(ai));
                float half = MAX(ABS(b->maxX - b->minX), ABS(b->maxY - b->minY));
                half /= 2.0f;
                fn_80429090(&left, &from, &side, half);
                fn_80429090(&right, &from, &side, -half);
                Placement hit;
                clear = !fn_8004A9CC(&from, &dir, len, 0x8000, &hit, fn_800B24AC(*fn_80442080(ai)),
                                     fn_800B1CC8(*fn_80442080(ai)), 0, 3);
                int color = 0xffff0000;
                if (clear) {
                    color = 0xff00ff00;
                }
                if (clear) {
                    fn_80429038(&dir, &to, &left);
                    fn_8042F76C(&dir);
                    len = fn_804290F8(&left, &to);
                    float size = MAX(ABS(fn_80134870T(ai)->maxX - fn_80134870T(ai)->minX),
                                     ABS(fn_80134870T(ai)->maxY - fn_80134870T(ai)->minY));
                    len -= size;
                    if (len > 10.0f) {
                        len = 10.0f;
                    }
                    clear = !fn_8004A9CC(&left, &dir, len, 0x8000, &hit, fn_800B24AC(*fn_80442080(ai)),
                                         fn_800B1CC8(*fn_80442080(ai)), 0, 3);
                    color = 0xffff0000;
                    if (clear) {
                        color = 0xff00ff00;
                    }
                    if (clear) {
                        fn_80429038(&dir, &to, &right);
                        fn_8042F76C(&dir);
                        len = fn_804290F8(&right, &to);
                        float size = MAX(ABS(fn_80134870T(ai)->maxX - fn_80134870T(ai)->minX),
                                         ABS(fn_80134870T(ai)->maxY - fn_80134870T(ai)->minY));
                        len -= size;
                        if (len > 10.0f) {
                            len = 10.0f;
                        }
                        clear = !fn_8004A9CC(&right, &dir, len, 0x8000, &hit, fn_800B24AC(*fn_80442080(ai)),
                                             fn_800B1CC8(*fn_80442080(ai)), 0, 3);
                        color = 0xffff0000;
                        if (clear) {
                            color = 0xff00ff00;
                        }
                    }
                }
            }
            if (fn_80134870(ai) && fn_8015E64C(ai) > 5.0f && fn_8015E8A8(ai, fn_800B1724(*fn_80134870(ai))) > 4.0f &&
                fn_8015EEA0(ai)) {
                clear = 1;
            }
            if (clear) {
                fn_80138A24(h, 0xa);
                fn_80462BB4(h, 5);
                fn_80138B7C(h, 0x10, 500, 500);
            }
            return h;
        }
    }
    return 0;
}

// BODY_THROW (docs/ai.md section 4.3).
extern "C" AIAction *fn_801409D0(void *ai, AIBehavior *rec)
{
    int grab = 0;
    Ent *t = fn_80134870(ai);
    if (t && fn_800B0C58(t) && fn_80085D3C(fn_80442080(ai)) && !fn_80461D48(ai, 0x28) && fn_800866C0(fn_800B14A0(t))) {
        grab = 1;
    }
    if (fn_800CD0EC(*fn_8044203C(ai)) || grab) {
        fn_80136214(ai, 0x11);
        return 0;
    }
    if (!fn_8015F008(ai) && fn_8015EE34(ai, fn_80134870(ai))) {
        AIAction *h = fn_80138738(0x11, 100, 200);
        if (h) {
            Vector v;
            if (fn_8015F6CC(ai, &v)) {
                fn_80138AE0(h, 0, &v, 1.0f);
            } else {
                fn_8042DC84(&v, fn_800B1750(*fn_80442080(ai)));
                fn_80138AE0(h, 0, &v, 1.0f);
            }
            if (fn_801369B0(ai)) {
                fn_80138A24(h, 7);
            }
            fn_80138A24(h, 0x12);
            return h;
        }
    }
    return 0;
}

// SWAT (docs/ai.md section 4.3).
extern "C" AIAction *fn_80140C10(void *ai, AIBehavior *rec)
{
    if (fn_80461D48(ai, 2) && fn_80461D48(ai, 0x33) && fn_80461D48(ai, 0x14) && fn_80461D48(ai, 0x18)) {
        AIAction *h = fn_80138738(0x12, 1000, 100);
        if (h) {
            Vector v;
            fn_8042DC84(&v, fn_800B1750(*fn_80442080(ai)));
            int hit;
            if (fn_8015E2FC(ai, &v, 2.0f, &hit, 0.0f)) {
                void *o = fn_800ACFA8(hit);
                if (o && fn_800B0CC0(o) && fn_8008572C(fn_80442080(ai), fn_800B1478(o)) && !fn_800A4538(fn_800B1478(o))) {
                    fn_80138A24(h, 2);
                    fn_80138A24(h, 0x19);
                } else {
                    fn_80138A24(h, 5);
                    if (fn_801369B0(ai) && fn_8015EC1C(fn_80461F3C(ai))) {
                        if (fn_80085D3C(fn_80442080(ai))) {
                            fn_80138A24(h, 7);
                        } else {
                            fn_80138A24(h, 0x14);
                        }
                    }
                }
            }
            return h;
        }
    }
    return 0;
}

// PICKUP (docs/ai.md section 4.3).
extern "C" AIAction *fn_80140E64(void *ai, AIBehavior *rec)
{
    Ent *t = fn_80134870(ai);
    if (!t) {
        return 0;
    }
    float dist = fn_804290F8(fn_800B1724(*fn_80442080(ai)), fn_800B1724(*t));
    if ((fn_800860FC(fn_80442080(ai)) && !fn_80461D48(ai, 0x3c) && dist < 10.0f) || dist < 3.0f) {
        AIAction *h = fn_80138738(0x13, 50, 500);
        if (h) {
            Vector d;
            fn_8042DC84(&d, fn_800B1724(*t));
            fn_8042D8A8(&d, fn_800B1724(*fn_80442080(ai)));
            d.z = 0.0f;
            float len = fn_8042EC54(&d);
            if (len > 1.0f) {
                fn_80138AE0(h, 0, &d, 0.25f);
            }
            int both = 0;
            Ent *o = fn_80462530(fn_804420D8(ai));
            if (o && o != t) {
                Vector a, b;
                float da = fn_8015F538(ai, fn_800B1724(*o), &a);
                float db = fn_8015F538(ai, fn_800B1724(*t), &b);
                int ahead = fn_8042EBF4(&a, &b) > 0.25f;
                int near = da > 2.0f && db > 0.1f && db < 2.0f;
                if (ahead && near) {
                    both = 1;
                }
            }
            if (o && fn_8008615C(fn_80442080(ai)) && fn_800CC6DC(*fn_8044203C(ai)) == 0x22) {
                Vector b, a;
                float db, da;
                db = fn_8015F538(ai, fn_800B1724(*t), &b);
                da = fn_8015F538(ai, fn_800B1724(*o), &a);
                if (db < da && db < fn_800B1884(*fn_80442080(ai), 0xd3) && fn_8042EBF4(&b, &a) > 0.0f) {
                    fn_80138A24(h, 2);
                    fn_80138B7C(h, 0x13, 100, 100);
                    return h;
                }
            }
            if (both || fn_80461F94(ai) == 0.0f) {
                fn_80138A24(h, 2);
                fn_80138A24(h, 0x19);
                fn_80138B7C(h, 0x12, 100, 100);
            } else {
                fn_80138A24(h, 4);
                if (fn_800860FC(fn_80442080(ai)) &&
                    fn_8015E580(fn_800B1724(*fn_80442080(ai)), fn_800B1724(*t)) > 2.5f) {
                    fn_80138A24(h, 7);
                }
            }
            return h;
        }
    }
    return 0;
}

// SUPER_BLOCK_THROWN (docs/ai.md section 4.3).
extern "C" AIAction *fn_80141394(void *ai, AIBehavior *rec)
{
    if (fn_80461D48(ai, 2)) {
        Ent *t = fn_80134870(ai);
        if (!t) {
            return 0;
        }
        if (fn_80461D48(ai, 0x2d) || fn_80461D48(ai, 0x2c)) {
            AIAction *h = fn_80138738(0x14, 1500, 100);
            if (h) {
                fn_80138A24(h, 0);
                if (fn_801369B0(ai) && fn_80461D48(ai, 0x2c)) {
                    fn_80138A24(h, 0x17);
                }
                fn_80462BB4(h, 5);
                return h;
            }
        }
    }
    return 0;
}

// AVOID_HAZARDS (docs/ai.md section 4.3).
extern "C" AIAction *fn_801414C8(void *ai, AIBehavior *rec)
{
    Vector pos, dir, fwd;
    fn_8042DC84(&pos, fn_800B1724(*fn_80442080(ai)));
    fn_80067050(*fn_80442080(ai), &fwd);
    fwd.z = 0.0f;
    float len = fn_8042EC54(&fwd);
    if (len < 0.1f) {
        fn_8042DC84(&fwd, fn_800B1750(*fn_80442080(ai)));
    }
    float reach = 2.5f; // dead: the fn_80429090 call below takes the literal
    if (fn_800CCAE8(*fn_8044203C(ai))) {
        reach = 6.0f;
    } else if (fn_800CCA58(*fn_8044203C(ai))) {
        reach = 4.0f;
    }
    fn_80429090(&dir, &pos, &fwd, 2.5f);
    if (fn_800CE4D0(fn_8044203C(ai))) {
        for (int i = 0; i < fn_80462D68(fn_8013726C(ai)); i++) {
            void *v = fn_80462DB0(fn_8013726C(ai), i);
            if (!v) {
                continue;
            }
            Vector hit;
            pos.z = 0.0f;
            dir.z = 0.0f;
            if (fn_801464E4(v, &dir)) {
                Vector out;
                Ent *t = fn_80134870(ai);
                if (t) {
                    fn_8042DC84(&pos, fn_800B1724(*t));
                    pos.z = 0.0f;
                }
                fn_80146604(v, &pos, &out);
                AIAction *h = fn_80138738(0x15, 1000, 0);
                if (h) {
                    fn_80138AE0(h, 0, &out, 1.0f);
                    fn_80462BDC(h, 40.0f);
                    return h;
                }
            }
            if (fn_80146A88(v, &pos, &dir, &hit)) {
                hit.z = pos.z;
                Vector away;
                fn_80429038(&away, &hit, &pos);
                away.z = 0.0f;
                fn_8042F76C(&away);
                fn_80433FFC(&away);
                AIAction *h = fn_80138738(0x15, 1000, 0);
                if (h) {
                    fn_80138AE0(h, 0, &away, 1.0f);
                    fn_80462BDC(h, 40.0f);
                    return h;
                }
            }
        }
    }
    for (int i = 0; i < fn_804622B4(fn_8013726C(ai)); i++) {
        void *v = fn_804622FC(fn_8013726C(ai), i);
        if (!v) {
            continue;
        }
        Vector hit;
        pos.z = 0.0f;
        dir.z = 0.0f;
        if (fn_801464E4(v, &pos)) {
            Vector out;
            fn_80146604(v, &pos, &out);
            AIAction *h = fn_80138738(0x15, 1000, 10);
            if (h) {
                fn_80138AE0(h, 0, &out, 1.0f);
                fn_80462BB4(h, 5);
                if (fn_800CCC28(*fn_8044203C(ai))) {
                    fn_80138A24(h, 5);
                }
                return h;
            }
        }
        if (fn_80146A88(v, &pos, &dir, &hit)) {
            hit.z = pos.z;
            Vector away;
            fn_80429038(&away, &hit, &pos);
            away.z = 0.0f;
            fn_8042F76C(&away);
            fn_80433FFC(&away);
            AIAction *h = fn_80138738(0x15, 1000, 10);
            if (h) {
                fn_80138AE0(h, 0, &away, 1.0f);
                fn_80462BB4(h, 5);
                if (fn_800CCC28(*fn_8044203C(ai))) {
                    fn_80138A24(h, 5);
                }
                return h;
            }
        }
    }
    Vector sum;
    int n = 0;
    fn_80447C38(&sum);
    for (int i = 0; i < fn_80462E98(fn_8013726C(ai)); i++) {
        Ent *e = fn_80462EE0(fn_8013726C(ai), i);
        if (e) {
            Vector at, d;
            fn_8042DC84(&at, fn_800B1724(*e));
            if (fn_804290F8(&at, &pos) < 6.0f) {
                fn_8042DC84(&d, &pos);
                fn_8042D8A8(&d, &at);
                d.z = 0.0f;
                fn_8042F76C(&d);
                fn_8042D854(&sum, &d);
                n++;
            }
        }
    }
    if (n) {
        AIAction *h = fn_80138738(0x15, 1000, 10);
        if (h) {
            fn_80435530(&sum, 1.0f / fn_8042CE28(n));
            if (fn_80085F7C(fn_80442080(ai))) {
                fn_80138A24(h, 9);
            } else if (fn_8008606C(fn_80442080(ai))) {
                fn_80138A24(h, 9);
                fn_80138A24(h, 5);
            } else {
                fn_80138A24(h, 5);
            }
            fn_80138AE0(h, 0, &sum, 1.0f);
            fn_80462BDC(h, 50.0f);
            return h;
        }
    }
    return 0;
}

// DEFEND_REGIONS (docs/ai.md section 4.3).
extern "C" AIAction *fn_80141D78(void *ai, AIBehavior *rec)
{
    if (fn_800CCC28(*fn_8044203C(ai))) {
        return 0;
    }
    Vector pos, dir, fwd;
    fn_8042DC84(&pos, fn_800B1724(*fn_80442080(ai)));
    fn_80067050(*fn_80442080(ai), &fwd);
    fwd.z = 0.0f;
    float len = fn_8042EC54(&fwd);
    if (len < 0.1f) {
        fn_8042DC84(&fwd, fn_800B1750(*fn_80442080(ai)));
    }
    fn_80429090(&dir, &pos, &fwd, 2.5f);
    for (int i = 0; i < fn_80462CD0(fn_8013726C(ai)); i++) {
        Region *r = fn_80462D18(fn_8013726C(ai), i);
        if (!r) {
            continue;
        }
        if (r->owner != fn_800B13D8(*fn_80442080(ai))) {
            continue;
        }
        if (!fn_801464E4(r, &pos)) {
            AIAction *h = fn_80138738(0x16, 1000, 0);
            if (h) {
                Vector out;
                fn_80146604(r, &pos, &out);
                Vector in;
                fn_80429038(&in, &r->centre, &pos);
                fn_8042F76C(&in);
                fn_80433FFC(&out);
                fn_80138AE0(h, 0, &out, 1.0f);
                fn_80462BB4(h, 5);
                fn_80462BDC(h, 1000.0f);
                Vector at;
                fn_8042DC84(&at, fn_800B1724(*fn_80442080(ai)));
                at.z += 1.0f;
                return h;
            } else {
                int n = 0;
                n++;
            }
        }
    }
    return 0;
}

// The .rodata claim's 8-align pad, read by the unclaimed fn_801420B4: becomes that handler's literal once it is matched.
extern "C" const float lbl_8049AF54 __attribute__((section(".rodata"))) = 3.0f;
