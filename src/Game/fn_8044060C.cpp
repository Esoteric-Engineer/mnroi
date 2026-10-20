// Element address of the growable int array (docs/versus.md, row 8).

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

extern "C" int *fn_8044060C(register IntArray *self, register int i)
{
    return &self->data[i];
}
