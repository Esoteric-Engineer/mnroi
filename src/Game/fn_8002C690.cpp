// FrameCtx level-load entry (guessed): resets the context for a new level; see docs/versus.md section 5, row 9d.

extern "C" {
char *strncpy(char *dst, const char *src, unsigned n);
void fn_80432CB4(int v);
void fn_80198304();
void fn_80432D28(void *p, float a, float b);
void fn_80432D50(void *p, float a);
void fn_80061778();
int fn_80431E08(void *self);
void fn_8002CA58(void *self);
void fn_801B60F4(void *p);
void fn_8002C824(void *self);
void fn_8002CB7C(void *self, const char *a, const char *b, int c, int d);
}

class GameFlow
{
public:
    char pad[0x300]; // size is a placeholder; > 8 keeps the instance out of .sdata
    void SetLoadProgress(float progress, int redraw);
};

struct FrameCtx
{
    char pad0[4];
    int f04;       // +0x4
    char pad8[0xC];
    char s14[0x60]; // +0x14
    char name[0x20]; // +0x74
    char b94[0x20]; // +0x94
};

extern GameFlow lbl_80552920;
extern int lbl_8066B9FC;

extern "C" int fn_8002C690(register FrameCtx *self, const char *name, const char *name2, int flags)
{
    fn_80432CB4(1);
    fn_80198304();
    fn_80432D28(&lbl_80552920, 0.0f, 0.05f);
    lbl_80552920.SetLoadProgress(0.0f, 1);
    fn_80061778();
    if (fn_80431E08(self)) {
        fn_8002CA58(self);
    }
    lbl_80552920.SetLoadProgress(0.5f, 1);
    fn_801B60F4(self->s14);
    strncpy(self->name, name, 0x20);
    self->name[0x1F] = 0;
    if (name2) {
        strncpy(self->b94, name2, 0x20);
        self->b94[0x1F] = 0;
    } else {
        self->b94[0] = 0;
    }
    fn_8002C824(self);
    self->f04 = 1;
    lbl_80552920.SetLoadProgress(1.0f, 1);
    lbl_8066B9FC = 200;
    fn_8002CB7C(self, name, name2, 0, flags);
    fn_80432D50(&lbl_80552920, 1.0f);
    lbl_80552920.SetLoadProgress(1.0f, 1);
    return 1;
}
