/* This function's only constant, split out of dtk's lbl_8049C190 blob.
   The pragma keeps the 8-byte const out of .sdata2. */
#pragma section R ".rodata.1"
__declspec(section ".rodata.1") const double Fp2UnsignedTwoTo31Const = 2147483648.0;

asm unsigned __cvt_fp2unsigned(register double d)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    lis     r9, Fp2UnsignedTwoTo31Const@ha
    addi    r9, r9, Fp2UnsignedTwoTo31Const@l
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
