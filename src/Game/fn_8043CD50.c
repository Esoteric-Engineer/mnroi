// Empty stub, a forwarder, a destructor and Vec3 helpers; the pool 0x80487728 is read through extern_pool (docs/versus.md, row 8).

extern void fn_8043DBC8(void *self, int a);
extern void fn_80441CDC(void *p, int inChrg);
extern void fn_8047ECD0(void *p, int inChrg);
extern void fn_80078324(void *p, int inChrg);
extern void fn_8043D9B0(void *p, int a);
extern void fn_8043DAEC(void *p);
extern double __ieee754_sqrt(double x);
extern char lbl_804F41A0[], lbl_804F41C0[], lbl_804F41D8[], lbl_804F41F8[], lbl_804F4218[];

void fn_8043CD50(register int a, register int b, register int c, register int d)
{
}

void fn_8043CD7C(register void *self, register int a)
{
    fn_8043DBC8(self, a);
}

void fn_8043CDBC(register char *self, register int inChrg)
{
    *(char **)(self + 0x8) = lbl_804F4218;
    *(char **)(self + 0xC) = lbl_804F41F8;
    *(char **)(self + 0x10) = lbl_804F41D8;
    *(char **)(self + 0x14) = lbl_804F41C0;
    *(char **)(self + 0x0) = lbl_804F41A0;
    fn_80441CDC(self + 0x104, 2);
    fn_80441CDC(self + 0xDC, 2);
    fn_8047ECD0(self + 0x40, 2);
    fn_80078324(self + 0x18, 2);
    fn_8043D9B0(self, 0);
    if (inChrg & 1)
        fn_8043DAEC(self);
}

void fn_8043CE8C(register float *out, register float *a, register float *b)
{
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
    out[2] = a[2] * b[2];
}

void fn_8043CEE4(register float *out, register float *v)
{
    float len = __ieee754_sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    if (len != 0.0f)
    {
        len = 1.0f / len;
        out[0] = len * v[0];
        out[1] = len * v[1];
        out[2] = len * v[2];
    }
    else
    {
        out[0] = 1.0f;
        out[1] = 0.0f;
        out[2] = 0.0f;
    }
}
