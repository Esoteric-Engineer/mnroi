// FrameCtx level load body (guessed): loads the level and primes the world; see docs/versus.md section 5, row 9d.

inline int sn_return_decl(int a) { return a; }

extern "C" {
int fn_804329E0(void *p);
void fn_8002CD84(void *self, int v);
void fn_8011C008(void *obj, int a);
void fn_80113D58();
int fn_8042D324(void *g);
unsigned int fn_8042D3B0(void *g, unsigned int start);
void fn_800164A0();
void fn_8023E98C();
void fn_8023DD7C(int a);
void fn_80119B8C();
void fn_80113DD4();
int fn_8002CE78(void *self, int a, int b, int c);
void fn_80432D50(void *p, float a);
void fn_80432A38(void *self, int v);
void fn_801B60F4(void *p);
int fn_80430050(void *p);
void fn_8002D110(void *self, int a, int b, int c);
void fn_801A9564(int a);
int fn_80431DDC(void *p);
void fn_80113E70();
void fn_80216DE0();
void fn_80126F0C(int a, int b);
void fn_80018C48();
}

class GameFlow
{
public:
    char pad[0x300]; // size is a placeholder; > 8 keeps the instance out of .sdata
    void SetLoadProgress(float progress, int redraw);
    void EndLoad();
};

struct FrameCtx
{
    char pad0[8];
    int f08; // +0x8
    char pad0C[0x2C];
    char s38[0x24]; // +0x38
};

extern GameFlow lbl_80552920;
extern char lbl_80593BE8[];
extern void *lbl_8066BE10;
extern int lbl_8066BD0C;
extern int lbl_8066C7DC;

extern "C" int fn_8002CB7C(register FrameCtx *self, int a, int b, int c, int d)
{
    unsigned int start;
    int r;
    if (fn_804329E0(self)) {
        fn_8002CD84(self, 0);
    }
    fn_8011C008(lbl_8066BE10, 5);
    fn_80113D58();
    start = fn_8042D324(lbl_80593BE8);
    while (fn_8042D3B0(lbl_80593BE8, start) <= 499) {
        fn_800164A0();
        fn_8023E98C();
        fn_8023DD7C(1);
    }
    fn_80119B8C();
    fn_80113DD4();
    fn_8011C008(lbl_8066BE10, 6);
    lbl_8066BD0C = 1;
    r = fn_8002CE78(self, a, b, 0);
    fn_80432D50(&lbl_80552920, 1.0f);
    lbl_80552920.SetLoadProgress(0.0f, 1);
    if (r == 0) {
        return 0;
    }
    fn_80432A38(self, r);
    if (d & 8) {
        fn_801B60F4(self->s38);
    }
    lbl_80552920.SetLoadProgress(0.5f, 1);
    fn_8002D110(self, fn_80430050(self), c, d);
    fn_801A9564(0);
    self->f08 = 1;
    lbl_8066C7DC = 15;
    if (fn_80431DDC(&lbl_80552920) == 0) {
        lbl_80552920.EndLoad();
    }
    lbl_80552920.SetLoadProgress(1.0f, 1);
    fn_80113E70();
    fn_80216DE0();
    lbl_8066BD0C = 0;
    fn_80126F0C(1, 0);
    fn_80018C48();
    return 1;
}
