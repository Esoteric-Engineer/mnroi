// Degree trigonometry: power, angle wraps and differences, table sine, series arcsine and arctangent, angle stepping (docs/core.md row 17).

struct Vector
{
    float x, y, z, w;
};

#define LERP(a, b, t) ((a) + ((b) - (a)) * (t))

inline int sn_return_decl(int a) { return a; }

extern "C" {
double __ieee754_sqrt(double x);
double fn_8016CBDC(double x);
float fn_8042CE28(int x);
float *fn_8042FB28(Vector *v);
float *fn_804304CC(Vector *v);
float fn_8042EBF4(Vector *a, Vector *b);
void fn_80429090(Vector *out, Vector *a, Vector *b, float s);
extern float lbl_804D3A24[];

float fn_801BD9C4(float x, int n)
{
    int i;
    float r = x;

    for (i = 0; i < n - 1; i++)
        r *= x;
    return r;
}

float fn_801BDA3C(float a)
{
    float n;
    float k;
    float r;

    if (a < 0.0f) {
        n = -a;
        if (n < 360.0f) {
            r = 360.0f - n;
        } else {
            k = fn_8016CBDC(n * 0.0027777778f);
            r = 360.0f - (n - k * 360.0f);
        }
    } else {
        if (a < 360.0f) {
            return a;
        }
        k = fn_8016CBDC(a * 0.0027777778f);
        r = a - k * 360.0f;
    }
    if (r == 360.0f) {
        r = 0.0f;
    }
    return r;
}

float fn_801BDB9C(float a)
{
    float r = fn_801BDA3C(a);
    if (r > 180.0f) {
        r = -(360.0f - r);
    }
    return r;
}

void fn_801BDC14(Vector *v)
{
    while (fn_8042FB28(v)[0] > 180.0f)
        fn_8042FB28(v)[0] -= 360.0f;
    while (fn_8042FB28(v)[0] < -180.0f)
        fn_8042FB28(v)[0] += 360.0f;
    while (fn_8042FB28(v)[1] > 180.0f)
        fn_8042FB28(v)[1] -= 360.0f;
    while (fn_8042FB28(v)[1] < -180.0f)
        fn_8042FB28(v)[1] += 360.0f;
    while (fn_8042FB28(v)[2] > 180.0f)
        fn_8042FB28(v)[2] -= 360.0f;
    while (fn_8042FB28(v)[2] < -180.0f)
        fn_8042FB28(v)[2] += 360.0f;
}

float fn_801BDE20(float a, float b)
{
    float d = fn_801BDA3C(b) - fn_801BDA3C(a);

    if (d < 0.0f) {
        if (d >= -180.0f) {
            return d;
        } else {
            return d + 360.0f;
        }
    } else {
        if (d <= 180.0f) {
            return d;
        } else {
            return -(360.0f - d);
        }
    }
}

void fn_801BDF18(Vector *out, Vector *a, Vector *b)
{
    fn_8042FB28(out)[0] = fn_801BDE20(fn_804304CC(a)[0], fn_804304CC(b)[0]);
    fn_8042FB28(out)[2] = fn_801BDE20(fn_804304CC(a)[2], fn_804304CC(b)[2]);
    fn_8042FB28(out)[1] = fn_801BDE20(fn_804304CC(a)[1], fn_804304CC(b)[1]);
}

float fn_801BE004(float a)
{
    int q;
    float r;
    int i;
    int j;
    float f;
    float t;
    float s0;
    float s1;

    a = fn_801BDA3C(a);
    if (a < 90.0f) {
        q = 0;
    } else if (a < 180.0f) {
        q = 1;
    } else if (a < 270.0f) {
        q = 2;
    } else {
        q = 3;
    }
    f = a * 45.511112f;
    i = f;
    t = f - fn_8042CE28(i);
    j = i + 1;
    switch (q) {
    case 0:
        s0 = lbl_804D3A24[i];
        if (j == 0x1000) {
            r = LERP(s0, -s0, t);
            break;
        }
        s1 = lbl_804D3A24[j];
        r = LERP(s0, s1, t);
        break;
    case 1:
        s0 = -lbl_804D3A24[0x1FFF - i];
        if (j == 0x2000) {
            r = LERP(s0, -s0, t);
            break;
        }
        s1 = -lbl_804D3A24[0x1FFF - j];
        r = LERP(s0, s1, t);
        break;
    case 2:
        s0 = lbl_804D3A24[i - 0x2000];
        if (j == 0x3000) {
            r = LERP(s0, -s0, t);
            break;
        }
        s1 = lbl_804D3A24[j - 0x2000];
        r = LERP(s0, s1, t);
        break;
    case 3:
        s0 = -lbl_804D3A24[0x3FFF - i];
        if (j == 0x4000) {
            r = LERP(s0, -s0, t);
            break;
        }
        s1 = lbl_804D3A24[j - 0x4000];
        s1 = -lbl_804D3A24[0x3FFF - j];
        r = LERP(s0, s1, t);
        break;
    }
    return r;
}
}

__asm__(".section .rodata\n"
        "\t.long 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068\n"
        "\t.long 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068\n"
        "\t.text"); // 0x8049EB70-0x8049EBA4, pools with no code

extern "C" float fn_801BE3C4(float x)
{
    float r;
    int neg = x < 0.0f;

    x = x < 0.0f ? -x : x;
    if (x > 0.70710677f)
    {
        x = __ieee754_sqrt(1.0f - x * x);
        r = 90.0f - (fn_801BD9C4(x, 3) / 6.0f + x + fn_801BD9C4(x, 5) * 0.075f + fn_801BD9C4(x, 7) * 0.066797f) * 57.295784f;
    }
    else
    {
        r = (fn_801BD9C4(x, 3) / 6.0f + x + fn_801BD9C4(x, 5) * 0.075f + fn_801BD9C4(x, 7) * 0.066797f) * 57.295784f;
    }
    if (neg)
        return -r;
    else
        return r;
}

__asm__(".section .rodata\n"
        "\t.long 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068\n"
        "\t.long 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068\n"
        "\t.long 0x6F727068, 0x6F727068\n"
        "\t.text"); // 0x8049EBC4-0x8049EC0C, pools with no code

extern "C" float fn_801BE5A8(float y, float x, int signedResult)
{
    float r;
    int xneg;
    int yneg;
    float t;

    if (x == 0.0f && y == 0.0f) {
        return 0.0f;
    }
    yneg = y < 0.0f;
    y = y < 0.0f ? -y : y;
    xneg = x < 0.0f;
    x = x < 0.0f ? -x : x;
    if (x > y) {
        t = y / x;
    } else {
        t = x / y;
    }
    t = t < 0.0f ? -t : t;
    r = (t - fn_801BD9C4(t, 3) / 3.0f + fn_801BD9C4(t, 5) / 5.0f - fn_801BD9C4(t, 7) / 7.0f + fn_801BD9C4(t, 9) * 0.063235f) * 57.295784f;
    if (y >= x) {
        r = 90.0f - r;
    }
    if (signedResult) {
        if (!yneg && xneg) {
            r = -r;
        }
    } else {
        r = 90.0f - r;
        if (yneg) {
            r = 180.0f - r;
        }
        if (!xneg) {
            r = -r;
        }
    }
    return r;
}

extern "C" float fn_801BE840(float a, float target, float step)
{
    float cur = fn_801BDA3C(a);
    float d = fn_801BDE20(cur, target);

    cur = cur < cur + d ? (cur + step > cur + d ? cur + d : cur + step)
                        : (cur - step < cur + d ? cur + d : cur - step);
    return fn_801BDA3C(cur);
}

__asm__(".section .rodata\n"
        "\t.long 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068\n"
        "\t.long 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068\n"
        "\t.long 0x6F727068, 0x6F727068, 0x6F727068\n"
        "\t.text"); // 0x8049EC2C-0x8049EC78, pools with no code

extern "C" void fn_801BE948(Vector *v, Vector *out)
{
    out->y = 0.0f;
    out->x = fn_801BE3C4(v->z);
    out->z = fn_801BE5A8(v->y, v->x, 0);
}

extern "C" void fn_801BE9C8(Vector *out, Vector *v, Vector *n)
{
    float s = fn_8042EBF4(n, v) * -2.0f;
    fn_80429090(out, n, v, s);
}
