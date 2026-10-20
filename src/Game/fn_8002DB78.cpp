// FrameCtx frontend request and by-name level reload (guessed); see docs/versus.md section 5, row 9d.
// Owns .rodata 0x80485890 ("NSD", the extension fn_8002DCEC appends to the level path).

inline int sn_return_decl(int a) { return a; }

struct FrameCtx;

struct Node {
    char pad0[0x198];
    virtual void v0();
    virtual void v1();
};

struct Rec {
    char pad0[0x1C0];
};

struct Scene {
    char pad0[0xC];
    unsigned int count; // +0xC
    char pad10[0x110];
    void *f120; // +0x120
    void *f124; // +0x124
    char pad128[4];
    Rec *recs; // +0x12C
    Node *f130; // +0x130
    Node *f134; // +0x134
    Node *f138; // +0x138
};

extern "C" {
void fn_800877AC(void *p);
int fn_80431E08(void *self);
int fn_804329E0(void *self);
Scene *fn_80430050(void *self);
void fn_8002C690(void *self, const char *name, const char *name2, int flags);
void fn_8002DCEC(FrameCtx *self, const char *name);
void fn_8002E2C0(void *self);
char *strncpy(char *dst, const char *src, unsigned n);
int strcmp(const char *a, const char *b);
void fn_8002D5F8(void *self, void *scene, int flags);
void fn_8002D110(void *self, void *scene, int b, int flags);
void fn_800A6B28(void *p);
Node *fn_800B1AC4(Node *node);
void fn_800AE398(Node *node, int a, int b);
void fn_800A92D4(void *p);
void fn_800619C0();
void fn_80016570();
void fn_80023010();
void fn_801A9564(int a);
void fn_801B4094(char *path, const char *ext);
void *fn_800A4DF8(const char *name, void *scene, int a);
int fn_80020B4C(const char *s, int a);
void fn_80020BF8(int a);
int fn_80432844(void *g);
int fn_80432870(void *g);
char *fn_804326B4(void *p);
char *fn_8043265C(char *p);
extern const char lbl_80485858[]; // "GENERIC.NCL"
}

struct GameFlow {
    char pad[0x2A0];
    void LoadFrontend();
    void EndLoad();
};

struct State {
    char pad0[0x620];
    int f620; // +0x620
};

struct FrameCtx {
    char pad0[8];
    int f08; // +0x8
    int f0C; // +0xC
    char pad10[0x4C];
    int pending; // +0x5C
    char pad60[0xC];
    int f6C; // +0x6C
    unsigned int f70; // +0x70
    char name[0x20]; // +0x74
    char pad94[0x20];
    int fB4; // +0xB4
};

extern char lbl_8054ED80[];
extern char lbl_8054EF38[];
extern char lbl_805526CC[];
extern State lbl_80552110;
extern GameFlow lbl_80552920;
extern int lbl_8066BD10;
extern int lbl_8066C7DC;

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
    if (fn_804329E0(self) && strcmp(name, (char *)fn_80430050(self) + 0x30) == 0) {
        self->f70 |= 0x20000;
        fn_8002DCEC(self, name);
    } else {
        strncpy(self->name, name, 0x20);
        self->name[0x1F] = 0;
        fn_8002E2C0(self);
    }
}

extern "C" void fn_8002DCEC(register FrameCtx *self, const char *name)
{
    Node *node;
    Node *next;
    unsigned int i;
    Rec *rec;
    char path[0x20];
    lbl_8066BD10 = 1;
    fn_8002D5F8(self, fn_80430050(self), self->f70);
    self->f08 = 0;
    self->f6C = 0;
    lbl_80552920.EndLoad();
    if (fn_80430050(self)->f120) {
        fn_800A6B28(fn_80430050(self)->f120);
        fn_80430050(self)->f120 = 0;
    }
    if (fn_80430050(self)->f124) {
        fn_800A6B28(fn_80430050(self)->f124);
        fn_80430050(self)->f124 = 0;
    }
    node = fn_80430050(self)->f130;
    while (node) {
        next = fn_800B1AC4(node);
        fn_800AE398(node, 1, 0);
        node->v1();
        node = next;
    }
    fn_80430050(self)->f130 = 0;
    node = fn_80430050(self)->f134;
    while (node) {
        next = fn_800B1AC4(node);
        fn_800AE398(node, 1, 0);
        node->v1();
        node = next;
    }
    fn_80430050(self)->f134 = 0;
    fn_80016570();
    node = fn_80430050(self)->f138;
    while (node) {
        next = fn_800B1AC4(node);
        fn_800AE398(node, 1, 0);
        node->v1();
        node = next;
    }
    fn_80430050(self)->f138 = 0;
    for (i = 0; i < fn_80430050(self)->count; i++) {
        rec = fn_80430050(self)->recs + i;
        fn_800A92D4(rec);
    }
    fn_800619C0();
    fn_80016570();
    strncpy(path, name, 0x20);
    path[0x1F] = 0;
    fn_801B4094(path, "NSD");
    fn_801A9564(0x83400);
    fn_80430050(self)->f120 = fn_800A4DF8(path, fn_80430050(self), 1);
    if (fn_80430050(self)->f120 == 0) {
    }
    fn_80016570();
    if (!fn_80432844(&lbl_80552110) && !fn_80432870(&lbl_80552110)) {
        if (lbl_80552110.f620 != 0) {
            fn_800A4DF8(lbl_805526CC, fn_80430050(self), 0);
            fn_80020B4C(lbl_80485858, 6);
            if (fn_80020B4C(lbl_805526CC, 0)) {
                fn_80020BF8(0);
            }
        } else {
            fn_800A4DF8(fn_8043265C(fn_804326B4(lbl_8054ED80)), fn_80430050(self), 0);
            if (fn_80020B4C(fn_8043265C(fn_804326B4(lbl_8054ED80)), 0)) {
                fn_80020BF8(0);
            }
        }
    } else {
        fn_800A4DF8(fn_8043265C(fn_804326B4(lbl_8054EF38)), fn_80430050(self), 0);
        fn_80020B4C(lbl_80485858, 6);
        if (fn_80020B4C(fn_8043265C(fn_804326B4(lbl_8054EF38)), 0)) {
            fn_80020BF8(0);
        }
    }
    fn_801A9564(0);
    fn_80016570();
    fn_8002D110(self, fn_80430050(self), 0, self->f70);
    fn_80016570();
    lbl_8066C7DC = 15;
    fn_80023010();
    self->f08 = 1;
    self->f70 &= ~0x10000;
    self->f70 &= ~0x20000;
    lbl_8066BD10 = 0;
}
