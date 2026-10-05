// String reference-count release and buffer swap; layout in docs/versus.md.
extern "C" {
extern void fn_8044A880(void *obj, int inChrg);
extern void fn_80449378(void *self, int cap);
extern int fn_8044A6F4(void *self);
extern int fn_80449CAC(register char *self);
extern char *fn_80449DA4(register char *first, register char *last, register char *out);
}

inline int sn_return_decl(int a) { return a; }

extern "C" void fn_8044A108(register int *count, register void *obj)
{
    *count = *count - 1;
    if (*count == 0)
    {
        if (obj != 0)
        {
            fn_8044A880(obj, 3);
        }
        else
        {
        }
    }
}

extern "C" void fn_8044A16C(register char *self, register char *other)
{
    int tmp = *(int *)other;
    *(int *)other = *(int *)self;
    *(int *)self = tmp;
    int cap = fn_8044A6F4(other);
    fn_80449378(other, fn_8044A6F4(self));
    fn_80449378(self, cap);
    int selfInline = fn_80449CAC(self);
    int otherInline = fn_80449CAC(other);
    char *selfPtr = *(char **)(other + 0x48);
    char *otherPtr = *(char **)(self + 0x48);
    if (otherInline)
    {
        *(char **)(self + 0x48) = self + 8;
    }
    else
    {
        *(char **)(self + 0x48) = selfPtr;
    }
    if (selfInline)
    {
        *(char **)(other + 0x48) = other + 8;
    }
    else
    {
        *(char **)(other + 0x48) = otherPtr;
    }
    if (otherInline == 0 && selfInline == 0)
    {
        return;
    }
    char buf[0x40];
    buf[0x3f] = 0;
    fn_80449DA4(self + 8, self + 0x48, buf);
    fn_80449DA4(other + 8, other + 0x48, self + 8);
    fn_80449DA4(buf, buf + 0x40, other + 8);
}
