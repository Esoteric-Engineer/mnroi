typedef unsigned long u32;

asm void DCEnable(void)
{
    // clang-format off
    nofralloc
    sync
    mfspr r3, HID0
    ori   r3, r3, 0x4000
    mtspr HID0, r3
    blr
    // clang-format on
}

asm void DCInvalidateRange(void* addr, u32 nBytes)
{
    // clang-format off
    nofralloc
    cmplwi r4, 0
    blelr
    clrlwi r5, r3, 27
    add    r4, r4, r5
    addi   r4, r4, 31
    srwi   r4, r4, 5
    mtctr  r4
loop:
    dcbi   0, r3
    addi   r3, r3, 32
    bdnz   loop
    blr
    // clang-format on
}

asm void DCFlushRange(void* addr, u32 nBytes)
{
    // clang-format off
    nofralloc
    cmplwi r4, 0
    blelr
    clrlwi r5, r3, 27
    add    r4, r4, r5
    addi   r4, r4, 31
    srwi   r4, r4, 5
    mtctr  r4
loop:
    dcbf   0, r3
    addi   r3, r3, 32
    bdnz   loop
    sc
    blr
    // clang-format on
}

asm void DCStoreRange(void* addr, u32 nBytes)
{
    // clang-format off
    nofralloc
    cmplwi r4, 0
    blelr
    clrlwi r5, r3, 27
    add    r4, r4, r5
    addi   r4, r4, 31
    srwi   r4, r4, 5
    mtctr  r4
loop:
    dcbst  0, r3
    addi   r3, r3, 32
    bdnz   loop
    sc
    blr
    // clang-format on
}

asm void DCFlushRangeNoSync(void* addr, u32 nBytes)
{
    // clang-format off
    nofralloc
    cmplwi r4, 0
    blelr
    clrlwi r5, r3, 27
    add    r4, r4, r5
    addi   r4, r4, 31
    srwi   r4, r4, 5
    mtctr  r4
loop:
    dcbf   0, r3
    addi   r3, r3, 32
    bdnz   loop
    blr
    // clang-format on
}

asm void ICInvalidateRange(void* addr, u32 nBytes)
{
    // clang-format off
    nofralloc
    cmplwi r4, 0
    blelr
    clrlwi r5, r3, 27
    add    r4, r4, r5
    addi   r4, r4, 31
    srwi   r4, r4, 5
    mtctr  r4
loop:
    icbi   0, r3
    addi   r3, r3, 32
    bdnz   loop
    sync
    isync
    blr
    // clang-format on
}

asm void ICFlashInvalidate(void)
{
    // clang-format off
    nofralloc
    mfspr r3, HID0
    ori   r3, r3, 0x0800
    mtspr HID0, r3
    blr
    // clang-format on
}

asm void ICEnable(void)
{
    // clang-format off
    nofralloc
    isync
    mfspr r3, HID0
    ori   r3, r3, 0x8000
    mtspr HID0, r3
    blr
    // clang-format on
}

asm void LCDisable(void)
{
    // clang-format off
    nofralloc
    lis    r3, 0xE000
    li     r4, 512
    mtctr  r4
loop:
    dcbi   0, r3
    addi   r3, r3, 32
    bdnz   loop
    mfspr  r4, 920
    rlwinm r4, r4, 0, 4, 2
    mtspr  920, r4
    blr
    // clang-format on
}

extern u32 PPCMfl2cr(void);
extern void PPCMtl2cr(register u32 l2cr);
extern void DBPrintf(char* msg);
extern char L2InvalidateStr[];

asm void L2GlobalInvalidate(void)
{
    // clang-format off
    nofralloc
    mflr   r0
    stw    r0, 4(r1)
    stwu   r1, -16(r1)
    stw    r31, 12(r1)
    sync
    bl     PPCMfl2cr
    clrlwi r3, r3, 1
    bl     PPCMtl2cr
    sync
    bl     PPCMfl2cr
    oris   r3, r3, 32
    bl     PPCMtl2cr
    b      l1
l1:
    b      wait1
wait1:
    bl     PPCMfl2cr
    clrlwi r0, r3, 31
    cmplwi r0, 0
    bne    wait1
    bl     PPCMfl2cr
    rlwinm r3, r3, 0, 11, 9
    bl     PPCMtl2cr
    b      l3
l3:
    lis    r3, L2InvalidateStr@ha
    addi   r31, r3, L2InvalidateStr@l
    b      l4
l4:
    b      wait2_test
wait2_body:
    mr     r3, r31
    crclr  4*cr1+eq
    bl     DBPrintf
wait2_test:
    bl     PPCMfl2cr
    clrlwi r0, r3, 31
    cmplwi r0, 0
    bne    wait2_body
    lwz    r0, 20(r1)
    lwz    r31, 12(r1)
    addi   r1, r1, 16
    mtlr   r0
    blr
    // clang-format on
}
