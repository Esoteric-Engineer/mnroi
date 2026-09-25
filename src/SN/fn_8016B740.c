extern char lbl_804CFF30[];
extern char lbl_80573680[];

asm void fn_8016B740(void)
{
    // clang-format off
    nofralloc
    lis     r5, (lbl_80573680+0x8870)@ha
    lis     r0, 1
    lwz     r9, (lbl_80573680+0x8870)@l(r5)
    ori     r0, r0, 0xfc00
    lis     r6, 1
    cmplw   r9, r0
    ori     r6, r6, 0xfc00
    bgt     L_8016B768
    lis     r9, (lbl_80573680+0x8870)@ha
    lwz     r6, (lbl_80573680+0x8870)@l(r9)
L_8016B768:
    lwz     r0, (lbl_80573680+0x8870)@l(r5)
    lis     r8, lbl_804CFF30@ha
    li      r10, 2
    lis     r7, (lbl_80573680+0x8868)@ha
    subf    r0, r6, r0
    srwi    r11, r6, 10
    stw     r0, (lbl_80573680+0x8870)@l(r5)
    lis     r9, (lbl_80573680+0x886C)@ha
    stw     r10, lbl_804CFF30@l(r8)
    clrlwi  r0, r6, 22
    stw     r11, (lbl_80573680+0x8868)@l(r7)
    stw     r0, (lbl_80573680+0x886C)@l(r9)
    blr
    // clang-format on
}
