extern int lbl_8066C3B0;
extern void free(void);

asm int __register_atexit(void (*func)(void))
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    mflr    r0
    stw     r31, 0xc(r1)
    stw     r0, 0x14(r1)
    lwz     r9, lbl_8066C3B0
    mr      r31, r3
    lwz     r10, 0x148(r9)
    cmpwi   r10, 0
    bne     have
    addi    r10, r9, 0x14c
    stw     r10, 0x148(r9)
have:
    lwz     r0, 4(r10)
    cmpwi   r0, 0x1f
    ble     store
    li      r3, 0x88
    bl      free
    mr.     r10, r3
    bne     alloced
    li      r3, -1
    b       done
alloced:
    lwz     r11, lbl_8066C3B0
    li      r0, 0
    stw     r0, 4(r10)
    lwz     r9, 0x148(r11)
    stw     r9, 0(r10)
    stw     r10, 0x148(r11)
store:
    lwz     r9, 4(r10)
    addi    r11, r10, 8
    li      r3, 0
    slwi    r0, r9, 2
    stwx    r31, r11, r0
    addi    r9, r9, 1
    stw     r9, 4(r10)
done:
    lwz     r0, 0x14(r1)
    mtlr    r0
    lwz     r31, 0xc(r1)
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
