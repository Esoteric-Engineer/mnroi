// AI manager: init, update, debug draw, shutdown, the per-AI loops and the encounter list. docs/ai.md row 1.
// .rodata: pool from 0x8049A85C (floats and the two strings), extern_pool.

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
extern void *lbl_8056A72C[];
extern char lbl_80569890[];
extern char lbl_8054ED80[];
extern char lbl_80593BE8[];
extern char lbl_80552110[];
struct AIRec { char b[0xdc]; };
extern AIRec lbl_8056996C[];

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
void fn_8013646C(int a, int b, int c, int d);
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
void fn_80134028(void *ai);
void fn_80134280(void *ai);
void fn_801346C0(void *ai);
int fn_80461A3C(void *rec);
struct Tune16 { int a; int b; int c; float f; };
extern Tune16 lbl_804CF968[];
void fn_80132AAC(void);
void fn_8013589C(void *ai);
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
PlayerEnt *fn_80442080(void *a);
int fn_800B13D8(Ent &actor);
int fn_800B92DC(void **text, const char *s, float x, float y);
void *fn_80133A30(void);
int fn_80461EB8(void *e);
void fn_80137494(void *ai, float x, float y);
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
    fn_80145D8C(lbl_80569890);
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
            fn_8013589C(ai);
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
            fn_8013589C(ai);
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
        sprintf(buf, "%s-%#.4d", (char *)fn_80442080(ai) + 0xfc, fn_800B13D8(*fn_80442080(ai)));
        fn_800B92DC(&lbl_8066D6DC, buf, x, y);
        y = y + 13.0f;
    }
    p = fn_80133A30();
    if (p) {
        if (fn_80461EB8(p)) {
            fn_80137494(p, x, y);
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
    fn_80145DF8(lbl_80569890);
    lbl_8066F1A8 = 0;
    fn_801498B0();
}

extern "C" void fn_80132B88(void)
{
    int i;

    lbl_8066F1A8 = 0;
    for (i = 0; i < lbl_8066BF1C; i++) {
        fn_80134028(lbl_8056A72C[i]);
    }
}

extern "C" void fn_80132C04(void)
{
    fn_8013866C();
    fn_80145D8C(lbl_80569890);
    fn_80145FE4(lbl_80569890);
    lbl_8066BF48 = 10;
}

extern "C" void fn_80132C54(void)
{
    int i;

    for (i = 0; i < lbl_8066F1A8; i++) {
        fn_80147DE4(&lbl_8056996C[i]);
    }
    lbl_8066F1A8 = 0;
    fn_80145DF8(lbl_80569890);
}

extern "C" void fn_80132CDC(void)
{
    int i;

    for (i = 0; i < lbl_8066BF1C; i++) {
        fn_80134280(lbl_8056A72C[i]);
    }
}

extern "C" void fn_80132D50(void)
{
    int i;

    for (i = 0; i < lbl_8066BF1C; i++) {
        fn_801346C0(lbl_8056A72C[i]);
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
                lbl_8056996C[i] = ((AIRec *)lbl_80569890)[lbl_8066F1A8];
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
    fn_8013646C(b, a, d, c);
}

extern "C" void fn_801336F0(void)
{
    int i;

    for (i = 0; i < lbl_8066BF1C; i++) {
        void *ai = lbl_8056A72C[i];
        PlayerEnt *e = fn_80442080(ai);
        if (e) {
            if (fn_80086B6C(e)) {
                fn_8009E09C(e);
            }
        }
    }
}

extern "C" int fn_8013379C(int a, int b)
{
    return fn_801475D8(lbl_80569890, a, b);
}

extern "C" void fn_801337F0(int a, int b)
{
    fn_801477B0(lbl_80569890, a, b);
}

extern "C" void fn_80133838(int a)
{
    fn_80147884(lbl_80569890, a);
}

extern "C" void fn_80133878(int a, int b)
{
    fn_80147968(lbl_80569890, a, b);
}

extern "C" void fn_801338C0(int a, int b)
{
    fn_80147A20(lbl_80569890, a, b);
}

extern "C" void fn_80133908(int a)
{
    fn_80147C40(lbl_80569890, a);
}

extern "C" void fn_80133948(int a)
{
    fn_80147B88(lbl_80569890, a);
}

extern "C" void fn_80133988(int a)
{
    fn_80147CF8(lbl_80569890, a);
}

extern "C" void fn_801339C8(int a)
{
    fn_80147D68(lbl_80569890, a);
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
