// Reserve for the growable array of 1-byte elements (docs/versus.md, row 8).

inline int sn_return_decl(int a)
{
    return a;
}

struct ByteArray
{
    char *data; // +0x0
    int n;      // +0x4
    int cap;    // +0x8
};

extern "C" {
int fn_80440490(register ByteArray *self);
void fn_802E1970(register ByteArray *self, int n, int elemSize);

void fn_80440344(register ByteArray *self, register int want)
{
    register int tmp = fn_80440490(self);
    int cap = tmp;

    if (cap < want) {
        int dbl = cap * 2;
        int n = want < dbl ? dbl : want;

        fn_802E1970(self, n, 1);
    }
}
}
