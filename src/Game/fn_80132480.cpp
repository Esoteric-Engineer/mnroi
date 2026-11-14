// AI manager (init, update, debug draw, the per-AI loops, the encounter list), the AIObject and the file's static init. docs/ai.md rows 1 and 6.
// .rodata: pool from 0x8049A85C (floats and strings), extern_pool. Merges the former Game/fn_80137CEC.c.
// Invented class names Volumes and AiObj give the static init its destructor calls (_._7Volumes, _._5AiObj in symbols.txt).

struct Ent {
    int pad;
};
struct PlayerEnt : Ent { // matching_notes 44
    int x;
};

class Vec2
{
public:
    float x; // +0x0
    float y; // +0x4
    Vec2() __asm__("fn_80426A2C");
};

struct AIObject {
    void *f0;              // +0x0
    int f4;                // +0x4
    float f8;              // +0x8
    char fC[8];            // +0xC bit set
    char f14[8];           // +0x14 bit set
    int f1C, f20, f24, f28, f2C, f30, f34, f38, f3C, f40; // +0x1C
    int f44[26];           // +0x44
    char fAC[0x24];        // +0xAC list
    char fD0[0x134];       // +0xD0
    void *f204;            // +0x204 brain
    char pad208[0x8];
    char f210[0x2f0];      // +0x210
    char f500[8];          // +0x500 bit set
    char f508[8];          // +0x508 bit set
    int f510, f514;        // +0x510
    unsigned int f518, f51C; // +0x518
    int f520, f524, f528;  // +0x520
    void *f52C;            // +0x52C
    void *f530;            // +0x530
    int f534, f538, f53C;  // +0x534
    char f540[0x10];       // +0x540
    int f550, f554;        // +0x550
    unsigned int f558, f55C; // +0x558
    int f560, f564;        // +0x560
    char pad568[0x28];
    int f590, f594;        // +0x590
    float f598[22];        // +0x598 PLAYER "AI weight" fields
};

extern "C" {
extern int lbl_8066BF1C; // registered AI count
extern int lbl_8066BF20; // AI enabled
extern int lbl_8066BF24;
extern float lbl_8066BF30;
extern int lbl_8066BF34;
extern int lbl_8066BF38;
extern float lbl_8066BF3C;
extern int lbl_8066BF28;
extern int lbl_8066BF2C;
extern int lbl_8066BF48; // update countdown
extern int lbl_8066BF4C; // initialised
extern int lbl_8066BF50;
extern int lbl_8066C7DC;
extern void *lbl_8066D6DC; // the overlay text object (docs/versus.md section 6)
extern int lbl_8066F1A8; // encounter record count
extern char lbl_8054ED80[];
extern char lbl_80593BE8[];
extern char lbl_80552110[];
class Volumes // the volume registry (docs/ai.md section 4.5); ctor and dtor in Game/fn_80461430.cpp
{
public:
    char b[0xdc];
    Volumes() __asm__("fn_80461430");
    ~Volumes();
};
class AiObj // the encounter record, as in Game/fn_80147DE4.cpp
{
public:
    char b[0xdc];
    AiObj() __asm__("fn_804619C8");
    ~AiObj();
};
Volumes lbl_80569890;
AiObj lbl_8056996C[16];
void *lbl_8056A72C[49];

void fn_80137F2C(void);
void fn_80145D8C(void *p);
void fn_80447DBC(void *p, int flags);
void fn_80138584(void);
void fn_80145DF8(void *p);
void fn_801498B0(void);
void fn_8013866C(void);
void fn_80145FE4(void *p);
void fn_80147DE4(void *rec);
void fn_801480D0(void *rec, void *actor);
int fn_80147FA4(void *rec, int id);
int fn_80148050(void *rec, int id);
void fn_8013646C(AIObject *ai, unsigned int event, Ent *src, Ent *other);
int fn_80086B6C(void *e);
void fn_8009E09C(void *e);
int fn_801475D8(void *c, int a, int b);
void fn_801477B0(void *c, int a, int b);
void fn_80147884(void *c, int a);
void fn_80147968(void *c, int a, int b);
void fn_80147A20(void *c, int a, int b);
void fn_80147C40(void *c, int a);
void fn_80147B88(void *c, int a);
void fn_80147CF8(void *c, int a);
void fn_80147D68(void *c, int a);
int fn_804621DC(void *e);
void *fn_80085980(void *actor);
void fn_80461CC0(void *ai, int bit);
void fn_80461D04(void *ai, int bit);
void *fn_80461E2C(void *ai);
void fn_8042DC84(void *p, int v);
void fn_80134028(AIObject *ai);
void fn_80134280(AIObject *ai);
void fn_801346C0(AIObject *ai);
int fn_80461A3C(void *rec);
struct Tune16 { int a; int b; int c; float f; };
extern Tune16 lbl_804CF968[];
void fn_80132AAC(void);
void fn_8013589C(AIObject *ai);
int fn_804439A4(void *p);
int fn_80094BD0(void *p);
int fn_80094C64(void *p);
void *fn_8043492C(void *p);
void *fn_800B14A0(void *p);
int fn_80132E30(void *p);
void *fn_80132F00(void *p);
int fn_80132FE4(void *p);
void fn_80148B08(void *p);
void fn_801497A8(void);
extern int sprintf(char *dst, const char *fmt, ...);
void fn_80426A54(Vec2 *v, float x, float y);
int fn_800FE284(int index);
int fn_80426E88(void *text, int font);
void fn_80101188(void *text, float height);
void fn_80100C50(void *text, int a);
void fn_8042AC7C(void *text, unsigned int color);
PlayerEnt *AI_GetEntity(void *a);
int fn_800B13D8(Ent &actor);
int fn_800B92DC(void **text, const char *s, float x, float y);
void *fn_80133A30(void);
int fn_80461EB8(void *e);
void fn_80137494(AIObject *ai, float x, float y);
void fn_8042D0A8(void *text);
void fn_80148B50(void *rec, float x, float y);
void fn_80149554(void);
void *fn_804326B4(void *list);
float fn_80461690(void *e);
unsigned int fn_804616BC(void *e);
int fn_804616E8(void *e);
void fn_80133AE4(int v);
void fn_80133B0C(float v);
void fn_80133B5C(float v);
}

inline int sn_return_decl(int a) { return a; } // function-end pair, prodg.md

extern "C" void fn_80132480(void)
{
    int i;
    void *e;
    float a;
    float b;

    if (lbl_8066BF4C) {
        fn_80132AAC();
    }
    lbl_8066BF1C = 0;
    for (i = 0; i < 48; i++) {
        lbl_8056A72C[i] = 0;
    }
    fn_80137F2C();
    lbl_8066BF2C = 0;
    lbl_8066BF28 = 0;
    fn_80145D8C(&lbl_80569890);
    lbl_8066F1A8 = 0;
    lbl_8066BF4C = 1;
    lbl_8066BF20 = 1;
    fn_80149554();
    e = fn_804326B4(lbl_8054ED80);
    a = -1.0f;
    b = 10000.0f;
    if (e) {
        a = fn_80461690(e);
        b = (float)fn_804616BC(e);
        lbl_8066BF50 = fn_804616E8(e);
    }
    if (a > 0.0f) {
        fn_80133AE4(1);
        fn_80133B0C(a);
        fn_80133B5C(b);
    }
    lbl_8066BF48 = 0;
}

extern "C" void fn_80132600(void)
{
    int i;

    if (!lbl_8066BF4C) {
        return;
    }
    if (fn_804439A4(lbl_80593BE8)) {
        return;
    }
    if (lbl_8066C7DC) {
        return;
    } else if (lbl_8066BF48 > 0) {
        lbl_8066BF48 = lbl_8066BF48 - 1;
        return;
    }
    if (lbl_8066BF20) {
        for (i = 0; i < lbl_8066BF1C; i++) {
            void *ai = lbl_8056A72C[i];
            fn_8013589C((AIObject *)ai);
        }
        return;
    }
    if (lbl_8066BF28 && lbl_8066BF1C > 0) {
    }
    if (fn_80094BD0(lbl_80552110)) {
        do {
            void *e = fn_8043492C(lbl_80552110);
            if (e) {
                if (!fn_80132E30(fn_800B14A0(e))) {
                    if (!fn_80132FE4(fn_800B14A0(e))) {
                    } else {
                    }
                }
            }
        } while (fn_80094C64(lbl_80552110));
    }
    {
        int j;
        for (j = 0; j < lbl_8066F1A8; j++) {
            fn_80148B08(&lbl_8056996C[j]);
        }
        for (i = 0; i < lbl_8066BF1C; i++) {
            void *ai = lbl_8056A72C[i];
            fn_8013589C((AIObject *)ai);
        }
    }
    fn_801497A8();
}

extern "C" void fn_80132838(void)
{
    float x;
    float y;

    if (!lbl_8066BF28) {
        return;
    }
    if (lbl_8066BF1C <= 0) {
        return;
    }
    if (!lbl_8066BF4C) {
        return;
    }
    x = 210.0f;
    y = 120.0f;
    Vec2 v;
    void *ai;
    char buf[0x50];
    void *p;
    float step;
    int j;
    fn_80426A54(&v, x, y);
    ai = lbl_8056A72C[lbl_8066BF2C];
    if (ai) {
        fn_80426E88(lbl_8066D6DC, fn_800FE284(6));
        fn_80101188(lbl_8066D6DC, 13.0f);
        fn_80100C50(lbl_8066D6DC, 0);
        fn_8042AC7C(lbl_8066D6DC, 0xFFB0B000);
        sprintf(buf, "%s-%#.4d", (char *)AI_GetEntity(ai) + 0xfc, fn_800B13D8(*AI_GetEntity(ai)));
        fn_800B92DC(&lbl_8066D6DC, buf, x, y);
        y = y + 13.0f;
    }
    p = fn_80133A30();
    if (p) {
        if (fn_80461EB8(p)) {
            fn_80137494((AIObject *)p, x, y);
        }
    }
    x = 360.0f;
    y = 120.0f;
    fn_8042AC7C(lbl_8066D6DC, 0xFFD0D0D0);
    fn_80101188(lbl_8066D6DC, 11.0f);
    step = 11.0f;
    fn_800B92DC(&lbl_8066D6DC, "Encounter:", x, y);
    y = y + step;
    for (j = 0; j < lbl_8066F1A8; j++) {
        fn_80148B50(&lbl_8056996C[j], x, y);
    }
    fn_8042D0A8(lbl_8066D6DC);
}

extern "C" void fn_80132AAC(void)
{
    int i;

    for (i = 0; i < lbl_8066BF1C; i++) {
        if (lbl_8056A72C[i]) {
            fn_80447DBC(lbl_8056A72C[i], 3);
        } else {
        }
        lbl_8056A72C[i] = 0;
    }
    lbl_8066BF1C = 0;
    fn_80138584();
    fn_80145DF8(&lbl_80569890);
    lbl_8066F1A8 = 0;
    fn_801498B0();
}

extern "C" void fn_80132B88(void)
{
    int i;

    lbl_8066F1A8 = 0;
    for (i = 0; i < lbl_8066BF1C; i++) {
        fn_80134028((AIObject *)lbl_8056A72C[i]);
    }
}

extern "C" void fn_80132C04(void)
{
    fn_8013866C();
    fn_80145D8C(&lbl_80569890);
    fn_80145FE4(&lbl_80569890);
    lbl_8066BF48 = 10;
}

extern "C" void fn_80132C54(void)
{
    int i;

    for (i = 0; i < lbl_8066F1A8; i++) {
        fn_80147DE4(&lbl_8056996C[i]);
    }
    lbl_8066F1A8 = 0;
    fn_80145DF8(&lbl_80569890);
}

extern "C" void fn_80132CDC(void)
{
    int i;

    for (i = 0; i < lbl_8066BF1C; i++) {
        fn_80134280((AIObject *)lbl_8056A72C[i]);
    }
}

extern "C" void fn_80132D50(void)
{
    int i;

    for (i = 0; i < lbl_8066BF1C; i++) {
        fn_801346C0((AIObject *)lbl_8056A72C[i]);
    }
}

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.text"); // 0x8049A8A0, a pool entry no function in the unit loads

extern "C" float fn_80132DC4(int index)
{
    if (index < 0 || index > 30) {
        return 0.0f;
    }
    return lbl_804CF968[index].f;
}

extern "C" int fn_80132E30(void *p)
{
    int id;
    int i;

    if (!p) {
        return 0;
    }
    id = fn_800B13D8(*(Ent *)p);
    if (!id) {
        return 0;
    }
    for (i = 0; i < lbl_8066F1A8; i++) {
        if (fn_80461A3C(&lbl_8056996C[i]) == id) {
            return 1;
        }
    }
    return 0;
}

extern "C" void *fn_80132F00(void *p)
{
    int id;
    int i;

    if (!p) {
        return 0;
    }
    id = fn_800B13D8(*(Ent *)p);
    if (!id) {
        return 0;
    }
    for (i = 0; i < lbl_8066F1A8; i++) {
        if (fn_80461A3C(&lbl_8056996C[i]) == id) {
            return &lbl_8056996C[i];
        }
    }
    return 0;
}

extern "C" int fn_80132FE4(void *p)
{
    if (lbl_8066F1A8 <= 15) {
        fn_80147DE4(&lbl_8056996C[lbl_8066F1A8]);
        fn_801480D0(&lbl_8056996C[lbl_8066F1A8], p);
        lbl_8066F1A8++;
        return 1;
    }
    return 0;
}

extern "C" int fn_80133078(void *p)
{
    int id;
    int i;

    if (!p) {
        return 0;
    }
    id = fn_800B13D8(*(Ent *)p);
    if (!id) {
        return 0;
    }
    for (i = 0; i < lbl_8066F1A8; i++) {
        if (fn_80461A3C(&lbl_8056996C[i]) == id) {
            if (lbl_8066F1A8 == 1) {
                lbl_8066F1A8--;
            } else if (i == 15) {
                lbl_8066F1A8--;
            } else {
                lbl_8056996C[i] = ((AiObj *)&lbl_80569890)[lbl_8066F1A8];
                lbl_8066F1A8--;
            }
            return 1;
        }
    }
    return 0;
}

extern "C" int fn_80133208(void *p)
{
    int i;

    if (!p) {
        return 0;
    }
    for (i = 0; i < lbl_8066F1A8; i++) {
        if (fn_80147FA4(&lbl_8056996C[i], fn_800B13D8(*(Ent *)p))) {
            return 1;
        }
    }
    return 0;
}

extern "C" void *fn_801332C0(void *p)
{
    int i;

    if (!p) {
        return 0;
    }
    for (i = 0; i < lbl_8066F1A8; i++) {
        if (fn_80147FA4(&lbl_8056996C[i], fn_800B13D8(*(Ent *)p))) {
            return &lbl_8056996C[i];
        }
    }
    return 0;
}

extern "C" int fn_8013338C(void *p)
{
    int i;

    if (!p) {
        return 0;
    }
    for (i = 0; i < lbl_8066F1A8; i++) {
        if (fn_80148050(&lbl_8056996C[i], fn_800B13D8(*(Ent *)p))) {
            return 1;
        }
    }
    return 0;
}

extern "C" void fn_80133444(void *p)
{
    if (!p) {
        return;
    }
    if (lbl_8066BF1C > 47) {
        return;
    }
    lbl_8056A72C[lbl_8066BF1C++] = p;
}

extern "C" void fn_801334B0(void *ai)
{
    int i;

    if (!ai) {
        return;
    }
    for (i = 0; i < lbl_8066BF1C; i++) {
        if (lbl_8056A72C[i] == ai) {
            if (i == lbl_8066BF1C - 1) {
                lbl_8056A72C[i] = 0;
            } else {
                lbl_8056A72C[i] = lbl_8056A72C[lbl_8066BF1C - 1];
                lbl_8056A72C[lbl_8066BF1C - 1] = 0;
            }
            lbl_8066BF1C--;
            return;
        }
    }
}

extern "C" void fn_801335C8(int v)
{
    if (!v) {
        lbl_8066BF24 = 1;
    }
}

extern "C" void fn_801335FC(int v)
{
    if (!v) {
        lbl_8066BF24 = 0;
    }
}

extern "C" int fn_80133630(void)
{
    return lbl_8066BF24;
}

extern "C" void fn_80133658(void)
{
    lbl_8066BF20 = 1;
}

extern "C" void fn_8013367C(void)
{
    lbl_8066BF20 = 0;
}

extern "C" void fn_801336A0(int a, int b, int c, int d)
{
    fn_8013646C((AIObject *)b, a, (Ent *)d, (Ent *)c);
}

extern "C" void fn_801336F0(void)
{
    int i;

    for (i = 0; i < lbl_8066BF1C; i++) {
        void *ai = lbl_8056A72C[i];
        PlayerEnt *e = AI_GetEntity(ai);
        if (e) {
            if (fn_80086B6C(e)) {
                fn_8009E09C(e);
            }
        }
    }
}

extern "C" int fn_8013379C(int a, int b)
{
    return fn_801475D8(&lbl_80569890, a, b);
}

extern "C" void fn_801337F0(int a, int b)
{
    fn_801477B0(&lbl_80569890, a, b);
}

extern "C" void fn_80133838(int a)
{
    fn_80147884(&lbl_80569890, a);
}

extern "C" void fn_80133878(int a, int b)
{
    fn_80147968(&lbl_80569890, a, b);
}

extern "C" void fn_801338C0(int a, int b)
{
    fn_80147A20(&lbl_80569890, a, b);
}

extern "C" void fn_80133908(int a)
{
    fn_80147C40(&lbl_80569890, a);
}

extern "C" void fn_80133948(int a)
{
    fn_80147B88(&lbl_80569890, a);
}

extern "C" void fn_80133988(int a)
{
    fn_80147CF8(&lbl_80569890, a);
}

extern "C" void fn_801339C8(int a)
{
    fn_80147D68(&lbl_80569890, a);
}

extern "C" int fn_80133A08(void)
{
    return lbl_8066BF28;
}

extern "C" void *fn_80133A30(void)
{
    return lbl_8056A72C[lbl_8066BF2C];
}

extern "C" int fn_80133A6C(void *a, void *b)
{
    void *x = a;
    void *y = b;

    if (fn_804621DC(x) == fn_804621DC(y)) {
        return 1;
    } else {
        return 0;
    }
}

extern "C" void fn_80133AE4(int v)
{
    lbl_8066BF34 = v;
}

extern "C" void fn_80133B0C(float v)
{
    lbl_8066BF30 = v;
}

extern "C" void fn_80133B34(float v)
{
    lbl_8066BF3C = v;
}

extern "C" void fn_80133B5C(float v)
{
    lbl_8066BF38 = (int)v;
}

extern "C" void fn_80133B94(void *actor, int a, int b, int c)
{
    void *ai;

    if (!actor) {
        return;
    }
    ai = fn_80085980(actor);
    if (ai) {
        if (a) {
            fn_80461CC0(ai, 0x39);
        } else {
            fn_80461D04(ai, 0x39);
        }
        if (b) {
            fn_8042DC84(fn_80461E2C(ai), b);
            fn_80461CC0(ai, 0x3a);
        } else {
            fn_80461D04(ai, 0x3a);
        }
        if (c) {
            fn_80461CC0(ai, 0x3b);
        } else {
            fn_80461D04(ai, 0x3b);
        }
    }
}

extern "C" {
void *fn_804617F0(void *p);
void fn_80461828(void *p, unsigned int count);
void fn_801B5BA8(void *p, int n, float f);
void fn_801B5E38(void *p, int n);
void fn_80461904(void *p);
void fn_80461A68(void *p);
void __6Vector(void *p);
void *Entity_GetActor(void *e);
void fn_800859AC(void *actor, void *ai);
}

extern "C" AIObject *fn_80133C8C(register AIObject *self, void *ent)
{
    int i;

    fn_804617F0((char *)self + 0xc);
    fn_804617F0((char *)self + 0x14);
    fn_801B5BA8((char *)self + 0xac, 4, 1.0f);
    fn_80461904((char *)self + 0xd0);
    fn_80461A68((char *)self + 0x210);
    fn_804617F0((char *)self + 0x500);
    fn_804617F0((char *)self + 0x508);
    __6Vector((char *)self + 0x540);
    __6Vector((char *)self + 0x570);
    __6Vector((char *)self + 0x580);
    self->f52C = ent;
    self->f530 = Entity_GetActor(ent);
    fn_800859AC(self->f530, self);
    fn_80461828((char *)self + 0x500, 0x2a);
    fn_80461828((char *)self + 0x508, 0x2a);
    fn_80461828((char *)self + 0xc, 0x41);
    fn_80461828((char *)self + 0x14, 0x20);
    for (i = 0; i < 26; i++) {
        self->f44[i] = 0;
    }
    self->f4 = 0;
    self->f534 = 0;
    self->f8 = 1.0f;
    self->f594 = 0;
    self->f558 = 0;
    self->f55C = 0;
    fn_801B5E38((char *)self + 0xac, 0x2b);
    self->f550 = 0;
    self->f554 = 0;
    self->f53C = 0;
    self->f510 = 1;
    self->f560 = 0;
    return self;
}

extern "C" {
struct AIBrainBase;
AIBrainBase *fn_80136AC8(AIObject *ai, int profile);
void fn_80150960(void *brain);
void fn_8014DDD4(void *p, AIObject *ai);
void fn_8014A3B4(void *p, AIObject *ai);
void fn_804618B0(void *p);
void fn_801343B0(AIObject *ai);
void fn_801B60F4(void *p);
void fn_801B6A70(void *p, int (*cmp)(void *, void *));
void fn_8014DE30(void *p);
void fn_8014A554(void *p);
void fn_801509A8(void *brain);
void fn_80462018(void *brain, int inChrg);
int fn_80085D3C(void *actor);
void *AI_GetTargetList(AIObject *ai);
void fn_8014F7B0(void *p, int v);
float fn_80461EE4(AIObject *ai);
float fn_80461F10(AIObject *ai);
float fn_80461FC0(AIObject *ai);
float fn_80461F68(AIObject *ai);
float fn_80461F94(AIObject *ai);
int fn_80085F7C(void *actor);
int fn_8008606C(void *actor);
unsigned int fn_80443970(void *clock);
void fn_804617CC(int v);
unsigned int fn_8015EA6C(int n, float *w);
void fn_8015105C(void *brain, int id);
void fn_8014DEB8(void *p);
int fn_8015EA18(int n);
void *fn_80461DD4(AIObject *ai);
}

extern "C" void fn_80133E5C(register AIObject *self, void *ent)
{
    self->f0 = ent;
    self->f204 = fn_80136AC8(self, (int)ent);
    fn_80150960(self->f204);
    fn_8014DDD4(self->fD0, self);
    fn_8014A3B4(self->f210, self);
    fn_804618B0(self->fC);
    fn_804618B0(self->f14);
    fn_804618B0(self->f500);
    fn_804618B0(self->f508);
    self->f534 = 1;
    self->f8 = 1.0f;
    self->f538 = 0;
    self->f1C = 0;
    self->f20 = 0;
    self->f24 = 0;
    fn_801343B0(self);
    fn_801B60F4(self->fAC);
    fn_801B6A70(self->fAC, fn_80133A6C);
    self->f564 = 0;
    self->f590 = 0;
    self->f594 = 0;
    self->f550 = 0;
    self->f554 = 0;
    self->f560 = 0;
    fn_80134280(self);
    fn_80133444(self);
}

extern "C" void fn_80133FA0(register AIObject *self)
{
    fn_8014DE30(self->fD0);
    fn_8014A554(self->f210);
    fn_801509A8(self->f204);
    if (self->f204) {
        fn_80462018(self->f204, 3);
    } else {
    }
    fn_80133078(AI_GetEntity(self));
    fn_801334B0(self);
}

extern "C" void fn_80134028(register AIObject *self)
{
    float w[6];
    int t;
    unsigned int r;

    if (!fn_80085D3C(self->f530)) {
        return;
    }
    fn_8014F7B0(AI_GetTargetList(self), 0);
    w[0] = fn_80461EE4(self) * fn_80461F10(self);
    w[1] = 2.0f * fn_80461EE4(self) * fn_80461FC0(self);
    w[2] = 2.0f * fn_80461EE4(self) * fn_80461F68(self);
    w[3] = fn_80461EE4(self) * 3.0f * fn_80461F94(self);
    w[4] = 2.0f * fn_80461EE4(self) * fn_80461F68(self);
    if (!fn_80085F7C(self->f530)) {
        w[4] = 0.0f;
    }
    if (!fn_80085F7C(self->f530) && !fn_8008606C(self->f530)) {
        w[1] = 0.0f;
    }
    t = fn_80443970(lbl_80593BE8);
    fn_804617CC(t);
    r = fn_8015EA6C(5, w);
    switch (r) {
    case 0:
        fn_8015105C(self->f204, 2);
        break;
    case 1:
        fn_8015105C(self->f204, 0x1b);
        break;
    case 2:
        fn_8015105C(self->f204, 3);
        break;
    case 3:
        fn_8015105C(self->f204, 4);
        break;
    case 4:
        fn_8015105C(self->f204, 0x18);
        break;
    }
}

extern "C" void fn_80134280(register AIObject *self)
{
    fn_8014DEB8(self->fD0);
    self->f514 = 0;
    self->f510 = 1;
    self->f518 = fn_8015EA18(8000) + 15000;
    self->f51C = fn_8015EA18(8000) + 15000;
    self->f558 = fn_8015EA18(7000) + 15000;
    self->f55C = fn_8015EA18(7000) + 20000;
    self->f550 = 0;
    self->f554 = 0;
    self->f2C = 0;
    self->f30 = 0;
    self->f34 = 0;
    self->f38 = 0;
    self->f28 = 0;
    self->f3C = 0;
    self->f40 = 0;
    self->f520 = 0;
    self->f528 = -1;
    self->f524 = 0;
    self->f528 = 0;
    self->f524 = 1;
    self->f594 = 0;
    fn_804618B0(fn_80461DD4(self));
}

extern "C" {
float fn_800B1884(Ent &e, int id);
int fn_800B18EC(Ent &e, int id);
float fn_8042CE28(int v);
}

// Reads 22 PLAYER tuning fields (ids 0x8B-0xA4, 0xF6, 0xF7) into +0x598.
extern "C" void fn_801343B0(register AIObject *self)
{
    self->f598[0] = fn_800B1884(*AI_GetEntity(self), 0x8B);
    self->f598[1] = fn_800B1884(*AI_GetEntity(self), 0x8C);
    self->f598[2] = fn_8042CE28(fn_800B18EC(*AI_GetEntity(self), 0xA4));
    self->f598[3] = fn_8042CE28(fn_800B18EC(*AI_GetEntity(self), 0x8D));
    self->f598[4] = fn_800B1884(*AI_GetEntity(self), 0x8E);
    self->f598[5] = fn_800B1884(*AI_GetEntity(self), 0x8F);
    self->f598[6] = fn_800B1884(*AI_GetEntity(self), 0x90);
    self->f598[7] = fn_800B1884(*AI_GetEntity(self), 0x91);
    self->f598[8] = fn_800B1884(*AI_GetEntity(self), 0x92);
    self->f598[9] = fn_800B1884(*AI_GetEntity(self), 0x9F);
    self->f598[10] = fn_800B1884(*AI_GetEntity(self), 0x93);
    self->f598[11] = fn_800B1884(*AI_GetEntity(self), 0x94);
    self->f598[12] = fn_800B1884(*AI_GetEntity(self), 0x95);
    self->f598[13] = fn_800B1884(*AI_GetEntity(self), 0x96);
    self->f598[14] = fn_800B1884(*AI_GetEntity(self), 0x97);
    self->f598[15] = fn_800B1884(*AI_GetEntity(self), 0x98);
    self->f598[16] = fn_800B1884(*AI_GetEntity(self), 0x99);
    self->f598[17] = fn_800B1884(*AI_GetEntity(self), 0x9A);
    self->f598[18] = fn_800B1884(*AI_GetEntity(self), 0x9B);
    self->f598[19] = fn_800B1884(*AI_GetEntity(self), 0x9C);
    self->f598[20] = fn_800B1884(*AI_GetEntity(self), 0xF7);
    self->f598[21] = fn_800B1884(*AI_GetEntity(self), 0xF6);
}

class AIActor
{
public:
    char d[0x5bc];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(int v); // +0x80
};

extern "C" {
void fn_80135F94(AIObject *ai);
void fn_80150A5C(void *brain);
void fn_8014B900(void *p);
PlayerEnt *AI_GetActor(AIObject *ai);
AIActor *fn_800CDA94(Ent &e);
void fn_8008656C(void *e, int v);
int fn_80150258(void *p);
Ent *fn_80150200(void *p);
Ent *fn_80461948(void *p);
}

extern "C" void fn_801346C0(register AIObject *self)
{
    fn_80134280(self);
    fn_80135F94(self);
    fn_80150A5C(self->f204);
    fn_8014B900(self->f210);
    fn_800CDA94(*AI_GetActor(self))->s15(0);
    fn_800CDA94(*AI_GetActor(self))->s15(7);
}

extern "C" void fn_801347B4(register AIObject *self)
{
    self->f4 = 1;
    fn_80150A5C(self->f204);
    fn_80134280(self);
}

extern "C" void fn_80134804(register AIObject *self)
{
    self->f4 = 0;
    if (AI_GetEntity(self)) {
        fn_8008656C(AI_GetEntity(self), 0);
    }
}

extern "C" Ent *fn_80134870(register AIObject *self)
{
    if (fn_80150258(AI_GetTargetList(self))) {
        return fn_80150200(AI_GetTargetList(self));
    } else {
        if (fn_80461948(AI_GetTargetList(self))) {
            return fn_80461948(AI_GetTargetList(self));
        } else {
            return 0;
        }
    }
    return 0;
}

struct Vector {
    float x, y, z, w;
    Vector();
};

class AIWorld
{
public:
    char d[0x198];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(Vector *out, int a); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20();
    virtual int s21(); // +0xB0
};

struct ViewObj {
    char pad[0xc0];
    char fC0[0x110]; // +0xC0
    char f1D0[0x10]; // +0x1D0
};

struct ViewOwner {
    char pad[0x3a0];
    ViewObj *f3A0; // +0x3A0
};

extern "C" {
extern float lbl_8066BF40;
extern AIWorld *lbl_8066BF54;
int fn_80444DA0(void *e);
Vector *fn_80444688(void *e);
float fn_804310C0(Vector *a, Vector *b);
ViewOwner *fn_8043289C(void *g);
int fn_801B9324(void *p, Vector *pos, float r);
int fn_8015EC1C(float chance);
int fn_804622B4(void *list);
void *fn_804622FC(void *list, int i);
int fn_801464E4(void *e, Vector *pos);
void fn_8042DC84V(Vector *dst, Vector *src) __asm__("fn_8042DC84");
int fn_800861EC(void *actor);
void *fn_800B24AC(void *actor);
int fn_80048DD0(void *body, Vector *pos, int a, int b, int c, float r, int d);
}

extern "C" int fn_80134940(void *e, Vector *pos, short kind, void *list)
{
    if (!fn_80444DA0(e)) {
        return 0;
    }
    if (fn_804310C0(fn_80444688(e), pos) < lbl_8066BF3C) {
        return 0;
    }
    ViewOwner *owner = fn_8043289C(lbl_80552110);
    if (owner && owner->f3A0) {
        ViewObj *cover = owner->f3A0;
        if (!fn_801B9324(cover->f1D0, fn_80444688(e), 0.15f)) {
            if (!fn_8015EC1C(lbl_8066BF40)) {
                return 0;
            }
        }
    }
    if (list) {
        void *l = list;
        int i;
        for (i = 0; i < fn_804622B4(l); i++) {
            void *it = fn_804622FC(l, i);
            if (fn_801464E4(it, fn_80444688(e))) {
                return 0;
            }
        }
    }
    if (lbl_8066BF54) {
        Vector v;
        fn_8042DC84V(&v, fn_80444688(e));
        if (fn_800861EC(lbl_8066BF54)) {
            v.z += 2.5f;
        }
        int hit = fn_80048DD0(fn_800B24AC(lbl_8066BF54), &v, 0, 0, lbl_8066BF54->s21(), -0.11f, 0);
        if (hit) {
            return 0;
        }
    } else {
        return 0;
    }
    return 1;
}

extern "C" {
int fn_8013513C(AIObject *ai);
int fn_801352EC(AIObject *ai, Vector *pos, int *n);
int fn_80135400(AIObject *ai, float t, Vector *pos);
int fn_80461D48(void *ai, int bit);
void *fn_8013726C(AIObject *ai);
void *fn_80147ACC(void *rec, void *actor);
unsigned int fn_8042EFF8(void *clock);
int fn_80134D64(AIObject *ai);
}

extern "C" void fn_80134BE0(register AIObject *self, float t)
{
    if (!fn_8013513C(self)) {
        return;
    }
    Vector v;
    int n = 0;
    if (!fn_801352EC(self, &v, &n)) {
        return;
    }
    if (!fn_80135400(self, t, &v)) {
        self->f53C = 0;
        return;
    }
    if (fn_80461D48(self, 3)) {
        void *p = fn_80147ACC(fn_8013726C(self), AI_GetEntity(self));
        if (p) {
            if (!fn_801464E4(p, &v)) {
                return;
            }
        }
    }
    if (self->f53C) {
        if (fn_8042EFF8(lbl_80593BE8) < self->f53C) {
            return;
        }
    } else {
        self->f53C = fn_8042EFF8(lbl_80593BE8) + lbl_8066BF38;
        return;
    }
    fn_80134D64(self);
}

class Matrix
{
public:
    char d[0x40];
    Matrix() __asm__("fn_8042D7B0");
};

class TeleActor
{
public:
    char d[0x3ac];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(int v); // +0x30
};
struct TeleActorD : TeleActor { // matching_notes 44
    int x;
};

struct ActorFlags {
    char pad[0x304];
    unsigned int f304; // +0x304
};

typedef int (*SpotTest)(void *e, Vector *pos, short kind, void *list);

extern "C" {
AIWorld *fn_80442080W(AIObject *ai) __asm__("AI_GetEntity");
unsigned int fn_801370B0(AIObject *ai);
void *fn_8009C55C(Vector *pos, int n, unsigned int mask, float r, SpotTest test, void *b, int c);
int fn_800CDA20(Ent &actor);
Ent *fn_800CD9B0(Ent &actor);
Ent *fn_800B1590(Ent &actor);
void fn_800F880C(Ent &actor, Ent *other, int a, int b);
int fn_80393D0C(Ent &actor, const char *name, int a, int b);
void fn_8042DCC0(Matrix *m);
void fn_8043432C(Matrix *m, Vector *pos);
void *fn_800B1A98(Ent &actor);
int fn_80461714(void *e, int a);
void fn_800AFAB0(Ent &actor, void *scene, int rec, Matrix *m, int a);
TeleActorD *fn_8044203CT(AIObject *ai) __asm__("AI_GetActor");
void fn_8009AEC8(Ent &actor, int v);
int fn_80097CE8(Ent &actor, int a, int mode, float speed, int set, float blend, float f);
void fn_800BD2D0(void *actor, int clip);
void fn_800BD3A8(void *actor, int clip);
void *fn_8009AD80(Ent &actor);
void *fn_800B1668(Ent &actor);
void fn_801A479C(void *a, void *b, int c);
void fn_8014F8BC(void *p);
void fn_8014F7B0(void *p, int v);
}

extern "C" int fn_80134D64(register AIObject *self)
{
    Vector v;
    int n = 0;
    if (!fn_801352EC(self, &v, &n)) {
        return 0;
    }
    lbl_8066BF54 = fn_80442080W(self);
    v.z += 1.0f;
    void *spot = fn_8009C55C(&v, n, fn_801370B0(self), 20.0f, fn_80134940, fn_8013726C(self), -1);
    lbl_8066BF54 = 0;
    if (spot) {
        if (fn_800CDA20(*AI_GetActor(self))) {
            fn_800F880C(*AI_GetActor(self), fn_800B1590(*fn_800CD9B0(*AI_GetActor(self))), 0, 0);
            return 0;
        }
        self->f550 = fn_80393D0C(*AI_GetEntity(self), "peonTeleQuick", 0xff, 0xff);
        {
            Matrix m;
            fn_8042DCC0(&m);
            fn_8043432C(&m, fn_80444688(spot));
            fn_800AFAB0(*AI_GetEntity(self), fn_800B1A98(*AI_GetEntity(self)), fn_80461714(spot, 0), &m, 0);
        }
        fn_8044203CT(self)->s5(2);
        fn_8009AEC8(*AI_GetEntity(self), 0);
        int clip = fn_80097CE8(*AI_GetEntity(self), 0x147, 0, 30.0f, 0, 7.5f, -1.0f);
        fn_800BD2D0(AI_GetActor(self), clip);
        fn_800BD3A8(AI_GetActor(self), clip);
        if (fn_8009AD80(*AI_GetEntity(self))) {
            fn_801A479C(fn_8009AD80(*AI_GetEntity(self)), fn_800B1668(*AI_GetEntity(self)), 1);
        }
        fn_8014F8BC(AI_GetTargetList(self));
        fn_8014F7B0(AI_GetTargetList(self), 0);
        ((ActorFlags *)self->f530)->f304 |= 0x20000000;
        self->f53C = 0;
        if (fn_80461D48(self, 0x39) && fn_80461D48(self, 0x3b)) {
            fn_80461D04(self, 0x39);
            fn_80461D04(self, 0x3b);
        }
        return 1;
    }
    return 0;
}

extern "C" {
int fn_800865B4(void *actor);
int fn_8015F384(AIObject *ai);
int fn_800CE4D0(void *actor);
int fn_800CCC28(Ent &actor);
}

extern "C" int fn_8013513C(register AIObject *self)
{
    if (!lbl_8066BF34 && !fn_80461D48(self, 0x39)) {
        return 0;
    }
    PlayerEnt *actor = AI_GetEntity(self);
    if (!actor) {
        return 0;
    }
    if (fn_80085D3C(actor)) {
        return 0;
    }
    if (!fn_800865B4(actor)) {
        return 0;
    }
    if (fn_8015F384(self)) {
        return 0;
    }
    if (fn_80461D48(self, 0x20) || fn_80461D48(self, 0x32)) {
        return 0;
    }
    if (fn_800CE4D0(AI_GetActor(self))) {
        if (!fn_80085F7C(AI_GetEntity(self)) && !fn_800861EC(AI_GetEntity(self))) {
            return 0;
        }
    }
    if (fn_800CCC28(*AI_GetActor(self))) {
        return 0;
    }
    return 1;
}

extern "C" {
extern char lbl_8052F060[];
void *fn_80430050(void *p);
int fn_8004DD38(void *scene, Vector *pos);
Vector *fn_800B1724(Ent &actor);
int fn_800B1CC8(Ent &actor);
}

extern "C" int fn_801352EC(register AIObject *self, Vector *pos, int *n)
{
    if (fn_80461D48(self, 0x3a) && fn_80461D48(self, 0x39)) {
        fn_8042DC84V(pos, (Vector *)fn_80461E2C(self));
        *n = fn_8004DD38(fn_80430050(lbl_8052F060), pos);
        return 1;
    }
    Ent *target = fn_80461948(self->fD0);
    if (target) {
        fn_8042DC84V(pos, fn_800B1724(*target));
        *n = fn_800B1CC8(*target);
        return 1;
    }
    return 0;
}

struct AIWorldD : AIWorld { // matching_notes 44
    int x;
};

extern "C" {
AIWorldD *fn_80442080D(AIObject *ai) __asm__("AI_GetEntity");
float fn_804290F8(Vector *a, Vector *b);
void fn_80429038(Vector *out, Vector *a, Vector *b);
float fn_8042EC54(Vector *v);
int fn_8004A9CC(Vector *from, Vector *dir, float len, unsigned int mask, void *hit, void *body, int b, int c, int d);
void *AI_GetMover(AIObject *ai);
void *fn_800B24ACE(Ent &actor) __asm__("fn_800B24AC");
void *AI_GetPath(void *p);
float fn_8014C0B8(void *p, AIObject *ai, Vector *from, Vector *to);
}

extern "C" int fn_80135400(register AIObject *self, float t, Vector *pos)
{
    if (fn_80461D48(self, 0x39)) {
        return 1;
    }
    float d = fn_804290F8(pos, fn_800B1724(*AI_GetEntity(self)));
    if (d > t) {
        return 1;
    }
    Vector eye;
    fn_80442080D(self)->s5(&eye, 0);
    float dz = eye.z - fn_800B1724(*AI_GetEntity(self))->z;
    Vector to;
    fn_8042DC84V(&to, pos);
    to.z += dz;
    Vector dir;
    fn_80429038(&dir, &to, &eye);
    float len = fn_8042EC54(&dir);
    if (fn_8004A9CC(&eye, &dir, len, 8, 0, fn_800B24ACE(*AI_GetEntity(self)), 0, 0, 0)) {
        float r = fn_8014C0B8(AI_GetPath(AI_GetMover(self)), self, fn_800B1724(*AI_GetEntity(self)), pos);
        if (r >= t || r == 0.0f) {
            return 1;
        }
    }
    return 0;
}

struct TeleTask {
    char pad[0x30];
    Vector f30; // +0x30 target position
};

struct NavSub {
    char pad[0x30];
    Vector f30; // +0x30
};

struct NavNode {
    char pad[0x10];
    NavSub f10; // +0x10
};

extern "C" {
void *AI_GetBrain(AIObject *ai);
int fn_80151AF8(void *brain, int id);
TeleTask *fn_8015105CT(void *brain, int id) __asm__("fn_8015105C");
NavNode *fn_800B3A74(void *scene, int v, int a, int b);
void AI_SetMoverMoveDest(void *p, Vector *v);
}

extern "C" void fn_80135668(register AIObject *self, int on)
{
    if (!on) {
        self->f564 = 0;
        return;
    }
    if (self->f564) {
        return;
    }
    self->f564 = 1;
    if (fn_80085D3C(AI_GetEntity(self))) {
        if (fn_80151AF8(AI_GetBrain(self), 0xb)) {
            TeleTask &task = *fn_8015105CT(AI_GetBrain(self), 0xb);
            if (&task) {
                Vector v;
                fn_8042DC84V(&v, fn_800B1724(*AI_GetEntity(self)));
                NavNode *node = fn_800B3A74(fn_80430050(lbl_8052F060), 0, 0, 0);
                if (node) {
                    NavSub *sub = &node->f10;
                    fn_8042DC84V(&v, &sub->f30);
                } else {
                    void *spot = fn_8009C55C(fn_800B1724(*AI_GetEntity(self)), fn_800B1CC8(*AI_GetEntity(self)),
                                             fn_801370B0(self), 20.0f, 0, 0, -1);
                    if (spot) {
                        fn_8042DC84V(&v, fn_80444688(spot));
                    }
                }
                fn_8042DC84V(&task.f30, &v);
                AI_SetMoverMoveDest(AI_GetMover(self), &v);
            }
        }
    }
}

class Actor10
{
public:
    char pad[0x10];
    int value; // +0x10
    void setValue(register int v);
};

extern "C" {
extern int lbl_8066BF44; // countdown handed to lbl_80593BE8's setValue
extern Actor10 lbl_80593BE8_A __asm__("lbl_80593BE8");
int fn_8008653C(void *actor);
int AI_TestStateBit(AIObject *ai, int v);
void fn_80461D98(AIObject *ai);
void fn_80135E48(AIObject *ai);
int fn_80085EEC(void *actor);
int fn_80085F1C(void *actor);
void fn_80461E58(AIObject *ai, int v);
void fn_8014E648(void *p);
void fn_801385A0(AIObject *ai);
void fn_8014ADB0(void *p);
void fn_80151A9C(void *brain);
void fn_80149570(AIObject *ai);
int fn_804324EC(void *clock);
int fn_8015F410(AIObject *ai, float chance);
float fn_80461F3C(AIObject *ai);
int fn_800B18EC(Ent &actor, int id);
void fn_80136678(AIObject *ai);
}

extern "C" void fn_8013589C(register AIObject *self)
{
    int i;
    int t;

    if (lbl_8066BF28) {
        if (!lbl_8066BF44) {
            lbl_8066BF44 = 0x10;
        }
    } else {
        lbl_8066BF44 = 0;
    }
    if (lbl_8066BF44) {
        lbl_80593BE8_A.setValue(lbl_8066BF44);
    }
    if (((ActorFlags *)self->f530)->f304 & 0x20000000) {
        self->f554 = fn_80393D0C(*AI_GetEntity(self), "peonTeleQuick", 0xff, 0xff);
        ((ActorFlags *)self->f530)->f304 &= ~0x20000000;
    }
    if (lbl_8066BF20 || (lbl_8066BF24 && !fn_8008653C(AI_GetEntity(self)))) {
        for (i = 0; i < 26; i++) {
            self->f44[i] = 0;
        }
        fn_8014B900(self->f210);
        return;
    }
    if (AI_TestStateBit(self, 1) && AI_TestStateBit(self, 2)) {
        i = 0;
        i++;
    }
    fn_80461D98(self);
    for (i = 0; i < 26; i++) {
        self->f44[i] = 0;
    }
    fn_80135E48(self);
    if (self->f4) {
        return;
    }
    if (fn_80085EEC(self->f530) || fn_80085F1C(self->f530)) {
        return;
    }
    fn_80461E58(self, 0);
    fn_8014E648(self->fD0);
    fn_801385A0(self);
    fn_8014ADB0(self->f210);
    fn_80151A9C(self->f204);
    fn_80134BE0(self, lbl_8066BF30);
    fn_80149570(self);
    if (self->f514) {
        t = self->f518 - fn_804324EC(lbl_80593BE8);
        if (t < 0 || fn_8015F410(self, 0.5f)) {
            t = 0;
            self->f51C = (int)((fn_80461F3C(self) + 1.0f) * 1000.0f);
            self->f514 = 0;
        }
        self->f518 = t;
    } else {
        t = self->f51C - fn_804324EC(lbl_80593BE8);
        if (t < 0 || !fn_8015F410(self, 0.2f)) {
            t = 0;
            self->f518 = (int)((100.0f - fn_80461F3C(self) + 1.0f) * 1000.0f);
            self->f514 = 1;
        }
        self->f51C = t;
    }
    if (self->f520) {
        t = self->f520 - fn_804324EC(lbl_80593BE8);
        if (t < 0) {
            t = 0;
        }
        self->f520 = t;
    }
    if (self->f524) {
        t = self->f524 - fn_804324EC(lbl_80593BE8);
        if (t <= 0) {
            t = 0;
            switch (self->f528) {
            case 0:
                self->f528 = 1;
                t = fn_800B18EC(*AI_GetEntity(self), 0xb9);
                break;
            case 1:
                self->f528 = 0;
                t = fn_800B18EC(*AI_GetEntity(self), 0xb8);
                break;
            }
        }
        self->f524 = t;
    }
    fn_80136678(self);
}

struct AIAction; // 0x70-byte action record, docs/ai.md section 3 Behaviors

extern "C" {
void *fn_80462074(void *e);
void fn_804620A0(void *e, int v);
typedef int (*EventPred)(void *e, void *key);
int fn_801B686C(void *list, void *key, EventPred pred);
void fn_8013880C(void *e);
void fn_801B6040(void *list, void *e);
int fn_801B6A44(void *list);
void *fn_801B5D3C(void *list, int i);
int fn_80462158(AIAction *e);
unsigned int fn_804621B0(AIAction *e);
unsigned int fn_80462184(AIAction *e);
void fn_80462130(AIAction *e, int v);
void fn_80462260(AIAction *e, unsigned int now);
unsigned int fn_80462234(AIAction *e);
unsigned int fn_80462208(AIAction *e);
void fn_801B6130(void *list, int i);
void fn_8013880CE(AIAction *e) __asm__("fn_8013880C");
}

extern "C" void fn_80135D64(register AIObject *self, void *list)
{
    if (!list) {
        return;
    }
    void *e = list;
    while (e) {
        void *cur = e;
        e = fn_80462074(e);
        fn_804620A0(cur, 0);
        if (fn_804621DC(cur) != -1 && fn_801B686C(self->fAC, cur, 0) != -1) {
            fn_8013880C(cur);
        } else {
            fn_801B6040(self->fAC, cur);
        }
    }
}

extern "C" void fn_80135E48(register AIObject *self)
{
    unsigned int now = fn_8042EFF8(lbl_80593BE8);
    int i;
    for (i = fn_801B6A44(self->fAC) - 1; i >= 0; i--) {
        AIAction *e = (AIAction *)fn_801B5D3C(self->fAC, i);
        if (e) {
            if (fn_80462158(e) && now - fn_804621B0(e) >= fn_80462184(e)) {
                fn_80462130(e, 0);
                fn_80462260(e, now);
            }
            if (!fn_80462158(e) && now - fn_80462234(e) >= fn_80462208(e)) {
                fn_801B6130(self->fAC, i);
                fn_8013880CE(e);
            }
        }
    }
}

extern "C" {
void fn_801B60F4(void *list);
unsigned int fn_804620C8(void *e);
int fn_804620F4(void *e, unsigned int i);
}

extern "C" void fn_80135F94(register AIObject *self)
{
    int n = fn_801B6A44(self->fAC);
    int i;
    for (i = 0; i < n; i++) {
        AIAction *e = (AIAction *)fn_801B5D3C(self->fAC, i);
        if (e) {
            fn_8013880CE(e);
        }
    }
    fn_801B60F4(self->fAC);
}

extern "C" int fn_80136040(void *item, void *key)
{
    int id = (int)key;
    void *e = item;
    if (e && fn_804621DC(e) == id) {
        return 1;
    }
    return 0;
}

extern "C" int fn_801360C0(void *item, void *key)
{
    int id = (int)key;
    void *e = item;
    if (e && fn_804621DC(e) != id) {
        return 1;
    }
    return 0;
}

extern "C" int fn_80136140(void *item, void *key)
{
    int id = (int)key;
    void *e = item;
    if (e && fn_804620C8(e)) {
        unsigned int i;
        for (i = 0; i < fn_804620C8(e); i++) {
            int v = fn_804620F4(e, i);
            if (v == id) {
                return 1;
            }
        }
    }
    return 0;
}

extern "C" int fn_80136214(register AIObject *self, int id)
{
    int found = 0;
    int idx = 0;
    while ((idx = fn_801B686C(self->fAC, (void *)id, fn_80136040)) != -1) {
        found = 1;
        AIAction *e = (AIAction *)fn_801B5D3C(self->fAC, idx);
        if (e) {
            fn_8013880CE(e);
        }
        fn_801B6130(self->fAC, idx);
    }
    return found;
}

extern "C" int fn_801362DC(register AIObject *self, int id)
{
    int found = 0;
    int idx = 0;
    while ((idx = fn_801B686C(self->fAC, (void *)id, fn_801360C0)) != -1) {
        found = 1;
        AIAction *e = (AIAction *)fn_801B5D3C(self->fAC, idx);
        if (e) {
            fn_8013880CE(e);
        }
        fn_801B6130(self->fAC, idx);
    }
    return found;
}

extern "C" int fn_801363A4(register AIObject *self, int id)
{
    int found = 0;
    int idx = 0;
    while ((idx = fn_801B686C(self->fAC, (void *)id, fn_80136140)) != -1) {
        found = 1;
        AIAction *e = (AIAction *)fn_801B5D3C(self->fAC, idx);
        if (e) {
            fn_8013880CE(e);
        }
        fn_801B6130(self->fAC, idx);
    }
    return found;
}

extern "C" {
void fn_8044243C(void *bits, int bit);
int fn_8009B04C(Ent &actor);
}

extern "C" void fn_8013646C(register AIObject *self, unsigned int event, Ent *src, Ent *other)
{
    fn_8044243C(self->f14, event);
    if (src && fn_800B13D8(*src)) {
        self->f1C = fn_800B13D8(*src);
    } else {
        self->f1C = 0;
    }
    switch (event) {
    case 1:
        self->f2C = fn_8042EFF8(lbl_80593BE8);
        break;
    case 6:
        self->f30 = fn_8042EFF8(lbl_80593BE8);
        if (other && fn_800B13D8(*other)) {
            self->f24 = fn_800B13D8(*other);
        }
        break;
    case 2:
        self->f38 = fn_8042EFF8(lbl_80593BE8);
        if (other && fn_800B13D8(*other)) {
            self->f20 = fn_800B13D8(*other);
        }
        break;
    case 3:
        break;
    case 4:
        self->f34 = fn_8042EFF8(lbl_80593BE8);
        self->f28 = fn_8009B04C(*src);
        break;
    case 5:
        break;
    case 7:
        break;
    case 8:
        break;
    case 9:
        self->f3C = fn_8042EFF8(lbl_80593BE8);
        break;
    case 10:
        self->f40 = fn_8042EFF8(lbl_80593BE8);
        break;
    }
}

extern "C" {
void fn_804424A0(void *bits, int bit);
int fn_80442508(void *bits, int bit);
}

extern "C" void fn_80136678(register AIObject *self)
{
    if (self->f2C && self->f2C + 3000 < fn_8042EFF8(lbl_80593BE8)) {
        self->f2C = 0;
        fn_804424A0(self->f14, 1);
    }
    if (self->f30 && self->f30 + 3000 < fn_8042EFF8(lbl_80593BE8)) {
        self->f30 = 0;
        fn_804424A0(self->f14, 6);
        self->f24 = 0;
    }
    if (self->f34 && self->f34 + 1000 < fn_8042EFF8(lbl_80593BE8)) {
        self->f34 = 0;
        fn_804424A0(self->f14, 4);
        self->f28 = 0;
    }
    if (self->f38 && self->f38 + 3000 < fn_8042EFF8(lbl_80593BE8)) {
        self->f38 = 0;
        fn_804424A0(self->f14, 2);
        self->f20 = 0;
    }
    if (self->f3C && self->f3C + 1000 < fn_8042EFF8(lbl_80593BE8)) {
        self->f3C = 0;
        fn_804424A0(self->f14, 9);
    }
    if (self->f40 && self->f40 + 1000 < fn_8042EFF8(lbl_80593BE8)) {
        self->f40 = 0;
        fn_804424A0(self->f14, 10);
    }
    if (fn_80442508(self->f14, 7)) {
        fn_804424A0(self->f14, 7);
    }
    if (fn_80442508(self->f14, 8)) {
        fn_804424A0(self->f14, 8);
    }
}

extern "C" int fn_801368B8(register AIObject *self)
{
    if (!fn_80085D3C(AI_GetEntity(self))) {
        if (fn_800861EC(AI_GetEntity(self))) {
            return 1;
        }
        return 0;
    }
    if (self->f514) {
        if (fn_8015F384(self) && fn_80085F7C(AI_GetEntity(self))) {
            return 1;
        }
        return 0;
    }
    return fn_80085F7C(AI_GetEntity(self));
}

extern "C" {
int fn_8008618C(void *actor);
int fn_8015E97C(float chance);
}

extern "C" int fn_801369B0(register AIObject *self)
{
    if (!fn_80085D3C(AI_GetEntity(self))) {
        return 0;
    }
    if (fn_80461F3C(self) == 0.0f) {
        return 0;
    }
    if (self->f514) {
        if (fn_8015F384(self)) {
            return 1;
        }
        return 0;
    }
    if (fn_8008618C(AI_GetEntity(self)) && !fn_8015F410(self, 0.1f) && !fn_8015E97C(0.05f)) {
        return 0;
    }
    return 1;
}

struct AIBrainBase {
    char d[0x274];
};

// Each profile's brain; the class names are unknown, so the constructors keep their fn_ symbols.
#define AI_BRAIN(name, ctor) \
    struct name : AIBrainBase {  \
        name(AIObject *ai) __asm__(ctor); \
    };

AI_BRAIN(Brain_801507C0, "fn_801507C0")
AI_BRAIN(Brain_801604A0, "fn_801604A0")
AI_BRAIN(Brain_8016056C, "fn_8016056C")
AI_BRAIN(Brain_80161298, "fn_80161298")
AI_BRAIN(Brain_80161364, "fn_80161364")
AI_BRAIN(Brain_80161430, "fn_80161430")
AI_BRAIN(Brain_80162B9C, "fn_80162B9C")
AI_BRAIN(Brain_801639B0, "fn_801639B0")
AI_BRAIN(Brain_80163A7C, "fn_80163A7C")
AI_BRAIN(Brain_80163B48, "fn_80163B48")
AI_BRAIN(Brain_80163C14, "fn_80163C14")
AI_BRAIN(Brain_80163CE0, "fn_80163CE0")
AI_BRAIN(Brain_80164340, "fn_80164340")
AI_BRAIN(Brain_80163E78, "fn_80163E78")
AI_BRAIN(Brain_80163F44, "fn_80163F44")
AI_BRAIN(Brain_80164010, "fn_80164010")
AI_BRAIN(Brain_801640DC, "fn_801640DC")
AI_BRAIN(Brain_801641A8, "fn_801641A8")
AI_BRAIN(Brain_8016440C, "fn_8016440C")
AI_BRAIN(Brain_80163DAC, "fn_80163DAC")
AI_BRAIN(Brain_80160638, "fn_80160638")
AI_BRAIN(Brain_80160704, "fn_80160704")
AI_BRAIN(Brain_80161174, "fn_80161174")
AI_BRAIN(Brain_80162764, "fn_80162764")
AI_BRAIN(Brain_80162938, "fn_80162938")
AI_BRAIN(Brain_80162A04, "fn_80162A04")
AI_BRAIN(Brain_80162C68, "fn_80162C68")
AI_BRAIN(Brain_80162D34, "fn_80162D34")
AI_BRAIN(Brain_8016388C, "fn_8016388C")
AI_BRAIN(Brain_80151CB8, "fn_80151CB8")
AI_BRAIN(Brain_80162AD0, "fn_80162AD0")

extern "C" AIBrainBase *fn_80136AC8(register AIObject *self, int profile)
{
    AIBrainBase *brain = 0;
    switch (profile) {
    case 0:
        brain = new Brain_801507C0(self);
        break;
    case 1:
        brain = new Brain_801604A0(self);
        break;
    case 2:
        brain = new Brain_8016056C(self);
        break;
    case 3:
        brain = new Brain_80161298(self);
        break;
    case 4:
        brain = new Brain_80161364(self);
        break;
    case 5:
        brain = new Brain_80161430(self);
        break;
    case 6:
        brain = new Brain_80162B9C(self);
        break;
    case 7:
        brain = new Brain_801639B0(self);
        break;
    case 8:
        brain = new Brain_80163A7C(self);
        break;
    case 9:
        brain = new Brain_80163B48(self);
        break;
    case 10:
        brain = new Brain_80163C14(self);
        break;
    case 11:
        brain = new Brain_80163CE0(self);
        break;
    case 12:
        brain = new Brain_80164340(self);
        break;
    case 13:
        brain = new Brain_80163E78(self);
        break;
    case 14:
        brain = new Brain_80163F44(self);
        break;
    case 15:
        brain = new Brain_80164010(self);
        break;
    case 16:
        brain = new Brain_801640DC(self);
        break;
    case 17:
        brain = new Brain_801641A8(self);
        break;
    case 18:
        brain = new Brain_8016440C(self);
        break;
    case 19:
        brain = new Brain_80163DAC(self);
        break;
    case 23:
        brain = new Brain_80160638(self);
        break;
    case 24:
        brain = new Brain_80160704(self);
        break;
    case 25:
        brain = new Brain_80161174(self);
        break;
    case 26:
        brain = new Brain_80162764(self);
        break;
    case 27:
        brain = new Brain_80162938(self);
        break;
    case 28:
        brain = new Brain_80162A04(self);
        break;
    case 20:
        brain = new Brain_80162C68(self);
        break;
    case 21:
        brain = new Brain_80162D34(self);
        break;
    case 22:
        brain = new Brain_8016388C(self);
        break;
    case 29:
        brain = new Brain_80151CB8(self);
        break;
    case 30:
        brain = new Brain_80162AD0(self);
        break;
    default:
        brain = new Brain_801507C0(self);
    }
    return brain;
}

extern "C" {
int fn_80085E2C(void *actor);
int fn_80085DFC(void *actor);
int fn_80085E5C(void *actor);
int fn_8008612C(void *actor);
int fn_8008603C(void *actor);
}

extern "C" unsigned int fn_801370B0(register AIObject *self)
{
    unsigned int mask = 0;
    if (fn_80085E2C(AI_GetEntity(self))) {
        mask |= 0x20000;
    } else if (!fn_80085DFC(AI_GetEntity(self))) {
        mask |= 0x10000;
    }
    if (!fn_80085E5C(AI_GetEntity(self))) {
        mask |= 0x80000;
    }
    if (fn_8008612C(AI_GetEntity(self)) && fn_801369B0(self)) {
        mask |= 0x400000;
    }
    if (fn_8008603C(AI_GetEntity(self)) && fn_801369B0(self)) {
        mask |= 0x800000;
    }
    if (fn_8008606C(AI_GetEntity(self))) {
        mask |= 0x1000000;
    }
    if (fn_801368B8(self) || fn_800861EC(AI_GetEntity(self))) {
        mask |= 0x200000;
    }
    return mask;
}

extern "C" void *fn_8013726C(register AIObject *self)
{
    return &lbl_80569890;
}

struct AIMoveOut {
    char pad[0x10];
    float f10;  // +0x10
    float f14;  // +0x14
    float f18;  // +0x18 length
    int pad1C;
    Vector f20; // +0x20
};

extern "C" {
Vector *AI_GetMoverHeading(void *p);
Vector *fn_8042FB28(Vector *v);
}

extern "C" void fn_80137298(register AIObject *self, int kind, AIMoveOut *out)
{
    if (kind == 0) {
        Vector v;
        fn_8042DC84V(&v, AI_GetMoverHeading(AI_GetMover(self)));
        fn_8042FB28(&v)->z = 0.0f;
        float len = fn_8042EC54(&v);
        fn_8042DC84V(&out->f20, &v);
        out->f18 = len;
        out->f10 = v.x;
        out->f14 = v.y;
    }
    if (kind == 7) {
        Vector v;
        fn_8042DC84V(&v, AI_GetMoverHeading(AI_GetMover(self)));
        v.y = 0.0f;
        float len = fn_8042EC54(&v);
        fn_8042DC84V(&out->f20, &v);
        out->f18 = len;
        out->f10 = v.x;
        out->f14 = v.z;
    }
}

extern "C" void fn_8013741C(register AIObject *self, int *out)
{
    int i;
    for (i = 0; i < 26; i++) {
        out[i] = self->f44[i];
    }
}

struct AIBehavior {
    char d[0x1c];
};

struct TargetEnt : Ent {
    char pad[0xf8];
    char name[0x20]; // +0xFC
};

class ScreenPos
{
public:
    float x, y, z, w; // z < 0 is behind the camera
    ScreenPos() __asm__("fn_80430728");
};

extern "C" {
extern AIBehavior lbl_80571814[]; // the behavior registry, docs/ai.md section 4.3
void *fn_80151BCC(void *brain);
char *fn_80461FEC(void *task);
unsigned int fn_80151C24(void *brain);
void *fn_80151C50(void *brain, int i);
int AI_HasMoverWaypoint(void *mover);
int AI_HasMoverDestThing(void *mover);
void *AI_GetMoverDestThing(void *mover);
void *fn_800ACFA8(void *handle);
char *fn_800AFF88(void *thing);
int AI_HasMoverMoveDest(void *mover);
int AI_HasMoverPath(void *mover);
int fn_80461E00(AIObject *ai);
float fn_80138868(AIObject *ai, float x, float y);
char *fn_80462288(AIBehavior *b);
void fn_800B16D8(Ent &actor, Vector *pos);
float fn_800B2620(Ent &actor);
ViewOwner *fn_80094630(void *g);
void fn_80430750(ScreenPos *out, Vector *pos, void *view);
void fn_804615A4(ViewObj *view, ScreenPos *pos, int a);
TargetEnt *fn_80134870T(AIObject *ai) __asm__("fn_80134870");
}

extern "C" void fn_80137494(register AIObject *self, float x, float y)
{
    float dx = 0.0f;
    float dy = 0.0f;
    float step = 13.0f;
    char buf[0x50];
    fn_80101188(lbl_8066D6DC, 11.0f);
    step = 11.0f;
    fn_80100C50(lbl_8066D6DC, 0);
    if (self == fn_80133A30()) {
        fn_8042AC7C(lbl_8066D6DC, 0xFFB0B000);
    } else {
        fn_8042AC7C(lbl_8066D6DC, 0xFFB0B0B0);
    }
    const char *none = "NONE";
    const char *behavior = none;
    if (fn_80151BCC(AI_GetBrain(self))) {
        behavior = fn_80461FEC(fn_80151BCC(AI_GetBrain(self)));
    }
    unsigned int ntasks = fn_80151C24(AI_GetBrain(self));
    const char *tname = none;
    int tid = 0;
    if (fn_80134870(self)) {
        tname = fn_80134870T(self)->name;
        tid = fn_800B13D8(*fn_80134870(self));
    }
    sprintf(buf, "Target:'%s' (%d) ", tname, tid);
    fn_800B92DC(&lbl_8066D6DC, buf, x + dx, y + dy);
    dy += step;
    char thing[0x50];
    const char *mover = none;
    if (AI_HasMoverWaypoint(AI_GetMover(self))) {
        mover = "WAYPOINT";
    } else if (AI_HasMoverDestThing(AI_GetMover(self))) {
        mover = "DEST_THING";
        void *handle = AI_GetMoverDestThing(AI_GetMover(self));
        void *dest = fn_800ACFA8(handle);
        if (dest) {
            sprintf(thing, "%s (%s)", mover, fn_800AFF88(dest));
            mover = thing;
        }
    } else if (AI_HasMoverMoveDest(AI_GetMover(self))) {
        mover = "MOVE_DEST";
    } else {
        mover = "TO_TARGET";
    }
    const char *pathing = none;
    if (AI_HasMoverPath(AI_GetMover(self))) {
        pathing = "YES";
    }
    sprintf(buf, "Mover:'%s'", mover);
    fn_800B92DC(&lbl_8066D6DC, buf, x + dx, y + dy);
    dy += step;
    sprintf(buf, "Pathing: %s", pathing);
    fn_800B92DC(&lbl_8066D6DC, buf, x + dx, y + dy);
    dy += step;
    sprintf(buf, "Conserve: %s", fn_80461E00(self) ? "ON" : "OFF");
    fn_800B92DC(&lbl_8066D6DC, buf, x + dx, y + dy);
    dy += step;
    x = 40.0f;
    y = 120.0f;
    dy += fn_80138868(self, x, y);
    x = 360.0f;
    y = 250.0f;
    dy = 0.0f;
    fn_80101188(lbl_8066D6DC, 12.0f);
    step = 11.0f;
    sprintf(buf, "Task Stack (%d)", ntasks);
    fn_800B92DC(&lbl_8066D6DC, buf, x + dx, y + dy);
    dy += step;
    sprintf(buf, "'%s' <TOP", behavior);
    fn_800B92DC(&lbl_8066D6DC, buf, x + dx, y + dy);
    dy += step;
    if (ntasks > 1) {
        int i;
        for (i = ntasks - 2; i >= 0; i--) {
            void *task = fn_80151C50(AI_GetBrain(self), i);
            sprintf(buf, "'%s'", fn_80461FEC(task));
            fn_800B92DC(&lbl_8066D6DC, buf, x + dx, y + dy);
            dy += step;
        }
    }
    x = 360.0f;
    y = 340.0f;
    {
        int j;
        for (j = 0; j < fn_801B6A44(self->fAC); j++) {
            AIAction *e = (AIAction *)fn_801B5D3C(self->fAC, j);
            AIBehavior *def = &lbl_80571814[fn_804621DC(e)];
            const char *name = fn_80462288(def);
            if (!name) {
                name = "BEHAVIOR_NONE";
            }
            fn_800B92DC(&lbl_8066D6DC, name, x + dx, y + dy);
            dy -= step;
        }
    }
    if (fn_80133A30() == self) {
        Vector pos;
        ScreenPos scr;
        fn_800B16D8(*AI_GetEntity(self), &pos);
        fn_8042FB28(&pos)->z += fn_800B2620(*AI_GetEntity(self));
        fn_80430750(&scr, &pos, fn_80094630(lbl_80552110)->f3A0->fC0);
        fn_804615A4(fn_80094630(lbl_80552110)->f3A0, &scr, 1);
        if (scr.z < 0.0f) {
            return;
        }
        fn_80101188(lbl_8066D6DC, 20.0f);
        fn_800B92DC(&lbl_8066D6DC, "(!)", scr.x, scr.y);
        fn_80101188(lbl_8066D6DC, 14.0f);
    }
}

extern "C" {
extern char *lbl_804CF8E8[]; // AI profile names, docs/characters.md section 3
int stricmp(const char *a, const char *b);
}

// AI profile name to index over lbl_804CF8E8; an unlisted name gives 0, AI_DEFAULT.
extern "C" int fn_80137CEC(char *name)
{
    int i;

    for (i = 0; lbl_804CF8E8[i] != 0; i++) {
        if (stricmp(lbl_804CF8E8[i], name) == 0) {
            return i;
        }
    }
    return 0;
}
