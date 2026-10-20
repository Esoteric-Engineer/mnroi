// Vector3 and matrix helpers (guessed layouts). The 0.0f/1.0f pool is read through extern_pool.

extern double __ieee754_sqrt(double x);

float fn_804340B8(register float *self, register float *v)
{
    float len = __ieee754_sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    if (len != 0.0f) {
        float inv = 1.0f / len;
        self[0] = inv * v[0];
        self[1] = inv * v[1];
        self[2] = inv * v[2];
    } else {
        self[0] = 1.0f;
        self[1] = 0.0f;
        self[2] = 0.0f;
    }
    return len;
}

float fn_804341BC(register float *a, register float *b)
{
    return (a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]) + (a[2] - b[2]) * (a[2] - b[2]);
}

extern void fn_8042DC84(void *dst, void *src);
extern void fn_8042FE08(void *self, void *dst, float s);

void fn_80434244(register void *self, register void *a, register void *b, register void *c, register void *d, register float s)
{
    float t = s;
    fn_8042DC84(self, d);
    fn_8042FE08(self, c, t);
    t = t * t;
    fn_8042FE08(self, b, t);
    t = t * s;
    fn_8042FE08(self, a, t);
}

extern void fn_8042DD30(void *dst, void *src);

void fn_804342EC(register void *self, register void *src)
{
    fn_8042DD30(self, src);
}

void fn_8043432C(register char *self, register float *v)
{
    *(float *)(self + 0x30) = v[0];
    *(float *)(self + 0x34) = v[1];
    *(float *)(self + 0x38) = v[2];
}

void fn_80434368(register float *out, register float *v, register float *m)
{
    out[0] = m[0] * v[0] + m[4] * v[1] + m[8] * v[2];
    out[1] = m[1] * v[0] + m[5] * v[1] + m[9] * v[2];
    out[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2];
}
