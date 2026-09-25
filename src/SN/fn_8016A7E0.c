extern char lbl_804CFDE2[];
void OSReport(const char* msg, ...);
void fn_80169304(void);
void fn_801694B8(void);
void fn_8016B6AC(void);
void fn_8016B828(void);
void fn_8016BC70(void);
void lbl_8016A8F4(void);
void lbl_8016A948(void);
void lbl_8016A95C(void);

asm void fn_8016A7E0(void)
{
    // clang-format off
    nofralloc
    cmpwi   r3, 7
    bge     L_8016A978
    slwi    r7, r3, 2
    lis     r6, (lbl_804CFDE2 + 0x1E)@h
    ori     r6, r6, (lbl_804CFDE2 + 0x1E)@l
    lwz     r3, 0x18(r31)
    lwz     r4, 0x20(r31)
    lwz     r5, 0x28(r31)
    lwzx    r6, r7, r6
    lis     r7, (lbl_804CFDE2 + 0x9E)@h
    ori     r7, r7, (lbl_804CFDE2 + 0x9E)@l
    stb     r6, 8(r7)
    li      r8, 0x10
    li      r6, 2
    sthbrx  r8, r6, r7
    stw     r3, 0xc(r7)
    stw     r4, 0x10(r7)
    stw     r5, 0x14(r7)
    mr      r3, r7
    li      r4, 0x18
    lwz     r0, 0x6a4(r31)
    mtlr    r0
    blrl
    li      r4, 0
    lis     r3, (lbl_804CFDE2 + 0xB6)@h
    ori     r3, r3, (lbl_804CFDE2 + 0xB6)@l
    stw     r4, 0(r3)
L_8016A84C:
    li      r3, 0
    stw     r3, 0x6b4(r31)
L_8016A854:
    lwz     r0, 0x69c(r31)
    mtlr    r0
    blrl
    cmpwi   r3, 0
    beq     L_8016A854
    stw     r3, 0x6b4(r31)
    cmplwi  r3, 0x8008
    ble     L_8016A87C
    lis     r3, 0
    ori     r3, r3, 0x8008
L_8016A87C:
    mr      r4, r3
    stw     r4, 0x6b8(r31)
    addi    r3, r31, 0x700
    lwz     r0, 0x6a0(r31)
    mtlr    r0
    blrl
    cmpwi   r3, 0
    beq     L_8016A8C0
    lis     r3, (lbl_804CFDE2 + 0xBA)@h
    ori     r3, r3, (lbl_804CFDE2 + 0xBA)@l
L_8016A8A4:
    lwz     r4, 0x6d0(r31)
    cmpwi   r4, 0
    bne     L_8016A8B8
    bl      OSReport
    b       L_8016A84C
L_8016A8B8:
    bl      fn_801694B8
    b       L_8016A84C
L_8016A8C0:
    lbz     r3, 0x700(r31)
    cmplwi  r3, 0x14
    blt     L_8016A8D8
    lis     r3, (lbl_804CFDE2 + 0xD6)@h
    ori     r3, r3, (lbl_804CFDE2 + 0xD6)@l
    b       L_8016A8A4
L_8016A8D8:
    slwi    r3, r3, 2
    lis     r4, (lbl_804CFDE2 + 0x3A)@h
    ori     r4, r4, (lbl_804CFDE2 + 0x3A)@l
    lwzx    r5, r3, r4
    mtlr    r5
    blrl
    b       L_8016A84C
entry lbl_8016A8F4
    li      r4, 0
    sth     r4, 0x702(r31)
    addi    r3, r31, 0x700
    li      r4, 8
    lwz     r0, 0x6a4(r31)
    mtlr    r0
    blrl
    lwz     r3, 0x708(r31)
L_8016A914:
    stw     r3, 0x18(r31)
    lwz     r3, 0x370(r31)
    addi    r3, r3, 4
    stw     r3, 0x370(r31)
    lis     r3, (lbl_804CFDE2 + 0xB6)@h
    ori     r3, r3, (lbl_804CFDE2 + 0xB6)@l
    lwz     r3, 0(r3)
    cmpwi   r3, 0
    beq     fn_80169304
    lwz     r3, 0x378(r31)
    ori     r3, r3, 0x400
    stw     r3, 0x378(r31)
    b       fn_80169304
entry lbl_8016A948
    li      r4, 1
    lis     r3, (lbl_804CFDE2 + 0xB6)@h
    ori     r3, r3, (lbl_804CFDE2 + 0xB6)@l
    stw     r4, 0(r3)
    b       L_8016A84C
entry lbl_8016A95C
    li      r4, 1
    lis     r3, (lbl_804CFDE2 + 0xB6)@h
    ori     r3, r3, (lbl_804CFDE2 + 0xB6)@l
    stw     r4, 0(r3)
    lis     r3, 0xffff
    ori     r3, r3, 0xffff
    b       L_8016A914
L_8016A978:
    mr      r30, r3
    lwz     r3, 0x18(r31)
    lwz     r4, 0x20(r31)
    lwz     r5, 0x28(r31)
    lwz     r6, 0x30(r31)
    li      r7, -1
    li      r8, 0
    cmpwi   r30, 7
    beq     L_8016A9C8
    cmpwi   r30, 0xa
    beq     L_8016A9B8
    cmpwi   r30, 0xb
    beq     L_8016A9C0
    li      r8, 1
    cmpwi   r30, 8
    bne     L_8016A9C0
L_8016A9B8:
    bl      fn_8016B828
    b       L_8016A9CC
L_8016A9C0:
    bl      fn_8016B6AC
    b       L_8016A9CC
L_8016A9C8:
    bl      fn_8016BC70
L_8016A9CC:
    stw     r3, 0x18(r31)
    lwz     r3, 0x370(r31)
    addi    r3, r3, 4
    stw     r3, 0x370(r31)
    b       fn_80169304
    // clang-format on
}
