// Rolls a random 0..1 value and sets flag 0x80 (< 0.33) or 0x100 (< 0.66) on `self`, then hands PLAYER field 220 (a string) to fn_80057894 with the flags.
// Owns .rodata 0x8048A460-0x8048A478; the trailing 0.0f is read by the unclaimed fn_800968EC.

typedef struct GState
{
    char pad[0x7B8];
    void *cur; // +0x7B8
} GState;

typedef struct Actor
{
    char pad0[0x28];
    void *owner; // +0x28
    char pad1[0x74 - 0x2C];
    unsigned flags; // +0x74
} Actor;

extern GState lbl_80552110;
extern int fn_80171F8C(void);
extern int fn_800ACD20(void *actor, int id);
extern void fn_80057894(int a, int b);

void fn_800965A4(register Actor *self)
{
    float r;

    self->flags = 0x202010;
    r = fn_80171F8C() * 4.656613e-10f;
    if (r < 0.33f) {
        self->flags |= 0x80;
    } else if (r < 0.66f) {
        self->flags |= 0x100;
    }
    fn_80057894(fn_800ACD20(self->owner, 220), self->flags);
    lbl_80552110.cur = self;
}

const float lbl_8048A474 __attribute__((section(".rodata"))) = 0.0f; // pads the .rodata claim to 8 bytes; read by the unclaimed fn_800968EC
