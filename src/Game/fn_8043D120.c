// Destructor of an object with vptr lbl_804F4438 that frees itself through fn_8043D09C (docs/versus.md, row 8).

extern char lbl_804F4438[];
extern void fn_8043F644(void *p, int a);
extern void fn_8043D09C(void *p);

void fn_8043D120(register char **self, register int inChrg)
{
    *self = lbl_804F4438;
    fn_8043F644(self, 0);
    if (inChrg & 1)
        fn_8043D09C(self);
}
