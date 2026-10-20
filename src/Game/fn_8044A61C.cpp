// String iterator pair class, reverse copy and reserve; see docs/versus.md.
extern "C" {
extern void fn_801ACFD4(void *p);
extern void fn_80449378(void *self, int cap);
extern char *fn_80449330(int n);
extern void fn_80449CE8(void *p);
extern int fn_80449CAC(register char *self);
extern char *fn_80449BE4(register char *self);
extern char *fn_80449C48(register char *self);
extern char *fn_80449DA4(register char *first, register char *last, register char *out);
}

struct Iter
{
    char *a;
    char *b;
    Iter(char *x, char *y);
    char *begin();
    char *end();
};

Iter::Iter(register char *x, register char *y) : a(x), b(y)
{
}

char *Iter::begin()
{
    return a;
}

char *Iter::end()
{
    return b;
}

extern "C" void fn_8044A6AC(register void *p)
{
    if (p != 0)
    {
        fn_801ACFD4(p);
    }
    else
    {
    }
    return;
}

extern "C" int fn_8044A6F4(register char *self)
{
    return *(int *)(self + 4);
}

extern "C" char *fn_8044A720(register char *first, register char *last, register char *dest)
{
    int n = last - first;
    dest = dest + n;
    dest = dest - 1;
    last = last - 1;
    while (--n != -1)
    {
        *dest = *last;
        last = last - 1;
        dest = dest - 1;
    }
    return dest;
}

extern "C" void fn_8044A79C(register char *self, register int n)
{
    if (n <= fn_8044A6F4(self))
    {
        return;
    }
    else if (n <= 0x3f)
    {
        fn_80449378(self, n);
    }
    else
    {
        char *p = fn_80449330(n);
        register char *old = fn_80449BE4(self);
        fn_80449DA4(old, fn_80449C48(self), p);
        fn_80449378(self, n);
        if (fn_80449CAC(self) == 0)
        {
            fn_80449CE8(*(char **)(self + 0x48));
        }
        *(char **)(self + 0x48) = p;
        *(char *)(*(char **)(self + 0x48) + *(int *)self) = 0;
    }
}
