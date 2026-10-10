// FrameCtx frontend request (guessed): sets +0xC and loads the frontend; see docs/versus.md section 5, row 9d.

inline int sn_return_decl(int a) { return a; }

extern "C" {
void fn_800877AC(void *p);
int fn_80431E08(void *self);
int fn_804329E0(void *self);
char *fn_80430050(void *self);
void fn_8002C690(void *self, const char *name, const char *name2, int flags);
void fn_8002DCEC(void *self, const char *name);
void fn_8002E2C0(void *self);
char *strncpy(char *dst, const char *src, unsigned n);
int strcmp(const char *a, const char *b);
}

struct GameFlow {
    char pad[0x2A0];
    void LoadFrontend();
};

struct FrameCtx {
    char pad0[0xC];
    int f0C; // +0xC
    char pad1[0x4C];
    int pending; // +0x5C
    char pad60[0xC];
    int f6C; // +0x6C
    unsigned int f70; // +0x70
    char name[0x20]; // +0x74
    char pad94[0x20];
    int fB4; // +0xB4
};

extern char lbl_8054ED80[];
extern GameFlow lbl_80552920;

extern "C" int fn_8002DB78(register FrameCtx *self)
{
    self->f0C = 1;
    fn_800877AC(lbl_8054ED80);
    lbl_80552920.LoadFrontend();
    return 1;
}

extern "C" void fn_8002DBD0(register FrameCtx *self)
{
    self->pending = 10;
}

extern "C" void fn_8002DBF8(register FrameCtx *self, const char *name)
{
    if (!fn_80431E08(self)) {
        fn_8002C690(self, name, 0, 0x1008);
        return;
    }
    self->f6C = 5;
    self->f70 = 0x10000;
    self->fB4 = 0;
    if (fn_804329E0(self) && strcmp(name, fn_80430050(self) + 0x30) == 0) {
        self->f70 |= 0x20000;
        fn_8002DCEC(self, name);
    } else {
        strncpy(self->name, name, 0x20);
        self->name[0x1F] = 0;
        fn_8002E2C0(self);
    }
}
