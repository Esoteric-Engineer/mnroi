// Obj8C destructor: releases the handle at +0x0, then frees through fn_8045A1FC on bit 0 (docs/versus.md section 5, row 2).
extern void fn_802466B8(void *handle);
extern void fn_8045A1FC(void *p);

__asm__(".text\n\t.globl _._5Obj8C\n\t.type _._5Obj8C,@function\n_._5Obj8C:");

void fn_804549C0(register int *self, register int inChrg)
{
    if (*self != 0) {
        fn_802466B8((void *)*self);
    }
    if (inChrg & 1) {
        fn_8045A1FC(self);
    }
}

__asm__(".size _._5Obj8C, 0x5C");
