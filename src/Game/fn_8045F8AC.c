// Block's destructor (vtable _vt.5Block, member at +0x8); hand-written C, see docs/matching_notes.md.
// Defined as fn_8045F8AC plus an assembler alias, since ngcas rejects a `_._` label.
extern char vtBlock[] __asm__("_vt.5Block");
extern void fn_80126AF8(void *member);
extern void fn_80460084(void *self);

typedef struct Block {
    const void *vptr; // +0x0
    int pad;          // +0x4
    int member;       // +0x8
} Block;

__asm__(".text\n\t.globl _._5Block\n\t.type _._5Block,@function\n_._5Block:");

void fn_8045F8AC(register Block *self, register int inChrg)
{
    self->vptr = vtBlock;
    fn_80126AF8(&self->member);
    if (inChrg & 1) {
        fn_80460084(self);
    }
}

__asm__(".size _._5Block, 0x60");
