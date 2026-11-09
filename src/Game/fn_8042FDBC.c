/* out = v * s, and out += v * s, on x, y and z. */

void fn_8042FDBC(register float *out, register float *v, register float s)
{
    out[0] = s * v[0];
    out[1] = s * v[1];
    out[2] = s * v[2];
}

void fn_8042FE08(register float *out, register float *v, register float s)
{
    out[0] += s * v[0];
    out[1] += s * v[1];
    out[2] += s * v[2];
}
