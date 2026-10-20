// Obj8Q destructor: releases the handle at +0x0, frees through fn_8045B750 on bit 0 (docs/versus.md section 5, row 2).
extern void fn_802466B8(void *handle);
extern void fn_8045B750(void *p);

__asm__(".text\n\t.globl _._5Obj8Q\n\t.type _._5Obj8Q,@function\n_._5Obj8Q:");

void fn_804558E8(register int *self, register int inChrg)
{
    if (*self != 0) {
        fn_802466B8((void *)*self);
    }
    if (inChrg & 1) {
        fn_8045B750(self);
    }
}

__asm__(".size _._5Obj8Q, 0x5C");
