// Vector/matrix helpers; the .rodata float pool is read through extern_pool.

typedef struct Obj28
{
    char pad[0x28];
    float f; // +0x28
} Obj28;

typedef struct Ctl
{
    float a;    // +0x0
    float b;    // +0x4
    char pad[0x14];
    Obj28 *obj; // +0x1C
} Ctl;

void fn_804354B8(register float *dst, register float *src)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
}

void fn_804354F4(register float *dst, register float *src)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
}

void fn_80435530(register float *self, register float s)
{
    self[0] = self[0] * s;
    self[1] = self[1] * s;
    self[2] = self[2] * s;
}

void fn_80435578(register float *self, register float v)
{
    if (v > 0.1f)
        self[0] = v;
    else
        self[0] = 0.1f;
}

Obj28 *fn_804355C0(register Ctl *self)
{
    return self->obj;
}

float fn_804355EC(register Ctl *self)
{
    return self->obj ? (self->obj->f - self->b) / self->obj->f * self->a : 0.0f;
}

float fn_80435650(register float *self)
{
    return self[0x58 / 4];
}

extern void fn_8042DD30(void *self, void *src);
extern void fn_80435948(void *self, void *src);

void fn_8043567C(register void *self, register void *src)
{
    fn_8042DD30(self, src);
    fn_80435948(self, self);
}

typedef struct Mat4
{
    float m[4][4];
} Mat4;

extern void *memcpy(void *dst, const void *src, unsigned int n);

void fn_804356C8(register Mat4 *dst, register Mat4 *src)
{
    memcpy(dst, src, 0x40);
}

extern void fn_80435A00(void *out, void *a, void *b);

void fn_8043570C(register void *out, register void *a, register void *b)
{
    fn_80435A00(out, a, b);
}

void fn_80435754(register float *v, register Mat4 *m)
{
    float out[3];
    out[0] = m->m[0][0] * v[0] + m->m[1][0] * v[1] + m->m[2][0] * v[2];
    out[1] = m->m[0][1] * v[0] + m->m[1][1] * v[1] + m->m[2][1] * v[2];
    out[2] = m->m[0][2] * v[0] + m->m[1][2] * v[1] + m->m[2][2] * v[2];
    v[0] = out[0];
    v[1] = out[1];
    v[2] = out[2];
}

int fn_80435820(register char *self)
{
    return *(int *)(self + 0x470);
}

int fn_8043584C(register char *self)
{
    return *(int *)(self + 0x474);
}

int fn_80435878(register char *self)
{
    return *(int *)(self + 0x778);
}
