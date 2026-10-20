// Rotation matrix from a quaternion {w, x, y, z}: fn_804418D0 returns the matrix's float array
// (docs/versus.md, row 8). The 1.0f/0.0f pool at 0x80487888 is read through extern_pool.

inline int sn_return_decl(int a)
{
    return a;
}

extern "C" float *fn_804418D0(void *m);

extern "C" void fn_80440FFC(register float *q, register float *m)
{
    float a, b, c;
    float aa, ab, ac, aw, bb, bc, bw, cc, cw;

    a = -q[2];
    b = -q[3];
    c = -q[1];
    aa = a * a;
    ab = a * b;
    ac = a * c;
    aw = a * q[0];
    bb = b * b;
    bc = b * c;
    bw = b * q[0];
    cc = c * c;
    cw = c * q[0];
    fn_804418D0(m)[0] = 1.0f - 2.0f * (bb + cc);
    fn_804418D0(m)[4] = 2.0f * (ab - cw);
    fn_804418D0(m)[8] = 2.0f * (ac + bw);
    fn_804418D0(m)[1] = 2.0f * (ab + cw);
    fn_804418D0(m)[5] = 1.0f - 2.0f * (aa + cc);
    fn_804418D0(m)[9] = 2.0f * (bc - aw);
    fn_804418D0(m)[2] = 2.0f * (ac - bw);
    fn_804418D0(m)[6] = 2.0f * (bc + aw);
    fn_804418D0(m)[10] = 1.0f - 2.0f * (aa + bb);
    fn_804418D0(m)[3] = fn_804418D0(m)[7] = fn_804418D0(m)[11] = fn_804418D0(m)[12] = fn_804418D0(m)[13] = fn_804418D0(m)[14] = 0.0f;
    fn_804418D0(m)[15] = 1.0f;
}
