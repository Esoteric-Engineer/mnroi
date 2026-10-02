extern unsigned char _ctype_[];
extern void tolower(void);

asm char* strlwr(char* s)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x18(r1)
    mflr    r0
    stmw    r29, 0xc(r1)
    stw     r0, 0x1c(r1)
    mr      r30, r3
    lbz     r0, 0(r30)
    mr      r31, r30
    cmpwi   r0, 0
    beq     done
    lis     r9, (_ctype_+1)@ha
    addi    r29, r9, (_ctype_+1)@l
loop:
    lbz     r0, 0(r31)
    extsb   r3, r0
    lbzx    r9, r3, r29
    andi.   r0, r9, 1
    beq     next
    bl      tolower
    stb     r3, 0(r31)
next:
    lbzu    r0, 1(r31)
    cmpwi   r0, 0
    bne     loop
done:
    mr      r3, r30
    lwz     r0, 0x1c(r1)
    mtlr    r0
    lmw     r29, 0xc(r1)
    addi    r1, r1, 0x18
    blr
    // clang-format on
}
