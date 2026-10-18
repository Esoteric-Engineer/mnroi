// Picks a random cutscene variant (0..2) for `self`, queues PLAYER field 173 + variant and marks it started; docs/versus.md row 20.
// Reads .rodata 0x8048A4C8 (its first literal) through extern_pool, the pool sits behind unclaimed code.

typedef struct GState
{
    char pad[0x7B8];
    void *cur; // +0x7B8
} GState;

typedef struct Actor
{
    char pad0[0x34];
    unsigned flags; // +0x34
    char pad1[0x6C - 0x38];
    unsigned variant; // +0x6C
    unsigned value; // +0x70
} Actor;

extern GState lbl_80552110;
extern int fn_80171F8C(void);
extern void *fn_8042FF2C(void *slot);
extern int fn_800ACD20(void *actor, int id);
extern void fn_80057894(int a, int b);

void fn_8009701C(register Actor *self)
{
    register void *actor;

    if ((self->flags & 0x10) || (self->flags & 0x40)) {
        return;
    }
    self->variant = (unsigned)(fn_80171F8C() * 4.656613e-10f * 3.0f);
    self->variant = self->variant > 2 ? 2 : self->variant;
    self->value = 0x42022000;
    actor = fn_8042FF2C(self);
    fn_80057894(fn_800ACD20(actor, self->variant + 173), self->value);
    self->flags |= 0x40;
    lbl_80552110.cur = self;
}
