// Transforms the point (x, y, z) by the 4x4 float matrix m (row-vector form, translation in the last row).
void fn_80447F78(register float *out, register float x, register float y, register float z, register float *m)
{
    out[0] = x * m[0] + y * m[4] + z * m[8] + m[12];
    out[1] = x * m[1] + y * m[5] + z * m[9] + m[13];
    out[2] = x * m[2] + y * m[6] + z * m[10] + m[14];
}
