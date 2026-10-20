// G and slot flag accessors (layouts guessed).

extern int fn_8043536C(void *self);

int fn_80434C2C(register char *self)
{
    if (fn_8043536C(self)) {
        return *(int *)(self + 0x4);
    } else {
        return 0;
    }
}

void fn_80434C88(register char *self)
{
    *(int *)(self + 0x1848) = -1;
}

void fn_80434CB0(register char *self)
{
    *(unsigned int *)(self + 0x28) |= 0x4;
}

void fn_80434CDC(register char *self, register int bit)
{
    *(unsigned int *)(self + 0x1848) &= ~(1 << bit);
}

void fn_80434D18(register char *self, register int v)
{
    *(int *)(self + 0x30) = v;
}

void fn_80434D40(register char *self, register int on)
{
    if (on)
        *(unsigned int *)(self + 0x28) |= 0x200;
    else
        *(unsigned int *)(self + 0x28) &= ~0x200;
}

void *fn_80434D88(register char *self)
{
    return self + 0x20;
}
