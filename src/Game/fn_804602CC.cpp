// Scales a matrix: multiplies it by a matrix with s on its diagonal (fn_8043AC1C).

class Matrix
{
public:
    float m[4][4];
    Matrix() __asm__("fn_8042D7B0");
};

inline int sn_return_decl(int a) { return a; }

extern "C" {
void fn_8042DCC0(Matrix *m);
void fn_8043AC1C(Matrix *self, Matrix *b);

void fn_804602CC(register Matrix *self, register float *s)
{
    Matrix t;
    fn_8042DCC0(&t);
    t.m[0][0] = s[0];
    t.m[1][1] = s[1];
    t.m[2][2] = s[2];
    fn_8043AC1C(self, &t);
}
}
