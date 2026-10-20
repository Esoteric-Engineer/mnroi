// Obj8I destructor: releases the handle at +0x0, then frees through fn_8045A978 on bit 0 (docs/versus.md section 5, row 2).
extern void fn_802466B8(void *handle);
extern void fn_8045A978(void *p);

__asm__(".text\n\t.globl _._5Obj8I\n\t.type _._5Obj8I,@function\n_._5Obj8I:");

void fn_80454FA4(register int *self, register int inChrg)
{
    if (*self != 0) {
        fn_802466B8((void *)*self);
    }
    if (inChrg & 1) {
        fn_8045A978(self);
    }
}

__asm__(".size _._5Obj8I, 0x5C");
