// Destructors, a three-vector copy, a capacity getter and vptr constructors (docs/versus.md, row 8).
// Names are guesses.

extern char lbl_804F4540[], lbl_804F4528[], lbl_804F44F0[], lbl_804F44D0[];
extern void fn_802E407C(void *p, int a);
extern void fn_802E4034(void *p);
extern void fn_80436370(void *dst, const void *src);
extern void fn_80440B78(void *p);
extern void fn_80440BD4(void *p);

void fn_804403CC(register void *self, register int inChrg)
{
    fn_802E407C(self, 0);
    if (inChrg & 1)
        fn_802E4034(self);
}

void *fn_80440420(register char *self, register const char *src)
{
    fn_80436370(self, src);
    fn_80436370(self + 0x10, src + 0x10);
    fn_80436370(self + 0x20, src + 0x20);
    return self;
}

int fn_80440490(register int *self)
{
    return self[2] & 0x3FFFFFFF;
}

void fn_804404C0(register void *self, register int inChrg)
{
    fn_80440B78(self);
    if (inChrg & 1)
        fn_80440BD4(self);
}

char **fn_80440510(register char **self)
{
    *self = lbl_804F4540;
    return self;
}

char **fn_80440544(register char **self)
{
    *self = lbl_804F4528;
    return self;
}

char **fn_80440578(register char **self)
{
    *self = lbl_804F44F0;
    return self;
}

char **fn_804405AC(register char **self)
{
    *self = lbl_804F44D0;
    return self;
}

int fn_804405E0(register int *self)
{
    return self[1];
}
