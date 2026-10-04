// Applies (2*a.w^2 - 1, 2*dot(a.xyz, b.xyz), 2*a.w) to self from two 4-vectors a and b.
extern const float lbl_8048CD2C[]; // 1.0f

typedef struct
{
    float v[4];
} Vec4;

extern float *fn_804352C8(void *v, int i);
extern void fn_80434988(Vec4 *self);
extern void *fn_8043BBD0(void *v);
extern void fn_80434A18(Vec4 *out, void *a, void *b);
extern void fn_8043B9EC(void *self, float s, void *v);
extern void fn_804364BC(void *self, float s, void *v);

void fn_804467B0(register void *self, register void *a, register void *b)
{
    float s8;
    float sc;
    float s10;
    Vec4 tmp;

    s8 = 2.0f * *fn_804352C8(a, 3) * *fn_804352C8(a, 3) - lbl_8048CD2C[0];
    sc = 2.0f * (*fn_804352C8(a, 0) * *fn_804352C8(b, 0) + *fn_804352C8(a, 1) * *fn_804352C8(b, 1) +
                 *fn_804352C8(a, 2) * *fn_804352C8(b, 2));
    s10 = 2.0f * *fn_804352C8(a, 3);
    fn_80434988(&tmp);
    fn_80434A18(&tmp, fn_8043BBD0(a), b);
    fn_8043B9EC(self, s8, b);
    fn_804364BC(self, sc, fn_8043BBD0(a));
    fn_804364BC(self, s10, &tmp);
}
