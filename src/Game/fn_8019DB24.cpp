// Sets an animation channel's time and clears its per-track state, when it has any.

struct Channel {
    char pad0[0x4];
    float time;       // +0x04
    char pad8[0x14];
    int active;       // +0x1C
    void *state;      // +0x20, count ints
    unsigned count;   // +0x24
};

extern "C" {
void *memset(void *dst, int value, unsigned n);

void fn_8019DB24(register Channel *self, float time)
{
    self->time = time;
    if (self->active == 0) {
        return;
    }
    memset(self->state, 0, self->count * 4);
}
}
