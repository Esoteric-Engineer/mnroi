// Obj8J destructor: releases the handle at +0x0, then frees through fn_8045AB14 on bit 0 (docs/versus.md section 5, row 2).
extern void fn_802466B8(void *handle);
extern void fn_8045AB14(void *p);

__asm__(".text\n\t.globl _._5Obj8J\n\t.type _._5Obj8J,@function\n_._5Obj8J:");

void fn_804550D8(register int *self, register int inChrg)
{
    if (*self != 0) {
        fn_802466B8((void *)*self);
    }
    if (inChrg & 1) {
        fn_8045AB14(self);
    }
}

__asm__(".size _._5Obj8J, 0x5C");
