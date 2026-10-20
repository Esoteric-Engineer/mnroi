// Accessors and one init function of the shape/placement family (layouts guessed); see docs/versus.md, row 8.

extern int fn_804367D8(void *self);
extern int fn_80436728(void *self);
extern int fn_80438480(int v);
extern void fn_80434988(void *self);
extern void fn_80436610(void *self);
extern void fn_80434BA4(void *out, void *v);
extern void *fn_80434D88(void *self);
extern void fn_80429090(void *out, void *a, void *b, float s);
extern void fn_8037E52C(void *a, int b, void *c);
extern void fn_8042DC84(void *dst, void *src);

int fn_80437004(register char *self)
{
    return *(unsigned int *)(self + 0x28) & 0x40;
}

void *fn_80437034(register void *self)
{
    return self;
}

float fn_8043705C(register char *self)
{
    return *(float *)(self + 0x24);
}

int fn_80437088(register char *self)
{
    return *(int *)(self + 0x2C);
}

void fn_804370B4(register char *self)
{
    *(int *)(self + 0x1840) = 0;
    *(unsigned int *)(self + 0x28) &= 0x7FFFFFFF;
}

void *fn_804370E8(register void *self)
{
    return self;
}

void *fn_80437110(register char *self)
{
    return self + 0x10;
}

float fn_8043713C(register char *self)
{
    return *(float *)(self + 0x30);
}

void *fn_80437168(register char *self)
{
    return self + 0x20;
}

int fn_80437194(register char *self)
{
    return *(int *)(self + 0x38);
}

int fn_804371C0(register char *self)
{
    return fn_804367D8(*(void **)(self + 0x30)) == 1;
}

void fn_80437210(register char *self, register int a, register char *b, register char *c, register int d, register int e)
{
    float local[4];
    *(int *)self = 1;
    *(float *)(self + 0x4) = *(float *)(c + 0x14) * fn_8043713C(b);
    *(int *)(self + 0x38) = d;
    *(int *)(self + 0x3C) = e;
    fn_80434988(local);
    fn_8037E52C(local, fn_80438480(fn_80436728((void *)a)), c);
    fn_80436610(local);
    fn_80434BA4(self + 0x20, local);
    fn_80429090(self + 0x10, fn_804370E8(b), fn_80434D88(b), *(float *)(self + 0x4));
    *(int *)(self + 0x30) = a;
    *(int *)(self + 0x34) = *(int *)(c + 0x10);
}

void fn_80437300(register char *self, register int a, register void *b, register void *c, register float s)
{
    *(int *)self = 2;
    *(int *)(self + 0x30) = a;
    fn_8042DC84(self + 0x10, b);
    fn_8042DC84(self + 0x20, c);
    *(float *)(self + 0x4) = s;
}
