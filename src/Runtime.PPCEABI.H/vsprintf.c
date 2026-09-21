extern void* lbl_8066C3B0;
extern void fn_80173CB4(void);

asm int vsprintf(char* s, const char* fmt, void* args)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x68(r1)
    mflr    r0
    stw     r0, 0x6c(r1)
    lwz     r10, lbl_8066C3B0
    lis     r9, 0x7fff
    mr      r11, r3
    ori     r9, r9, 0xffff
    li      r0, 0x208
    stw     r9, 0x1c(r1)
    sth     r0, 0x14(r1)
    addi    r3, r1, 0x8
    stw     r9, 0x10(r1)
    stw     r11, 0x18(r1)
    stw     r10, 0x64(r1)
    stw     r11, 0x8(r1)
    bl      fn_80173CB4
    lwz     r9, 0x8(r1)
    li      r0, 0
    stb     r0, 0(r9)
    lwz     r0, 0x6c(r1)
    mtlr    r0
    addi    r1, r1, 0x68
    blr
    // clang-format on
}

asm int vsnprintf(char* s, unsigned long n, const char* fmt, void* args)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x70(r1)
    mflr    r0
    stmw    r30, 0x68(r1)
    stw     r0, 0x74(r1)
    mr      r30, r4
    lwz     r11, lbl_8066C3B0
    mr      r9, r3
    li      r0, 0x208
    mr      r4, r5
    stw     r9, 0x18(r1)
    sth     r0, 0x14(r1)
    mr      r5, r6
    stw     r9, 0x8(r1)
    addi    r3, r1, 0x8
    stw     r11, 0x64(r1)
    stw     r30, 0x10(r1)
    stw     r30, 0x1c(r1)
    bl      fn_80173CB4
    lwz     r9, 0x8(r1)
    li      r0, 0
    cmplw   r3, r30
    stb     r0, 0(r9)
    ble     done
    li      r3, -1
done:
    lwz     r0, 0x74(r1)
    mtlr    r0
    lmw     r30, 0x68(r1)
    addi    r1, r1, 0x70
    blr
    // clang-format on
}
