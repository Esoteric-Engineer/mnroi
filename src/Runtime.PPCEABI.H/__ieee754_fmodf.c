#pragma force_active on

const float FmodfZeroConst[2] = {0.0f, -0.0f};

asm float __ieee754_fmodf(float x, float y)
{
    // clang-format off
    nofralloc
    stwu r1, -0x10(r1)
    stfs f1, 0x8(r1)
    lwz r11, 0x8(r1)
    mr r0, r11
    fmr f0, f2
    stfs f0, 0x8(r1)
    lwz r9, 0x8(r1)
    clrrwi r6, r0, 31
    clrlwi r10, r0, 1
    clrlwi. r8, r9, 1
    beq L_80400080
    lis r0, 0x7f7f
    ori r0, r0, 0xffff
    cmpw r10, r0
    bgt L_80400080
    lis r0, 0x7f80
    cmpw r8, r0
    ble L_80400094
L_80400080:
    stw r11, 0x8(r1)
    lfs f0, 0x8(r1)
    fmuls f1, f0, f2
    fdivs f1, f1, f1
    b L_804001F8
L_80400094:
    cmpw r10, r8
    blt L_804001EC
    beq L_804001CC
    lis r0, 0x7f
    ori r0, r0, 0xffff
    cmpw r10, r0
    bgt L_804000CC
    li r7, -0x7e
    slwi. r0, r10, 8
    ble L_804000D4
L_804000BC:
    subi r7, r7, 0x1
    slwi. r0, r0, 1
    bgt L_804000BC
    b L_804000D4
L_804000CC:
    srawi r9, r10, 23
    subi r7, r9, 0x7f
L_804000D4:
    lis r0, 0x7f
    ori r0, r0, 0xffff
    cmpw r8, r0
    bgt L_80400104
    li r9, -0x7e
    cmpwi cr7, r7, -0x7e
    slwi. r0, r8, 8
    blt L_80400110
L_804000F4:
    subi r9, r9, 0x1
    slwi. r0, r0, 1
    bge L_804000F4
    b L_80400110
L_80400104:
    srawi r9, r8, 23
    cmpwi cr7, r7, -0x7e
    subi r9, r9, 0x7f
L_80400110:
    blt cr7, L_80400120
    clrlwi r0, r10, 9
    oris r10, r0, 0x80
    b L_80400128
L_80400120:
    subfic r11, r7, -0x7e
    slw r10, r10, r11
L_80400128:
    cmpwi r9, -0x7e
    blt L_8040013C
    clrlwi r0, r8, 9
    oris r8, r0, 0x80
    b L_80400144
L_8040013C:
    subfic r11, r9, -0x7e
    slw r8, r8, r11
L_80400144:
    subf r11, r9, r7
    b L_80400164
L_8040014C:
    subf. r0, r8, r10
    bge L_8040015C
    add r10, r10, r10
    b L_80400164
L_8040015C:
    beq L_804001CC
    add r10, r0, r0
L_80400164:
    mr r0, r11
    cmpwi r0, 0x0
    subi r11, r11, 0x1
    bne L_8040014C
    subf. r0, r8, r10
    blt L_80400180
    mr r10, r0
L_80400180:
    cmpwi r10, 0x0
    beq L_804001CC
    lis r0, 0x7f
    ori r0, r0, 0xffff
    cmpw r10, r0
    bgt L_804001B0
    lis r0, 0x7f
    ori r0, r0, 0xffff
L_804001A0:
    add r10, r10, r10
    subi r9, r9, 0x1
    cmpw r10, r0
    ble L_804001A0
L_804001B0:
    cmpwi r9, -0x7e
    blt L_804001E0
    addi r0, r9, 0x7f
    addis r9, r10, -0x80
    slwi r0, r0, 23
    or r10, r9, r0
    b L_804001E8
L_804001CC:
    srwi r0, r6, 31
    la r9, FmodfZeroConst
    slwi r0, r0, 2
    lfsx f1, r9, r0
    b L_804001F8
L_804001E0:
    subfic r11, r9, -0x7e
    sraw r10, r10, r11
L_804001E8:
    or r11, r10, r6
L_804001EC:
    stw r11, 0x8(r1)
    lfs f0, 0x8(r1)
    fmr f1, f0
L_804001F8:
    addi r1, r1, 0x10
    blr
    // clang-format on
}
