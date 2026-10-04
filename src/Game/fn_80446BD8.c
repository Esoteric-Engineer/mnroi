int fn_80446BD8(register char *self)
{
    return *(int *)(self + 0x68);
}

int fn_80446C04(register char *self)
{
    return *(int *)(self + 0x63C);
}

void fn_80446C30(register char *self, register float v)
{
    *(float *)(self + 0x190) = v;
}

void fn_80446C58(register char *self, register float v)
{
    *(float *)(self + 0x194) = v;
}
