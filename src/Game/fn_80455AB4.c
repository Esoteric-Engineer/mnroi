// Destructor (guessed class Obj8S): releases the handle at +0x0, frees through fn_8045BA84 on bit 0 (docs/versus.md section 5, row 2).
extern void fn_802466B8(void *handle);
extern void fn_8045BA84(void *p);

void fn_80455AB4(register int *self, register int inChrg)
{
    if (*self != 0) {
        fn_802466B8((void *)*self);
    }
    if (inChrg & 1) {
        fn_8045BA84(self);
    }
}
