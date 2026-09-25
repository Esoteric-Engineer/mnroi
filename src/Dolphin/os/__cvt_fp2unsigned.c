extern char lbl_8049C190[];

asm unsigned __cvt_fp2unsigned(register double d)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    lis     r9, (lbl_8049C190 + 0x38)@ha
    addi    r9, r9, (lbl_8049C190 + 0x38)@l
    lfd     f0, 0(r9)
    fcmpu   cr0, f1, f0
    cror    3, 2, 1
    bso     L_big
    fctiwz  f0, f1
    stfd    f0, 8(r1)
    lwz     r3, 12(r1)
    b       L_end
L_big:
    fsub    f0, f1, f0
    fctiwz  f13, f0
    stfd    f13, 8(r1)
    lwz     r3, 12(r1)
    xoris   r3, r3, 0x8000
L_end:
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
