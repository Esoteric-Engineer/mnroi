// Trajectory solves: launch speed, the two launch angles, and the time to reach a height (docs/core.md row 17).

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

inline int sn_return_decl(int a) { return a; }

extern "C" {
double __ieee754_sqrt(double x);
float fn_80441B0C(Vector *a, Vector *b);
void fn_8042A7D8(float deg, float *s, float *c);
float *fn_8042FB28(Vector *v);
float fn_801BE5A8(float y, float x, int deg);
float fn_801BDB9C(float v);

int fn_801BC9DC(Vector *from, Vector *to, float angle, float g, float *speed)
{
    float d = fn_80441B0C(to, from);
    float h = to->z - from->z;
    float s;
    float c;
    float t;

    fn_8042A7D8(angle, &s, &c);
    t = g * 0.5f * d / (c * s) * (1.0f / (1.0f - h * c / (d * s)));
    if (t < 0.0f) {
        return 0;
    }
    {
        register float *p = speed;
        *p = __ieee754_sqrt(t);
    }
    return 1;
}

int fn_801BCB08(Vector *from, Vector *to, float v, float g, float *lo, float *hi)
{
    float d = fn_80441B0C(to, from);
    float h = to->z - from->z;
    float d2 = d * d;
    float v2 = v * v;
    float ng = -g;
    float disc = d2 - ng * ng * d2 * d2 / (v2 * v2) + 2.0f * ng * d2 * h / v2;
    float r;
    float a;
    float den;
    float b;

    if (disc < 0.0f) {
        return 0;
    }
    r = __ieee754_sqrt(disc);
    a = v2 * (-d + r);
    den = ng * d2;
    *lo = fn_801BDB9C(fn_801BE5A8(a, den, 1));
    b = v2 * (-d - r);
    *hi = fn_801BDB9C(fn_801BE5A8(b, den, 1));
    return 1;
}

float fn_801BCCE0(float x, Vector *o, float y)
{
    float a = fn_8042FB28(o)[2];
    float b = fn_8042FB28(o)[1];
    float c = fn_8042FB28(o)[0] - x / y;
    float disc;

    if (a == 0.0f) {
        return -c / b;
    } else {
        disc = b * b - a * 4.0f * c;
        if (disc < 0.0f) {
            return 50.0f;
        } else {
            disc = __ieee754_sqrt(disc);
            if (disc > b) {
                return (-b + disc) / (2.0f * a);
            } else {
                return (-b - disc) / (2.0f * a);
            }
        }
    }
}
}
