// A point times a matrix, and a matrix wrapper (docs/core.md row 19).

inline int sn_return_decl(int a) { return a; }

struct Vector
{
    float x, y, z;
};

struct Matrix
{
    float m[4][4];
};

extern "C" void fn_8042DEE8(void *a, void *b);

extern "C" void fn_8042DA10(register Vector *out, register const Vector *v, register const Matrix *m)
{
    out->x = m->m[0][0] * v->x + m->m[1][0] * v->y + m->m[2][0] * v->z + m->m[3][0];
    out->y = m->m[0][1] * v->x + m->m[1][1] * v->y + m->m[2][1] * v->z + m->m[3][1];
    out->z = m->m[0][2] * v->x + m->m[1][2] * v->y + m->m[2][2] * v->z + m->m[3][2];
}

extern "C" void fn_8042DAE0(register void *a, register void *b)
{
    fn_8042DEE8(a, b);
}
