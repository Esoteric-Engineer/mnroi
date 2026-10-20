// Destructor of the owner of the int array at fn_8044197C (docs/versus.md, row 8).

extern void fn_8044197C(void *p);
extern void fn_804419D8(void *p);

void fn_80441738(register void *self, register int inChrg)
{
    fn_8044197C(self);
    if (inChrg & 1)
        fn_804419D8(self);
}
