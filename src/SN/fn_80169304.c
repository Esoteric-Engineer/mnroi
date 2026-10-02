extern char lbl_804CFC70[];
extern void fn_8016951C(void);
extern void fn_80169560(void);

asm void fn_80169304(void)
{
    // clang-format off
    nofralloc
    lwz     r4, 0x6cc(r31)
    cmpwi   r4, 0x3
    bne     L_8016931C
    lis     r5, 0xcc00
    li      r4, 0x1000
    stw     r4, 0x3000(r5)
L_8016931C:
    li      r5, 0x0
    stw     r5, 0x6bc(r31)
    bl      fn_8016951C
    bl      fn_80169560
    lwz     r5, 0x360(r31)
    mtcrf   255, r5
    lwz     r5, 0x358(r31)
    mtlr    r5
    lwz     r5, 0x6c8(r31)
    lis     r4, 0xcc00
    sth     r5, 0x4010(r4)
    lis     r5, lbl_804CFC70@h
    ori     r5, r5, lbl_804CFC70@l
    li      r4, 0x0
    stw     r4, 0x0(r5)
    lwz     r30, 0xf0(r31)
    lwz     r29, 0xe8(r31)
    lwz     r28, 0xe0(r31)
    lwz     r27, 0xd8(r31)
    lwz     r26, 0xd0(r31)
    lwz     r25, 0xc8(r31)
    lwz     r24, 0xc0(r31)
    lwz     r23, 0xb8(r31)
    lwz     r22, 0xb0(r31)
    lwz     r21, 0xa8(r31)
    lwz     r20, 0xa0(r31)
    lwz     r19, 0x98(r31)
    lwz     r18, 0x90(r31)
    lwz     r17, 0x88(r31)
    lwz     r16, 0x80(r31)
    lwz     r15, 0x78(r31)
    lwz     r14, 0x70(r31)
    lwz     r13, 0x68(r31)
    lwz     r12, 0x60(r31)
    lwz     r11, 0x58(r31)
    lwz     r10, 0x50(r31)
    lwz     r9, 0x48(r31)
    lwz     r8, 0x40(r31)
    lwz     r7, 0x38(r31)
    lwz     r6, 0x30(r31)
    lwz     r5, 0x28(r31)
    lwz     r4, 0x20(r31)
    lwz     r2, 0x10(r31)
    lwz     r3, 0x18(r31)
    lwz     r1, 0x8(r31)
    lwz     r0, 0x0(r31)
    lwz     r31, 0xf8(r31)
    rfi     
    // clang-format on
}
