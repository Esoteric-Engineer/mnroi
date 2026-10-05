// String iterator accessors taking the const Iter overloads; see docs/versus.md.
struct Iter
{
    char *a;
    char *b;
    Iter(char *x, char *y);
    char *begin() const;
    char *end() const;
};

inline int sn_return_decl(int a) { return a; }

extern "C" char *fn_8044A4F4(register char *self)
{
    Iter it(*(char **)(self + 0x48), *(char **)(self + 0x48) + *(int *)self);
    return it.begin();
}

extern "C" char *fn_8044A554(register char *self)
{
    Iter it(*(char **)(self + 0x48), *(char **)(self + 0x48) + *(int *)self);
    return it.end();
}
