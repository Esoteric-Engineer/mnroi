// Obj8W destructor: releases the handle at +0x0, frees through fn_8045BF18 on bit 0 (docs/versus.md section 5, row 2).
extern void fn_802466B8(void *handle);
extern void fn_8045BF18(void *p);

__asm__(".text\n\t.globl _._5Obj8W\n\t.type _._5Obj8W,@function\n_._5Obj8W:");

void fn_80455D94(register int *self, register int inChrg)
{
    if (*self != 0) {
        fn_802466B8((void *)*self);
    }
    if (inChrg & 1) {
        fn_8045BF18(self);
    }
}

__asm__(".size _._5Obj8W, 0x5C");
