// Vec4 "all components within eps" test; the result is a one-byte class returned by value (docs/versus.md, row 8).
extern "C" {
void *fn_80434988(void *self);
void fn_804349B0(void *out, void *a, void *b);
void fn_8043B500(float *self, float v);
int fn_8043B534(float *a, float *b);
void fn_8043B5C4(float *self, float *a);
}

class Flag
{
public:
    char v;
    Flag(int v);
};

inline int sn_return_decl(int a) { return a; }

extern "C" Flag fn_8043B3DC(register float *a, register float *b, register float eps)
{
    float d[4];
    float e[4];
    int m;

    fn_80434988(d);
    fn_804349B0(d, a, b);
    fn_8043B5C4(d, d);
    fn_80434988(e);
    fn_8043B500(e, eps);
    m = fn_8043B534(e, d) & 0xE;
    return Flag(m == 0);
}
