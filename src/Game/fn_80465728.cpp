// Blends two rotations.

class Vec4
{
public:
    float x, y, z, w;
    Vec4 &normalize() __asm__("fn_801BCE6C");
    Vec4 &operator*=(float s) __asm__("fn_801BD0CC");
};

inline int sn_return_decl(int a) { return a; }

extern "C" {
float fn_801BD138(const Vec4 &a, const Vec4 &b);
Vec4 fn_80465EF0(Vec4 a, const Vec4 &b);   // a - b
Vec4 fn_80465DF8(float s, Vec4 v);         // s * v
Vec4 fn_80465E78(Vec4 a, const Vec4 &b);   // a + b

Vec4 fn_80465728(register Vec4 a, register const Vec4 &b, register float t)
{
    float d = fn_801BD138(a, b);
    const float limit = -0.7f;
    if (d < limit)
        a *= -1.0f;
    Vec4 r = fn_80465E78(a, fn_80465DF8(t, fn_80465EF0(b, a)));
    r.normalize();
    return r;
}
}
