// FrameCtx attract-start level load (guessed): picks the level for the pending request; see docs/versus.md section 5, row 9d.
// Owns .rodata 0x804858FC ("intro.bik").

typedef struct State {
    char pad0[0x61C];
    int levelSet;  // +0x61C
    int f620;      // +0x620
    int f624;      // +0x624
    int f628;      // +0x628
} State;

typedef struct FrameCtx {
    char pad0[0x328];
    unsigned int count; // +0x328
    void *objs[1];      // +0x32C
} FrameCtx;

int fn_8002E570(FrameCtx *self, const char *s);
void fn_8002C690(void *ctx, const char *name, const char *name2, int flags);
void fn_800884A4(void *rec, const char *name, int v);
void *fn_804326B4(void *table);
void *fn_80087424(void *p);
void fn_800944C0(void *g, void *rec, int player);
char *fn_80432688(void *rec);
char *fn_8043265C(void *rec);
int fn_80432844(void *g);
int fn_80432870(void *g);
void *fn_800FD5FC(void *obj, int v);
void *fn_80432924(void *g);
void fn_800AD1FC(void *a, void *b, int c, int d);
void fn_8002F884(FrameCtx *self, int mode);

extern int lbl_8066B6C0;
extern State lbl_80552110;
extern char lbl_8052F060[];
extern char lbl_8054ED80[];
extern char lbl_8054EF38[];
extern char lbl_805526AC[];
extern char lbl_805526CC[];
extern char lbl_805526EC[];

void fn_8002F4A8(register FrameCtx *self)
{
    unsigned int i;
    void *obj;
    void *w;

    lbl_8066B6C0 = 4;
    if (fn_8002E570(self, "intro.bik") == 0) {
        lbl_8066B6C0 = 5;
        if (lbl_80552110.levelSet != 0) {
            if (lbl_80552110.f620 != 0) {
                fn_8002C690(lbl_8052F060, lbl_805526AC, lbl_805526CC, 0x1018);
            } else {
                fn_8002C690(lbl_8052F060, lbl_805526AC, 0, 0x1008);
            }
            lbl_80552110.levelSet = 0;
        } else if (lbl_80552110.f624 != 0) {
            fn_800884A4(lbl_8054ED80, lbl_805526EC, 0);
            fn_800944C0(&lbl_80552110, fn_80087424(fn_804326B4(lbl_8054ED80)), 0);
            fn_8002C690(lbl_8052F060, fn_80432688(fn_804326B4(lbl_8054ED80)), fn_8043265C(fn_804326B4(lbl_8054ED80)), 0x1008);
            lbl_80552110.f624 = 0;
        } else if (lbl_80552110.f628 != 0) {
            fn_800884A4(lbl_8054EF38, lbl_805526EC, 0);
            fn_8002C690(lbl_8052F060, fn_80432688(fn_804326B4(lbl_8054EF38)), fn_8043265C(fn_804326B4(lbl_8054EF38)), 0x1008);
            lbl_80552110.f628 = 0;
        } else if (fn_80432844(&lbl_80552110) != 0 || fn_80432870(&lbl_80552110) != 0) {
            fn_8002C690(lbl_8052F060, fn_80432688(fn_804326B4(lbl_8054EF38)), fn_8043265C(fn_804326B4(lbl_8054EF38)), 0x1008);
        } else {
            fn_800944C0(&lbl_80552110, fn_80087424(fn_804326B4(lbl_8054ED80)), 0);
            fn_8002C690(lbl_8052F060, fn_80432688(fn_804326B4(lbl_8054ED80)), fn_8043265C(fn_804326B4(lbl_8054ED80)), 0x1008);
        }
        fn_8002F884(self, 3);
        if (self->count != 0) {
            for (i = 0; i < self->count; i++) {
                obj = self->objs[i];
                if (obj != 0) {
                    w = fn_800FD5FC(obj, 0);
                    if (w != 0) {
                        fn_800AD1FC(fn_80432924(&lbl_80552110), w, 1, 0);
                    }
                }
            }
        }
    }
}
