// Obj8K destructor: releases the handle at +0x0, then frees through fn_8045AC6C on bit 0 (docs/versus.md section 5, row 2).
extern void fn_802466B8(void *handle);
extern void fn_8045AC6C(void *p);

__asm__(".text\n\t.globl _._5Obj8K\n\t.type _._5Obj8K,@function\n_._5Obj8K:");

void fn_804551FC(register int *self, register int inChrg)
{
    if (*self != 0) {
        fn_802466B8((void *)*self);
    }
    if (inChrg & 1) {
        fn_8045AC6C(self);
    }
}

__asm__(".size _._5Obj8K, 0x5C");
