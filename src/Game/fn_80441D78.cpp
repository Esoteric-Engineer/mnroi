// Growable array of 8-byte and 4-byte elements: accessors, swap-remove and find, plus a vptr constructor
// (docs/versus.md, row 8). Layout: data pointer +0x0, count +0x4.

inline int sn_return_decl(int a)
{
    return a;
}

struct Pair8
{
    int a, b;
};

struct PairArray
{
    Pair8 *data; // +0x0
    int n;       // +0x4
};

struct IntArray
{
    int *data; // +0x0
    int n;     // +0x4
};

extern char lbl_804F4810[];

extern "C" {
int fn_80441D78(register IntArray *self)
{
    return self->n;
}

Pair8 *fn_80441DA4(register PairArray *self, register int i)
{
    return &self->data[i];
}

void fn_80441DE0(register PairArray *self, register int i)
{
    self->n--;
    self->data[i] = self->data[self->n];
}

int *fn_80441E44(register int *self)
{
    self[0] = 0;
    return self;
}

char *fn_80441E74(register char *self)
{
    return self + 4;
}

void *fn_80441EA0(register void *self)
{
    return self;
}

int fn_80441EC8(register IntArray *self, register const int *key)
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

void fn_80441F50(register IntArray *self, register int i)
{
    self->n--;
    self->data[i] = self->data[self->n];
}

char *fn_80441FAC(register char *self)
{
    *(char **)(self + 0x24) = lbl_804F4810;
    return self;
}

int *fn_80441FE0(register int *self, register int a)
{
    self[1] = a;
    return self;
}
}
