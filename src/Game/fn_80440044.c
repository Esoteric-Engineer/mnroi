// Constructor, destructor and a forwarder over fn_8043EBB4 (docs/versus.md, row 8).
// Names are guesses.

extern char lbl_804F4268[];
extern void fn_80434988(void *p);
extern void fn_804404C0(void *p, int a);
extern void fn_8043D120(void *p, int a);
extern void fn_80440874(void *p);
extern int fn_8043EBB4(void *self, int a, int b);

char *fn_80440044(register char *self)
{
    fn_80434988(self);
    return self;
}

void fn_80440084(register char **self, register int inChrg)
{
    *self = lbl_804F4268;
    fn_804404C0((char *)self + 0x20, 2);
    fn_8043D120(self, 0);
    if (inChrg & 1)
        fn_80440874(self);
}

int fn_804400F4(register void *self, register int *p, register int b)
{
    return fn_8043EBB4(self, p[1], b);
}
