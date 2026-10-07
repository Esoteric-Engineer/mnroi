// Vec4 helpers: component mask compare, fill, abs and forwarders (docs/versus.md section 5, row 8).

typedef struct Flag
{
    char v;
} Flag;

extern void fn_8043B5C4(float *self, float *a);

extern float lbl_8064A650[4];

float *fn_8043B4A4(void)
{
    return lbl_8064A650;
}

// Flag(int), the constructor of a one-byte class (fn_8043B3DC builds one into its result).
Flag *__4Flagi(register Flag *self, register int v)
{
    self->v = v;
    return self;
}

void fn_8043B500(register float *self, register float v)
{
    self[0] = v;
    self[1] = v;
    self[2] = v;
    self[3] = v;
}

// Component-wise a < b as a mask: x = 8, y = 4, z = 2, w = 1.
int fn_8043B534(register float *a, register float *b)
{
    register int n; // declared first: the DOL's registers come out r0, r10, r8 in this order
    register int m;
    register int t;

    t = a[0] < b[0] ? 8 : 0;
    m = t;
    if (a[1] < b[1]) {
        m |= 4;
    }
    n = m;
    if (a[2] < b[2]) {
        n |= 2;
    }
    return (a[3] < b[3]) | n;
}

extern float fn_8043B638(float x);

void fn_8043B5C4(register float *self, register float *a)
{
    self[0] = fn_8043B638(a[0]);
    self[1] = fn_8043B638(a[1]);
    self[2] = fn_8043B638(a[2]);
    self[3] = fn_8043B638(a[3]);
}

extern float fabsf(float x);

float fn_8043B638(register float x)
{
    return fabsf(x);
}

extern void fn_8043C4D4(void *self, void *a);

void fn_8043B664(register void *self, register void *a)
{
    fn_8043C4D4(self, a);
}

void fn_8043B6A4(register void *self, register void *a)
{
    fn_8043C4D4(self, a);
}

void fn_8043B6E4(register void *self, register void *a)
{
    fn_8043C4D4(self, a);
}

void fn_8043B724(register void *self, register void *a)
{
    fn_8043C4D4(self, a);
}

void fn_8043B764(register void *self, register void *a)
{
    fn_8043C4D4(self, a);
}

void fn_8043B7A4(register float *self, register float s)
{
    self[0] = self[0] * s;
    self[1] = self[1] * s;
}

float fn_8043B7E0(register char *self)
{
    return *(float *)(self + 0x34);
}

char *fn_8043B80C(register char *self, register int i)
{
    return *(char **)(self + 0x64) + i * 64;
}

void fn_8043B848(register char *self, register int a, register int b)
{
    *(int *)(self + 0xEC) = a;
    *(int *)(self + 0xF0) = b;
}

typedef struct VEntry
{
    short delta;
    short index;
    void *pfn; // +0x4
} VEntry;

typedef struct Counted
{
    VEntry *vptr;       // +0x0
    unsigned short use; // +0x4
    short refs;         // +0x6
} Counted;

// Drops one reference and deletes the object through its virtual destructor at zero.
void fn_8043B878(register Counted *self)
{
    if (self->use != 0) {
        self->refs = self->refs - 1;
        if (self->refs == 0) {
            if (self != 0) {
                register VEntry *e = self->vptr + 1;
                ((void (*)(void *, int))e->pfn)((char *)self + e->delta, 3);
            } else {
            }
        }
    }
}

typedef struct Vec4
{
    float v[4];
} Vec4;

extern void *fn_80434988(void *self);
extern void fn_8043632C(void *dst, void *src);
extern float fn_80436548(void *a, void *b);
extern void *fn_8043C814(void *self, int i);
extern void fn_8037BA8C(void *self, void *a);

void *fn_8043B914(register void *self)
{
    fn_80434988(self);
    return self;
}

// Three Vec4 members at +0x0, +0x10, +0x20.
void *fn_8043B954(register char *self)
{
    fn_80434988(self);
    fn_80434988(self + 0x10);
    fn_80434988(self + 0x20);
    return self;
}

void *fn_8043B9AC(register void *self)
{
    fn_8043B954(self);
    return self;
}

void fn_8043B9EC(register float *self, register float s, register float *v)
{
    float t = s;
    self[0] = t * v[0];
    self[1] = t * v[1];
    self[2] = t * v[2];
    self[3] = t * v[3];
}

float fn_8043BA58(register float *self)
{
    return fn_80436548(self, self);
}

Vec4 *fn_8043BAA0(register Vec4 *self, register int i)
{
    return self + i;
}

void fn_8043BAD8(register Vec4 *self, register void *a, register void *b, register void *c)
{
    fn_8043632C(self, a);
    fn_8043632C(self + 1, b);
    fn_8043632C(self + 2, c);
}

void fn_8043BB40(register Vec4 *self, register void *src)
{
    fn_8043632C(self, fn_8043C814(src, 0));
    fn_8043632C(self + 1, fn_8043C814(src, 1));
    fn_8043632C(self + 2, fn_8043C814(src, 2));
}

void *fn_8043BBD0(register void *self)
{
    return self;
}

void *fn_8043BBF8(register void *self, register void *a)
{
    fn_80434988(self);
    fn_8037BA8C(self, a);
    return self;
}
