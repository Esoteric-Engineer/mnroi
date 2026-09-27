extern void __sinit(void);
extern int fflush(void* stream);
extern unsigned int lbl_8066C3B0;

// fclose(fp): flush if writable, call fp->_close, mark fp closed.
asm int fclose(void* fp)
{
    // clang-format off
    nofralloc
    stwu    r1, -16(r1)
    mflr    r0
    stmw    r30, 8(r1)
    stw     r0, 20(r1)
    mr.     r31, r3
    beq     not_open
    lwz     r0, 92(r31)
    cmpwi   r0, 0
    bne     have_data
    lwz     r0, lbl_8066C3B0
    stw     r0, 92(r31)
have_data:
    lwz     r3, 92(r31)
    lwz     r0, 56(r3)
    cmpwi   r0, 0
    bne     have_init
    crclr   4*cr1+eq
    bl      __sinit
have_init:
    lhz     r0, 12(r31)
    cmpwi   r0, 0
    bne     is_open
not_open:
    li      r3, 0
    b       epilogue
is_open:
    andi.   r9, r0, 8
    beq     no_flush
    mr      r3, r31
    bl      fflush
    mr      r30, r3
    b       have_result
no_flush:
    li      r30, 0
have_result:
    lwz     r0, 44(r31)
    cmpwi   r0, 0
    beq     done
    lwz     r3, 28(r31)
    mtlr    r0
    blrl
    cmpwi   r3, 0
    bge     done
    li      r30, -1
done:
    li      r0, 0
    mr      r3, r30
    sth     r0, 12(r31)
epilogue:
    lwz     r0, 20(r1)
    mtlr    r0
    lmw     r30, 8(r1)
    addi    r1, r1, 16
    blr
    // clang-format on
}
