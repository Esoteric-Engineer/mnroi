// AI manager init: resets the registry and the AI state, then applies the settings from the resource list. docs/ai.md row 1.

extern "C" {
extern int lbl_8066BF1C; // registered AI count
extern int lbl_8066BF20; // AI enabled
extern int lbl_8066BF28;
extern int lbl_8066BF2C;
extern int lbl_8066BF48; // update countdown
extern int lbl_8066BF4C; // initialised
extern int lbl_8066BF50;
extern int lbl_8066F1A8;
extern void *lbl_8056A72C[];
extern char lbl_80569890[];
extern char lbl_8054ED80[];

void fn_80132AAC(void);
void fn_80137F2C(void);
void fn_80145D8C(void *p);
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
