// Copies the first three components of a Vector4-like object into a float[3].

extern "C" float *fn_804352C8(void *v, int i);

inline int sn_return_decl(int a) { return a; }

extern "C" void fn_80434BA4(register float *out, register void *v)
{
    out[0] = *fn_804352C8(v, 0);
    out[1] = *fn_804352C8(v, 1);
    out[2] = *fn_804352C8(v, 2);
}
