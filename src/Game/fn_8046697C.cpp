// The frame clock's inline functions (docs/core.md row 18; the clock is section 4.8).

inline int sn_return_decl(int a) { return a; }

struct Clock {
    char pad[0x8];
    int ms;
    char pad2[0x2C];
    float scale;
    int pause;
};

extern "C" {
void fn_8046697C(register Clock *self, register int ms)
{
    self->ms = ms;
}

float fn_804669A4(register Clock *self)
{
    return self->scale;
}

int fn_804669D0(register Clock *self)
{
    return self->pause > 0;
}
}
