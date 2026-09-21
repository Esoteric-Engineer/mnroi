extern void fn_801726FC(void);

asm char* strcat(char* dst, const char* src)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x10(r1)
    mflr    r0
    stw     r31, 0xc(r1)
    stw     r0, 0x14(r1)
    mr      r31, r3
    andi.   r0, r31, 0x3
    bne     tail
    lwz     r9, 0(r31)
    lis     r0, 0x8080
    ori     r0, r0, 0x8080
    subis   r11, r9, 0x101
    subi    r11, r11, 0x101
    andc    r9, r11, r9
    and.    r11, r9, r0
    bne     tail
    lis     r0, 0x8080
    ori     r0, r0, 0x8080
wloop:
    lwzu    r11, 4(r3)
    subis   r9, r11, 0x101
    subi    r9, r9, 0x101
    andc    r11, r9, r11
    and.    r9, r11, r0
    beq     wloop
tail:
    lbz     r0, 0(r3)
    cmpwi   r0, 0
    beq     call
bloop:
    lbzu    r0, 1(r3)
    cmpwi   r0, 0
    bne     bloop
call:
    bl      fn_801726FC
    mr      r3, r31
    lwz     r0, 0x14(r1)
    mtlr    r0
    lwz     r31, 0xc(r1)
    addi    r1, r1, 0x10
    blr
    // clang-format on
}
