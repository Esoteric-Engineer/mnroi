extern unsigned char lbl_8049C6A1[];

asm int isspace(int c)
{
    nofralloc
    lis     r9, lbl_8049C6A1@ha
    addi    r9, r9, lbl_8049C6A1@l
    lbzx    r3, r3, r9
    rlwinm  r3, r3, 0, 28, 28
    blr
}
