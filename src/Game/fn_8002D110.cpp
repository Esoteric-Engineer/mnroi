// FrameCtx level-load finish (guessed): primes the world for the loaded level; see docs/versus.md section 5, row 9d.
// Owns .rodata 0x8048586C-0x80485884 ("menu", "cButton", 0.0f, 300.0f).

inline int sn_return_decl(int a) { return a; }

extern "C" {
int strcmp(const char *a, const char *b);
char *strstr(const char *a, const char *b);
void fn_80432518(void *g);
void fn_804325CC(void *g);
void fn_801AA30C();
void fn_80023DC8();
void fn_80018198();
void fn_8001A05C();
void fn_80048558(void *lv);
void fn_800ACB14();
void fn_800916BC(void *g, void *lv, int b, int c);
void fn_801A29A0();
void fn_8021B1A0(void *p, int a, float x, float y, void *q);
int fn_8002FC00(void *p);
void fn_80094938(void *g, float v);
void fn_8002F884(void *self, int mode);
void fn_80087100();
void fn_800899B8();
void fn_8011C008(void *obj, int a);
void fn_801AF71C(void *g);
void fn_800B9518();
void fn_8039E5D8(void *p);
void fn_800B5694(void *p);
void fn_8007DC60();
void fn_800527C8();
void fn_800B3008(int a);
void fn_80132C04();
void fn_8003EC5C();
int fn_8042F268(void *p);
int fn_80430CD8(void *p, int bit);
void fn_80198D14(char *name, int a);
void fn_80232EBC(char *name, int a);
void fn_801A1EEC(char *name, int a);
void fn_8023597C(char *name, int a);
void fn_800909A0(char *name, int a);
unsigned int fn_80432B20(void *p);
char *fn_8007A2C4(void *p);
int fn_800B13D8(void *p);
}

class GameFlow
{
public:
    char pad[0x300]; // size is a placeholder; > 8 keeps the instance out of .sdata
};

struct Pmf // a member-function pointer: delta, index, function
{
    short delta;
    short index;
    void *pfn;
};

struct Level;

struct Widget
{
    char pad0[0x24];
    char *f24; // +0x24
};

struct Entry
{
    char pad0[0x14C];
    Widget *f14C; // +0x14C
};

struct Scene
{
    char pad0[0x120];
    Level *f120; // +0x120
};

struct Level
{
    char pad0[0x70];
    int f70; // +0x70
    char pad74[0x1C];
    float f90; // +0x90
    float f94; // +0x94
    char pad98[0x28];
    float fC0; // +0xC0
    char padC4[0xD0];
    Entry **f194; // +0x194
};

struct FrameCtx
{
    char pad0[0x10];
    int f10; // +0x10
    char pad14[0x60];
    char s74[0x20]; // +0x74
};

extern GameFlow lbl_80552920;
extern char lbl_80552110[];
extern char lbl_80593BE8[];
extern char lbl_80594E00[];
extern char lbl_8064AA80[];
extern char lbl_8066D568[8];
extern char lbl_8066D578[4];
extern void *lbl_8066BE10;
extern int lbl_8066B6D0;
extern int lbl_8066C5A8;

extern "C" void fn_8002D110(register FrameCtx *self, Scene *a, int b, int c)
{
    Level *obj;
    unsigned int i;
    Entry *entry;
    register Pmf *p;
    register Pmf *q;
    register char *tgt;
    lbl_8066B6D0 = 1;
    fn_80432518(lbl_80593BE8);
    fn_804325CC(lbl_80593BE8);
    fn_801AA30C();
    fn_80023DC8();
    fn_80018198();
    fn_8001A05C();
    fn_80048558(a);
    fn_800ACB14();
    fn_800916BC(lbl_80552110, a, b, c);
    fn_801A29A0();
    obj = a->f120;
    if (obj) {
        fn_8021B1A0(lbl_80594E00, obj->f70, obj->f90, obj->f94, (char *)obj + 0x80);
        lbl_8066C5A8 = fn_8002FC00((char *)obj + 0x80);
        if (obj->fC0 != 0.0f) {
            fn_80094938(lbl_80552110, obj->fC0);
        } else {
            fn_80094938(lbl_80552110, 300.0f);
        }
    }
    fn_8002F884(self, 3);
    fn_80087100();
    fn_800899B8();
    fn_8011C008(lbl_8066BE10, 8);
    fn_801AF71C(lbl_80593BE8);
    fn_800B9518();
    fn_8039E5D8(lbl_8064AA80);
    fn_800B5694(&lbl_80552920);
    fn_8007DC60();
    fn_800527C8();
    fn_800B3008(self->f10);
    fn_80132C04();
    fn_8003EC5C();
    if (fn_8042F268(lbl_8066D568)) {
        if (strcmp(self->s74, "menu")) {
            if (fn_80430CD8(lbl_8066D578, 4)) {
                fn_80198D14(self->s74, 1);
            }
            if (fn_80430CD8(lbl_8066D578, 1)) {
                fn_80232EBC(self->s74, 1);
            }
            if (fn_80430CD8(lbl_8066D578, 2)) {
                fn_801A1EEC(self->s74, 1);
            }
            if (fn_80430CD8(lbl_8066D578, 8)) {
                fn_8023597C(self->s74, 1);
            }
            if (fn_80430CD8(lbl_8066D578, 0x10)) {
                fn_800909A0(self->s74, 1);
            }
        }
        for (i = 0; i < fn_80432B20(obj); i++) {
            entry = obj->f194[i];
            if (!entry) {
                continue;
            }
            if (entry->f14C) {
                if (strstr(fn_8007A2C4(entry->f14C), "cButton")) {
                    p = (Pmf *)(entry->f14C->f24 + 0xB8);
                    tgt = (char *)entry->f14C + p->delta;
                    ((void (*)(char *, int, int, int, float, float, float, float, int))p->pfn)(
                        tgt, 0, fn_800B13D8(entry), 0, 0.0f, 0.0f, 0.0f, 0.0f, 0);
                } else {
                    q = (Pmf *)(entry->f14C->f24 + 0x40);
                    ((void (*)(char *, int, float, float, float, float, int))q->pfn)(
                        (char *)entry->f14C + q->delta, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
                }
            }
        }
        if (strcmp(self->s74, "menu")) {
            if (fn_80430CD8(lbl_8066D578, 4)) {
                fn_80198D14(0, 0);
            }
            if (fn_80430CD8(lbl_8066D578, 1)) {
                fn_80232EBC(0, 0);
            }
            if (fn_80430CD8(lbl_8066D578, 2)) {
                fn_801A1EEC(0, 0);
            }
            if (fn_80430CD8(lbl_8066D578, 8)) {
                fn_8023597C(0, 0);
            }
            if (fn_80430CD8(lbl_8066D578, 0x10)) {
                fn_800909A0(0, 0);
            }
        }
    }
}
