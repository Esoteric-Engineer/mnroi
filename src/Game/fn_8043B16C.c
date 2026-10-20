// Flag-bit accessors and float getters on objects of unknown class (docs/versus.md section 5, row 8).

extern double __ieee754_sqrt(double x);

unsigned int fn_8043B16C(register char *self)
{
    return *(unsigned int *)(self + 0x4) & 0x10000;
}

unsigned int fn_8043B19C(register char *self)
{
    return *(unsigned int *)(self + 0x4) & 0x20000;
}

int fn_8043B1CC(register char *self)
{
    register int r = 1;
    if (*(int *)(self + 0x1C) == 0) {
        r = 0;
    }
    return r;
}

int fn_8043B208(register char *self)
{
    register int r = 1;
    if (*(int *)(self + 0x40) == 0) {
        r = 0;
    }
    return r;
}

void fn_8043B244(register char *self, register unsigned int bit)
{
    if (bit <= 31) {
        *(unsigned int *)(self + 0x40) |= 1 << bit;
    }
}

void fn_8043B284(register char *self, register unsigned int bit)
{
    if (bit <= 31) {
        *(unsigned int *)(self + 0x40) &= ~(1 << bit);
    }
}

int fn_8043B2C8(register char *self)
{
    register int r = 0;
    if (self != 0 && *(int *)(self + 0x28) != 0 && !(*(unsigned int *)(self + 0x34) & 0x2)) {
        r = 1;
    }
    return r;
}

int fn_8043B31C(register int *self)
{
    return *self;
}

float fn_8043B348(register float *self)
{
    return __ieee754_sqrt(self[0] * self[0] + self[1] * self[1]);
}

float fn_8043B3B0(register char *self)
{
    return *(float *)(self + 0x54);
}
