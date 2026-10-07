// Leaf accessors on the object that owns the 0xB0-byte slots at +0x10; see docs/versus.md section 5, row 2.

int fn_8044D74C(register char *self)
{
    return *(int *)(self + 0x150);
}

int fn_8044D778(register char *self)
{
    return *(int *)(self + 0x154);
}

void fn_8044D7A4(register char *self, register int v)
{
    *(int *)(self + 0x280) = v;
}

int fn_8044D7CC(register char *self)
{
    return *(int *)(self + 0x160);
}

int fn_8044D7F8(register char *self)
{
    return *(int *)(self + 0x17C);
}

void fn_8044D824(register char *self, register int v)
{
    *(int *)(self + 0x134) = v;
}
