#pragma section R ".rodata.1"
__declspec(section ".rodata.1") const int mon_lengths[2][12] = {
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

#pragma force_active on
const int year_lengths[2] = {365, 366};

asm void* gmtime_r(const long* tim_p, void* res)
{
    // clang-format off
    nofralloc
    lwz     r11, 0x0(r3)
    lis     r0, 0xc22e
    ori     r0, r0, 0x4507
    lis     r9, 0x1
    mulhw   r0, r11, r0
    srawi   r10, r11, 31
    ori     r9, r9, 0x5180
    add     r0, r0, r11
    srawi   r0, r0, 16
    subf    r3, r10, r0
    mullw   r9, r3, r9
    subf.   r5, r9, r11
    bge     L_80172DE4
L_80172DD4:
    addis   r0, r5, 0x1
    subi    r3, r3, 0x1
    addic.  r5, r0, 0x5180
    blt     L_80172DD4
L_80172DE4:
    lis     r0, 0x1
    ori     r0, r0, 0x517f
    cmpw    r5, r0
    ble     L_80172E10
    lis     r0, 0x1
    ori     r0, r0, 0x517f
L_80172DFC:
    subis   r9, r5, 0x1
    addi    r3, r3, 0x1
    subi    r5, r9, 0x5180
    cmpw    r5, r0
    bgt     L_80172DFC
L_80172E10:
    lis     r9, 0x91a2
    srawi   r6, r5, 31
    ori     r9, r9, 0xb3c5
    lis     r0, 0x9249
    mulhw   r9, r5, r9
    addi    r10, r3, 0x4
    ori     r0, r0, 0x2493
    mulhw   r0, r10, r0
    lis     r11, 0x8888
    ori     r11, r11, 0x8889
    add     r9, r9, r5
    srawi   r7, r10, 31
    srawi   r9, r9, 11
    subf    r9, r6, r9
    add     r0, r0, r10
    mulli   r8, r9, 0xe10
    srawi   r0, r0, 2
    subf    r0, r7, r0
    stw     r9, 0x8(r4)
    slwi    r9, r0, 3
    subf    r9, r0, r9
    subf    r5, r8, r5
    subf    r10, r9, r10
    mulhw   r11, r5, r11
    srawi   r8, r5, 31
    stw     r10, 0x18(r4)
    cmpwi   r10, 0x0
    add     r11, r11, r5
    srawi   r11, r11, 5
    subf    r11, r8, r11
    mulli   r0, r11, 0x3c
    stw     r11, 0x4(r4)
    subf    r0, r0, r5
    stw     r0, 0x0(r4)
    bge     L_80172EA4
    addi    r0, r10, 0x7
    stw     r0, 0x18(r4)
L_80172EA4:
    li      r11, 0x7b2
    cmpwi   r3, 0x0
    blt     L_80172F20
    lis     r8, 0x51eb
    subi    r7, r13, 0x3278
    ori     r8, r8, 0x851f
    b       L_80172EC8
L_80172EC0:
    subf    r3, r0, r3
    addi    r11, r11, 0x1
L_80172EC8:
    li      r10, 0x0
    srawi   r9, r11, 31
    andi.   r0, r11, 0x3
    bne     L_80172EF0
    mulhw   r0, r11, r8
    srawi   r0, r0, 5
    subf    r0, r9, r0
    mulli   r0, r0, 0x64
    cmpw    r11, r0
    bne     L_80172F08
L_80172EF0:
    mulhw   r0, r11, r8
    srawi   r0, r0, 7
    subf    r0, r9, r0
    mulli   r0, r0, 0x190
    cmpw    r11, r0
    bne     L_80172F0C
L_80172F08:
    li      r10, 0x1
L_80172F0C:
    slwi    r0, r10, 2
    lwzx    r0, r7, r0
    cmpw    r3, r0
    bge     L_80172EC0
    b       L_80172F88
L_80172F20:
    lis     r8, 0x51eb
    subi    r7, r13, 0x3278
    ori     r8, r8, 0x851f
L_80172F2C:
    subi    r11, r11, 0x1
    li      r10, 0x0
    andi.   r0, r11, 0x3
    bne     L_80172F58
    mulhw   r0, r11, r8
    srawi   r9, r11, 31
    srawi   r0, r0, 5
    subf    r0, r9, r0
    mulli   r0, r0, 0x64
    cmpw    r11, r0
    bne     L_80172F74
L_80172F58:
    mulhw   r0, r11, r8
    srawi   r9, r11, 31
    srawi   r0, r0, 7
    subf    r0, r9, r0
    mulli   r0, r0, 0x190
    cmpw    r11, r0
    bne     L_80172F78
L_80172F74:
    li      r10, 0x1
L_80172F78:
    slwi    r9, r10, 2
    lwzx    r0, r9, r7
    add.    r3, r3, r0
    blt     L_80172F2C
L_80172F88:
    subi    r0, r11, 0x76c
    mulli   r10, r10, 0x30
    li      r11, 0x0
    stw     r0, 0x14(r4)
    stw     r11, 0x10(r4)
    lis     r9, mon_lengths@ha
    stw     r3, 0x1c(r4)
    addi    r9, r9, mon_lengths@l
    add     r8, r10, r9
    lwzx    r0, r10, r9
    cmpw    r3, r0
    blt     L_80172FE0
L_80172FB8:
    lwz     r9, 0x10(r4)
    slwi    r0, r9, 2
    lwzx    r11, r8, r0
    addi    r9, r9, 0x1
    stw     r9, 0x10(r4)
    slwi    r10, r9, 2
    subf    r3, r11, r3
    lwzx    r0, r10, r8
    cmpw    r3, r0
    bge     L_80172FB8
L_80172FE0:
    addi    r0, r3, 0x1
    li      r9, -0x1
    stw     r0, 0xc(r4)
    mr      r3, r4
    stw     r9, 0x20(r4)
    blr
    // clang-format on
}
