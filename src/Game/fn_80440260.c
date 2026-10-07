// Destructor and constructors of the array family at 0x80440260 (docs/versus.md, row 8).
// Names are guesses.

extern char lbl_804F4458[];
extern void fn_8044098C(void *p);
extern void fn_804409E8(void *p);
extern void fn_802E40D8(void *p, int a);

void fn_80440260(register void *self, register int inChrg)
{
    fn_8044098C(self);
    if (inChrg & 1)
        fn_804409E8(self);
}

int *fn_804402B0(register int *self)
{
    self[0] = 0;
    self[1] = 0;
    self[2] = 0x80000000;
    return self;
}

char **fn_804402F0(register char **self, register int a)
{
    fn_802E40D8(self, a);
    *self = lbl_804F4458;
    return self;
}
