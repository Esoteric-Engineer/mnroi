// FrameCtx deferred level-request step and the small request functions after it; see docs/versus.md section 5, row 9d.

extern "C" {
int fn_8002CA58(void *self);
int fn_804329E0(void *self);
int fn_8002CD84(void *self, int v);
void fn_8002CB7C(void *self, const char *a, const char *b, int c, int d);
void fn_800949FC(void *g, int v);
void *fn_80430050(void *self);
void *fn_80432924(void *g);
void *fn_800B3A74(void *scene, int v, int a, int b);
void fn_800AF800(void *g, void *scene, void *node, int a);
int fn_80432A8C(void *self);
void fn_8002F884(void *self, int mode);
void *fn_80052974();
int fn_80052C88(void *obj, const char *name, int v);
void fn_80053160(void *obj);
char *strncpy(char *dst, const char *src, int n);
void fn_80132600();
void fn_80093F64(void *g);
int fn_80431DDC(void *g);
int fn_80432DCC(void *g);
void fn_80094E04(void *g);
float fn_80426A84(void *g);
void fn_800A6E58(void *scene, float v);
void fn_80052924();
void fn_8003E5C4();
void fn_80094F98(void *g);
void fn_80094ED0(void *g);
void fn_8007C910();
int fn_80095B24(void *g);
int fn_80095B74(void *g);
void *fn_800945B0(void *g);
void *fn_804328E0(void *g);
void *fn_80094630(void *g);
void fn_80024044(void *scene, void *v);
void fn_8003FDE4(void *v);
void fn_8021A1B8();
void fn_8003CB08(void *v);
void fn_8001B3C4();
void fn_8021A1D4();
void fn_8002EA24(void *p);
void fn_8001B3F4();
void fn_80132838();
void fn_8003EC38();
void fn_8012557C(int v);
}

struct GameFlow {
    char pad[0x2A0];
    void SetCommand(int cmd);
};

struct FrameCtx {
    char pad0[0x5C];
    int f5C; // +0x5C
    char pad60[8];
    unsigned int f68; // +0x68
    int f6C; // +0x6C
    unsigned int f70; // +0x70
    char name[0x20]; // +0x74
    char name2[0x20]; // +0x94
    int fB4; // +0xB4
    char padB8[0x40];
    int fF8; // +0xF8
    char padFC[4];
    int f100; // +0x100
    char pad104[0x114];
    int f218; // +0x218
    char pad21C[0x88];
    char b2a4[0x80]; // +0x2A4
    int f324; // +0x324
};

extern char lbl_80552110[];
extern GameFlow lbl_80552920;
extern char lbl_80593BE8[];
extern char lbl_8052F060[];
extern int lbl_8066B6CC;

extern "C" void fn_8002E2C0(register FrameCtx *self)
{
    switch (self->f6C) {
    case 0:
        if (!(self->f70 & 0x2000)) {
            self->f6C = 4;
        } else {
            self->f6C = 0;
            fn_8002CA58(self);
        }
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
    case 5:
        if (fn_804329E0(self)) {
            fn_8002CD84(self, self->f70);
        }
        self->f6C = 0;
        fn_8002CB7C(self, self->name, self->name2, self->fB4, self->f70);
        self->f70 &= ~0x10000;
        if (self->fF8) {
            fn_800949FC(lbl_80552110, 0);
            self->fF8 = 0;
        }
        break;
    case 6:
        break;
    case 7:
        break;
    }
}

extern "C" void fn_8002E3EC(register FrameCtx *self)
{
    if (fn_80430050(self)) {
        if (fn_80432924(lbl_80552110)) {
            void *node = fn_800B3A74(fn_80430050(self), self->f100, 1, 0);
            if (node) {
                fn_800AF800(fn_80432924(lbl_80552110), fn_80430050(self), node, 0);
            }
        }
    }
}

extern "C" int fn_8002E4B4(register FrameCtx *self, int v)
{
    self->f218 = v;
    self->f5C = 1;
    return 1;
}

extern "C" int fn_8002E4F8(register FrameCtx *self)
{
    if (fn_80432A8C(self)) {
        fn_8002CA58(self);
    }
    lbl_80552920.SetCommand(1);
    fn_8002F884(self, 2);
    return 1;
}

extern "C" int fn_8002E570(register FrameCtx *self, int v)
{
    int r = 1;
    r = 0;
    return r;
}

extern "C" int fn_8002E5B0(register FrameCtx *self, const char *name, int v)
{
    strncpy(self->b2a4, name, 0x80);
    self->b2a4[0x7F] = 0;
    self->f324 = v;
    self->f5C = 3;
    return 1;
}

extern "C" int fn_8002E61C(register FrameCtx *self, const char *name, int v)
{
    fn_80052C88(fn_80052974(), name, v);
    return 1;
}

extern "C" void fn_8002E674(register FrameCtx *self)
{
    self->f5C = 4;
}

extern "C" void fn_8002E69C(register FrameCtx *self)
{
    fn_80053160(fn_80052974());
}

struct Scene {
    char pad[0x120];
    void *f120; // +0x120
};

extern "C" void fn_8002E6DC(register FrameCtx *self)
{
    fn_80132600();
    fn_80093F64(lbl_80552110);
    if (!fn_80431DDC(&lbl_80552920) && !fn_80432DCC(&lbl_80552920)) {
        fn_80094E04(lbl_80552110);
    }
    if (((Scene *)fn_80430050(self))->f120) {
        register Scene *scene = (Scene *)fn_80430050(self);
        fn_800A6E58(scene->f120, fn_80426A84(lbl_80593BE8));
    }
    fn_80052924();
    fn_8003E5C4();
    if (fn_80431DDC(&lbl_80552920) || fn_80432DCC(&lbl_80552920)) {
        fn_80094F98(lbl_80552110);
    } else {
        fn_80094ED0(lbl_80552110);
    }
    fn_8007C910();
}

extern "C" void fn_8002E7F4(register FrameCtx *self)
{
    int ok = 1;
    if (fn_80095B24(lbl_80552110)) {
        if (fn_800945B0(lbl_80552110) != fn_804328E0(lbl_80552110)) {
            ok = 0;
        }
    }
    if (fn_80095B74(lbl_80552110)) {
        if (fn_800945B0(lbl_80552110) != fn_804328E0(lbl_80552110)) {
            ok = 0;
        }
    }
    if (ok) {
        register void *scene = fn_80430050(self);
        fn_80024044(scene, fn_80094630(lbl_80552110));
    }
    fn_8003FDE4(fn_80094630(lbl_80552110));
    fn_8021A1B8();
    fn_8003CB08(fn_80094630(lbl_80552110));
    fn_8001B3C4();
    fn_8021A1D4();
    fn_8021A1B8();
    if (self->f68 & 0x10) {
        fn_8002EA24(lbl_8052F060);
    }
    fn_8001B3F4();
    fn_80132838();
    fn_8003EC38();
    fn_8021A1D4();
}

extern "C" void fn_8002E95C(register FrameCtx *self)
{
}

extern "C" void fn_8002E97C(register FrameCtx *self)
{
    fn_8012557C(lbl_8066B6CC);
}
