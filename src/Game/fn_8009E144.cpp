// Starts a timed state on an actor from its tuning field 195 (PLAYER, int). Row 20 of docs/versus.md.

inline int sn_return_decl(int a) { return a; }

struct GState {
    char pad0[0x768];
    int f768; // +0x768
};

struct Actor {
    char pad0[0x2FC];
    void *f2FC;
    char pad1[4];
    unsigned int flags; // +0x304
    char pad2[0x2C];
    float f334;
    int f338;
};

extern char lbl_80593BE8[];
extern char lbl_805720E8[];
extern GState lbl_80552110;

extern "C" {
unsigned int fn_8042EFF8(void *g);
int fn_800B18EC(void *self, int id);
int fn_8043B31C(void *p);
void fn_8042D1E8(void *p, int a, int b);
int fn_80085D3C(void *actor);
}

extern "C" void fn_8009E144(register Actor *self)
{
    self->f334 = (unsigned int)(fn_8042EFF8(lbl_80593BE8) + fn_800B18EC(self, 0xC3));
    self->f338 = lbl_80552110.f768;
    self->flags |= 0x2000;
    if (self->f2FC != 0)
        fn_8042D1E8(lbl_805720E8, fn_8043B31C(self->f2FC), 1);
    else if (fn_80085D3C(self) != 0)
        fn_8042D1E8(lbl_805720E8, 1, 1);
}
