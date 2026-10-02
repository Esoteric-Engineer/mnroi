extern char lbl_804CFF30[];
extern char lbl_804CFC7C[];

asm void fn_8016C3BC(int x)
{
    // clang-format off
    nofralloc
    cmpwi   r3, -0x8000
    bnelr
    lis     r9, (lbl_804CFF30+0x10)@ha
    lis     r11, lbl_804CFC7C@ha
    li      r0, 0
    stw     r3, (lbl_804CFF30+0x10)@l(r9)
    stw     r0, lbl_804CFC7C@l(r11)
    blr
    // clang-format on
}
