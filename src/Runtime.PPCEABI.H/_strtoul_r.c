extern unsigned char _ctype_[];

asm unsigned long _strtoul_r(void* reent, const char* nptr, char** endptr, int base)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    stmw    r30, 0x8(r1)
    lis     r9, (_ctype_+1)@ha
    mr      r31, r3
    addi    r8, r9, (_ctype_+1)@l
    mr      r10, r4
    li      r30, 0
skipws:
    lbz     r9, 0(r10)
    addi    r10, r10, 1
    extsb   r11, r9
    lbzx    r0, r11, r8
    andi.   r9, r0, 8
    bne     skipws
    cmpwi   r11, 0x2d
    bne     notminus
    lbz     r0, 0(r10)
    li      r30, 1
    b       signnext
notminus:
    cmpwi   r11, 0x2b
    bne     signdone
    lbz     r0, 0(r10)
signnext:
    addi    r10, r10, 1
    extsb   r11, r0
signdone:
    cmpwi   r6, 0
    beq     zerox
    cmpwi   r6, 0x10
    bne     basefix
zerox:
    cmpwi   r11, 0x30
    bne     basefix
    lbz     r0, 0(r10)
    extsb   r0, r0
    cmpwi   r0, 0x78
    beq     ishex
    cmpwi   r0, 0x58
    bne     basefix
ishex:
    lbz     r0, 1(r10)
    li      r6, 0x10
    addi    r10, r10, 2
    extsb   r11, r0
basefix:
    cmpwi   r6, 0
    bne     setup
    cmpwi   r11, 0x30
    li      r6, 0xa
    bne     setup
    li      r6, 8
setup:
    li      r0, -1
    li      r3, 0
    divwu   r7, r0, r6
    li      r8, 0
    mullw   r0, r7, r6
    nor     r12, r0, r0
    cmpwi   cr6, r5, 0
    b       cond
loop:
    cmpw    r11, r6
    bge     done
    cmpwi   r8, 0
    blt     overflow
    cmplw   r3, r7
    bgt     overflow
    cmpw    r3, r7
    bne     accum
    cmpw    r11, r12
    ble     accum
overflow:
    li      r8, -1
    b       advance
accum:
    mullw   r3, r3, r6
    li      r8, 1
    add     r3, r3, r11
advance:
    lbz     r0, 0(r10)
    addi    r10, r10, 1
    extsb   r11, r0
cond:
    lis     r9, (_ctype_+1)@ha
    addi    r9, r9, (_ctype_+1)@l
    lbzx    r0, r11, r9
    andi.   r9, r0, 4
    beq     notdigit
    subi    r11, r11, 0x30
    b       loop
notdigit:
    andi.   r9, r0, 3
    beq     done
    andi.   r9, r0, 1
    subi    r0, r11, 0x57
    beq     lower
    subi    r0, r11, 0x37
lower:
    mr      r11, r0
    b       loop
done:
    cmpwi   cr7, r8, 0
    bge     cr7, nooverflow
    li      r0, 0x22
    li      r3, -1
    stw     r0, 0(r31)
    b       endptr_
nooverflow:
    cmpwi   r30, 0
    beq     endptr_
    neg     r3, r3
endptr_:
    beq     cr6, ret
    beq     cr7, store
    subi    r4, r10, 1
store:
    stw     r4, 0(r5)
ret:
    lmw     r30, 0x8(r1)
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
