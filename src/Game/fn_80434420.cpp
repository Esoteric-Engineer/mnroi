// Inverse of a rigid 4x4 matrix: transposed 3x3 block, translation -R^T * t. Pool is read through extern_pool.

extern "C" float *fn_8042DC3C(void *m, int row, int col);
extern "C" float fn_80435280(void *m, int row, int col);

inline int sn_return_decl(int a) { return a; }

extern "C" void fn_80434420(register void *dst, register void *src)
{
    float tx, ty, tz;
    *fn_8042DC3C(dst, 0, 1) = fn_80435280(src, 1, 0);
    *fn_8042DC3C(dst, 0, 2) = fn_80435280(src, 2, 0);
    *fn_8042DC3C(dst, 1, 2) = fn_80435280(src, 2, 1);
    *fn_8042DC3C(dst, 1, 0) = fn_80435280(src, 0, 1);
    *fn_8042DC3C(dst, 2, 0) = fn_80435280(src, 0, 2);
    *fn_8042DC3C(dst, 2, 1) = fn_80435280(src, 1, 2);
    *fn_8042DC3C(dst, 0, 0) = fn_80435280(src, 0, 0);
    *fn_8042DC3C(dst, 1, 1) = fn_80435280(src, 1, 1);
    *fn_8042DC3C(dst, 2, 2) = fn_80435280(src, 2, 2);
    tx = fn_80435280(src, 3, 0);
    ty = fn_80435280(src, 3, 1);
    tz = fn_80435280(src, 3, 2);
    *fn_8042DC3C(dst, 3, 0) = -(fn_80435280(src, 0, 0) * tx + fn_80435280(src, 0, 1) * ty + fn_80435280(src, 0, 2) * tz);
    *fn_8042DC3C(dst, 3, 1) = -(fn_80435280(src, 1, 0) * tx + fn_80435280(src, 1, 1) * ty + fn_80435280(src, 1, 2) * tz);
    *fn_8042DC3C(dst, 3, 2) = -(fn_80435280(src, 2, 0) * tx + fn_80435280(src, 2, 1) * ty + fn_80435280(src, 2, 2) * tz);
    *fn_8042DC3C(dst, 0, 3) = 0.0f;
    *fn_8042DC3C(dst, 1, 3) = 0.0f;
    *fn_8042DC3C(dst, 2, 3) = 0.0f;
    *fn_8042DC3C(dst, 3, 3) = 1.0f;
}
