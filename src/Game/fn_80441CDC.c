// Destructor of the six-vptr class built by fn_8043FA30 (docs/versus.md, row 8).

extern char lbl_8050A5B8[], lbl_804F4640[], lbl_804F4620[], lbl_8050A5A0[], lbl_804F4688[], lbl_804F4660[];
extern void fn_80380840(void *p, int a);
extern void fn_8043DAEC(void *p);

void fn_80441CDC(register char *self, register int inChrg)
{
    *(char **)(self + 0x8) = lbl_8050A5B8;
    *(char **)(self + 0xC) = lbl_804F4640;
    *(char **)(self + 0x10) = lbl_804F4620;
    *(char **)(self + 0x14) = lbl_8050A5A0;
    *(char **)(self + 0x18) = lbl_804F4688;
    *(char **)self = lbl_804F4660;
    fn_80380840(self, 0);
    if (inChrg & 1)
        fn_8043DAEC(self);
}
