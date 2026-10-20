// Release method of the third record-table group (same shape as fn_804561D4; docs/versus.md section 5, row 2).
extern void fn_802467D0(void *handle, void *key);

void fn_80456518(register int *self)
{
    if (*self != 0) {
        fn_802467D0((void *)*self, self + 1);
    }
}
