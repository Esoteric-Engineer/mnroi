// Release method: hands the handle at +0x0 back with &self[1] (docs/versus.md section 5, row 2).
extern void fn_802467D0(void *handle, void *key);

void fn_80456064(register int *self)
{
    if (*self != 0) {
        fn_802467D0((void *)*self, self + 1);
    }
}
