extern void sprintf(void);

#pragma section R ".rodata.1"
__declspec(section ".rodata.1") const char AsctimeNames[57] = "SunMonTueWedThuFriSatJanFebMarAprMayJunJulAugSepOctNovDec";
__declspec(section ".rodata.1") const char AsctimeFormat[] = "%.3s %.3s %.2d %.2d:%.2d:%.2d %d\n";

asm char* asctime_r(void* tim_p, char* result)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x20(r1)
    mflr    r0
    stmw    r28, 0x10(r1)
    stw     r0, 0x24(r1)
    lwz     r10, 0x10(r3)
    mr      r28, r4
    lwz     r0, 0x18(r3)
    lis     r29, AsctimeNames@ha
    lwz     r11, 0x14(r3)
    slwi    r6, r10, 1
    add     r6, r6, r10
    slwi    r5, r0, 1
    lis     r30, (AsctimeNames+0x15)@ha
    lwz     r7, 0xc(r3)
    lwz     r8, 0x8(r3)
    add     r5, r5, r0
    lwz     r9, 0x4(r3)
    addi    r29, r29, AsctimeNames@l
    lwz     r10, 0x0(r3)
    addi    r30, r30, (AsctimeNames+0x15)@l
    addi    r11, r11, 0x76c
    lis     r4, AsctimeFormat@ha
    add     r5, r5, r29
    add     r6, r6, r30
    stw     r11, 0x8(r1)
    addi    r4, r4, AsctimeFormat@l
    mr      r3, r28
    crclr   4*cr1+eq
    bl      sprintf
    mr      r3, r28
    lwz     r0, 0x24(r1)
    mtlr    r0
    lmw     r28, 0x10(r1)
    addi    r1, r1, 0x20
    blr
    // clang-format on
}
