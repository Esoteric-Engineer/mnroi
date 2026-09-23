typedef struct {
    unsigned char* ptr;
    int cnt;
} FileBuf;

extern void __sinit(void);
extern void fn_80178224(void);
extern void fn_80177E04(void);
extern void fn_80178B10(void);
extern void _fwalk(void);
extern unsigned int lbl_8066C3B0;

asm int fn_80177E24(FileBuf* stream)
{
    // clang-format off
    nofralloc
    stwu    r1, -16(r1)
    mflr    r0
    stw     r31, 12(r1)
    stw     r0, 20(r1)
    mr      r31, r3
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
    li      r0, 0
    lhz     r9, 12(r31)
    stw     r0, 4(r31)
    andi.   r0, r9, 32
    bne     ret_neg1
    andi.   r0, r9, 4
    bne     flag4
    andi.   r0, r9, 16
    beq     ret_neg1
    andi.   r0, r9, 8
    beq     flag_common
    mr      r3, r31
    bl      fn_80178224
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
    b       after_flag4
flag4:
    lwz     r0, 48(r31)
    cmpwi   r0, 0
    beq     after_flag4
    lwz     r0, 60(r31)
    cmpwi   r0, 0
    stw     r0, 4(r31)
    beq     after_flag4
    lwz     r0, 56(r31)
    li      r3, 0
    stw     r0, 0(r31)
    b       epilogue
after_flag4:
    lwz     r0, 16(r31)
    cmpwi   r0, 0
    bne     have_16
    mr      r3, r31
    bl      fn_80178B10
have_16:
    lhz     r0, 12(r31)
    andi.   r9, r0, 3
    beq     call_ptr
    lis     r4, fn_80177E04@ha
    lwz     r3, 92(r31)
    addi    r4, r4, fn_80177E04@l
    bl      _fwalk
call_ptr:
    lwz     r0, 16(r31)
    lwz     r11, 32(r31)
    mr      r4, r0
    lwz     r3, 28(r31)
    lwz     r5, 20(r31)
    mtlr    r11
    stw     r0, 0(r31)
    blrl
    lhz     r0, 12(r31)
    cmpwi   r3, 0
    stw     r3, 4(r31)
    rlwinm  r0, r0, 0, 19, 17
    sth     r0, 12(r31)
    bgt     ret0
    bne     flag64
    ori     r0, r0, 32
    sth     r0, 12(r31)
    b       ret_neg1
flag64:
    ori     r0, r0, 64
    li      r9, 0
    sth     r0, 12(r31)
    stw     r9, 4(r31)
ret_neg1:
    li      r3, -1
    b       epilogue
ret0:
    li      r3, 0
epilogue:
    lwz     r0, 20(r1)
    mtlr    r0
    lwz     r31, 12(r1)
    addi    r1, r1, 16
    blr
    // clang-format on
}
