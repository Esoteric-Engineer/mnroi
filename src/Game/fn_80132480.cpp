// AI manager: init, per-frame update and debug draw. docs/ai.md row 1.
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
extern int lbl_8066BF28;
extern int lbl_8066BF2C;
extern int lbl_8066BF48; // update countdown
extern int lbl_8066BF4C; // initialised
extern int lbl_8066BF50;
extern int lbl_8066C7DC;
extern void *lbl_8066D6DC; // the overlay text object (docs/versus.md section 6)
extern int lbl_8066F1A8;
extern void *lbl_8056A72C[];
extern char lbl_80569890[];
extern char lbl_8054ED80[];
extern char lbl_80593BE8[];
extern char lbl_80552110[];
struct AIRec { char b[0xdc]; };
extern AIRec lbl_8056996C[];

void fn_80132AAC(void);
void fn_80137F2C(void);
void fn_80145D8C(void *p);
void fn_8013589C(void *ai);
int fn_804439A4(void *p);
int fn_80094BD0(void *p);
int fn_80094C64(void *p);
void *fn_8043492C(void *p);
void *fn_800B14A0(void *p);
int fn_80132E30(void *p);
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
