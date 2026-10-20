// 4x4 float matrix product, out = a * b in this game's row-vector convention, and a forwarder.

typedef struct Mat4
{
    float m[4][4];
} Mat4;

#define ELEM(i, j) \
    out->m[i][j] = a->m[0][j] * b->m[i][0] + a->m[1][j] * b->m[i][1] + a->m[2][j] * b->m[i][2] + a->m[3][j] * b->m[i][3]

void fn_80435A00(register Mat4 *out, register Mat4 *a, register Mat4 *b)
{
    ELEM(0, 0);
    ELEM(0, 1);
    ELEM(0, 2);
    ELEM(0, 3);
    ELEM(1, 0);
    ELEM(1, 1);
    ELEM(1, 2);
    ELEM(1, 3);
    ELEM(2, 0);
    ELEM(2, 1);
    ELEM(2, 2);
    ELEM(2, 3);
    ELEM(3, 0);
    ELEM(3, 1);
    ELEM(3, 2);
    ELEM(3, 3);
}

extern void fn_80436F3C(void *a, void *b);

void fn_80435E28(register void *a, register void *b)
{
    fn_80436F3C(a, b);
}
