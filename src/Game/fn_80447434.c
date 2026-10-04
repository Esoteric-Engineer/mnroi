// Small accessors on the object whose constructors are fn_80447618/fn_804479B0 (two 0x40-byte matrices, flags at +0x28).
typedef struct Mat40
{
    int w[16];
} Mat40;

float fn_80447434(register float *self)
{
    return *self;
}

int fn_80447460(register char *self)
{
    return *(int *)(self + 0x14) & 0x1000000;
}

void fn_80447490(register char *self)
{
    *(unsigned int *)(self + 0x28) |= 0x100;
}

void fn_804474BC(register char *self, register int on)
{
    if (on)
        *(unsigned int *)(self + 0x28) |= 0x1000;
    else
        *(unsigned int *)(self + 0x28) &= ~0x1000;
}

void fn_80447504(register char *self, register Mat40 *src)
{
    *(Mat40 *)self = *src;
    *(Mat40 *)(self + 0x40) = *src;
    *(int *)(self + 0x84) = 0;
    *(int *)(self + 0x80) = 0;
}
