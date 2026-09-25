extern char lbl_8057BD88[];
extern void DCInvalidateRange(void);
extern void fn_80168770(void);
extern void fn_80168C9C(void);
extern void fn_8016918C(void);
extern void fn_801691A4(void);

asm void fn_801691B8(void)
{
    // clang-format off
    nofralloc
    mflr    r30
    bl      fn_8016918C
    bne     L_80169218
    lis     r3, (lbl_8057BD88 + 0x118)@h
    ori     r3, r3, (lbl_8057BD88 + 0x118)@l
    li      r4, 0x20
    bl      DCInvalidateRange
    lis     r3, 0xcc00
    ori     r3, r3, 0x6000
    li      r4, 0x14
    stw     r4, 0x0(r3)
    lis     r4, 0x1200
    stw     r4, 0x8(r3)
    li      r4, 0
    stw     r4, 0xc(r3)
    stw     r4, 0x10(r3)
    lis     r4, (lbl_8057BD88 + 0x118)@h
    ori     r4, r4, (lbl_8057BD88 + 0x118)@l
    stw     r4, 0x14(r3)
    li      r4, 0x20
    stw     r4, 0x18(r3)
    li      r4, 3
    stw     r4, 0x1c(r3)
    bl      fn_801691A4
L_80169218:
    addi    r3, r31, 0x708
    stw     r4, 0x0(r3)
    lis     r4, 0x8000
    ori     r4, r4, 0x24
    lwzu    r5, 0x4(r4)
    stwu    r5, 0x4(r3)
    lwzu    r5, 0x4(r4)
    stwu    r5, 0x4(r3)
    addi    r3, r3, 4
    lis     r4, (lbl_8057BD88 + 0x118)@h
    ori     r4, r4, (lbl_8057BD88 + 0x118)@l
    li      r5, 0x20
    bl      fn_80168770
    li      r4, 0x2c
    li      r5, 0x702
    sthbrx  r4, r5, r31
    addi    r3, r31, 0x700
    addi    r4, r4, 8
    lwz     r0, 0x6a4(r31)
    mtlr    r0
    blrl
    cmpwi   r3, 0
    bne     fn_80168C9C
    mtlr    r30
    blr
    // clang-format on
}
