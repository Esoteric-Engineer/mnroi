extern void* lbl_8066C3B0;
extern void strlen(void);
extern void eofread(void);
extern void __svfscanf(void);

asm int sscanf(const char* str, const char* fmt, ...)
{
    // clang-format off
    nofralloc
    stwu    r1, -0xf8(r1)
    mflr    r0
    stmw    r30, 0xf0(r1)
    stw     r0, 0xfc(r1)
    addi    r11, r1, 0x100
    lis     r0, 0x200
    addi    r30, r1, 0x8
    stw     r11, 0xe4(r1)
    stw     r0, 0xe0(r1)
    mr      r11, r3
    stw     r30, 0xe8(r1)
    stw     r5, 0x10(r1)
    stw     r6, 0x14(r1)
    stw     r7, 0x18(r1)
    stw     r8, 0x1c(r1)
    stw     r9, 0x20(r1)
    stw     r10, 0x24(r1)
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
    li      r0, 4
    mr      r30, r4
    sth     r0, 0x8c(r1)
    mr      r3, r11
    stw     r11, 0x80(r1)
    stw     r11, 0x90(r1)
    bl      strlen
    lwz     r11, lbl_8066C3B0
    lis     r9, eofread@ha
    li      r0, 0
    addi    r9, r9, eofread@l
    stw     r3, 0x94(r1)
    addi    r8, r1, 0xe0
    stw     r9, 0xa0(r1)
    mr      r4, r30
    stw     r11, 0xdc(r1)
    addi    r9, r1, 0x70
    stw     r3, 0x84(r1)
    mr      r5, r9
    stw     r0, 0xcc(r1)
    addi    r3, r1, 0x80
    stw     r0, 0xb0(r1)
    lwz     r11, 0xe0(r1)
    lwz     r10, 8(r8)
    lwz     r0, 4(r8)
    stw     r11, 0x70(r1)
    stw     r0, 4(r9)
    stw     r10, 8(r9)
    bl      __svfscanf
    lwz     r0, 0xfc(r1)
    mtlr    r0
    lmw     r30, 0xf0(r1)
    addi    r1, r1, 0xf8
    blr
    // clang-format on
}
