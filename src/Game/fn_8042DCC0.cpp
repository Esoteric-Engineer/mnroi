// Matrix identity and Euler angles (degrees) to a rotation matrix (docs/core.md row 19).

struct Matrix {
    float m[4][4];
};

inline int sn_return_decl(int a) { return a; }

struct Vector
{
    float x, y, z;
};

extern "C" {
void *memset(void *dst, int value, unsigned int n);
void fn_8042A7D8(float deg, float *s, float *c);

void fn_8042DCC0(register Matrix *self)
{
    memset(self, 0, 0x40);
    self->m[0][0] = 1.0f;
    self->m[1][1] = 1.0f;
    self->m[2][2] = 1.0f;
    self->m[3][3] = 1.0f;
}

void fn_8042DD30(register Matrix *m, register const Vector *e)
{
    float cx, sx, cz, sz, cy, sy;
    fn_8042A7D8(e->x, &sx, &cx);
    fn_8042A7D8(e->z, &sz, &cz);
    fn_8042A7D8(e->y, &sy, &cy);
    float sxsz = sx * sz;
    float sxcz = sx * cz;
    float cxsz = cx * sz;
    float cxcz = cx * cz;
    m->m[0][0] = cy * cz;
    m->m[0][1] = cy * sz;
    m->m[0][2] = -sy;
    m->m[0][3] = 0.0f;
    m->m[1][0] = sy * sxcz - cxsz;
    m->m[1][1] = sy * sxsz + cxcz;
    m->m[1][2] = cy * sx;
    m->m[1][3] = 0.0f;
    m->m[2][0] = sy * cxcz + sxsz;
    m->m[2][1] = sy * cxsz - sxcz;
    m->m[2][2] = cx * cy;
    m->m[2][3] = 0.0f;
    m->m[3][0] = 0.0f;
    m->m[3][1] = 0.0f;
    m->m[3][2] = 0.0f;
    m->m[3][3] = 1.0f;
}
}
