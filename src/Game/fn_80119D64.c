// Music cue setup outside a versus match. The record table lbl_80497D24 has 0x5C-byte entries.

typedef struct {
    char pad[0x75C];
} State;

typedef struct {
    int a;
    int b;
} Cue;

typedef struct {
    int head;
    Cue cues[11];
} Record;

extern State lbl_80552110; // the game-state object G
extern void *lbl_8066BE10;
extern Record *lbl_8066BDF4;
extern int lbl_8066BDF8;
extern int lbl_8066BE00;
extern int lbl_8066BE04;
extern int lbl_8066BE08;
extern int lbl_8066F088;
extern char lbl_80568E30[];
extern char lbl_80593BE8[];
extern char lbl_8054ED80[];
extern Record lbl_80497D24[];

int fn_80432844(State *g);
int fn_80432870(State *g);
void fn_8045E8B0(void *self, int a, int b);
unsigned int fn_8042EFF8(void *obj);
void fn_8011C008(void *obj, int a);
void fn_8011C410(void *obj, float a);
void *fn_804326B4(void *table);
unsigned int fn_80442E7C(void *obj);

void fn_80119D64(int a)
{
    if (fn_80432844(&lbl_80552110) || fn_80432870(&lbl_80552110)) {
        return;
    }
    if (a > 10) {
        return;
    }
    if (lbl_8066BDF4 == 0) {
        return;
    }
    lbl_8066BE04 = a;
    fn_8045E8B0(lbl_80568E30, lbl_8066BDF4->cues[a].a, lbl_8066BDF4->cues[a].b);
    if (lbl_8066BDF8 == 0x18 && a == 1) {
        lbl_8066BE08 = fn_8042EFF8(lbl_80593BE8);
    }
}

void fn_80119E58(int a)
{
    fn_8011C008(lbl_8066BE10, a);
}

void fn_80119E94(int a)
{
    lbl_8066F088 = 0;
    fn_8011C410(lbl_8066BE10, 0.0f);
    if (fn_80432844(&lbl_80552110) || fn_80432870(&lbl_80552110)) {
        return;
    }
    lbl_8066BDF8 = fn_80442E7C(fn_804326B4(lbl_8054ED80));
    if (lbl_8066BDF8 > 0x3D) {
        return;
    }
    lbl_8066BDF4 = &lbl_80497D24[lbl_8066BDF8];
    fn_80119D64(0);
    lbl_8066BE00 = 0;
}
