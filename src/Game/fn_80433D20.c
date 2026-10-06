// Small accessors and Vector4/Vector3 helpers after the handle classes (names and layouts are guesses).

typedef struct Entry
{
    char pad[8];
    int v[7];
} Entry; // 0x24 bytes, indexed through +0x24 of the owner

float fn_80433D20(register char *self, register int a, register int b)
{
    return *(float *)(*(Entry **)(self + 0x24))[a].v[b];
}

int fn_80433D70(register char *self, register int a, register int b)
{
    return *(int *)(*(Entry **)(self + 0x24))[a].v[b];
}

void fn_80433DC0(register char *self, register float x)
{
    if (x < 0.0f)
        *(float *)(self + 0x13C) = 0.0f;
    else
        *(float *)(self + 0x13C) = x;
}

int fn_80433E08(register char *self)
{
    return *(unsigned int *)(self + 0x464) & 1;
}

int fn_80433E38(register char *self)
{
    return *(unsigned int *)(self + 0x464) & 0x40;
}

int fn_80433E68(register char *self)
{
    return *(int *)(self + 0x778) && *(int *)(self + 0x598);
}

int fn_80433EB0(register char *self)
{
    return *(unsigned int *)self & 2;
}

int fn_80433EE0(register char *self)
{
    return *(unsigned int *)self & 0x1000;
}

int fn_80433F10(register int a)
{
    return a;
}

float *fn_80433F38(register float *self, register float x, register float y, register float z, register float w)
{
    self[0] = x;
    self[1] = y;
    self[2] = z;
    self[3] = w;
    return self;
}

void fn_80433F80(register float *self, register float x, register float y, register float z, register float w)
{
    self[0] = x;
    self[1] = y;
    self[2] = z;
    self[3] = w;
}

void fn_80433FC0(register float *self, register float *v)
{
    self[0] = v[0];
    self[1] = v[1];
    self[2] = v[2];
}

void fn_80433FFC(register float *self)
{
    self[0] = -self[0];
    self[1] = -self[1];
    self[2] = -self[2];
}

extern double __ieee754_sqrt(double x);

float fn_80434040(register float *self)
{
    return __ieee754_sqrt(self[0] * self[0] + self[1] * self[1] + self[2] * self[2]);
}
