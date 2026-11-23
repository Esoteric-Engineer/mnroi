// Degrees to sine and cosine (docs/core.md row 19).

inline int sn_return_decl(int a) { return a; }

extern "C" float sinf(float x);
extern "C" float cosf(float x);

extern "C" void fn_8042A7D8(register float deg, register float *s, register float *c)
{
    float rad = deg * 0.017453292f;
    if (s) {
        *s = sinf(rad);
    }
    if (c) {
        *c = cosf(rad);
    }
}
