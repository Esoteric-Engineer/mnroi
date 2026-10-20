// Reserve and push for the growable array of 16-byte elements, and a forwarding method (docs/versus.md, row 8).
// Layout: data pointer +0x0, count +0x4, capacity +0x8 (starts at 0x80000000).

struct VecArray
{
    char (*data)[0x10]; // +0x0
    int n;              // +0x4
    int cap;            // +0x8
};

extern "C" {
int fn_8043FEC0(register VecArray *self);
void fn_802E1970(register VecArray *self, int n, int elemSize);
void fn_802E1A24(register VecArray *self, int elemSize);
void fn_8043632C(void *dst, const void *src);
void fn_80440344(void *self, int a);

void fn_8043F490(register VecArray *self, register int want)
{
    register int tmp = fn_8043FEC0(self);
    int cap = tmp;

    if (cap < want) {
        int dbl = cap * 2;
        int n = want < dbl ? dbl : want;

        fn_802E1970(self, n, 0x10);
    }
}

void fn_8043F520(register VecArray *self, register const void *v)
{
    if (self->n == fn_8043FEC0(self))
        fn_802E1A24(self, 0x10);
    fn_8043632C(self->data[self->n++], v);
}

inline int sn_return_decl(int a)
{
    return a;
}

void fn_8043F5AC(register char *self, register int a)
{
    fn_80440344(self, a);
    *(int *)(self + 4) = a;
}
}
