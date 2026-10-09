// FrameCtx level-load request (guessed): checks the level's .ngl exists, then records name and flags; see docs/versus.md section 5, row 9d.

inline int sn_return_decl(int a) { return a; }

extern "C" {
char *strncpy(char *dst, const char *src, unsigned n);
void fn_801B4094(char *path, const char *ext);
void *fn_801A8368(const char *path, const char *mode, int flags);
void fn_801A875C(void *file);
extern const char lbl_8048584C[]; // "ngl"
extern const char lbl_80485884[]; // "rb"
}

struct FrameCtx
{
    char pad0[0x5C];
    int f5C;         // +0x5C
    char pad60[0xC];
    int f6C;         // +0x6C
    unsigned int f70; // +0x70
    char name[0x20]; // +0x74
    char pad94[0x20];
    int fB4;         // +0xB4
    char b8[0x20];   // +0xB8
    char d8[0x20];   // +0xD8
};

extern "C" void fn_8002D7A8(register FrameCtx *self, const char *name, unsigned int flags, int v, const char *name2, const char *name3)
{
    void *file;
    char path[0x20];
    strncpy(path, name, 0x20);
    fn_801B4094(path, lbl_8048584C);
    file = fn_801A8368(path, lbl_80485884, 3);
    if (!file) {
        return;
    }
    fn_801A875C(file);
    self->f70 = flags;
    self->fB4 = v;
    if (name) {
        strncpy(self->name, name, 0x20);
        self->name[0x1F] = 0;
    } else {
        self->f70 |= 0x2000;
    }
    if (name2) {
        strncpy(self->b8, name2, 0x20);
        self->b8[0x1F] = 0;
        self->f70 |= 0x4000;
    }
    if (name3) {
        strncpy(self->d8, name3, 0x20);
        self->d8[0x1F] = 0;
        self->f70 |= 0x8000;
    }
    self->f6C = 0;
    self->f5C = 0x10;
}
