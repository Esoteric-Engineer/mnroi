extern unsigned char _ctype_[];

asm int tolower(int c)
{
    nofralloc
    lis     r9, (_ctype_+1)@ha
    addi    r9, r9, (_ctype_+1)@l
    lbzx    r0, r3, r9
    andi.   r9, r0, 0x1
    beqlr
    addi    r3, r3, 0x20
    blr
}
