// String insert-range core (grows through the 0x8044A5F4 factor); see docs/nonmatching.md.
extern "C" {
extern char *fn_80449BE4(register char *self);
extern char *fn_80449C48(register char *self);
extern char *fn_80449DA4(register char *first, register char *last, register char *out);
extern int fn_8044A6F4(void *self);
extern float fn_8044A5F4();
extern void fn_8044A720(char *first, char *last, char *dest);
extern void fn_8044A79C(void *self, int cap);
}

inline int sn_return_decl(int a) { return a; }

extern "C" void fn_80449EEC(register char *self, register char *const &first, register char *const &last, register char *const &pos)
{
    int n = last - first;
    if (n == 0)
    {
        return;
    }
    int newLen = *(int *)self + n;
    if (newLen <= fn_8044A6F4(self))
    {
        if (pos == fn_80449C48(self))
        {
            char *dst = *(char **)(self + 0x48) + *(int *)self;
            fn_80449DA4(first, last, dst);
            *(char *)(*(char **)(self + 0x48) + newLen) = 0;
        }
        else
        {
            fn_8044A720(pos, fn_80449C48(self), pos - fn_80449BE4(self) + *(char **)(self + 0x48) + n);
            fn_80449DA4(first, last, pos - fn_80449BE4(self) + *(char **)(self + 0x48));
            *(char *)(*(char **)(self + 0x48) + newLen) = 0;
        }
        *(int *)self = newLen;
    }
    else
    {
        int newCap = (int)((float)fn_8044A6F4(self) * fn_8044A5F4());
        if (newCap < newLen)
        {
            newCap = newLen;
        }
        int off = pos - fn_80449BE4(self);
        fn_8044A79C(self, newCap);
        fn_80449EEC(self, first, last, fn_80449BE4(self) + off);
    }
}
