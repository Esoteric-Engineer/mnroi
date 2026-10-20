// Obj8N destructor: releases the handle at +0x0, then frees through fn_8045B20C on bit 0 (docs/versus.md section 5, row 2).
extern void fn_802466B8(void *handle);
extern void fn_8045B20C(void *p);

__asm__(".text\n\t.globl _._5Obj8N\n\t.type _._5Obj8N,@function\n_._5Obj8N:");

void fn_804555C8(register int *self, register int inChrg)
{
    if (*self != 0) {
        fn_802466B8((void *)*self);
    }
    if (inChrg & 1) {
        fn_8045B20C(self);
    }
}

__asm__(".size _._5Obj8N, 0x5C");
