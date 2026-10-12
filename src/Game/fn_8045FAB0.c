// SinkB's destructor (vptr lbl_804F5B60) over Sink's, then the class delete; docs/versus.md section 5, row 18.
extern char lbl_804F5B60[];
extern void fn_8045E2A4(void *self, int inChrg);
extern void fn_80460084(void *self);

void fn_8045FAB0(register void **self, register int inChrg)
{
    *self = lbl_804F5B60;
    fn_8045E2A4(self, 0);
    if (inChrg & 1) {
        fn_80460084(self);
    }
}
