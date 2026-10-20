// FrameCtx level-load "when" dispatch and the pending-14/15 setters (guessed); see docs/versus.md section 5, row 9d.

inline int sn_return_decl(int a) { return a; }

struct FrameCtx {
    char pad0[0x5C];
    int pending; // +0x5C
};

struct Scene {
    char pad0[0x130];
    int head; // +0x130
};

extern "C" {
int strcmp(const char *a, const char *b);
int fn_8002D994(FrameCtx *ctx);
void fn_80433198(void *owner, int a, int b);
extern const char lbl_80485888[]; // "NOW"
extern char lbl_8057229C[];
extern char lbl_8052F060[];
extern char lbl_8057230C[];
void *fn_80432924(void *g);
void fn_80086410(void *p);
Scene *fn_80430050(void *p);
int fn_800B1AC4(int node);
int fn_800B0C58(int node);
int fn_800B14A0(int node);
int fn_8008582C(int id);
int fn_80085D3C(int id);
void fn_80030930(int id, int a, int b, int c, float f1, int d, int e, int f, int g, float f2);
void fn_80133658(void);
void fn_8043323C(void *list, int flag);
int fn_8002DB78(FrameCtx *ctx);
}

struct State {
    char pad0[0x760];
    int phase; // +0x760
    char pad1[0x1C];
    int f780; // +0x780
};
extern State lbl_80552110;

extern "C" int fn_8002D90C(register FrameCtx *self, const char *when)
{
    if (strcmp(when, lbl_80485888) == 0) {
        fn_8002D994(self);
    } else {
        fn_80433198(lbl_8057229C, 0, 0xBB8);
    }
    lbl_80552110.phase = 0xF;
    return 1;
}

extern "C" int fn_8002D994(register FrameCtx *self)
{
    self->pending = 0xF;
    return 1;
}

extern "C" int fn_8002D9C4(register FrameCtx *self)
{
    int node, next;
    register Scene *scene;
    lbl_80552110.phase = 0xF;
    fn_80086410(fn_80432924(&lbl_80552110));
    if (lbl_80552110.f780 != 0) {
        fn_8002DB78(self);
    } else {
        scene = fn_80430050(lbl_8052F060);
        for (node = scene->head; node != 0; node = next) {
            next = fn_800B1AC4(node);
            if (!fn_800B0C58(node)) {
                continue;
            }
            if (!fn_8008582C(fn_800B14A0(node))) {
                continue;
            }
            if (fn_80085D3C(fn_800B14A0(node))) {
                continue;
            }
            fn_80030930(fn_800B14A0(node), 0, 0, 0, 0.0f, 0, 0, 0, 1, 0.0f);
        }
        fn_80133658();
        fn_8043323C(lbl_8057230C, 1);
        fn_80433198(lbl_8057229C, 1, 0xBB8);
    }
    return 1;
}

extern "C" void fn_8002DB50(register FrameCtx *self)
{
    self->pending = 0xE;
}
