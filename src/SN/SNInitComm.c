extern char lbl_804CFDE2[];
extern char lbl_8057BD88[];
void OSDisableInterrupts(void);
void OSRestoreInterrupts(void);
void __OSMaskInterrupts(void);
void SNSelect(void);
void SNDeselect(void);
void SNWiggleSelect(void);
int SNRead8(void);
void SNWrite8(int arg);
int SNRead32(void);

asm void SNInitComm(void)
{
    // clang-format off
    nofralloc
    mflr    r0
    stw     r0, 0x4(r1)
    stwu    r1, -0x10(r1)
    stw     r31, 0x8(r1)
    stw     r30, 0xc(r1)
    addi    r31, r4, 0x0
    addi    r30, r3, 0x0
    bl      OSDisableInterrupts
    lis     r0, (lbl_804CFDE2 + 0x146)@h
    ori     r0, r0, (lbl_804CFDE2 + 0x146)@l
    lis     r4, (lbl_804CFDE2 + 0x142)@h
    ori     r4, r4, (lbl_804CFDE2 + 0x142)@l
    stw     r0, 0x0(r4)
    stw     r4, 0x0(r30)
    addi    r30, r3, 0x0
    lis     r3, (lbl_804CFDE2 + 0x13E)@h
    ori     r3, r3, (lbl_804CFDE2 + 0x13E)@l
    stw     r31, 0x0(r3)
    lis     r3, 0x1
    ori     r3, r3, 0x8000
    bl      __OSMaskInterrupts
    li      r0, 0x0
    lis     r3, 0xcc00
    stw     r0, 0x6828(r3)
L_retry:
    bl      SNSelect
L_wait0:
    bl      SNRead8
    cmpwi   r3, 0x0
    beq     L_wait0
L_skip0:
    bl      SNWiggleSelect
    bl      SNRead8
    cmpwi   r3, 0xff
    beq     L_skip0
    bl      SNWiggleSelect
    li      r3, 0x0
    bl      SNWrite8
    li      r3, 0x0
    bl      SNWrite8
    li      r3, 0x4
    bl      SNWrite8
    li      r3, 0x80
    bl      SNWrite8
    li      r3, 0x0
    bl      SNWrite8
    bl      SNWiggleSelect
L_wait1:
    bl      SNRead8
    cmpwi   r3, 0x0
    beq     L_wait1
L_skip1:
    bl      SNWiggleSelect
    bl      SNRead8
    cmpwi   r3, 0xff
    beq     L_skip1
    bl      SNWiggleSelect
    bl      SNRead32
    mr      r5, r3
    bl      SNRead32
    mr      r6, r3
    li      r3, 0xf
    mtctr   r3
L_delay:
    bdnz    L_delay
    bl      SNDeselect
    lis     r4, 0x534e
    ori     r4, r4, 0x444c
    subf    r5, r4, r5
    cmpwi   r5, 0x0
    bne     L_retry
    lis     r3, (lbl_8057BD88 + 0x138)@h
    ori     r3, r3, (lbl_8057BD88 + 0x138)@l
    stw     r6, 0x0(r3)
    li      r5, 0x1
    slw     r5, r5, r6
    stw     r5, 0x4(r3)
    li      r5, -0x1
    subfic  r4, r6, 0x20
    srw     r5, r5, r4
    clrrwi  r4, r5, 2
    stw     r5, 0x8(r3)
    stw     r4, 0xc(r3)
    mr      r3, r30
    bl      OSRestoreInterrupts
    lwz     r31, 0x8(r1)
    lwz     r30, 0xc(r1)
    lwz     r0, 0x14(r1)
    addi    r1, r1, 0x10
    mtlr    r0
    blr
    // clang-format on
}
