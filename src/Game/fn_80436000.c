// Vector/box/quaternion helpers; the .rodata float pool is read through extern_pool.

typedef struct Mat4
{
    float m[4][4];
} Mat4;

extern void __6Vector(void *v);
extern void fn_80435300(void *self, float x, float y, float z, float w);

void fn_80436000(register float *out, register float *a, register float *b, register float s)
{
    out[0] = a[0] + s * b[0];
    out[1] = a[1] + s * b[1];
    out[2] = a[2] + s * b[2];
}

int fn_80436068(register float *a, register float *b)
{
    if (a[4] < b[0] || a[5] < b[1] || a[6] < b[2] || b[4] < a[0] || b[5] < a[1] || b[6] < a[2])
        return 0;
    return 1;
}

void fn_80436100(register float *v, register Mat4 *m)
{
    float tmp[4];
    __6Vector(tmp);
    tmp[0] = m->m[0][0] * v[0] + m->m[1][0] * v[1] + m->m[2][0] * v[2] + m->m[3][0];
    tmp[1] = m->m[0][1] * v[0] + m->m[1][1] * v[1] + m->m[2][1] * v[2] + m->m[3][1];
    tmp[2] = m->m[0][2] * v[0] + m->m[1][2] * v[1] + m->m[2][2] * v[2] + m->m[3][2];
    v[0] = tmp[0];
    v[1] = tmp[1];
    v[2] = tmp[2];
}

int fn_804361FC(register float *box, register float *p)
{
    if (p[0] < box[0] || p[0] > box[4] || p[1] < box[1] || p[1] > box[5] || p[2] < box[2] || p[2] > box[6])
        return 0;
    return 1;
}

int fn_80436294(register char *self)
{
    register int r = 1;
    if (*self == 0)
        r = 0;
    return r;
}

void *fn_804362D4(register void *self, register float *v)
{
    fn_80435300(self, v[0], v[1], v[2], 0.0f);
    return self;
}

void fn_8043632C(register float *dst, register float *src)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
}

void *fn_80436370(register void *dst, register void *src)
{
    fn_8043632C(dst, src);
    return dst;
}

void fn_804363B8(register float *self)
{
    self[0] = self[1] = self[2] = self[3] = 0.0f;
}

void fn_804363F0(register float *a, register float *b)
{
    a[0] = a[0] + b[0];
    a[1] = a[1] + b[1];
    a[2] = a[2] + b[2];
    a[3] = a[3] + b[3];
}

void fn_80436454(register float *self, register float s)
{
    float t = s;
    self[0] = self[0] * t;
    self[1] = self[1] * t;
    self[2] = self[2] * t;
    self[3] = self[3] * t;
}

void fn_804364BC(register float *self, register float s, register float *v)
{
    float t = s;
    self[0] = self[0] + t * v[0];
    self[1] = self[1] + t * v[1];
    self[2] = self[2] + t * v[2];
    self[3] = self[3] + t * v[3];
}

float fn_80436548(register float *a, register float *b)
{
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

extern float fn_80438308(float x);
extern float fn_804383EC(void *self);

float fn_804365A0(register float *self)
{
    return fn_80438308(self[0] * self[0] + self[1] * self[1] + self[2] * self[2]);
}

void fn_80436610(register void *self)
{
    fn_80436454(self, fn_804383EC(self));
}

char *fn_80436658(register char *self)
{
    return self + 0x30;
}

void *fn_80436684(register void *self)
{
    return self;
}

char *fn_804366AC(register char *self)
{
    return self + 0x10;
}

extern float *fn_804352C8(void *self, int i);

float fn_804366D8(register char *self)
{
    return *fn_804352C8(self + 0x10, 3);
}

int fn_80436728(register char *self)
{
    return *(int *)(self + 8);
}

typedef struct Node
{
    char pad[0xC];
    struct Node *next; // +0xC
} Node;

Node *fn_80436754(register Node *self)
{
    Node *p = self;
    while (p->next)
        p = p->next;
    return p;
}

char *fn_804367A8(register char *self)
{
    return self + *(int *)(self + 0x10);
}

extern int fn_804384A8(void *self);

int fn_804367D8(register char *self)
{
    return fn_804384A8(self + 0x14);
}

int fn_80436820(register char *self)
{
    return *(int *)(self + 4);
}

int fn_8043684C(register char *self)
{
    return *(int *)(self + 4);
}
