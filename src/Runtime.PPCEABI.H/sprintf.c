extern void* lbl_8066C3B0;
extern void vfprintf(void);

asm int sprintf(char* str, const char* fmt, ...)
{
    // clang-format off
    nofralloc
    stwu    r1, -0xf8(r1)
    mflr    r0
    stw     r31, 0xf4(r1)
    stw     r0, 0xfc(r1)
    lis     r31, 0x200
    addi    r0, r1, 0x100
    addi    r11, r1, 0x8
    stw     r0, 0xe4(r1)
    stw     r11, 0xe8(r1)
    mr      r12, r3
    stw     r5, 0x10(r1)
    stw     r6, 0x14(r1)
    stw     r7, 0x18(r1)
    stw     r8, 0x1c(r1)
    stw     r9, 0x20(r1)
    stw     r10, 0x24(r1)
    stw     r31, 0xe0(r1)
    bne     cr1, skipfp
    stfd    f1, 0x28(r1)
    stfd    f2, 0x30(r1)
    stfd    f3, 0x38(r1)
    stfd    f4, 0x40(r1)
    stfd    f5, 0x48(r1)
    stfd    f6, 0x50(r1)
    stfd    f7, 0x58(r1)
    stfd    f8, 0x60(r1)
skipfp:
    lwz     r10, lbl_8066C3B0
    lis     r9, 0x7fff
    ori     r9, r9, 0xffff
    li      r0, 0x208
    stw     r9, 0x94(r1)
    addi    r8, r1, 0xe0
    stw     r9, 0x88(r1)
    addi    r11, r1, 0x70
    sth     r0, 0x8c(r1)
    mr      r5, r11
    stw     r12, 0x90(r1)
    addi    r3, r1, 0x80
    stw     r10, 0xdc(r1)
    stw     r12, 0x80(r1)
    lwz     r0, 4(r8)
    lwz     r10, 8(r8)
    stw     r31, 0x70(r1)
    stw     r0, 4(r11)
    stw     r10, 8(r11)
    bl      vfprintf
    lwz     r9, 0x80(r1)
    li      r0, 0
    stb     r0, 0(r9)
    lwz     r0, 0xfc(r1)
    mtlr    r0
    lwz     r31, 0xf4(r1)
    addi    r1, r1, 0xf8
    blr
    // clang-format on
}
