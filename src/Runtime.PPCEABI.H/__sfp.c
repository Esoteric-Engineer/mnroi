extern char lbl_8057C0A0[];
extern int lbl_8066C3B4;
extern void __sinit(void);

// __sfp(reent): find a free FILE in the glue list and reset its fields.
asm void* __sfp(void* reent)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    mflr    r0
    stw     r31, 0xc(r1)
    stw     r0, 0x14(r1)
    mr      r31, r3
    lwz     r0, 0x38(r31)
    cmpwi   r0, 0
    bne     have_init
    bl      __sinit
have_init:
    lwz     r8, 0x1d8(r31)
    cmpwi   r8, 0
    bne     have_glue
    lis     r10, (lbl_8057C0A0+0x444)@ha
    lis     r11, (lbl_8057C0A0+0x84)@ha
    addi    r9, r10, (lbl_8057C0A0+0x444)@l
    stw     r8, (lbl_8057C0A0+0x444)@l(r10)
    addi    r11, r11, (lbl_8057C0A0+0x84)@l
    li      r0, 10
    stw     r0, 4(r9)
    stw     r11, 8(r9)
    stw     r9, 0x1d8(r31)
have_glue:
    addi    r11, r31, 0x1d8
glue_loop:
    lwz     r9, 4(r11)
    lwz     r8, 8(r11)
    subic.  r9, r9, 1
    blt     next_glue
file_loop:
    lha     r0, 0xc(r8)
    cmpwi   r0, 0
    beq     found
    addi    r8, r8, 0x60
    subic.  r9, r9, 1
    bge     file_loop
next_glue:
    lwz     r11, 0(r11)
    b       glue_loop
found:
    subfic  r0, r9, 9
    lwz     r7, lbl_8066C3B4
    li      r11, 0
    li      r9, 1
    slwi    r6, r0, 3
    sth     r9, 0xc(r8)
    stw     r11, 4(r8)
    add     r9, r6, r7
    stw     r11, 8(r8)
    lwz     r0, 4(r9)
    cmpwi   r0, 0
    ble     no_buf
    lwzx    r0, r6, r7
    cmpwi   r0, 0
    beq     no_buf
    lwz     r10, 4(r9)
    lwz     r9, 0(r9)
    li      r11, 0x81
    stw     r9, 0x10(r8)
    stw     r10, 0x14(r8)
    lwzx    r0, r6, r7
    sth     r11, 0xc(r8)
    stw     r0, 0(r8)
    b       init_rest
no_buf:
    lhz     r0, 0xc(r8)
    addi    r11, r8, 0x4a
    li      r9, 1
    stw     r11, 0x10(r8)
    ori     r0, r0, 2
    stw     r9, 0x14(r8)
    sth     r0, 0xc(r8)
    stw     r11, 0(r8)
init_rest:
    li      r9, 0
    li      r0, -1
    sth     r0, 0xe(r8)
    mr      r3, r8
    stw     r9, 0x50(r8)
    stw     r31, 0x5c(r8)
    stw     r9, 0x18(r8)
    stw     r9, 0x30(r8)
    stw     r9, 0x34(r8)
    stw     r9, 0x4c(r8)
    lwz     r0, 0x14(r1)
    mtlr    r0
    lwz     r31, 0xc(r1)
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
