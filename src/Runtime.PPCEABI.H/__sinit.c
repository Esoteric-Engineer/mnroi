extern char lbl_8057C124[];
extern char lbl_8057C4E4[];
extern void snstd(void);
extern void fn_80178684(void);

// __sinit(reent): stdio init. Sets up stdin/stdout/stderr and the first glue.
asm void __sinit(void* reent)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x18(r1)
    mflr    r0
    stmw    r29, 12(r1)
    stw     r0, 0x1c(r1)
    mr      r30, r3
    lis     r9, fn_80178684@ha
    addi    r9, r9, fn_80178684@l
    li      r0, 1
    addi    r29, r30, 0x1e4
    stw     r9, 0x3c(r30)
    stw     r0, 0x38(r30)
    mr      r3, r29
    li      r4, 4
    li      r5, 0
    mr      r6, r30
    bl      snstd
    addi    r3, r30, 0x244
    li      r4, 9
    li      r5, 1
    mr      r6, r30
    bl      snstd
    addi    r3, r30, 0x2a4
    li      r4, 10
    li      r5, 2
    mr      r6, r30
    bl      snstd
    lis     r8, lbl_8057C4E4@ha
    li      r10, 3
    addi    r11, r8, lbl_8057C4E4@l
    stw     r10, 0x1dc(r30)
    stw     r29, 0x1e0(r30)
    lis     r9, lbl_8057C124@ha
    stw     r11, 0x1d8(r30)
    li      r0, 0
    stw     r0, lbl_8057C4E4@l(r8)
    addi    r9, r9, lbl_8057C124@l
    li      r10, 10
    stw     r9, 8(r11)
    stw     r10, 4(r11)
    lwz     r0, 0x1c(r1)
    mtlr    r0
    lmw     r29, 12(r1)
    addi    r1, r1, 0x18
    blr
    // clang-format on
}
