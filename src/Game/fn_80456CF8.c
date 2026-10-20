// Release method (the fn_80456C50 shape, docs/versus.md section 5, row 2).
extern void fn_802467D0(void *handle, void *key);

void fn_80456CF8(register int *self)
{
    if (*self != 0) {
        fn_802467D0((void *)*self, self + 1);
    }
}
