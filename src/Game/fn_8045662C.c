// Obj98 destructor: releases the handle at +0x0, frees through fn_8045CC7C on bit 0 (docs/versus.md section 5, row 2).
extern void fn_802466B8(void *handle);
extern void fn_8045CC7C(void *p);

__asm__(".text\n\t.globl _._5Obj98\n\t.type _._5Obj98,@function\n_._5Obj98:");

void fn_8045662C(register int *self, register int inChrg)
{
    if (*self != 0) {
        fn_802466B8((void *)*self);
    }
    if (inChrg & 1) {
        fn_8045CC7C(self);
    }
}

__asm__(".size _._5Obj98, 0x5C");
