// ShapeBase destructor, hand-written C because the DOL keeps the flag in a register; see docs/versus.md.
extern void fn_80436DD0(void *p);
extern char lbl_804F3318[];

void fn_80436EBC(register char *self, register int inChrg)
{
    *(char **)(self + 0x4) = lbl_804F3318;
    if (inChrg & 1)
    {
        fn_80436DD0(self);
    }
}
