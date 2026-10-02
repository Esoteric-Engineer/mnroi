static char lower[] = "0123456789abcdefghijklmnopqrstuvwxyz";
extern void strrev(char* s);

asm char* itoa(int value, char* str, int base)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x8(r1)
    mflr    r0
    stw     r0, 0xc(r1)
    srwi.   r0, r3, 31
    beq     L_pos
    cmpwi   r5, 0xa
    bne     L_pos
    neg     r3, r3
L_pos:
    lis     r9, lower@ha
    cmpwi   cr7, r0, 0
    addi    r8, r9, lower@l
    li      r10, 0
L_loop:
    divwu   r0, r3, r5
    mullw   r9, r0, r5
    subf    r9, r9, r3
    lbzx    r11, r8, r9
    mr.     r3, r0
    stbx    r11, r4, r10
    addi    r10, r10, 1
    bne     L_loop
    beq     cr7, L_term
    li      r0, 0x2d
    stbx    r0, r4, r10
    addi    r10, r10, 1
L_term:
    stbx    r3, r4, r10
    mr      r3, r4
    bl      strrev
    lwz     r0, 0xc(r1)
    mtlr    r0
    addi    r1, r1, 0x8
    blr
    // clang-format on
}
