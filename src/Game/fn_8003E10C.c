// Resets the pools (free lists of 0x50- and 0xD0-byte nodes and three small tables) and the level's two records. docs/versus.md section 5, row 25.

typedef struct {
    char pad0[0x10];
    int bit;  // +0x10
    int f14;  // +0x14
    char pad18[0x10];
} Rec28;

typedef struct Node50 {
    char pad0[0x40];
    struct Node50 *next; // +0x40
    char pad44[0xC];
} __attribute__((aligned(8))) Node50;

typedef struct NodeD0 {
    char pad0[0xC0];
    struct NodeD0 *next; // +0xC0
    char padC4[0xC];
} __attribute__((aligned(8))) NodeD0;

typedef struct {
    char pad[0x75C];
} State;

extern Rec28 lbl_8053EF18[8];
extern Node50 lbl_8052F4F0[0x80];
extern NodeD0 lbl_80531CF0[0x100];
extern Node50 *lbl_8066B770;
extern NodeD0 *lbl_8066B77C;
extern int lbl_8053F3D4[3];
extern int lbl_8053EE80[3];
extern int lbl_8053EE8C[3];
extern State lbl_80552110; // the game-state object G
extern char lbl_8054EF38[];
extern char lbl_8054ED80[];

extern void fn_80044E5C(int a);
extern int fn_80432844(State *g);
extern int fn_80432870(State *g);
extern void *fn_804326B4(void *table);
extern void *fn_80435820(void *x);
extern void fn_800482DC(void *x);
extern void *fn_8043584C(void *x);
extern void fn_80048344(void *x);

void fn_8003E10C(void)
{
    int i;
    void *level;

    i = 0;
    while (i <= 7) {
        lbl_8053EF18[i].f14 = 0;
        lbl_8053EF18[i].bit = 1 << i;
        i++;
    }
    i = 0;
    while ((unsigned int)i <= 0x7E) {
        lbl_8052F4F0[i].next = &lbl_8052F4F0[i + 1];
        i++;
    }
    lbl_8052F4F0[0x7F].next = 0;
    lbl_8066B770 = lbl_8052F4F0;
    i = 0;
    while ((unsigned int)i <= 0xFE) {
        lbl_80531CF0[i].next = &lbl_80531CF0[i + 1];
        i++;
    }
    lbl_80531CF0[0xFF].next = 0;
    lbl_8066B77C = lbl_80531CF0;
    i = 0;
    while (i <= 2) {
        lbl_8053F3D4[i] = 0;
        lbl_8053EE80[i] = -1;
        lbl_8053EE8C[i] = -1;
        i++;
    }
    fn_80044E5C(0);
    level = 0;
    if (fn_80432844(&lbl_80552110) != 0 || fn_80432870(&lbl_80552110) != 0) {
        level = fn_804326B4(lbl_8054EF38);
    } else {
        level = fn_804326B4(lbl_8054ED80);
    }
    if (level != 0) {
        fn_800482DC(fn_80435820(level));
        fn_80048344(fn_8043584C(level));
    }
}
