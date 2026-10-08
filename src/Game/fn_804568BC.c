// Destructor (guessed class Obj104): releases the handle at +0x0, frees through fn_8045CF50 on bit 0 (docs/versus.md section 5, row 2).
extern void fn_802466B8(void *handle);
extern void fn_8045CF50(void *p);

void fn_804568BC(register int *self, register int inChrg)
{
    if (*self != 0) {
        fn_802466B8((void *)*self);
    }
    if (inChrg & 1) {
        fn_8045CF50(self);
    }
}
