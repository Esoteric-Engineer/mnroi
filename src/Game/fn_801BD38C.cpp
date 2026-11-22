// Quaternion from Euler angles in degrees, and a vector rotated by a quaternion (docs/core.md row 17).

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

struct Quat {
    float w, x, y, z;
};

inline int sn_return_decl(int a) { return a; }

extern "C" {
void fn_8042A7D8(float deg, float *s, float *c);
Vec4 fn_801BD1C0(const Vec4 &a, const Vec4 &b);
}

extern "C" Vec4 fn_801BD38C(const Vector *angles)
{
    float s;
    float c;

    fn_8042A7D8(angles->x / 2.0f, &s, &c);
    Vec4 qx(c, 0.0f, -s, 0.0f);
    fn_8042A7D8(angles->y / 2.0f, &s, &c);
    Vec4 qy(c, 0.0f, 0.0f, -s);
    fn_8042A7D8(angles->z / 2.0f, &s, &c);
    Vec4 qz(c, -s, 0.0f, 0.0f);
    Vec4 r = fn_801BD1C0(fn_801BD1C0(qz, qy), qx);
    return r;
}

extern "C" Vector fn_801BD530(const Vector &v, const Quat &q)
{
    float a = q.w * v.x + q.x * v.y - q.z * v.z;
    float b = -q.x * v.x + q.w * v.y + q.y * v.z;
    float c = q.z * v.x - q.y * v.y + q.w * v.z;
    float d = q.y * v.x + q.z * v.y + q.x * v.z;
    float rx = a * q.w + b * q.x - c * q.z + d * q.y;
    float ry = -a * q.x + b * q.w + c * q.y + d * q.z;
    float rz = a * q.z - b * q.y + c * q.w + d * q.x;
    float eps = 0.001f;
    return Vector(rx, ry, rz, 1.0f);
}
