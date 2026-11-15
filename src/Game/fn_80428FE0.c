/* out = a + b and out = a - b on x, y and z. */

void fn_80428FE0(register float *out, register float *a, register float *b)
{
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
}

void fn_80429038(register float *out, register float *a, register float *b)
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
}
