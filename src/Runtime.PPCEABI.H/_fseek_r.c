extern int lbl_8066C3B0;
extern void __sinit(void);
extern int fflush(void* fp);
extern void __smakebuf(void* fp);
extern int __srefill(void* fp);
extern int _fstat_r(void* reent, int fd, void* st);
extern void* __sseek;

// _fseek_r(reent, fp, offset, whence): Newlib fseek with the block-aligned seek optimisation.
asm int _fseek_r(void* reent, void* fp, int offset, int whence)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x68(r1)
    mflr    r0
    stmw    r24, 0x48(r1)
    stw     r0, 0x6c(r1)
    mr      r31, r3
    mr      r25, r4
    mr      r27, r5
    lwz     r0, 0x5c(r31)
    cmpwi   r0, 0x0
    bne     L_801786DC
    lwz     r0, lbl_8066C3B0
    stw     r0, 0x5c(r31)
L_801786DC:
    lwz     r3, 0x5c(r31)
    lwz     r0, 0x38(r3)
    cmpwi   r0, 0x0
    bne     L_801786F4
    crclr   6
    bl      __sinit
L_801786F4:
    lwz     r0, 0xc(r31)
    lis     r9, 0x108
    lwz     r30, 0x5c(r31)
    andis. r0, r0, 0x108
    cmpw    r0, r9
    bne     L_80178714
    mr      r3, r31
    bl      fflush
L_80178714:
    lwz     r26, 0x28(r31)
    cmpwi   r26, 0x0
    bne     L_80178728
    li      r0, 0x1d
    b       L_801787FC
L_80178728:
    cmpwi   r27, 0x1
    beq     L_8017874C
    bgt     L_80178740
    cmpwi   r27, 0x0
    beq     L_801787EC
    b       L_801787F8
L_80178740:
    cmpwi   r27, 0x2
    beq     L_801787EC
    b       L_801787F8
L_8017874C:
    mr      r3, r31
    bl      fflush
    lhz     r0, 0xc(r31)
    andi. r9, r0, 0x1000
    bne     L_80178788
    lwz     r3, 0x1c(r31)
    li      r4, 0x0
    li      r5, 0x1
    mtlr    r26
    blrl
    mr      r29, r3
    cmpwi   r29, -0x1
    bne     L_8017878C
L_80178780:
    li      r3, -0x1
    b       L_80178A7C
L_80178788:
    lwz     r29, 0x58(r31)
L_8017878C:
    lhz     r0, 0xc(r31)
    andi. r9, r0, 0x4
    beq     L_801787BC
    lwz     r0, 0x4(r31)
    lwz     r9, 0x30(r31)
    subf    r29, r0, r29
    lwz     r10, 0x10(r31)
    cmpwi   r9, 0x0
    beq     L_801787DC
    lwz     r0, 0x3c(r31)
    subf    r29, r0, r29
    b       L_801787DC
L_801787BC:
    andi. r9, r0, 0x8
    lwz     r10, 0x10(r31)
    beq     L_801787DC
    lwz     r0, 0x0(r31)
    cmpwi   r0, 0x0
    beq     L_801787DC
    subf    r0, r10, r0
    add     r29, r29, r0
L_801787DC:
    add     r25, r25, r29
    li      r27, 0x0
    li      r24, 0x1
    b       L_80178808
L_801787EC:
    li      r24, 0x0
    lwz     r10, 0x10(r31)
    b       L_80178808
L_801787F8:
    li      r0, 0x16
L_801787FC:
    li      r3, -0x1
    stw     r0, 0x0(r30)
    b       L_80178A7C
L_80178808:
    cmpwi   r10, 0x0
    bne     L_80178818
    mr      r3, r31
    bl      __smakebuf
L_80178818:
    lhz     r9, 0xc(r31)
    andi. r0, r9, 0x81a
    cmpwi   r0, 0x0
    bne     L_80178A34
    andi. r0, r9, 0x400
    bne     L_8017889C
    lis     r9, __sseek@ha
    addi    r9, r9, __sseek@l
    cmpw    r26, r9
    bne     L_80178878
    lha     r4, 0xe(r31)
    cmpwi   r4, 0x0
    blt     L_80178878
    mr      r3, r30
    addi    r5, r1, 0x8
    bl      _fstat_r
    cmpwi   r3, 0x0
    bne     L_80178878
    lwz     r9, 0xc(r1)
    li      r0, 0x0
    ori     r0, r0, 0x8000
    rlwinm  r9, r9, 0, 16, 19
    cmpw    r9, r0
    beq     L_80178888
L_80178878:
    lhz     r0, 0xc(r31)
    ori     r0, r0, 0x800
    sth     r0, 0xc(r31)
    b       L_80178A34
L_80178888:
    lhz     r0, 0xc(r31)
    li      r9, 0x400
    stw     r9, 0x54(r31)
    ori     r0, r0, 0x400
    sth     r0, 0xc(r31)
L_8017889C:
    cmpwi   r27, 0x0
    bne     L_801788AC
    mr      r28, r25
    b       L_801788CC
L_801788AC:
    lha     r4, 0xe(r31)
    mr      r3, r30
    addi    r5, r1, 0x8
    bl      _fstat_r
    cmpwi   r3, 0x0
    bne     L_80178A34
    lwz     r0, 0x18(r1)
    add     r28, r0, r25
L_801788CC:
    cmpwi   r24, 0x0
    bne     L_80178928
    lhz     r0, 0xc(r31)
    andi. r9, r0, 0x1000
    beq     L_801788E8
    lwz     r29, 0x58(r31)
    b       L_80178908
L_801788E8:
    lwz     r3, 0x1c(r31)
    li      r4, 0x0
    li      r5, 0x1
    mtlr    r26
    blrl
    mr      r29, r3
    cmpwi   r29, -0x1
    beq     L_80178A34
L_80178908:
    lwz     r0, 0x4(r31)
    lwz     r9, 0x30(r31)
    mr      r8, r0
    subf    r29, r0, r29
    cmpwi   r9, 0x0
    beq     L_8017895C
    lwz     r0, 0x3c(r31)
    subf    r29, r0, r29
L_80178928:
    lwz     r0, 0x30(r31)
    lwz     r8, 0x4(r31)
    cmpwi   r0, 0x0
    beq     L_8017895C
    lwz     r0, 0x10(r31)
    add     r29, r29, r8
    lwz     r9, 0x38(r31)
    lwz     r11, 0x3c(r31)
    mr      r10, r0
    subf    r30, r0, r9
    subf    r29, r30, r29
    add     r30, r30, r11
    b       L_80178974
L_8017895C:
    lwz     r0, 0x10(r31)
    lwz     r9, 0x0(r31)
    mr      r10, r0
    subf    r30, r0, r9
    subf    r29, r30, r29
    add     r30, r30, r8
L_80178974:
    lhz     r9, 0xc(r31)
    andi. r0, r9, 0x2000
    bne     L_801789B8
    cmpw    r28, r29
    blt     L_801789B8
    add     r0, r29, r30
    cmplw   r28, r0
    bge     L_801789B8
    subf    r0, r29, r28
    rlwinm  r9, r9, 0, 27, 25
    subf    r11, r0, r30
    sth     r9, 0xc(r31)
    add     r0, r10, r0
    li      r3, 0x0
    stw     r0, 0x0(r31)
    stw     r11, 0x4(r31)
    b       L_80178A7C
L_801789B8:
    lwz     r0, 0x54(r31)
    li      r5, 0x0
    lwz     r3, 0x1c(r31)
    mtlr    r26
    neg     r0, r0
    and     r29, r28, r0
    mr      r4, r29
    blrl
    cmpwi   r3, -0x1
    beq     L_80178A34
    lhz     r9, 0xc(r31)
    li      r0, 0x0
    stw     r0, 0x4(r31)
    subf. r30, r29, r28
    rlwinm  r9, r9, 0, 27, 25
    sth     r9, 0xc(r31)
    beq     L_80178A2C
    mr      r3, r31
    bl      __srefill
    cmpwi   r3, 0x0
    bne     L_80178A34
    lwz     r9, 0x4(r31)
    cmplw   r9, r30
    blt     L_80178A34
    lwz     r0, 0x0(r31)
    subf    r9, r30, r9
    stw     r9, 0x4(r31)
    add     r0, r0, r30
    stw     r0, 0x0(r31)
L_80178A2C:
    li      r3, 0x0
    b       L_80178A7C
L_80178A34:
    mr      r3, r31
    bl      fflush
    mr. r30, r3
    bne     L_80178780
    mr      r4, r25
    mr      r5, r27
    lwz     r3, 0x1c(r31)
    mtlr    r26
    blrl
    cmpwi   r3, -0x1
    beq     L_80178780
    lhz     r0, 0xc(r31)
    li      r3, 0x0
    lwz     r9, 0x10(r31)
    rlwinm  r0, r0, 0, 27, 25
    stw     r30, 0x4(r31)
    sth     r0, 0xc(r31)
    stw     r9, 0x0(r31)
L_80178A7C:
    lwz     r0, 0x6c(r1)
    mtlr    r0
    lmw     r24, 0x48(r1)
    addi    r1, r1, 0x68
    blr
    // clang-format on
}
