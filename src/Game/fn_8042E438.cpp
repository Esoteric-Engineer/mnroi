// Copies a matrix.

struct Matrix {
    float m[4][4];
};

inline int sn_return_decl(int a) { return a; }

extern "C" void fn_8042E438(register Matrix *self, register Matrix *src)
{
    *self = *src;
}
