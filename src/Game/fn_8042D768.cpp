// Small value-class inlines (docs/core.md row 19).

inline int sn_return_decl(int a) { return a; }

struct Float4
{
    float x, y, z, w;
};

struct Float2
{
    float x, y;
};

struct Vector
{
    float x, y, z;
};

extern "C" Float4 *fn_8042D768(register Float4 *self, register float x, register float y, register float z,
                               register float w)
{
    self->x = x;
    self->y = y;
    self->z = z;
    self->w = w;
    return self;
}

extern "C" void *fn_8042D7B0(register void *self)
{
    return self;
}

extern "C" void fn_8042D7D8(register Float2 *dst, register const Float2 *src)
{
    dst->x = src->x;
    dst->y = src->y;
}

extern "C" void fn_8042D80C(register Vector *dst, register const Vector *src)
{
    dst->x = -src->x;
    dst->y = -src->y;
    dst->z = -src->z;
}
