// Destructor of a multiply-inherited object (five vptrs at +0x0, +0x8..+0x14), freed by fn_8043DAEC (docs/versus.md, row 8).

extern char lbl_804F4400[], lbl_804F43E0[], lbl_804F43C0[], lbl_804F43A8[], lbl_804F4388[];
extern void fn_8043F8B0(void *p, int a);
extern void fn_8043F858(void *p, int a);
extern void fn_8043D120(void *p, int a);
extern void fn_8043DAEC(void *p);

void fn_8043D9B0(register char *self, register int inChrg)
{
    *(char **)(self + 0x8) = lbl_804F4400;
    *(char **)(self + 0xC) = lbl_804F43E0;
    *(char **)(self + 0x10) = lbl_804F43C0;
    *(char **)(self + 0x14) = lbl_804F43A8;
    *(char **)self = lbl_804F4388;
    fn_8043F8B0(self + 0x10, 0);
    fn_8043F858(self + 0xC, 0);
    fn_8043D120(self, 0);
    if (inChrg & 1)
        fn_8043DAEC(self);
}
