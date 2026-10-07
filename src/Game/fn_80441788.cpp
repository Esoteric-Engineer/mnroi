// Growable int array: reserve, push, element address, plus an identity method, a W setter and the capacity
// getter (docs/versus.md, row 8). Layout: data pointer +0x0, count +0x4, capacity +0x8.

inline int sn_return_decl(int a)
{
    return a;
}

struct IntArray
{
    int *data; // +0x0
    int n;     // +0x4
    int cap;   // +0x8
};

extern "C" {
int fn_8044194C(register IntArray *self);
void fn_802E1970(register IntArray *self, int n, int elemSize);
void fn_802E1A24(register IntArray *self, int elemSize);
float *fn_80438360(void *self, int i);

void fn_80441788(register IntArray *self, register int want)
{
    register int tmp = fn_8044194C(self);
    int cap = tmp;

    if (cap < want) {
        int dbl = cap * 2;
        int n = want < dbl ? dbl : want;

        fn_802E1970(self, n, 4);
    }
}

void fn_80441810(register IntArray *self, register const int *v)
{
    if (self->n == fn_8044194C(self))
        fn_802E1A24(self, 4);
    self->data[self->n++] = *v;
}

int *fn_80441894(register IntArray *self, register int i)
{
    return &self->data[i];
}

void *fn_804418D0(register void *self)
{
    return self;
}

void fn_804418F8(register void *self, register float v)
{
    *fn_80438360(self, 3) = v;
}

int fn_8044194C(register IntArray *self)
{
    return self->cap & 0x3FFFFFFF;
}
}
