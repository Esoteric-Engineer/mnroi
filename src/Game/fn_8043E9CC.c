// Constructors over the Holder and Flag classes, and an offset adder (docs/versus.md, row 8).
// Names are guesses.

extern char lbl_804F4268[];
extern void __6Holder(void *p);
extern void fn_80440044(void *p);
extern void fn_8043F818(void *p);
extern void fn_804363B8(void *p);
extern void __4Flagi(void *p, int a);

char *fn_8043E9CC(register char *self)
{
    __6Holder(self);
    *(char **)self = lbl_804F4268;
    fn_80440044(self + 0x10);
    fn_8043F818(self + 0x20);
    fn_804363B8(self + 0x10);
    return self;
}

char *fn_8043EA3C(register char *self)
{
    __4Flagi(self + 0x10, 0);
    __4Flagi(self + 0x11, 0);
    return self;
}

int fn_8043EA94(register int *self, register int off)
{
    return off + *self;
}
