// Movie destructor (in-charge flag in a register, so hand-written C); see docs/versus.md section 5.
extern void __builtin_delete(void *p);

__asm__(".text\n\t.globl _._5Movie\n\t.type _._5Movie,@function\n_._5Movie:");

void fn_8043ABD0(register void *self, register int inChrg)
{
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}

__asm__(".size _._5Movie, 0x4C");
