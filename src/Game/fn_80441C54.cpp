// Flag-mask clear and an argument swap forwarder (docs/versus.md, row 8).

struct Flagged
{
    unsigned int flags; // +0x0
};

extern "C" int fn_8004DCA0(void *a, void *b);

extern "C" void fn_80441C54(register Flagged *self, register unsigned int mask)
{
    self->flags &= ~mask;
}

inline int sn_return_decl(int a)
{
    return a;
}

extern "C" int fn_80441C90(register void *a, register void *b)
{
    return fn_8004DCA0(b, a);
}
