// Destructors and constructors of the classes around fn_8043E540 (docs/versus.md, row 8).
// Names are guesses.

extern void fn_80440260(void *p, int a);
extern void fn_8043E850(void *p, int a);
extern void fn_8043FE4C(void *p);
extern void fn_8043EEE8(void *p);
extern void fn_804402B0(void *p);
extern void fn_8043FEF0(void *p);
extern void fn_8043FF4C(void *p);
extern void fn_80434988(void *p);
extern void fn_8043D120(void *p, int a);
extern void fn_8043FFC0(void *p);

void fn_8043E7A0(register char *self, register int inChrg)
{
    fn_80440260(self + 0xC, 2);
    fn_8043E850(self, 2);
    if (inChrg & 1)
        fn_8043FE4C(self);
}

char *fn_8043E804(register char *self)
{
    fn_8043EEE8(self);
    fn_804402B0(self + 0xC);
    return self;
}

void fn_8043E850(register void *self, register int inChrg)
{
    fn_8043FEF0(self);
    if (inChrg & 1)
        fn_8043FF4C(self);
}

char *fn_8043E8A0(register char *self)
{
    fn_80434988(self);
    fn_80434988(self + 0x10);
    return self;
}

void fn_8043E8EC(register void *self, register int inChrg)
{
    fn_8043D120(self, 0);
    if (inChrg & 1)
        fn_8043FFC0(self);
}
