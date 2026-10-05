// String copy-construct and append helpers, plus a release-and-set pointer setter; see docs/versus.md.
extern "C" {
extern void fn_80449298(void *self, int inChrg) __asm__("_._6String");
extern void *fn_804493A0(void *self, const char *s) __asm__("__6StringPCc");
extern void *fn_804496F4(void *self, void *src) __asm__("__6StringRC6String");
extern void fn_8044A108(void *a, void *b);
extern void fn_8044A16C(void *self, void *src);
extern void fn_8044A2D8(void *self, void *const &a, void *const &b, void *const &c);
extern void fn_8044A2D8_s(void *self, const char *const &a, const char *const &b, void *const &c) __asm__("fn_8044A2D8");
extern void *fn_8044A4F4(void *self);
extern void *fn_8044A554(void *self);
extern void *fn_80449C48(void *self);
}

inline int sn_return_decl(int a) { return a; }

extern "C" void *fn_80449930(register void *self, register void *src)
{
    char tmp[0x50];
    fn_804496F4(tmp, src);
    fn_8044A16C(self, tmp);
    fn_80449298(tmp, 2);
    return self;
}

extern "C" int fn_80449990(register int *self)
{
    return *self;
}

extern "C" void fn_804499BC(register int *self, register int v)
{
    if (*self != 0)
    {
        fn_8044A108((void *)*self, (void *)*self);
    }
    *self = v;
}

extern "C" void *fn_80449A0C(register void *self, register const char *src)
{
    char tmp[0x50];
    fn_804493A0(tmp, src);
    fn_8044A16C(self, tmp);
    fn_80449298(tmp, 2);
    return self;
}

extern "C" void *fn_80449A6C(register void *self, register const char *s)
{
    const char *p = s;
    while (*p != 0)
    {
        p++;
    }
    fn_8044A2D8_s(self, s, p, fn_80449C48(self));
    return self;
}

extern "C" void *fn_80449B04(register void *self, register void *other)
{
    fn_8044A2D8(self, fn_8044A4F4(other), fn_8044A554(other), fn_80449C48(self));
    return self;
}
