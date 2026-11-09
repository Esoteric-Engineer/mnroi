// Unpacks four shorts to a quaternion (14 fraction bits), and the by-value quaternion operators.

class Vec4
{
public:
    float x, y, z, w;
    Vec4();
    Vec4 &operator+=(const Vec4 &b) __asm__("fn_801BCFD4");
    Vec4 &operator-=(const Vec4 &b) __asm__("fn_801BD050");
    Vec4 &operator*=(float s) __asm__("fn_801BD0CC");
};

struct Packed {
    short v[4];
};

inline int sn_return_decl(int a) { return a; }

extern "C" {
Vec4 fn_80465C9C(register Packed *self)
{
    Vec4 q;
    q.x = self->v[0] / 16384.0f;
    q.y = self->v[1] / 16384.0f;
    q.z = self->v[2] / 16384.0f;
    q.w = self->v[3] / 16384.0f;
    return q;
}

Vec4 fn_80465DF8(register float s, register Vec4 v)
{
    return v *= s;
}

Vec4 fn_80465E78(register Vec4 a, register const Vec4 &b)
{
    return a += b;
}

Vec4 fn_80465EF0(register Vec4 a, register const Vec4 &b)
{
    return a -= b;
}
}
