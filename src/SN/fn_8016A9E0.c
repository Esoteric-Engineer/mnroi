extern void fn_8016AAD0(void);
extern void fn_8016AAD8(void);
extern void fn_8016AAE0(void);
extern void fn_8016AAE8(void);
extern void fn_8016AAF0(void);
extern void fn_8016AAF8(void);
extern void fn_8016AB00(void);
extern void fn_8016AB08(void);
extern void fn_8016AB10(void);
extern void fn_8016AB18(void);
extern void fn_8016AB20(void);
extern void fn_8016AB28(void);

asm void fn_8016A9E0(void)
{
    // clang-format off
    nofralloc
    li      r3, 0x10
    lis     r4, fn_8016AAD0@h
    ori     r4, r4, fn_8016AAD0@l
    stw     r3, 0(r4)
    li      r3, 0x11
    lis     r4, fn_8016AAD8@h
    ori     r4, r4, fn_8016AAD8@l
    stw     r3, 0(r4)
    li      r3, 0x12
    lis     r4, fn_8016AAE0@h
    ori     r4, r4, fn_8016AAE0@l
    stw     r3, 0(r4)
    li      r3, 0x13
    lis     r4, fn_8016AAE8@h
    ori     r4, r4, fn_8016AAE8@l
    stw     r3, 0(r4)
    li      r3, 0x14
    lis     r4, fn_8016AAF0@h
    ori     r4, r4, fn_8016AAF0@l
    stw     r3, 0(r4)
    li      r3, 0x15
    lis     r4, fn_8016AAF8@h
    ori     r4, r4, fn_8016AAF8@l
    stw     r3, 0(r4)
    li      r3, 0x16
    lis     r4, fn_8016AB00@h
    ori     r4, r4, fn_8016AB00@l
    stw     r3, 0(r4)
    li      r3, 0x17
    lis     r4, fn_8016AB08@h
    ori     r4, r4, fn_8016AB08@l
    stw     r3, 0(r4)
    li      r3, 0x18
    lis     r4, fn_8016AB10@h
    ori     r4, r4, fn_8016AB10@l
    stw     r3, 0(r4)
    li      r3, 0x19
    lis     r4, fn_8016AB18@h
    ori     r4, r4, fn_8016AB18@l
    stw     r3, 0(r4)
    li      r3, 0x1a
    lis     r4, fn_8016AB20@h
    ori     r4, r4, fn_8016AB20@l
    stw     r3, 0(r4)
    li      r3, 0x1b
    lis     r4, fn_8016AB28@h
    ori     r4, r4, fn_8016AB28@l
    stw     r3, 0(r4)
    blr
    // clang-format on
}
