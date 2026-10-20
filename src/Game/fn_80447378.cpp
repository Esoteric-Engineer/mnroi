// Scales the first two floats of a vec in place; the first pair-carrying function after fn_80446DE8.c.
struct Vec2
{
    float x, y;
};

extern "C" void fn_80447378(register Vec2 *self, register float s)
{
    self->x *= s;
    self->y *= s;
}
