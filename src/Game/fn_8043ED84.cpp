// Growable arrays of 16-bit, 32-bit and 16-byte elements: reserve, push, find, remove and accessors
// (docs/versus.md, row 8). Layout: data pointer +0x0, count +0x4, capacity +0x8 (starts at 0x80000000).

inline int sn_return_decl(int a)
{
    return a;
}

struct ShortArray
{
    unsigned short *data; // +0x0
    int n;                // +0x4
    int cap;              // +0x8
};

struct IntArray
{
    int *data; // +0x0
    int n;     // +0x4
    int cap;   // +0x8
};

struct Vec16
{
    float x, y, z, w;
};

struct VecArray
{
    Vec16 *data; // +0x0
    int n;       // +0x4
    int cap;     // +0x8
};

extern "C" {
int fn_80440148(register IntArray *self);
int fn_8043FDCC(register IntArray *self);
void fn_802E1970(register IntArray *self, int n, int elemSize);
void fn_802E1A24(register IntArray *self, int elemSize);
void *fn_802E3FE4(int size);
void *fn_804402F0(void *p, int a);

void fn_8043ED84(register IntArray *self, register int want)
{
    register int tmp = fn_80440148(self);
    int cap = tmp;

    if (cap < want) {
        int dbl = cap * 2;
        int n = want < dbl ? dbl : want;

        fn_802E1970(self, n, 4);
    }
}

void fn_8043EE0C(register IntArray *self, register const int *v)
{
    if (self->n == fn_80440148(self))
        fn_802E1A24(self, 4);
    self->data[self->n++] = *v;
}

int fn_8043EE90(register IntArray *self)
{
    return (int)self->data;
}

int fn_8043EEBC(register IntArray *self)
{
    return self->n;
}

IntArray *fn_8043EEE8(register IntArray *self)
{
    self->data = 0;
    self->n = 0;
    self->cap = 0x80000000;
    return self;
}

Vec16 *fn_8043EF28(register VecArray *self, register int i)
{
    return &self->data[i];
}

int fn_8043EF64(register VecArray *self)
{
    return self->n;
}

int fn_8043EF90(register const Vec16 *key, register const Vec16 *arr, register unsigned int count)
{
    unsigned int i;

    i = 0;
    while (i < count) {
        if (arr[i].x == key->x && arr[i].y == key->y && arr[i].z == key->z)
            return (unsigned short)i;
        i++;
    }
    return 0;
}

int *fn_8043F058(register IntArray *self, register int i)
{
    return &self->data[i];
}

IntArray *fn_8043F094(register IntArray *self)
{
    self->data = 0;
    self->n = 0;
    self->cap = 0x80000000;
    return self;
}

IntArray *fn_8043F0D4(register IntArray *self)
{
    self->data = 0;
    self->n = 0;
    self->cap = 0x80000000;
    return self;
}

int fn_8043F114(register IntArray *self, register const int *key)
{
    int i;

    i = 0;
    while (i < self->n) {
        if (self->data[i] == *key)
            return i;
        i++;
    }
    return -1;
}

void fn_8043F19C(register IntArray *self, register const int *v)
{
    if (self->n == fn_8043FDCC(self))
        fn_802E1A24(self, 4);
    self->data[self->n++] = *v;
}

int fn_8043F220(register IntArray *self)
{
    return self->n;
}

unsigned short *fn_8043F24C(register ShortArray *self, register int i)
{
    return &self->data[i];
}

int *fn_8043F288(register IntArray *self, register int i)
{
    return &self->data[i];
}

void fn_8043F2C4(register ShortArray *self, register int i)
{
    self->n--;
    self->data[i] = self->data[self->n];
}

void fn_8043F320(register IntArray *self, register int i)
{
    self->n--;
    self->data[i] = self->data[self->n];
}

void *fn_8043F37C(register int a, register int b, register int c, register int d)
{
    return fn_804402F0(fn_802E3FE4(0xC), d);
}

void fn_8043F3DC(register int a, register int b, register int c, register int d)
{
}

void fn_8043F408(register int a, register int b, register int c, register int d)
{
}

void fn_8043F434(register int a, register int b, register int c, register int d, register int e)
{
}

void fn_8043F464(register char *self, register int v)
{
    *self = v;
}
}
