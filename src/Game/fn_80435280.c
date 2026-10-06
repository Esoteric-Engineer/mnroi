// Matrix (4x4 floats) and quaternion (4 floats) accessors, then the Placement handle accessors (class names guessed).

typedef struct Mat4
{
    float m[4][4];
} Mat4;

float fn_80435280(register Mat4 *self, register int a, register int b)
{
    return self->m[a][b];
}

float *fn_804352C8(register float *self, register int i)
{
    return self + i;
}

void fn_80435300(register float *self, register float x, register float y, register float z, register float w)
{
    self[0] = x;
    self[1] = y;
    self[2] = z;
    self[3] = w;
}

int fn_80435340(register int *self)
{
    return *self;
}

unsigned int fn_8043536C(register unsigned int *self)
{
    return *self & 0x2;
}

void fn_8043539C(register char *self)
{
    *(int *)self = 0;
    *(int *)(self + 0x30) = 0;
}
