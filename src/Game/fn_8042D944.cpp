// Builds a matrix from a rotation and a position (docs/core.md row 19).

inline int sn_return_decl(int a) { return a; }

struct Matrix
{
    float m[4][4];
    float &at(int row, int col) __asm__("fn_8042DC3C");
};

extern "C" void fn_8042DD30(Matrix *m, void *rot);
extern "C" void fn_8042DC84(float *dst, const float *src);

extern "C" void fn_8042D944(register Matrix *m, register void *rot, register const float *pos)
{
    fn_8042DD30(m, rot);
    fn_8042DC84(m->m[3], pos);
    m->at(3, 3) = 1.0f;
}
