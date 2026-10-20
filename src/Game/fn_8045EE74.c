// HandleF's destructor (vptr reset, release the implementation, deleting variant); hand-written C, see docs/matching_notes.md.
// Defined as fn_8045EE74 plus an assembler alias, since ngcas rejects a `_._` label.
extern char lbl_804F58A0[];
extern void fn_8042A37C(void *impl);
extern void __builtin_delete(void *p);

typedef struct HandleF {
    void *impl;
    const void *vptr;
} HandleF;

__asm__(".text\n\t.globl _._7HandleF\n\t.type _._7HandleF,@function\n_._7HandleF:");

void fn_8045EE74(register HandleF *self, register int inChrg)
{
    self->vptr = lbl_804F58A0;
    fn_8042A37C(self->impl);
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}

__asm__(".size _._7HandleF, 0x60");
