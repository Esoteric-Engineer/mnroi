// Obj122 destructor: releases the handle at +0x0, frees through fn_8045D94C on bit 0 (docs/versus.md section 5, row 2).
extern void fn_802466B8(void *handle);
extern void fn_8045D94C(void *p);

__asm__(".text\n\t.globl _._6Obj122\n\t.type _._6Obj122,@function\n_._6Obj122:");

void fn_8045730C(register int *self, register int inChrg)
{
    if (*self != 0) {
        fn_802466B8((void *)*self);
    }
    if (inChrg & 1) {
        fn_8045D94C(self);
    }
}

__asm__(".size _._6Obj122, 0x5C");
