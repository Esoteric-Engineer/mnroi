// Level destructor (guessed name): releases the handle at +0x0, then frees through fn_80459E04 on bit 0 (docs/versus.md section 5, row 2).
extern void fn_802466B8(void *handle);
extern void fn_80459E04(void *p);

void fn_80454610(register int *self, register int inChrg)
{
    if (*self != 0) {
        fn_802466B8((void *)*self);
    }
    if (inChrg & 1) {
        fn_80459E04(self);
    }
}
