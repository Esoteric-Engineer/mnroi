// The file at 0x8002B9F0 (docs/versus.md section 5, row 9d): per-frame service calls, then the object they run on. Names are guesses.

inline int sn_return_decl(int a) { return a; }

class FrameCtx;

extern "C" {
void fn_801336F0();
void fn_800924BC(void *g);
int fn_80432A0C(void *p);
void fn_8002F884(void *p, int v);
int fn_800936D0(void *g);
int fn_80093410(void *g);
void fn_80432DF8(void *p);
}

struct GState
{
    char pad0[0x61C];
    int f61c; // +0x61C
    int f620;
    int f624;
    int f628;
    int f62c;
    int f630;
    int f634;
};
extern GState lbl_80552110;
extern char lbl_8052F060[];
extern char lbl_80572354[];
extern char lbl_8057237C[];

extern "C" void fn_8002B9F0(int arg)
{
    fn_801336F0();
    fn_800924BC(&lbl_80552110);
    if (fn_80432A0C(lbl_8052F060) == 0x109) {
        fn_8002F884(lbl_8052F060, 3);
    }
    if (arg != 0) {
        if (fn_800936D0(&lbl_80552110) == 0) {
            fn_80432DF8(lbl_80572354);
        }
    } else {
        if (fn_80093410(&lbl_80552110) == 0) {
            fn_80432DF8(lbl_8057237C);
        }
    }
}

// 0x24-byte member, constructed by fn_801B54E8.
class Sub24
{
public:
    char b[0x24];
    Sub24(int a, float f) __asm__("fn_801B54E8");
    ~Sub24();
};

// 8-byte element, constructed by fn_80426A2C.
class Cell8
{
public:
    char b[8];
    Cell8() __asm__("fn_80426A2C");
};

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

class FrameCtx
{
public:
    char pad0[4];
    int f04;           // +0x4
    int f08;
    int f0c;
    int f10;
    Sub24 s14;         // +0x14
    Sub24 s38;         // +0x38
    int f5c;           // +0x5C
    int f60;
    char pad64[4];
    unsigned int flags; // +0x68
    int f6c;           // +0x6C
    int f70;
    char b74;          // +0x74
    char pad75[0x1F];
    char b94;
    char pad95[0x1F];
    int fb4;           // +0xB4
    char bb8;
    char padb9[0x1F];
    char bd8;          // +0xD8
    char padd9[0x1F];
    int ff8;           // +0xF8
    int ffc;
    int f100;
    char b104;         // +0x104
    char b105;
    char pad106[0x6F];
    char b175;         // +0x175
    char b176;
    char pad177[0x1F];
    char b196;         // +0x196
    char pad197[0x81];
    int f218;          // +0x218
    char b21c;
    char pad21d[0x7F];
    int f29c;          // +0x29C
    int f2a0;
    char b2a4;
    char pad2a5[0x7F];
    int f324;          // +0x324
    int f328;
    int f32c;
    char pad330[0x3C];
    Cell8 cells[4];    // +0x36C
    Vector vecs[4];    // +0x390
    FrameCtx();
    ~FrameCtx();
};

FrameCtx::FrameCtx() : s14(0x19, 0.2f), s38(0x19, 0.2f)
{
    f04 = 0;
    f08 = 0;
    f0c = 0;
    f10 = 0;
    ffc = 0;
    f6c = 0;
    f70 = 0;
    fb4 = 0;
    b74 = 0;
    b94 = 0;
    bb8 = 0;
    bd8 = 0;
    ff8 = 0;
    f100 = 0;
    b104 = 0x20;
    b105 = 0;
    b175 = 0x20;
    b176 = 0;
    b196 = 0;
    f218 = 0;
    b21c = 0;
    f29c = 0;
    f2a0 = 0;
    b2a4 = 0;
    f324 = 0;
    f5c = 0;
    f60 = 0x12;
    fn_8002F884(this, 1);
    f328 = 0;
    f32c = 0;
}

FrameCtx::~FrameCtx()
{
}

extern "C" int fn_8002BD04()
{
    int r = 0;
    return r;
}

extern "C" {
void fn_801AF790(void *p);
void *fn_8042FA34();
void fn_80430C58(void *p, int id, float f);
int fn_804329E0(void *p);
int fn_8042D4CC();
int fn_8042D52C(int v);
int fn_8005287C();
void fn_80015DB8(int v);
int fn_8002E570(void *p, const char *s);
void fn_8002F3A8(void *p);
void fn_8002E9B4(void *p);
void fn_8002EAD4(void *p);
void fn_8002EE1C(void *p);
void fn_80233E54();
void fn_8007DD34();
void fn_8002E6DC(void *p);
void *fn_80430050(void *p);
void fn_80074814(void *p);
void fn_8011912C();
void fn_8002E95C(void *p);
void fn_80094024(void *g);
void fn_8039F13C(void *p);
void fn_80219EAC(int v);
void fn_80095000(void *g);
void fn_8043105C();
void fn_80219DA0(int a, int b, int c);
void fn_8002ED14(void *p);
void fn_800B5AFC(void *p);
void fn_8021A1B8();
int fn_80431DDC(void *p);
void fn_800951E4(void *g);
void Update__8GameFlow(void *p);
void fn_80015894();
void fn_8001854C();
void fn_8021A1D4();
void fn_80028910();
void fn_8021A164(int v);
void fn_80061A10();
void fn_800748A4(void *p);
void fn_80061B44();
void fn_80219E64();
void *fn_8042F024(void *g);
void fn_80164608(void *a, void *b);
void *fn_804325A0(void *g);
void fn_8002C214(FrameCtx *p);
void fn_8002E97C(void *p);
void *fn_804324EC(void *g);
void fn_80430C80(void *p, int a, void *b);
void fn_80432998(void *p);
}

extern char lbl_80593BE8[];
extern char lbl_80552920[];
extern char lbl_8064AA80[];
extern char lbl_80571E04[];
extern char lbl_80571E54[];
extern int lbl_8066C7DC;
extern int lbl_8066B6C0;
extern int lbl_8066B63C;
extern int lbl_8066B6D0;
extern int lbl_8066B650;

extern "C" void fn_8002BD34(register FrameCtx *self, int arg)
{
    fn_801AF790(lbl_80593BE8);
    fn_80430C58(fn_8042FA34(), 0x12, 0.0f);
    fn_80430C58(fn_8042FA34(), 0x22, 0.0f);
    fn_80430C58(fn_8042FA34(), 0x23, 0.0f);
    fn_80430C58(fn_8042FA34(), 0x25, 0.0f);
    fn_80430C58(fn_8042FA34(), 0x26, 0.0f);
    if (fn_804329E0(self) != 0 && lbl_8066C7DC == 0) {
        if (fn_8042D52C(fn_8042D4CC()) != 0 && fn_8005287C() != 0) {
            fn_80015DB8(fn_8042D4CC());
        }
    }
    if (lbl_8066B6C0 == 0) {
        if (lbl_80552110.f61c != 0 || lbl_80552110.f624 != 0 || lbl_80552110.f628 != 0 ||
            lbl_80552110.f634 != 0 || fn_8002E570(self, "EAGames_logo") == 0) {
            lbl_8066B6C0 = 5;
            fn_8002F3A8(self);
            fn_8002F884(self, 2);
        } else {
            lbl_8066B6C0 = 1;
        }
    }
    if ((arg ^ 1) & 1) {
        if (self->flags & 1) {
            fn_8002E9B4(self);
        }
    }
    if (self->flags & 0x20) {
        fn_8002EAD4(self);
    }
    if (lbl_8066B63C != 0 && (self->flags & 8)) {
        fn_8002EE1C(self);
    }
    fn_80233E54();
    if (self->flags & 2) {
        if (lbl_8066B6D0 != 0) {
            fn_8007DD34();
            lbl_8066B6D0 = 0;
        }
        fn_8002E6DC(self);
        fn_80074814(fn_80430050(self));
    }
    fn_8011912C();
    fn_8002E95C(self);
    if (self->flags & 2) {
        fn_80094024(&lbl_80552110);
    }
    if (self->flags & 0x80) {
        fn_8039F13C(lbl_8064AA80);
    }
    fn_80219EAC(1);
    if ((arg ^ 1) & 1) {
        if ((self->flags & 4) && lbl_8066C7DC == 0) {
            fn_80095000(&lbl_80552110);
        } else {
            if (lbl_8066C7DC != 0) {
                fn_8043105C();
            }
            if (self->flags & 0x10) {
                fn_80219DA0(5, 0, 0);
            }
        }
        if (self->flags & 0x100) {
            fn_8002ED14(self);
        }
        if (!(self->flags & 0x100)) {
            fn_800B5AFC(lbl_80552920);
        }
        if (self->flags & 0x10) {
            fn_8021A1B8();
            if (fn_80431DDC(lbl_80552920) == 0) {
                fn_800951E4(&lbl_80552110);
            }
            Update__8GameFlow(lbl_80552920);
            if (fn_8042D52C(fn_8042D4CC()) != 0) {
                fn_80015894();
            }
            fn_8001854C();
            fn_8021A1D4();
        }
        if (!(self->flags & 0x20)) {
            if (!(self->flags & 0x100)) {
                fn_80028910();
            }
            fn_8021A164(1);
        }
        if (self->flags & 2) {
            fn_80061A10();
            fn_800748A4(fn_80430050(self));
            fn_80061B44();
        }
        if (!(self->flags & 0x20)) {
            fn_80219E64();
        }
    }
    fn_80164608(lbl_80571E04, fn_8042F024(lbl_80593BE8));
    fn_80164608(lbl_80571E54, fn_804325A0(lbl_80593BE8));
    fn_8002C214((FrameCtx *)lbl_8052F060);
    fn_8002E97C(self);
    if (lbl_8066B650 != 0) {
    }
    fn_80430C80(fn_8042FA34(), 1, fn_804324EC(lbl_80593BE8));
    fn_80432998(fn_8042FA34());
    fn_8002BD04();
}

extern "C" {
void fn_80432AF8(void *p);
void fn_8002E2C0(void *p);
void fn_8002E4F8(void *p);
void fn_8002E61C(void *p, char *s, int v);
int fn_80432A60(void *p);
void fn_8002E69C(void *p);
int fn_8012D470();
void fn_80432CD8(void *p);
void EndLoad__8GameFlow(void *p);
int fn_80126DF0();
void fn_80128634();
void fn_8002F4A8(void *p);
void fn_80015960(int a, int b, int c);
int fn_8002C594(void *p);
void fn_8002F9A8(void *p);
void fn_8002CB1C(void *p);
void fn_8002E3EC(void *p);
void fn_8021A9EC(int a, int b);
int SetCommandBlocking__8GameFlowi(void *p, int v);
void LoadLevel__8GameFlowPc(void *p, char *name);
}

extern int lbl_8066B640;
extern int lbl_8066B6D4;
extern int lbl_8066B668;

// FrameCtx state machine: acts on the pending state at +0x5C (guessed).
extern "C" void fn_8002C214(register FrameCtx *self)
{
    if ((lbl_8066B6C0 != 1 && lbl_8066B6C0 != 2 && lbl_8066B6C0 != 3) || lbl_8066B640 == 0) {
        if (lbl_8066B6D4 != 0 && lbl_8066B668 != 0) {
            lbl_8066B6C0 = 5;
            fn_8002F884(self, 2);
            fn_80432AF8(self);
            lbl_8066B6D4 = 0;
            return;
        }
    }
    switch (self->f5c) {
    case 0:
        if (self->f6c != 0) {
            fn_8002E2C0(self);
        }
        return;
    case 5:
        self->f5c = self->f60;
        self->f60 = 0x12;
        break;
    case 1:
        self->f5c = 0;
        fn_8002E4F8(self);
        self->f218 = 0;
        break;
    case 2:
        self->f5c = 0;
        fn_8002E570(self, &self->b21c);
        break;
    case 3:
        self->f5c = 0;
        fn_8002E61C(self, &self->b2a4, self->f324);
        break;
    case 4:
        self->f5c = 0;
        if (fn_80432A60(self) != 2) {
            fn_8002E69C(self);
        }
        break;
    case 6:
        break;
    case 7:
        if (fn_8012D470() == 0) {
            break;
        }
        fn_80432CD8(lbl_80552920);
        EndLoad__8GameFlow(lbl_80552920);
        if (fn_80126DF0() != 0) {
            fn_80128634();
        }
        self->f5c = 0;
        fn_8002F4A8(self);
        break;
    case 8:
        self->f5c = 0;
        break;
    case 9:
        self->f5c = 0;
        break;
    case 10:
        fn_80015960(fn_8042D4CC(), 3, 0);
        self->f5c = 0;
        fn_8002C594(self);
        break;
    case 11:
        self->f5c = 0;
        fn_8002F9A8(self);
        break;
    case 12:
        break;
    case 13:
        self->f5c = 0;
        fn_8002CB1C(self);
        break;
    case 16:
        self->f5c = 0;
        fn_8002E2C0(self);
        break;
    case 17:
        self->f5c = 0;
        fn_8002E3EC(self);
        self->f100 = 0;
        break;
    case 14:
        if (fn_8005287C() == 0) {
            break;
        }
        self->f5c = 0;
        fn_8021A9EC(1, 0);
        SetCommandBlocking__8GameFlowi(lbl_80552920, 0x58);
        break;
    case 15:
        if (fn_8005287C() == 0) {
            break;
        }
        self->f5c = 0;
        LoadLevel__8GameFlowPc(lbl_80552920, 0);
        break;
    default:
        break;
    }
}

extern "C" {
int fn_80426AB0(void *p);
void *fn_80431DB0(void *p);
void fn_8008856C(void *p, void *v, int f);
void fn_80432D00(void *p, int v);
void fn_8002DBF8(void *p, void *q);
int fn_80432924(void *g);
void fn_800949FC(void *g, int v);
}

extern char lbl_8054ED80[];
extern char lbl_8054EF38[];

// Frame-start hook run from fn_8002C214's states 10 and 13 (guessed).
extern "C" int fn_8002C594(register void *self)
{
    if (fn_80426AB0(&lbl_80552110)) {
        fn_8008856C(lbl_8054ED80, fn_80431DB0(lbl_8054ED80), 1);
    } else {
        fn_8008856C(lbl_8054EF38, fn_80431DB0(lbl_8054EF38), 1);
    }
    fn_80432D00(lbl_80552920, 0);
    fn_8002DBF8(lbl_8052F060, (char *)fn_80430050(self) + 0x30);
    if (fn_80432924(&lbl_80552110)) {
        fn_800949FC(&lbl_80552110, 1);
    }
    return 0;
}
