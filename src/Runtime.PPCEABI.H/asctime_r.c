extern char lbl_8049C420[];
extern char lbl_8049C435[];
extern char lbl_8049C45C[];
extern void sprintf(void);

asm char* asctime_r(void* tim_p, char* result)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x20(r1)
    mflr    r0
    stmw    r28, 0x10(r1)
    stw     r0, 0x24(r1)
    lwz     r10, 0x10(r3)
    mr      r28, r4
    lwz     r0, 0x18(r3)
    lis     r29, lbl_8049C420@ha
    lwz     r11, 0x14(r3)
    slwi    r6, r10, 1
    add     r6, r6, r10
    slwi    r5, r0, 1
    lis     r30, lbl_8049C435@ha
    lwz     r7, 0xc(r3)
    lwz     r8, 0x8(r3)
    add     r5, r5, r0
    lwz     r9, 0x4(r3)
    addi    r29, r29, lbl_8049C420@l
    lwz     r10, 0x0(r3)
    addi    r30, r30, lbl_8049C435@l
    addi    r11, r11, 0x76c
    lis     r4, lbl_8049C45C@ha
    add     r5, r5, r29
    add     r6, r6, r30
    stw     r11, 0x8(r1)
    addi    r4, r4, lbl_8049C45C@l
    mr      r3, r28
    crclr   4*cr1+eq
    bl      sprintf
    mr      r3, r28
    lwz     r0, 0x24(r1)
    mtlr    r0
    lmw     r28, 0x10(r1)
    addi    r1, r1, 0x20
    blr
    // clang-format on
}
