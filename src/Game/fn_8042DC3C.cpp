// The matrix element accessor (docs/core.md row 19).

inline int sn_return_decl(int a) { return a; }

struct Matrix
{
    float m[4][4];
};

extern "C" float *fn_8042DC3C(register Matrix *self, register int row, register int col)
{
    return &self->m[row][col];
}
