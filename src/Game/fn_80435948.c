// Transposes the 3x3 part of a 4x4 matrix into self and clears the translation; the .rodata float pool is read through extern_pool.

typedef struct Mat4
{
    float m[4][4];
} Mat4;

void fn_80435948(register Mat4 *self, register Mat4 *src)
{
    float tmp;
    self->m[0][0] = src->m[0][0];
    self->m[1][1] = src->m[1][1];
    self->m[2][2] = src->m[2][2];
    tmp = src->m[0][1];
    self->m[0][1] = src->m[1][0];
    self->m[1][0] = tmp;
    tmp = src->m[0][2];
    self->m[0][2] = src->m[2][0];
    self->m[2][0] = tmp;
    tmp = src->m[1][2];
    self->m[1][2] = src->m[2][1];
    self->m[2][1] = tmp;
    self->m[0][3] = self->m[1][3] = self->m[2][3] = 0.0f;
    self->m[3][0] = self->m[3][1] = self->m[3][2] = 0.0f;
    self->m[3][3] = 1.0f;
}
