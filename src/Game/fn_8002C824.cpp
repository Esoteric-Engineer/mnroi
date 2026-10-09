// FrameCtx level setup and teardown (guessed): registers three handles on three lists, and removes them again; see docs/versus.md section 5, row 9d.

inline int sn_return_decl(int a) { return a; }

extern "C" {
void fn_8002A260();
void fn_80018110();
void fn_800912E4(void *g);
void fn_80132480();
void fn_80052790();
void fn_8003E10C();
void fn_8002B9F0(int arg);
void fn_800527AC();
void fn_80132AAC();
void fn_80091AB8(void *g);
void fn_8001812C();
void fn_8002A2A8();
void fn_80428C6C(void *list, struct Cue arg);
}

class FrameCtx
{
public:
    void OnA(int) __asm__("fn_8002D994");
    void OnB() __asm__("fn_8002DB50");
};

typedef void (FrameCtx::*PmA)(int);
typedef void (FrameCtx::*PmB)();

class Link
{
public:
    void *impl;       // +0x0
    const void *vptr; // +0x4
    Link(void *owner, const PmB &name) __asm__("__4LinkPvPCv");
    Link(void *owner, const PmA &name) __asm__("__4LinkPvPCi");
    Link(const Link &other);
    ~Link();
};

class Cue
{
public:
    void *impl;       // +0x0
    const void *vptr; // +0x4
    Cue(const int &name) __asm__("__3CuePCi");
    Cue(const Cue &other);
    ~Cue();
};

void fn_80432EE8(void *list, Link arg);
void fn_80433058(void *list, Link arg);
extern "C" void fn_80428594(void *list, Cue arg);

extern char lbl_80552110[];
extern char lbl_80572354[];
extern char lbl_8057237C[];
extern char lbl_8057229C[];

extern "C" void fn_8002C824(register FrameCtx *self)
{
    fn_8002A260();
    fn_80018110();
    fn_800912E4(lbl_80552110);
    fn_80132480();
    fn_80052790();
    fn_8003E10C();
    fn_80432EE8(lbl_80572354, Link(self, &FrameCtx::OnB));
    fn_80432EE8(lbl_8057237C, Link(self, &FrameCtx::OnA));
    fn_80428594(lbl_8057229C, Cue((int)fn_8002B9F0));
}

extern "C" void fn_8002C924(register FrameCtx *self)
{
    fn_80428C6C(lbl_8057229C, Cue((int)fn_8002B9F0));
    fn_80433058(lbl_8057237C, Link(self, &FrameCtx::OnA));
    fn_80433058(lbl_80572354, Link(self, &FrameCtx::OnB));
    fn_800527AC();
    fn_80132AAC();
    fn_80091AB8(lbl_80552110);
    fn_8001812C();
    fn_8002A2A8();
}
