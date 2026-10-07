// Matrix concatenation: self = b * self (row-major 4x4; docs/versus.md, row 8).
struct Mat {
    float f[16];
};

extern void fn_8042D7B0(void *self);
extern void fn_8042E438(void *dst, float *src);

void fn_8043AC1C(register float *self, register float *b)
{
    struct Mat tmp; // +0x8, constructed by fn_8042D7B0, then a copy of *self
    struct Mat *m;

    fn_8042D7B0(&tmp);
    m = &tmp;
    fn_8042E438(m, self);
    self[0] = m->f[0] * b[0] + m->f[4] * b[1] + m->f[8] * b[2] + m->f[12] * b[3];
    self[1] = m->f[1] * b[0] + m->f[5] * b[1] + m->f[9] * b[2] + m->f[13] * b[3];
    self[2] = m->f[2] * b[0] + m->f[6] * b[1] + m->f[10] * b[2] + m->f[14] * b[3];
    self[3] = m->f[3] * b[0] + m->f[7] * b[1] + m->f[11] * b[2] + m->f[15] * b[3];
    self[4] = m->f[0] * b[4] + m->f[4] * b[5] + m->f[8] * b[6] + m->f[12] * b[7];
    self[5] = m->f[1] * b[4] + m->f[5] * b[5] + m->f[9] * b[6] + m->f[13] * b[7];
    self[6] = m->f[2] * b[4] + m->f[6] * b[5] + m->f[10] * b[6] + m->f[14] * b[7];
    self[7] = m->f[3] * b[4] + m->f[7] * b[5] + m->f[11] * b[6] + m->f[15] * b[7];
    self[8] = m->f[0] * b[8] + m->f[4] * b[9] + m->f[8] * b[10] + m->f[12] * b[11];
    self[9] = m->f[1] * b[8] + m->f[5] * b[9] + m->f[9] * b[10] + m->f[13] * b[11];
    self[10] = m->f[2] * b[8] + m->f[6] * b[9] + m->f[10] * b[10] + m->f[14] * b[11];
    self[11] = m->f[3] * b[8] + m->f[7] * b[9] + m->f[11] * b[10] + m->f[15] * b[11];
    self[12] = m->f[0] * b[12] + m->f[4] * b[13] + m->f[8] * b[14] + m->f[12] * b[15];
    self[13] = m->f[1] * b[12] + m->f[5] * b[13] + m->f[9] * b[14] + m->f[13] * b[15];
    self[14] = m->f[2] * b[12] + m->f[6] * b[13] + m->f[10] * b[14] + m->f[14] * b[15];
    self[15] = m->f[3] * b[12] + m->f[7] * b[13] + m->f[11] * b[14] + m->f[15] * b[15];
}
