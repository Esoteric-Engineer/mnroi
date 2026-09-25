extern char lbl_804CFC80[];
void fn_80169BF8(void);

asm void fn_80169B48(void)
{
    // clang-format off
    nofralloc
    stw     r31, 0xdf8(r0)
    mfsrr0  r31
    stw     r31, 0xdf4(r0)
    mfcr    r31
    mtsprg  0, r31
    mfxer   r31
    mtsprg  1, r31
    mfsrr1  r31
    stw     r31, 0xdf0(r0)
    extrwi  r31, r31, 6, 10
    cmpwi   r31, 0x10
    bne     L_80169BA8
    lis     r31, (lbl_804CFC80 + 0x8)@h
    ori     r31, r31, (lbl_804CFC80 + 0x8)@l
    clrlwi  r31, r31, 4
    lwz     r31, 0x0(r31)
    cmpwi   r31, 0
    bne     L_80169BA8
    mfsprg  r31, 0
    mtcrf   255, r31
    mfsprg  r31, 1
    mtxer   r31
    lwz     r31, 0xdf8(r0)
    opword  0x484121E4
L_80169BA8:
    mfsprg  r31, 0
    mtcrf   255, r31
    mfsprg  r31, 1
    mtxer   r31
    mfmsr   r31
    ori     r31, r31, 0x30
    mtsrr1  r31
    lis     r31, fn_80169BF8@h
    ori     r31, r31, fn_80169BF8@l
    mtsrr0  r31
    mflr    r31
    stw     r31, 0xdec(r0)
    bl      L_80169BDC
L_80169BDC:
    mflr    r31
    stw     r31, 0xde8(r0)
    rfi
    opword  0
    opword  0
    opword  0
    opword  0
    // clang-format on
}
