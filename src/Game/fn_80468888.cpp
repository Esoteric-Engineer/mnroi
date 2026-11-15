// A quaternion's float constructor and squared length.

struct Vec4 {
    float x, y, z, w;
};

inline int sn_return_decl(int a) { return a; }

extern "C" {
Vec4 *fn_80468888(register Vec4 *self, register float a, register float b, register float c, register float d)
{
    self->x = a;
    self->y = b;
    self->z = c;
    self->w = d;
    return self;
}

float fn_804688D0(register Vec4 *self)
{
    return self->x * self->x + self->y * self->y + self->z * self->z + self->w * self->w;
}
}
