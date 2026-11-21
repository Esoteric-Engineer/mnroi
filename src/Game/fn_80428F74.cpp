// Vector's constructor (w = 1) and its x, y, z setter (docs/core.md row 1).

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

Vector::Vector()
{
    w = 1.0f;
}

extern "C" void fn_80428FA8(register Vector *v, register float x, register float y, register float z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}
