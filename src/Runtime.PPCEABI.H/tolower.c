extern unsigned char lbl_8049C6A1[];

asm int tolower(int c)
{
    nofralloc
    lis     r9, lbl_8049C6A1@ha
    addi    r9, r9, lbl_8049C6A1@l
    lbzx    r0, r3, r9
    andi.   r9, r0, 0x1
    beqlr
    addi    r3, r3, 0x20
    blr
}
