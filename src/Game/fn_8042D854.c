/* Vector inlines (docs/core.md row 19). */

void fn_8042D854(register float *a, register float *b)
{
    a[0] += b[0];
    a[1] += b[1];
    a[2] += b[2];
}

void fn_8042D8A8(register float *a, register float *b)
{
    a[0] -= b[0];
    a[1] -= b[1];
    a[2] -= b[2];
}

void fn_8042D8FC(register float *dst, register float *a, register float *b)
{
    dst[0] = a[0] * b[0];
    dst[1] = a[1] * b[1];
}
