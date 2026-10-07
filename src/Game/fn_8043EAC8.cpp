// Push onto the growable array of 16-bit values: grow when full, then append (docs/versus.md, row 8).
// Layout: data pointer +0x0, count +0x4, capacity +0x8 (starts at 0x80000000).

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

extern "C" {
int fn_8043FD4C(register ShortArray *self);
void fn_802E1A24(register ShortArray *self, int elemSize);

void fn_8043EAC8(register ShortArray *self, register const unsigned short *v)
{
    if (self->n == fn_8043FD4C(self))
        fn_802E1A24(self, 2);
    self->data[self->n++] = *v;
}
}
