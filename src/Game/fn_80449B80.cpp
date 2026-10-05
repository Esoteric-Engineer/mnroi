// String byte-range copy helpers and the iterator pair; see docs/versus.md.
extern "C" {
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void fn_8044A6AC(void *self);
extern void fn_8044A5B4(void *self);

extern char fn_801ACF38(char *p);
}

struct Iter
{
    char *a;
    char *b;
    Iter(char *x, char *y);
    char *begin();
    char *end();
};

extern "C" char *fn_80449B80(register char *first, register char *last, register char *out)
{
    memcpy(out, first, last - first);
    return out + (last - first);
}

inline int sn_return_decl(int a) { return a; }

extern "C" char *fn_80449BE4(register char *self)
{
    return Iter(*(char **)(self + 0x48), *(char **)(self + 0x48) + *(int *)self).begin();
}

extern "C" char *fn_80449C48(register char *self)
{
    return Iter(*(char **)(self + 0x48), *(char **)(self + 0x48) + *(int *)self).end();
}

extern "C" int fn_80449CAC(register char *self)
{
    return *(char **)(self + 0x48) == self + 8;
}

extern "C" void fn_80449CE8(register void *self)
{
    fn_8044A6AC(self);
}

extern "C" void fn_80449D20(register void *self)
{
    fn_8044A5B4(self);
}

extern "C" char fn_80449D58(register char *self)
{
    register char *p = self;
    return fn_801ACF38(p);
}

extern "C" char *fn_80449DA4(register char *first, register char *last, register char *out)
{
    while (first != last)
    {
        *out++ = *first++;
    }
    return out;
}

extern "C" char *fn_80449DFC(register char *self, register char **first, register char **last)
{
    int off = *first - fn_80449BE4(self);
    fn_80449DA4(*last, fn_80449C48(self), *first);
    int i = *(int *)self - (*last - *first);
    while (i < *(int *)self)
    {
        *(char *)(*(char **)(self + 0x48) + i) = 0;
        i++;
    }
    *(int *)self = *(int *)self - (*last - *first);
    return fn_80449BE4(self) + off;
}
