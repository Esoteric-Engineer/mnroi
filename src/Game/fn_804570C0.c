// Destructor (guessed class Obj119): releases the handle at +0x0, frees through fn_8045D7BC on bit 0 (docs/versus.md section 5, row 2).
extern void fn_802466B8(void *handle);
extern void fn_8045D7BC(void *p);

void fn_804570C0(register int *self, register int inChrg)
{
    if (*self != 0) {
        fn_802466B8((void *)*self);
    }
    if (inChrg & 1) {
        fn_8045D7BC(self);
    }
}
