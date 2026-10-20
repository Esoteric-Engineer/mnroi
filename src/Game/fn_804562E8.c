// Obj93 destructor: releases the handle at +0x0, frees through fn_8045C78C on bit 0 (docs/versus.md section 5, row 2).
extern void fn_802466B8(void *handle);
extern void fn_8045C78C(void *p);

__asm__(".text\n\t.globl _._5Obj93\n\t.type _._5Obj93,@function\n_._5Obj93:");

void fn_804562E8(register int *self, register int inChrg)
{
    if (*self != 0) {
        fn_802466B8((void *)*self);
    }
    if (inChrg & 1) {
        fn_8045C78C(self);
    }
}

__asm__(".size _._5Obj93, 0x5C");
