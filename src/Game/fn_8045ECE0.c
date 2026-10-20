// HandleE's destructor (vptr reset, release the implementation, deleting variant); hand-written C, see docs/matching_notes.md.
// Defined as fn_8045ECE0 plus an assembler alias, since ngcas rejects a `_._` label.
extern char lbl_804F58B8[];
extern void fn_8042A37C(void *impl);
extern void __builtin_delete(void *p);

typedef struct HandleE {
    void *impl;
    const void *vptr;
} HandleE;

__asm__(".text\n\t.globl _._7HandleE\n\t.type _._7HandleE,@function\n_._7HandleE:");

void fn_8045ECE0(register HandleE *self, register int inChrg)
{
    self->vptr = lbl_804F58B8;
    fn_8042A37C(self->impl);
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}

__asm__(".size _._7HandleE, 0x60");
