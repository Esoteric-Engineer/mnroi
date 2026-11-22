// A vector packed into three u16 components and a scale of 0x8000 over its largest one (docs/core.md row 17).

struct Vector
{
    float x, y, z, w;
};

struct Packed
{
    unsigned short x, y, z, s;
};

inline int sn_return_decl(int a) { return a; }

extern "C" {
float fabsf(float x);
float fn_80468934(float a, float b);
}

extern "C" Packed fn_801BD7B4(const Vector *v)
{
    Packed p;
    const float m = fn_80468934(fn_80468934(fabsf(v->x), fabsf(v->y)), fabsf(v->z));
    const float eps = 0.0001f;

    if (m < eps) {
        p.x = p.y = p.z = 0;
        p.s = 1;
    } else {
        if (m <= 1.0f) {
            p.s = 0x8000;
        } else {
            p.s = 32768.0f / m;
        }
        p.x = v->x * (unsigned int)p.s;
        p.y = v->y * (unsigned int)p.s;
        p.z = v->z * (unsigned int)p.s;
    }
    return p;
}
