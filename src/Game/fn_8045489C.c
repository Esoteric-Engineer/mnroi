// Obj8B destructor: releases the handle at +0x0, then frees through fn_8045A0A4 on bit 0 (docs/versus.md section 5, row 2).
extern void fn_802466B8(void *handle);
extern void fn_8045A0A4(void *p);

__asm__(".text\n\t.globl _._5Obj8B\n\t.type _._5Obj8B,@function\n_._5Obj8B:");

void fn_8045489C(register int *self, register int inChrg)
{
    if (*self != 0) {
        fn_802466B8((void *)*self);
    }
    if (inChrg & 1) {
        fn_8045A0A4(self);
    }
}

__asm__(".size _._5Obj8B, 0x5C");
