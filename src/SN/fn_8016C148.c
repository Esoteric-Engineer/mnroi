extern char lbl_8057BD88[];
extern char lbl_804CFF30[];
extern char lbl_8049C190[];
extern void fn_8016BEE4(void);
extern void fn_8016BF04(void);
extern void fn_8016BF28(void);
extern void fn_8016BFB0(void);
extern void fn_8016BFF4(void);
extern void fn_8016C074(void);
extern void fn_8016B828(void);
extern void OSReport(const char*, ...);
extern void OSLoadContext(void*);

asm void fn_8016C148(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x40(r1)
    mflr    r0
    stmw    r28, 0x30(r1)
    stw     r0, 0x44(r1)
    mr      r29, r4
    lwz     r9, 0x198(r29)
    lwz     r30, 0x0(r9)
    clrlwi  r31, r30, 16
    andi.   r0, r30, 0x8000
    beq     L_8016C174
    oris    r31, r31, 0xffff
L_8016C174:
    rlwinm  r0, r30, 18, 25, 29
    lis     r9, 0xcc00
    lwzx    r11, r29, r0
    ori     r9, r9, 0x601c
    cmpw    r6, r9
    add     r31, r31, r11
    bne     L_8016C380
    li      r0, 0xa
    lis     r11, 0xc00
    mtctr   r0
    addi    r8, r1, 0x8
    ori     r11, r11, 0x6000
    li      r10, 0x0
L_8016C1A8:
    oris    r9, r11, 0xc000
    lwz     r0, 0x0(r9)
    addi    r11, r11, 0x4
    stwx    r0, r10, r8
    addi    r10, r10, 0x4
    bdnz    L_8016C1A8
    lwz     r10, 0x10(r1)
    lis     r8, (lbl_8057BD88+0x1E4)@ha
    lwz     r0, 0x14(r1)
    li      r9, 0x0
    mr      r4, r10
    lwz     r11, (lbl_8057BD88+0x1E4)@l(r8)
    srwi    r10, r10, 16
    slwi    r0, r0, 2
    ori     r9, r9, 0xe000
    add     r28, r11, r0
    cmpw    r10, r9
    beq     L_8016C308
    bgt     L_8016C228
    li      r0, 0x0
    ori     r0, r0, 0xa800
    cmpw    r10, r0
    beq     L_8016C278
    bgt     L_8016C214
    cmpwi   r10, 0x1200
    beq     L_8016C26C
    b       L_8016C354
L_8016C214:
    li      r0, 0x0
    ori     r0, r0, 0xab00
    cmpw    r10, r0
    beq     L_8016C344
    b       L_8016C354
L_8016C228:
    li      r0, 0x0
    ori     r0, r0, 0xe200
    cmpw    r10, r0
    beq     L_8016C334
    bgt     L_8016C248
    li      r0, 0x0
    ori     r0, r0, 0xe100
    b       L_8016C260
L_8016C248:
    li      r0, 0x0
    ori     r0, r0, 0xe300
    cmpw    r10, r0
    beq     L_8016C344
    li      r0, 0x0
    ori     r0, r0, 0xe401
L_8016C260:
    cmpw    r10, r0
    beq     L_8016C334
    b       L_8016C354
L_8016C26C:
    lwz     r3, 0x1c(r1)
    bl      fn_8016BF28
    b       L_8016C394
L_8016C278:
    lwz     r0, 0x20(r1)
    cmpwi   r0, 0x0
    bne     L_8016C294
    lis     r3, (lbl_8057BD88+0x1B8)@ha
    addi    r3, r3, (lbl_8057BD88+0x1B8)@l
    bl      fn_8016BF28
    b       L_8016C2F0
L_8016C294:
    mr      r3, r28
    bl      fn_8016C074
    lis     r9, (lbl_8057BD88+0x1D8)@ha
    cmpwi   r3, 0x0
    stw     r3, (lbl_8057BD88+0x1D8)@l(r9)
    bne     L_8016C300
    lwz     r5, 0x20(r1)
    lis     r9, (lbl_804CFF30+0x10)@ha
    lis     r11, (lbl_8057BD88+0x1E0)@ha
    lwz     r3, (lbl_804CFF30+0x10)@l(r9)
    lwz     r4, 0x1c(r1)
    lis     r6, fn_8016BFF4@ha
    stw     r5, (lbl_8057BD88+0x1E0)@l(r11)
    addi    r6, r6, fn_8016BFF4@l
    mr      r7, r28
    li      r8, 0x1
    bl      fn_8016B828
    cmpwi   r3, -0x1
    bne     L_8016C2F0
    lis     r0, 0x3
    lis     r9, (lbl_8057BD88+0x1D8)@ha
    ori     r0, r0, 0x1100
    stw     r0, (lbl_8057BD88+0x1D8)@l(r9)
L_8016C2F0:
    lis     r9, (lbl_8057BD88+0x1D8)@ha
    lwz     r0, (lbl_8057BD88+0x1D8)@l(r9)
    cmpwi   r0, 0x0
    beq     L_8016C394
L_8016C300:
    bl      fn_8016BFB0
    b       L_8016C394
L_8016C308:
    lis     r11, (lbl_8057BD88+0x1D8)@ha
    lis     r9, 0xcc00
    lwz     r0, (lbl_8057BD88+0x1D8)@l(r11)
    ori     r9, r9, 0x6020
    lis     r3, (lbl_8057BD88+0x1B8)@ha
    stw     r0, 0x0(r9)
    addi    r3, r3, (lbl_8057BD88+0x1B8)@l
    clrrwi  r0, r0, 24
    stw     r0, (lbl_8057BD88+0x1D8)@l(r11)
    bl      fn_8016BF28
    b       L_8016C394
L_8016C334:
    lis     r9, (lbl_8057BD88+0x198)@ha
    lwz     r0, (lbl_8057BD88+0x198)@l(r9)
    cmpwi   r0, 0x0
    bne     L_8016C380
L_8016C344:
    lis     r3, (lbl_8057BD88+0x1B8)@ha
    addi    r3, r3, (lbl_8057BD88+0x1B8)@l
    bl      fn_8016BF28
    b       L_8016C394
L_8016C354:
    lis     r3, (lbl_8049C190+0x40)@ha
    addi    r3, r3, (lbl_8049C190+0x40)@l
    crclr   6
    bl      OSReport
    opword  1
    lis     r0, 0x5
    lis     r9, (lbl_8057BD88+0x1D8)@ha
    ori     r0, r0, 0x2000
    stw     r0, (lbl_8057BD88+0x1D8)@l(r9)
    bl      fn_8016BFB0
    b       L_8016C394
L_8016C380:
    bl      fn_8016BEE4
    rlwinm  r0, r30, 13, 25, 29
    lwzx    r9, r29, r0
    stw     r9, 0x0(r31)
    bl      fn_8016BF04
L_8016C394:
    lwz     r9, 0x198(r29)
    addi    r9, r9, 0x4
    stw     r9, 0x198(r29)
    mr      r3, r29
    bl      OSLoadContext
    lwz     r0, 0x44(r1)
    mtlr    r0
    lmw     r28, 0x30(r1)
    addi    r1, r1, 0x40
    blr
    // clang-format on
}
