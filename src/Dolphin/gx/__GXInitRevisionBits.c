extern void* const __GXData;

asm void __GXInitRevisionBits(void)
{
    // clang-format off
    nofralloc
    li      r11, 0
    slwi    r10, r11, 2
    b       L_80190740
L_80190740:
    li      r0, 2
    mtctr   r0
    li      r7, 1
    li      r5, 8
    lis     r4, -13311
    b       L_80190758
L_80190758:
    b       L_8019075C
L_8019075C:
    lwz     r9,  __GXData
    addi    r8, r10, 28
    addi    r6, r10, 60
    lwzx    r0, r9, r8
    rlwimi  r0, r7, 30, 1, 1
    ori     r3, r11, 128
    stwx    r0, r9, r8
    addi    r10, r10, 4
    addi    r8, r10, 28
    lwzx    r0, r9, r6
    rlwimi  r0, r7, 31, 0, 0
    addi    r11, r11, 1
    stwx    r0, r9, r6
    stb     r5, -32768(r4)
    stb     r3, -32768(r4)
    ori     r3, r11, 128
    addi    r11, r11, 1
    lwzx    r0, r9, r6
    addi    r6, r10, 60
    addi    r10, r10, 4
    stw     r0, -32768(r4)
    lwzx    r0, r9, r8
    rlwimi  r0, r7, 30, 1, 1
    stwx    r0, r9, r8
    addi    r8, r10, 28
    lwzx    r0, r9, r6
    rlwimi  r0, r7, 31, 0, 0
    stwx    r0, r9, r6
    stb     r5, -32768(r4)
    stb     r3, -32768(r4)
    ori     r3, r11, 128
    addi    r11, r11, 1
    lwzx    r0, r9, r6
    addi    r6, r10, 60
    addi    r10, r10, 4
    stw     r0, -32768(r4)
    lwzx    r0, r9, r8
    rlwimi  r0, r7, 30, 1, 1
    stwx    r0, r9, r8
    addi    r8, r10, 28
    lwzx    r0, r9, r6
    rlwimi  r0, r7, 31, 0, 0
    stwx    r0, r9, r6
    stb     r5, -32768(r4)
    stb     r3, -32768(r4)
    ori     r3, r11, 128
    addi    r11, r11, 1
    lwzx    r0, r9, r6
    addi    r6, r10, 60
    addi    r10, r10, 4
    stw     r0, -32768(r4)
    lwzx    r0, r9, r8
    rlwimi  r0, r7, 30, 1, 1
    stwx    r0, r9, r8
    lwzx    r0, r9, r6
    rlwimi  r0, r7, 31, 0, 0
    stwx    r0, r9, r6
    stb     r5, -32768(r4)
    stb     r3, -32768(r4)
    lwzx    r0, r9, r6
    stw     r0, -32768(r4)
    bdnz    L_8019075C
    li      r3, 1
    li      r0, 0
    rlwimi  r0, r3, 0, 31, 31
    mr      r7, r0
    li      r0, 0
    rlwimi  r0, r3, 0, 31, 31
    mr      r8, r0
    rlwimi  r7, r3, 1, 30, 30
    rlwimi  r7, r3, 2, 29, 29
    rlwimi  r7, r3, 3, 28, 28
    rlwimi  r7, r3, 4, 27, 27
    li      r9, 0
    li      r6, 16
    lis     r5, -13311
    rlwimi  r8, r3, 1, 30, 30
    stb     r6, -32768(r5)
    li      r0, 4096
    stw     r0, -32768(r5)
    rlwimi  r7, r3, 5, 26, 26
    rlwimi  r8, r3, 2, 29, 29
    stw     r7, -32768(r5)
    li      r4, 4114
    rlwimi  r9, r3, 0, 31, 31
    stb     r6, -32768(r5)
    rlwimi  r8, r3, 3, 28, 28
    li      r3, 88
    stw     r4, -32768(r5)
    li      r0, 97
    rlwimi  r8, r3, 24, 0, 7
    stw     r9, -32768(r5)
    stb     r0, -32768(r5)
    stw     r8, -32768(r5)
    blr
    // clang-format on
}
