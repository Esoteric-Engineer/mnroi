extern double lbl_8066C370;
extern double lbl_8066C378;
extern double lbl_8066C380;
extern double lbl_8066C388;
extern double copysign(double x, double y);

asm double scalbn(double x, int n)
{
    // clang-format off
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    fmr f2, f1
    fmr f0, f2
    stfd f0, 0x8(r1)
    lwz r9, 0x8(r1)
    lwz r10, 0xc(r1)
    mr r7, r10
    mr r8, r9
    extrwi r11, r8, 11, 1
    cmpwi r11, 0x0
    bne L_FEB8
    clrlwi r0, r8, 1
    or. r9, r7, r0
    beq L_FF80
    lfd f0, lbl_8066C370
    fmul f2, f2, f0
    fmr f0, f2
    stfd f0, 0x8(r1)
    lwz r9, 0x8(r1)
    lwz r10, 0xc(r1)
    mr r8, r9
    extrwi r11, r8, 11, 1
    lis r0, 0xffff
    subi r11, r11, 0x36
    ori r0, r0, 0x3cb0
    cmpw r3, r0
    bge L_FEB8
    lfd f1, lbl_8066C378
    b L_FF7C
L_FEB8:
    cmpwi r11, 0x7ff
    bne L_FEC8
    fadd f1, f2, f2
    b L_FF80
L_FEC8:
    add r11, r11, r3
    cmpwi r11, 0x7fe
    bgt L_FF24
    cmpwi r11, 0x0
    ble L_FF0C
    stfd f2, 0x8(r1)
    slwi r11, r11, 20
    rlwinm r0, r8, 0, 12, 0
    lwz r9, 0x8(r1)
    lwz r10, 0xc(r1)
    or r9, r0, r11
    stw r9, 0x8(r1)
    stw r10, 0xc(r1)
    lfd f0, 0x8(r1)
    fmr f2, f0
    fmr f1, f2
    b L_FF80
L_FF0C:
    cmpwi r11, -0x36
    bgt L_FF4C
    li r0, 0x0
    ori r0, r0, 0xc350
    cmpw r3, r0
    ble L_FF38
L_FF24:
    lfd f1, lbl_8066C380
    bl copysign
    lfd f0, lbl_8066C380
    fmul f1, f1, f0
    b L_FF80
L_FF38:
    lfd f1, lbl_8066C378
    bl copysign
    lfd f0, lbl_8066C378
    fmul f1, f1, f0
    b L_FF80
L_FF4C:
    addi r11, r11, 0x36
    stfd f2, 0x8(r1)
    lwz r9, 0x8(r1)
    lwz r10, 0xc(r1)
    slwi r11, r11, 20
    rlwinm r0, r8, 0, 12, 0
    or r9, r0, r11
    stw r9, 0x8(r1)
    stw r10, 0xc(r1)
    lfd f0, 0x8(r1)
    fmr f2, f0
    lfd f1, lbl_8066C388
L_FF7C:
    fmul f1, f2, f1
L_FF80:
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
    // clang-format on
}
