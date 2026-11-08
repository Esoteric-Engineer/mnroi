// Sets bit 0 of +0x294 (returns 0 if it was already set), plays voice event 1, spawns the group's clip players, then plays motion 0xC0 or starts the attached effect.

inline int sn_return_decl(int a) { return a; }

struct Actor {
    char pad0[0x2C];
    unsigned int flags; // +0x2C
    char pad30[0x170];
    int f1A0; // +0x1A0
    int f1A4; // +0x1A4
    char pad1A8[0xEC];
    unsigned int f294; // +0x294
};

extern int lbl_8066B9FC;
extern char lbl_805724F0[];

extern "C" {
int fn_800A3F14(void *self);
int fn_800A3F74(void *self);
int fn_800A3FA4(void *self);
unsigned int fn_8009ABC0(void *self);
int fn_8009ABEC(void *self);
int fn_8010CDCC(void *self, int event, void *target, int a3, int a4, int a5, int a6);
int fn_800B21A4(void *self);
void fn_80098710(void *self, void *other, float f, void *a, void *v);
int fn_80097CE8(void *self, int motion, int a, float speed, int c, float blend, float e);
void fn_8009A778(void *self);
int fn_800B10D8(void *self);
void fn_800AFFD4(void *self, int on);
void fn_800AE398(void *self, int a, int b);
void fn_80428EEC(void *x, int on);
void fn_8007E9F4(void *self, void *other, int a, int b, float f);

int fn_800A3588(register Actor *self, void *other, float f, void *a, void *v, float g)
{
    int saved = lbl_8066B9FC;

    if (fn_800A3F14(self)) {
        return 0;
    }

    self->f294 |= 1;
    fn_8010CDCC(self, 1, 0, fn_8009ABC0(self), 10, 0, 0);
    self->flags &= ~0x40;

    if (fn_800B21A4(self)) {
        fn_80098710(self, other, g, a, v);
    }

    if (fn_800A3F74(self)) {
        fn_80097CE8(self, 0xC0, 0, 30.0f, 0, 7.5f, -1.0f);
    } else if (!(self->f1A0 == 0 && self->f1A4 == 0)) {
        if (self->f294 & 0x100) {
            fn_8009A778(self);
            self->f1A0 = 0;
            self->f1A4 = 0;
        } else if (fn_800B10D8(self)) {
            fn_8009A778(self);
            fn_800AFFD4(self, 1);
        } else {
            fn_800AE398(self, 0, 0);
        }
    } else if (fn_800A3FA4(self)) {
        if (fn_800B10D8(self)) {
            fn_8009A778(self);
            fn_800AFFD4(self, 1);
        } else {
            fn_800AE398(self, 0, 0);
        }
    } else {
        fn_80097CE8(self, 0xC0, 0, 30.0f, 0, 7.5f, -1.0f);
    }

    if (fn_8009ABEC(self)) {
        fn_80428EEC(lbl_805724F0, fn_8009ABEC(self));
    }

    if (!fn_800A3F74(self)) {
        fn_8007E9F4(self, other, 0, 0, f);
    }

    return 1;
}
}
