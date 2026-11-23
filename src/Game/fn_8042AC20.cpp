// A 2D position with a changed flag (docs/core.md row 19). Names are guesses.

struct Pos2
{
    float x;
    float y;
    int value;
    char pad[0x10];
    int changed;
};

extern "C" void fn_8042AC20(register Pos2 *self, register float x, register float y)
{
    if (self->x != x || self->y != y) {
        self->x = x;
        self->y = y;
        self->changed = 1;
    }
}

extern "C" void fn_8042AC7C(register Pos2 *self, register int value)
{
    if (value != self->value) {
        self->value = value;
    }
    self->changed = 1;
}

extern "C" Pos2 *fn_8042ACC0(register Pos2 *self, register float x, register float y)
{
    self->x = x;
    self->y = y;
    return self;
}
