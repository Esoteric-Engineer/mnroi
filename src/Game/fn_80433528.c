// Link's destructor (vptr reset, release the implementation, deleting variant); hand-written C because the DOL keeps the flag in r30.
// Defined as fn_80433528 plus an assembler alias, since ngcas rejects a `_._` label (docs/nonmatching.md).
extern char lbl_804F3148[];
extern void fn_8042A37C(void *impl);
extern void __builtin_delete(void *p);

typedef struct Link {
    void *impl;
    const void *vptr;
} Link;

__asm__(".text\n\t.globl _._4Link\n\t.type _._4Link,@function\n_._4Link:");

void fn_80433528(register Link *self, register int inChrg)
{
    self->vptr = lbl_804F3148;
    fn_8042A37C(self->impl);
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}

__asm__(".size _._4Link, 0x60");
