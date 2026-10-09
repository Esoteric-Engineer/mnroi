// FrameCtx level teardown (guessed): clears the context's state and returns 1; see docs/versus.md section 5, row 9d.

inline int sn_return_decl(int a) { return a; }

extern "C" {
void *fn_80432924(void *g);
void fn_8009E09C(void *p);
int fn_804329E0(void *p);
void fn_8002CD84(void *self, int v);
void fn_8002C924(void *self);
void fn_801B60F4(void *p);
void fn_80016570();
void fn_80113EE8();
void fn_801147D4();
void fn_80126F0C(int a, int b);
void fn_80198360();
void fn_80432CB4(int v);
}

struct FrameCtx
{
    char pad0[4];
    int f04; // +0x4
    char pad8[0xC];
    char s14[0x24]; // +0x14
    char s38[0x24]; // +0x38
};

extern char lbl_80552110[];

extern "C" int fn_8002CA58(register FrameCtx *self)
{
    fn_8009E09C(fn_80432924(lbl_80552110));
    if (fn_804329E0(self)) {
        fn_8002CD84(self, 0);
    }
    self->f04 = 0;
    fn_8002C924(self);
    fn_801B60F4(self->s14);
    fn_801B60F4(self->s38);
    fn_80016570();
    fn_80113EE8();
    fn_80016570();
    fn_801147D4();
    fn_80016570();
    fn_80126F0C(0, 0);
    fn_80198360();
    fn_80432CB4(0);
    return 1;
}
