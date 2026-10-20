// Release method of the second record-table group (same shape as fn_80456064; docs/versus.md section 5, row 2).
extern void fn_802467D0(void *handle, void *key);

void fn_804561D4(register int *self)
{
    if (*self != 0) {
        fn_802467D0((void *)*self, self + 1);
    }
}
