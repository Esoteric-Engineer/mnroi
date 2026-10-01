extern char lbl_8057C0A0[];

struct { int v; } lbl_8066C3A0 = {0};
char* lbl_8066C3A4 = lbl_8057C0A0 + 4;

extern int fn_8017A6CC(void);

asm int _vfiwrite(void* reent, const char* buf, unsigned long n, int flush)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x28(r1)
    mflr    r0
    stmw    r25, 0xc(r1)
    stw     r0, 0x2c(r1)
    mr      r29, r3
    mr      r27, r4
    mr      r31, r5
    cmpwi   r6, 0x1
    bne     notflush
    lis     r30, (lbl_8057C0A0+4)@ha
    lwz     r5, lbl_8066C3A0
    addi    r4, r30, (lbl_8057C0A0+4)@l
    bl      fn_8017A6CC
    addi    r30, r30, (lbl_8057C0A0+4)@l
    li      r0, 0
    stw     r0, lbl_8066C3A0
    stw     r30, lbl_8066C3A4
    b       done
fail:
    li      r3, 0
    b       done
notflush:
    li      r30, 0
    cmplw   r30, r31
    bge     finish
    lis     r28, (lbl_8057C0A0+4)@ha
    li      r25, 0
    addi    r26, r28, (lbl_8057C0A0+4)@l
loop:
    lbzx    r0, r27, r30
    lwz     r9, lbl_8066C3A4
    stb     r0, 0(r9)
    lwz     r11, lbl_8066C3A4
    lwz     r9, lbl_8066C3A0
    addi    r11, r11, 1
    addi    r5, r9, 1
    stw     r11, lbl_8066C3A4
    stw     r5, lbl_8066C3A0
    cmpwi   r5, 0x7f
    ble     next
    mr      r3, r29
    addi    r4, r28, (lbl_8057C0A0+4)@l
    bl      fn_8017A6CC
    cmpwi   r3, 0
    stw     r26, lbl_8066C3A4
    stw     r25, lbl_8066C3A0
    beq     fail
next:
    addi    r30, r30, 1
    cmplw   r30, r31
    blt     loop
finish:
    mr      r3, r30
done:
    lwz     r0, 0x2c(r1)
    mtlr    r0
    lmw     r25, 0xc(r1)
    addi    r1, r1, 0x28
    blr
    // clang-format on
}
