/* A point and a direction times a row-major matrix: x' = m00 x + m10 y + m20 z + m30. */

void fn_804708F8(register float *out, register float *p, register float *m)
{
    out[0] = m[0] * p[0] + m[4] * p[1] + m[8] * p[2] + m[12];
    out[1] = m[1] * p[0] + m[5] * p[1] + m[9] * p[2] + m[13];
    out[2] = m[2] * p[0] + m[6] * p[1] + m[10] * p[2] + m[14];
}

void fn_804709C8(register float *out, register float *p, register float *m)
{
    out[0] = m[0] * p[0] + m[4] * p[1] + m[8] * p[2];
    out[1] = m[1] * p[0] + m[5] * p[1] + m[9] * p[2];
    out[2] = m[2] * p[0] + m[6] * p[1] + m[10] * p[2];
}
