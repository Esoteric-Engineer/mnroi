extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int);
extern void __AXSetPBDefault(void);
extern void* lbl_8064F228[];

asm void* AXAcquireVoice(void)
{
    // clang-format off
    nofralloc
    mflr    r0
    lis     r6, lbl_8064F228@ha
    stw     r0, 0x4(r1)
    stwu    r1, -0x38(r1)
    stmw    r26, 0x20(r1)
    addi    r28, r3, 0x0
    addi    r29, r4, 0x0
    addi    r30, r5, 0x0
    addi    r27, r6, lbl_8064F228@l
    bl      OSDisableInterrupts
    lwz     r4, 0x0(r27)
    addi    r31, r3, 0x0
    cmplwi  r4, 0x0
    beq     L_80406C60
    lwz     r0, 0x0(r4)
    stw     r0, 0x0(r27)
L_80406C60:
    cmplwi  r4, 0x0
    addi    r26, r4, 0x0
    bne     L_80406D1C
    subi    r0, r28, 0x1
    cmplwi  r28, 0x1
    mtctr   r0
    addi    r5, r27, 0x4
    addi    r6, r27, 0x84
    ble     L_80406D1C
L_80406C84:
    lwz     r3, 0x0(r5)
    li      r4, 0x0
    cmplwi  r3, 0x0
    beq     L_80406CD4
    lwz     r7, 0x0(r6)
    cmplw   r3, r7
    bne     L_80406CB4
    li      r0, 0x0
    stw     r0, 0x0(r6)
    mr      r4, r3
    stw     r0, 0x0(r5)
    b       L_80406CD4
L_80406CB4:
    cmplwi  r7, 0x0
    beq     L_80406CD4
    lwz     r3, 0x4(r7)
    li      r0, 0x0
    addi    r4, r7, 0x0
    stw     r3, 0x0(r6)
    lwz     r3, 0x0(r6)
    stw     r0, 0x0(r3)
L_80406CD4:
    cmplwi  r4, 0x0
    addi    r26, r4, 0x0
    beq     L_80406D10
    lhz     r0, 0x146(r4)
    cmplwi  r0, 0x1
    bne     L_80406CF4
    li      r0, 0x1
    stw     r0, 0x20(r4)
L_80406CF4:
    lwz     r12, 0x10(r4)
    cmplwi  r12, 0x0
    beq     L_80406D1C
    mtlr    r12
    addi    r3, r26, 0x0
    blrl    
    b       L_80406D1C
L_80406D10:
    addi    r5, r5, 0x4
    addi    r6, r6, 0x4
    bdnz    L_80406C84
L_80406D1C:
    cmplwi  r26, 0x0
    beq     L_80406D74
    slwi    r0, r28, 2
    add     r4, r27, r0
    lwz     r3, 0x0(r4)
    li      r0, 0x0
    stw     r3, 0x0(r26)
    stw     r0, 0x4(r26)
    lwz     r0, 0x0(r26)
    cmplwi  r0, 0x0
    beq     L_80406D58
    lwz     r3, 0x0(r4)
    stw     r26, 0x4(r3)
    stw     r26, 0x0(r4)
    b       L_80406D60
L_80406D58:
    stw     r26, 0x80(r4)
    stw     r26, 0x0(r4)
L_80406D60:
    stw     r28, 0xc(r26)
    mr      r3, r26
    stw     r29, 0x10(r26)
    stw     r30, 0x14(r26)
    bl      __AXSetPBDefault
L_80406D74:
    mr      r3, r31
    bl      OSRestoreInterrupts
    mr      r3, r26
    lmw     r26, 0x20(r1)
    lwz     r0, 0x3c(r1)
    addi    r1, r1, 0x38
    mtlr    r0
    blr     
    // clang-format on
}
