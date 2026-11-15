// Quaternion operations. Components are in the order (w, x, y, z).

class Vector
{
public:
    float x, y, z, w;
    Vector(float x, float y, float z, float w) __asm__("fn_8042D768");
};

class Vec4
{
public:
    float x, y, z, w;
    Vec4(float a, float b, float c, float d) __asm__("fn_80468888");
};

inline int sn_return_decl(int a) { return a; }

extern "C" {
float __ieee754_sqrtf(float x);
float __ieee754_acosf(float x);
Vector fn_801BD530(const Vector &v, const Vec4 *q);
float fn_8042EBF4(const Vector *a, const Vector *b);
float fn_804688D0(Vec4 *self);
}

extern "C" Vec4 *fn_801BCE6C(register Vec4 *self)
{
    float len = __ieee754_sqrtf(fn_804688D0(self));
    if (len != 0.0f) {
        self->x /= len;
        self->y /= len;
        self->z /= len;
        self->w /= len;
    }
    return self;
}

extern "C" float fn_801BCF14(register Vec4 *q)
{
    Vector axis(1.0f, 0.0f, 0.0f, 0.0f);
    Vector r = fn_801BD530(axis, q);
    register float a = __ieee754_acosf(fn_8042EBF4(&axis, &r));
    return r.y < 0.0f ? a * -1.0f : a;
}

extern "C" Vec4 *fn_801BCFD4(register Vec4 *self, const Vec4 &b)
{
    self->x += b.x;
    self->y += b.y;
    self->z += b.z;
    self->w += b.w;
    return self;
}

extern "C" Vec4 *fn_801BD050(register Vec4 *self, const Vec4 &b)
{
    self->x -= b.x;
    self->y -= b.y;
    self->z -= b.z;
    self->w -= b.w;
    return self;
}

extern "C" Vec4 *fn_801BD0CC(register Vec4 *self, float s)
{
    self->x *= s;
    self->y *= s;
    self->z *= s;
    self->w *= s;
    return self;
}

extern "C" float fn_801BD138(const Vec4 &a, const Vec4 &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

extern "C" Vec4 fn_801BD1C0(const Vec4 &a, const Vec4 &b)
{
    return Vec4(a.x * b.x - a.y * b.y - a.z * b.z - a.w * b.w,
                a.x * b.y + a.w * b.z - a.z * b.w + a.y * b.x,
                a.x * b.z + a.y * b.w - a.w * b.y + a.z * b.x,
                a.x * b.w + a.z * b.y - a.y * b.z + a.w * b.x);
}
