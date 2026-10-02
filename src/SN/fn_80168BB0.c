extern void OSReport(const char* msg, ...);
extern void fn_801694B8(void);
extern void fn_80169304(void);
extern char lbl_804CFD6C[];
extern char lbl_804CFC8C[];
extern char lbl_804CFD00[];

asm void fn_80168BB0(void)
{
    // clang-format off
    nofralloc
    li      r3, 0
    stw     r3, 0x6b4(r31)
L_poll:
    lwz     r0, 0x69c(r31)
    mtlr    r0
    blrl
    cmpwi   r3, 0
    beq     L_poll
    stw     r3, 0x6b4(r31)
    cmplwi  r3, 0x8008
    ble     L_clamped
    lis     r3, 0
    ori     r3, r3, 0x8008
L_clamped:
    mr      r4, r3
    stw     r4, 0x6b8(r31)
    addi    r3, r31, 0x700
    lwz     r0, 0x6a0(r31)
    mtlr    r0
    blrl
    cmpwi   r3, 0
    beq     L_recv
    lis     r3, lbl_804CFD6C@h
    ori     r3, r3, lbl_804CFD6C@l
    lwz     r4, 0x6d0(r31)
    cmpwi   r4, 0
    bne     L_err1
    bl      OSReport
    b       L_tail
L_err1:
    bl      fn_801694B8
    b       L_tail
L_recv:
    lwz     r3, 0x6b4(r31)
    lwz     r4, 0x6b8(r31)
    subf    r3, r4, r3
    stw     r3, 0x6b4(r31)
    lbz     r3, 0x700(r31)
    cmplwi  r3, 0x14
    blt     L_dispatch
    lis     r3, (lbl_804CFD6C+0x19)@h
    ori     r3, r3, (lbl_804CFD6C+0x19)@l
    lwz     r4, 0x6d0(r31)
    cmpwi   r4, 0
    bne     L_err2
    bl      OSReport
    b       L_tail
L_err2:
    bl      fn_801694B8
    b       L_tail
L_dispatch:
    lis     r4, lbl_804CFC8C@h
    ori     r4, r4, lbl_804CFC8C@l
    li      r5, 1
    stw     r5, 0(r4)
    slwi    r3, r3, 2
    lis     r4, lbl_804CFD00@h
    ori     r4, r4, lbl_804CFD00@l
    lwzx    r5, r3, r4
    mtlr    r5
    blrl
L_tail:
    lwz     r5, 0x6bc(r31)
    cmpwi   r5, 0
    beq     fn_80168BB0
    b       fn_80169304
    // clang-format on
}
