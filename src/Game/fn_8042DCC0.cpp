// Sets a matrix to the identity.

struct Matrix {
    float m[4][4];
};

inline int sn_return_decl(int a) { return a; }

extern "C" {
void *memset(void *dst, int value, unsigned int n);

void fn_8042DCC0(register Matrix *self)
{
    memset(self, 0, 0x40);
    self->m[0][0] = 1.0f;
    self->m[1][1] = 1.0f;
    self->m[2][2] = 1.0f;
    self->m[3][3] = 1.0f;
}
}
