typedef struct {
    unsigned char* ptr;
    int cnt;
} FileBuf;

extern void __sinit(void);
extern void fflush(void);
extern void fn_8017A6CC(void);
extern unsigned int lbl_8066C3B0;

#pragma section R ".rodata.1"
__declspec(section ".rodata.1") const char UngetcErrorStr[] =
    "\nungetc error: *static buffer overflow* - char not added to buffer\n";

asm int ungetc(int c, FileBuf* stream)
{
    // clang-format off
    nofralloc
    stwu    r1, -16(r1)
    mflr    r0
    stmw    r30, 8(r1)
    stw     r0, 20(r1)
    mr      r30, r3
    mr      r31, r4
    cmpwi   r30, -1
    beq     ret_neg1
    lwz     r0, 92(r31)
    cmpwi   r0, 0
    bne     have_92
    lwz     r0, lbl_8066C3B0
    stw     r0, 92(r31)
have_92:
    lwz     r3, 92(r31)
    lwz     r0, 56(r3)
    cmpwi   r0, 0
    bne     have_56
    crclr   4*cr1+eq
    bl      __sinit
have_56:
    lhz     r9, 12(r31)
    rlwinm  r0, r9, 0, 27, 25
    andi.   r11, r9, 4
    sth     r0, 12(r31)
    bne     flag4
    andi.   r0, r9, 16
    beq     ret_neg1
    andi.   r11, r9, 8
    beq     flag_common
    mr      r3, r31
    bl      fflush
    mr.     r3, r3
    bne     ret_neg1
    lhz     r0, 12(r31)
    stw     r3, 24(r31)
    rlwinm  r0, r0, 0, 29, 27
    stw     r3, 8(r31)
    sth     r0, 12(r31)
flag_common:
    lhz     r0, 12(r31)
    ori     r0, r0, 4
    sth     r0, 12(r31)
flag4:
    lwz     r0, 48(r31)
    clrlwi  r30, r30, 24
    cmpwi   r0, 0
    beq     l90
    lwz     r9, 4(r31)
    lwz     r0, 52(r31)
    cmpw    r9, r0
    blt     ldc
    lis     r4, UngetcErrorStr@ha
    li      r3, 1
    addi    r4, r4, UngetcErrorStr@l
    li      r5, 68
    bl      fn_8017A6CC
ret_neg1:
    li      r3, -1
    b       epilogue
ldc:
    lwz     r11, 0(r31)
    mr      r3, r30
    addi    r0, r11, -1
    stw     r0, 0(r31)
    stb     r30, -1(r11)
    lwz     r9, 4(r31)
    b       l12c
l90:
    lwz     r0, 16(r31)
    cmpwi   r0, 0
    beq     ld0
    lwz     r11, 0(r31)
    cmplw   r11, r0
    ble     ld0
    lbz     r0, -1(r11)
    cmpw    r0, r30
    bne     ld0
    lwz     r9, 4(r31)
    addi    r0, r11, -1
    stw     r0, 0(r31)
    mr      r3, r30
l12c:
    addi    r9, r9, 1
    stw     r9, 4(r31)
    b       epilogue
ld0:
    lwz     r11, 4(r31)
    addi    r7, r31, 64
    lwz     r9, 0(r31)
    li      r10, 10
    addi    r8, r31, 73
    li      r0, 1
    stw     r0, 4(r31)
    mr      r3, r30
    stw     r11, 60(r31)
    stw     r9, 56(r31)
    stw     r7, 48(r31)
    stw     r10, 52(r31)
    stw     r8, 0(r31)
    stb     r30, 73(r31)
epilogue:
    lwz     r0, 20(r1)
    mtlr    r0
    lmw     r30, 8(r1)
    addi    r1, r1, 16
    blr
    // clang-format on
}
