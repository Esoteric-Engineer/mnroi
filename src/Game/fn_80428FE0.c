/* Vector helpers on x, y and z: add, subtract, add scaled, distance. */

void fn_80428FE0(register float *out, register float *a, register float *b)
{
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
}

void fn_80429038(register float *out, register float *a, register float *b)
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
}

void fn_80429090(register float *out, register float *a, register float *b, register float s)
{
    out[0] = s * b[0] + a[0];
    out[1] = s * b[1] + a[1];
    out[2] = s * b[2] + a[2];
}

extern double __ieee754_sqrt(double x);

float fn_804290F8(register float *a, register float *b)
{
    return __ieee754_sqrt((a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1])
                          + (a[2] - b[2]) * (a[2] - b[2]));
}
