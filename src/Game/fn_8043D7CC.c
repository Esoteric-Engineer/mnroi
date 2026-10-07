// Destructor of the object derived from the lbl_804F4438 holder (docs/versus.md, row 8).

extern char lbl_804F4418[];
extern void fn_8043D120(void *p, int a);
extern void fn_8043D09C(void *p);

void fn_8043D7CC(register char **self, register int inChrg)
{
    *self = lbl_804F4418;
    fn_8043D120(self, 0);
    if (inChrg & 1)
        fn_8043D09C(self);
}
