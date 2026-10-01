extern unsigned char _ctype_[];

asm int isdigit(int c)
{
    nofralloc
    lis     r9, (_ctype_+1)@ha
    addi    r9, r9, (_ctype_+1)@l
    lbzx    r3, r3, r9
    rlwinm  r3, r3, 0, 29, 29
    blr
}
