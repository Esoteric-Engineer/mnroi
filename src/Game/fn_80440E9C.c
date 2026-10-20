// Root-based constructor, squared length of a vector and a 4x4 matrix translate (docs/versus.md, row 8).
// Names are guesses.

extern void fn_8042D7B0(void *p);

void *fn_80440E9C(register void *self)
{
    fn_8042D7B0(self);
    return self;
}

float fn_80440EDC(register float *v)
{
    return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}

void fn_80440F30(register float *m, register float *v)
{
    m[12] = m[12] + (m[0] * v[0] + m[4] * v[1] + m[8] * v[2]);
    m[13] = m[13] + (m[1] * v[0] + m[5] * v[1] + m[9] * v[2]);
    m[14] = m[14] + (m[2] * v[0] + m[6] * v[1] + m[10] * v[2]);
}
