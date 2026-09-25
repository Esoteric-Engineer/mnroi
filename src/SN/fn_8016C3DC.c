extern char lbl_804CFF30[];
extern char lbl_8057BD88[];
extern void fn_8016BF04(void);
extern void fn_8016C094(void);
extern void __OSSetExceptionHandler(void);

asm void fn_8016C3DC(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -8(r1)
    mflr    r0
    stw     r0, 0xc(r1)
    lis     r9, (lbl_804CFF30+0x10)@ha
    lwz     r0, (lbl_804CFF30+0x10)@l(r9)
    cmpwi   r0, -0x8000
    bne     L_end
    li      r0, 0
    li      r6, 1
    lis     r4, (lbl_8057BD88+0x1D8)@ha
    lis     r5, (lbl_8057BD88+0x198)@ha
    lis     r8, (lbl_8057BD88+0x1DC)@ha
    li      r11, -1
    lis     r10, (lbl_8057BD88+0x1E4)@ha
    lis     r7, (lbl_8057BD88+0x1E9)@ha
    lis     r9, (lbl_8057BD88+0x1E8)@ha
    stw     r0, (lbl_8057BD88+0x1D8)@l(r4)
    stw     r11, (lbl_8057BD88+0x1DC)@l(r8)
    stw     r0, (lbl_8057BD88+0x1E4)@l(r10)
    stb     r6, (lbl_8057BD88+0x1E8)@l(r9)
    stw     r0, (lbl_8057BD88+0x198)@l(r5)
    stb     r6, (lbl_8057BD88+0x1E9)@l(r7)
    bl      fn_8016BF04
    lis     r4, fn_8016C094@ha
    li      r3, 2
    addi    r4, r4, fn_8016C094@l
    bl      __OSSetExceptionHandler
L_end:
    lwz     r0, 0xc(r1)
    mtlr    r0
    addi    r1, r1, 8
    blr
    // clang-format on
}
