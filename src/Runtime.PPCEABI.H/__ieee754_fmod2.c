#pragma force_active on

const double Fmod2ZeroConst = 0.0;
const double Fmod2NegZeroConst = -0.0;

asm double __ieee754_fmod2(double x, double y)
{
    // clang-format off
    nofralloc
    stwu r1, -0x20(r1)
    stmw r28, 0x10(r1)
    fmr f0, f1
    stfd f0, 0x8(r1)
    lwz r11, 0x8(r1)
    lwz r12, 0xc(r1)
    mr r7, r12
    fmr f0, f2
    stfd f0, 0x8(r1)
    lwz r9, 0x8(r1)
    lwz r10, 0xc(r1)
    mr r6, r10
    clrrwi r3, r11, 31
    clrlwi r5, r9, 1
    clrlwi r8, r11, 1
    or. r0, r5, r6
    beq L_803FF8F8
    lis r0, 0x7fef
    ori r0, r0, 0xffff
    cmpw r8, r0
    bgt L_803FF8F8
    neg r0, r6
    lis r9, 0x7ff0
    or r0, r6, r0
    srwi r0, r0, 31
    or r0, r5, r0
    cmplw r0, r9
    ble L_803FF904
L_803FF8F8:
    fmul f1, f1, f2
    fdiv f1, f1, f1
    b L_803FFBD4
L_803FF904:
    cmpw r8, r5
    bgt L_803FF920
    blt L_803FFBD4
    cmplw r7, r6
    blt L_803FFBD4
    cmpw r7, r6
    beq L_803FFB9C
L_803FF920:
    lis r0, 0xf
    ori r0, r0, 0xffff
    cmpw r8, r0
    bgt L_803FF974
    cmpwi r8, 0x0
    bne L_803FF958
    li r10, -0x413
    mr r0, r7
    cmpwi r7, 0x0
    ble L_803FF97C
L_803FF948:
    subi r10, r10, 0x1
    slwi. r0, r0, 1
    bgt L_803FF948
    b L_803FF97C
L_803FF958:
    li r10, -0x3fe
    slwi. r0, r8, 11
    ble L_803FF97C
L_803FF964:
    subi r10, r10, 0x1
    slwi. r0, r0, 1
    bgt L_803FF964
    b L_803FF97C
L_803FF974:
    srawi r9, r8, 20
    subi r10, r9, 0x3ff
L_803FF97C:
    lis r0, 0xf
    ori r0, r0, 0xffff
    cmpw r5, r0
    bgt L_803FF9D8
    cmpwi r5, 0x0
    bne L_803FF9B8
    li r4, -0x413
    mr r0, r6
    cmpwi r6, 0x0
    cmpwi cr7, r10, -0x3fe
    ble L_803FF9E4
L_803FF9A8:
    subi r4, r4, 0x1
    slwi. r0, r0, 1
    bgt L_803FF9A8
    b L_803FF9E4
L_803FF9B8:
    li r4, -0x3fe
    cmpwi cr7, r10, -0x3fe
    slwi. r0, r5, 11
    ble L_803FF9E4
L_803FF9C8:
    subi r4, r4, 0x1
    slwi. r0, r0, 1
    bgt L_803FF9C8
    b L_803FF9E4
L_803FF9D8:
    srawi r9, r5, 20
    cmpwi cr7, r10, -0x3fe
    subi r4, r9, 0x3ff
L_803FF9E4:
    blt cr7, L_803FF9F4
    clrlwi r0, r8, 12
    oris r8, r0, 0x10
    b L_803FFA24
L_803FF9F4:
    subfic r11, r10, -0x3fe
    cmpwi r11, 0x1f
    bgt L_803FFA18
    subfic r0, r11, 0x20
    slw r9, r8, r11
    srw r0, r7, r0
    or r8, r9, r0
    slw r7, r7, r11
    b L_803FFA24
L_803FFA18:
    subi r0, r11, 0x20
    slw r8, r7, r0
    li r7, 0x0
L_803FFA24:
    cmpwi r4, -0x3fe
    blt L_803FFA38
    clrlwi r0, r5, 12
    oris r5, r0, 0x10
    b L_803FFA68
L_803FFA38:
    subfic r11, r4, -0x3fe
    cmpwi r11, 0x1f
    bgt L_803FFA5C
    subfic r0, r11, 0x20
    slw r9, r5, r11
    srw r0, r6, r0
    or r5, r9, r0
    slw r6, r6, r11
    b L_803FFA68
L_803FFA5C:
    subi r0, r11, 0x20
    slw r5, r6, r0
    li r6, 0x0
L_803FFA68:
    subf r11, r4, r10
    b L_803FFAB8
L_803FFA70:
    subf r9, r5, r8
    subf r10, r6, r7
    cmplw r7, r6
    bge L_803FFA84
    subi r9, r9, 0x1
L_803FFA84:
    cmpwi r9, 0x0
    bge L_803FFAA0
    srwi r0, r7, 31
    add r9, r8, r8
    add r8, r9, r0
    add r7, r7, r7
    b L_803FFAB8
L_803FFAA0:
    or. r0, r9, r10
    beq L_803FFB9C
    add r9, r9, r9
    srwi r0, r10, 31
    add r8, r9, r0
    add r7, r10, r10
L_803FFAB8:
    mr r0, r11
    cmpwi r0, 0x0
    subi r11, r11, 0x1
    bne L_803FFA70
    subf r9, r5, r8
    cmplw r7, r6
    subf r10, r6, r7
    bge L_803FFADC
    subi r9, r9, 0x1
L_803FFADC:
    cmpwi r9, 0x0
    blt L_803FFAEC
    mr r8, r9
    mr r7, r10
L_803FFAEC:
    or. r0, r8, r7
    beq L_803FFB9C
    lis r0, 0xf
    ori r0, r0, 0xffff
    cmpw r8, r0
    bgt L_803FFB28
    lis r11, 0xf
    ori r11, r11, 0xffff
L_803FFB0C:
    srwi r0, r7, 31
    add r9, r8, r8
    add r8, r9, r0
    add r7, r7, r7
    subi r4, r4, 0x1
    cmpw r8, r11
    ble L_803FFB0C
L_803FFB28:
    cmpwi r4, -0x3fe
    blt L_803FFB5C
    addi r0, r4, 0x3ff
    addis r9, r8, -0x10
    slwi r0, r0, 20
    or r8, r9, r0
    or r30, r8, r3
    mr r31, r7
    stw r30, 0x8(r1)
    stw r31, 0xc(r1)
    lfd f0, 0x8(r1)
    fmr f1, f0
    b L_803FFBD4
L_803FFB5C:
    subfic r11, r4, -0x3fe
    cmpwi r11, 0x14
    bgt L_803FFB80
    subfic r0, r11, 0x20
    srw r9, r7, r11
    slw r0, r8, r0
    or r7, r9, r0
    sraw r8, r8, r11
    b L_803FFBBC
L_803FFB80:
    cmpwi r11, 0x1f
    bgt L_803FFBB0
    subfic r0, r11, 0x20
    srw r9, r7, r11
    slw r0, r8, r0
    or r7, r0, r9
    b L_803FFBB8
L_803FFB9C:
    srwi r0, r3, 31
    la r9, Fmod2ZeroConst
    slwi r0, r0, 3
    lfdx f1, r9, r0
    b L_803FFBD4
L_803FFBB0:
    subi r0, r11, 0x20
    sraw r7, r8, r0
L_803FFBB8:
    mr r8, r3
L_803FFBBC:
    or r28, r8, r3
    mr r29, r7
    stw r28, 0x8(r1)
    stw r29, 0xc(r1)
    lfd f0, 0x8(r1)
    fmr f1, f0
L_803FFBD4:
    lmw r28, 0x10(r1)
    addi r1, r1, 0x20
    blr
    // clang-format on
}
