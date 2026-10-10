// FrameCtx frontend request (guessed): sets +0xC and loads the frontend; see docs/versus.md section 5, row 9d.

inline int sn_return_decl(int a) { return a; }

extern "C" void fn_800877AC(void *p);

struct GameFlow {
    char pad[0x2A0];
    void LoadFrontend();
};

struct FrameCtx {
    char pad0[0xC];
    int f0C; // +0xC
    char pad1[0x4C];
    int pending; // +0x5C
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
