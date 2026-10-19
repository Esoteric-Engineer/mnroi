// Per-frame audio update (a guess from its callees): a position for fn_804304FC, the 48 cue records and the volume pair at lbl_8066BD6C/70.
// The role-index branch is in docs/versus.md section 4.3. Float pool through extern_pool at 0x804976F8.

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
};

struct Sub : Ent {
    int pad2;
};

typedef struct Record {
    char pad0[0x48];
    int active; // +0x48
    char pad1[0x14];
} Record __attribute__((aligned(8)));

extern "C" {

extern int fn_80432844(void *g);             // G+0x770
extern int fn_80432870(void *g);             // G+0x774
extern unsigned int fn_80434900(void *g);    // G+0x590, the active slot count
extern Sub *fn_80443D44(void *g, int player);
extern Sub *fn_80432924(void *g);
extern int fn_804427A4(void *g);
extern char *fn_80094630(void *g);
extern char *fn_8043289C(void *g);
extern int fn_80432A60(void *level);
extern unsigned int fn_8042EFF8(void *p);
extern void fn_8042DC84(void *dst, void *src);
extern void fn_800B16D8(Ent &actor, Vector *out);
extern void fn_80428FA8(Vector *v, float x, float y, float z);
extern void fn_80428FE0(Vector *out, Vector *a, Vector *b);
extern void fn_8042FDBC(Vector *out, Vector *v, float f);
extern void fn_804304FC(void *a, void *b, Vector *pos, float f);
extern unsigned int fn_8010C7EC(void *obj, int a, int b);
extern void fn_80114E2C(int index);
extern void fn_80112884(void);
extern void fn_8010E6E8(void);
extern void fn_8010E530(void);
extern void fn_80457478(void *x, unsigned int volume);
extern void *fn_80052974(void);
extern int fn_8043AA90(void *x);

extern char lbl_80552110[]; // the game-state object G
extern char lbl_8052F060[]; // the level object
extern char lbl_80593BE8[];
extern char lbl_80567730[];
extern char lbl_80567740[];
extern char lbl_80567750[];
extern Record lbl_80567760[];
extern char lbl_8066D808[8];
extern int lbl_8066B63C;
extern int lbl_8066BD18;
extern int lbl_8066BD90;
extern unsigned int lbl_8066BD78;
extern unsigned int lbl_8066BD98;
extern void *lbl_8066BD6C;
extern void *lbl_8066BD70;
extern int lbl_8066BD50;
extern int lbl_8066F074;

void fn_8011389C(void)
{
    if (lbl_8066B63C == 0)
        return;
    if (lbl_8066BD18 == 0) {
        lbl_8066BD90 = -1;
    } else if (lbl_8066BD90 == -1) {
        lbl_8066BD90 = fn_8042EFF8(lbl_80593BE8);
    }
    if (fn_80432A60(lbl_8052F060) != 2) {
        char *focus;
        if (fn_804427A4(lbl_80552110))
            focus = fn_80094630(lbl_80552110);
        else
            focus = fn_8043289C(lbl_80552110);
        if (focus) {
            fn_8042DC84(lbl_80567730, focus + 0x390);
            fn_8042DC84(lbl_80567740, focus + 0x370);
            Vector pos;
            float level = 0.5f;
            if (fn_80432844(lbl_80552110) || fn_80432870(lbl_80552110)) {
                Vector sum;
                fn_80428FA8(&sum, 0.0f, 0.0f, 0.0f);
                for (unsigned int i = 0; i < fn_80434900(lbl_80552110); i++) {
                    Vector p;
                    fn_800B16D8(*fn_80443D44(lbl_80552110, i), &p);
                    fn_80428FE0(&sum, &sum, &p);
                }
                fn_8042FDBC(&pos, &sum, 1.0f / fn_80434900(lbl_80552110));
                level = fn_8010C7EC(lbl_8066D808, 1, 0xcc) / 32767.0f;
            } else {
                if (fn_80432924(lbl_80552110))
                    fn_800B16D8(*fn_80432924(lbl_80552110), &pos);
                level = fn_8010C7EC(lbl_8066D808, 1, 0xcb) / 32767.0f;
            }
            fn_804304FC(lbl_80567750, lbl_80567730, &pos, level);
        }
    }
    lbl_8066F074 = 0;
    for (unsigned int i = 0; i <= 0x2f; i++) {
        if (lbl_80567760[i].active)
            fn_80114E2C(i);
    }
    fn_80112884();
    fn_8010E6E8();
    fn_8010E530();
    unsigned int volume = fn_8010C7EC(lbl_8066D808, 1, lbl_8066BD18 ? 0x12f : 0x130);
    volume = volume * lbl_8066BD78 / 100;
    if (volume != lbl_8066BD98) {
        fn_80457478(lbl_8066BD6C, volume);
        fn_80457478(lbl_8066BD70, volume);
        lbl_8066BD98 = volume;
    }
    if (lbl_8066BD50 && !fn_8043AA90(fn_80052974()))
        lbl_8066BD50 = 0;
}
}
