// Rotates a vector by a quaternion: q v q*, with q in the order (w, x, y, z).

class Vector
{
public:
    float x, y, z, w;
    Vector(float x, float y, float z, float w) __asm__("fn_8042D768");
};

struct Vec4 {
    float w, x, y, z;
};

inline int sn_return_decl(int a) { return a; }

extern "C" Vector fn_801BD530(const Vector &v, const Vec4 &q)
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
