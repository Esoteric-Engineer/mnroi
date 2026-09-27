extern void vfprintf(void);

asm int fprintf(void* fp, const char* fmt, ...)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x90(r1)
    mflr    r0
    stw     r0, 0x94(r1)
    lis     r12, 0x200
    addi    r0, r1, 0x98
    addi    r11, r1, 0x8
    stw     r0, 0x84(r1)
    stw     r11, 0x88(r1)
    stw     r5, 0x10(r1)
    stw     r6, 0x14(r1)
    stw     r7, 0x18(r1)
    stw     r8, 0x1c(r1)
    stw     r9, 0x20(r1)
    stw     r10, 0x24(r1)
    stw     r12, 0x80(r1)
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
    addi    r11, r1, 0x80
    addi    r9, r1, 0x70
    lwz     r10, 8(r11)
    mr      r5, r9
    lwz     r0, 4(r11)
    stw     r12, 0x70(r1)
    stw     r0, 4(r9)
    stw     r10, 8(r9)
    bl      vfprintf
    lwz     r0, 0x94(r1)
    mtlr    r0
    addi    r1, r1, 0x90
    blr
    // clang-format on
}
