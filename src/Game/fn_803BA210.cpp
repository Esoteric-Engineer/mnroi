// Effect end point setter (vtable slot 28).

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

struct Effect {
    char pad0[0x110];
    Vector end;         // +0x110
    char pad120[0x5C];
    unsigned int flags; // +0x17C
};

extern "C" {
int fn_8039D480(Effect *self);
void fn_8042DC84(Vector *dst, Vector *src);

void fn_803BA210(register Effect *self, Vector *pos, int z)
{
    if (!pos) {
        self->flags &= ~0x2000000;
    } else {
        if (fn_8039D480(self))
            return;
        fn_8042DC84(&self->end, pos);
        self->flags |= 0x2000000;
    }
}
}
