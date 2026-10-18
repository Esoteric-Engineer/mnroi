// Starts a timed state on an actor, reading PLAYER tuning field 192 (int). Row 20 of docs/versus.md.

typedef struct Actor {
    char pad0[0x2FC];
    void *f2FC;
    char pad1[4];
    unsigned int flags; // +0x304
    char pad2[0x2C];
    float f334;
    int f338;
} Actor;

typedef struct GState {
    char pad0[0x768];
    int f768; // +0x768
} GState;

extern char lbl_80593BE8[];
extern char lbl_8057210C[];
extern GState lbl_80552110;

extern void *fn_80085954(void *actor);
extern void fn_800CD67C(void *p, int a);
extern unsigned int fn_8042EFF8(void *g);
extern int fn_800B18EC(void *self, int id);
extern void fn_80216E48(int a);
extern int fn_8043B31C(void *p);
extern void fn_8042D1E8(void *p, int a, int b);
extern int fn_80085D3C(void *actor);

void fn_8009DF60(register Actor *self, int arg)
{
    register void *p;

    self->flags |= 0x1000;
    self->flags &= ~0x2000;
    if (fn_80085954(self) != 0 && arg == 0) {
        p = fn_80085954(self);
        fn_800CD67C(p, 1);
    }
    self->f334 = (unsigned int)(fn_8042EFF8(lbl_80593BE8) + fn_800B18EC(self, 0xC0));
    self->f338 = lbl_80552110.f768;
    fn_80216E48(1);
    if (self->f2FC != 0)
        fn_8042D1E8(lbl_8057210C, fn_8043B31C(self->f2FC), 1);
    else if (fn_80085D3C(self) != 0)
        fn_8042D1E8(lbl_8057210C, 1, 1);
}
