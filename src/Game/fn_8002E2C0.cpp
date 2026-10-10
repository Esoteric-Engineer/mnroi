// FrameCtx deferred level-request step (guessed), switch on +0x6C; see docs/versus.md section 5, row 9d.

extern "C" {
int fn_8002CA58(void *self);
int fn_804329E0(void *self);
int fn_8002CD84(void *self, int v);
void fn_8002CB7C(void *self, const char *a, const char *b, int c, int d);
void fn_800949FC(void *g, int v);
}

struct FrameCtx {
    char pad0[0x6C];
    int f6C; // +0x6C
    unsigned int f70; // +0x70
    char name[0x20]; // +0x74
    char name2[0x20]; // +0x94
    int fB4; // +0xB4
    char padB8[0x40];
    int fF8; // +0xF8
};

extern char lbl_80552110[];

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
