// FrameCtx level unload (guessed), called by fn_8002CA58 and fn_8002CB7C; see docs/versus.md section 5, row 9d.

inline int sn_return_decl(int a) { return a; }

extern "C" {
int fn_80430050(void *p);
void fn_8002D5F8(void *self, int a, int b);
void fn_800B3420(int a, int b);
void fn_80432A38(void *self, int v);
void fn_800910B8();
int fn_8042F268(void *p);
void fn_8019EE28(int a);
void fn_801A2588(int a);
void fn_802359A0(int a);
void fn_8023350C(int a, int b);
void fn_8019EFB8();
void fn_801A294C();
void fn_8023365C();
void fn_80061940();
void fn_8002CA20();
}

struct FrameCtx
{
    char pad0[8];
    int f08; // +0x8
    int f0C; // +0xC
};

extern char lbl_8066D568[8];
extern int lbl_8066B664;

extern "C" int fn_8002CD84(register FrameCtx *self, int v)
{
    fn_8002D5F8(self, fn_80430050(self), v);
    self->f0C = 0;
    fn_800B3420(fn_80430050(self), 0);
    fn_80432A38(self, 0);
    fn_800910B8();
    if (fn_8042F268(lbl_8066D568) == 0 && lbl_8066B664 != 0) {
        fn_8019EE28(1);
        fn_801A2588(1);
        fn_802359A0(1);
        fn_8023350C(2, 0);
    }
    fn_8019EFB8();
    fn_801A294C();
    fn_8023365C();
    fn_80061940();
    fn_80432A38(self, 0);
    fn_8002CA20();
    self->f08 = 0;
    return 1;
}
