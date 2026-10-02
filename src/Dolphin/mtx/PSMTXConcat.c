static float Unit01[2] = { 0.0f, 1.0f };

asm void PSMTXConcat(const register float* mA, const register float* mB, register float* mAB)
{
    nofralloc
    stwu r1, -64(r1)
    psq_l f0, 0(mA), 0, 0
    stfd f14, 8(r1)
    psq_l f6, 0(mB), 0, 0
    lis r6, Unit01@ha
    psq_l f7, 8(mB), 0, 0
    stfd f15, 16(r1)
    addi r6, r6, Unit01@l
    stfd f31, 40(r1)
    psq_l f8, 16(mB), 0, 0
    ps_muls0 f12, f6, f0
    psq_l f2, 16(mA), 0, 0
    ps_muls0 f13, f7, f0
    psq_l f31, 0(r6), 0, 0
    ps_muls0 f14, f6, f2
    psq_l f9, 24(mB), 0, 0
    ps_muls0 f15, f7, f2
    psq_l f1, 8(mA), 0, 0
    ps_madds1 f12, f8, f0, f12
    psq_l f3, 24(mA), 0, 0
    ps_madds1 f14, f8, f2, f14
    psq_l f10, 32(mB), 0, 0
    ps_madds1 f13, f9, f0, f13
    psq_l f11, 40(mB), 0, 0
    ps_madds1 f15, f9, f2, f15
    psq_l f4, 32(mA), 0, 0
    psq_l f5, 40(mA), 0, 0
    ps_madds0 f12, f10, f1, f12
    ps_madds0 f13, f11, f1, f13
    ps_madds0 f14, f10, f3, f14
    ps_madds0 f15, f11, f3, f15
    psq_st f12, 0(mAB), 0, 0
    ps_muls0 f2, f6, f4
    ps_madds1 f13, f31, f1, f13
    ps_muls0 f0, f7, f4
    psq_st f14, 16(mAB), 0, 0
    ps_madds1 f15, f31, f3, f15
    psq_st f13, 8(mAB), 0, 0
    ps_madds1 f2, f8, f4, f2
    ps_madds1 f0, f9, f4, f0
    ps_madds0 f2, f10, f5, f2
    lfd f14, 8(r1)
    psq_st f15, 24(mAB), 0, 0
    ps_madds0 f0, f11, f5, f0
    psq_st f2, 32(mAB), 0, 0
    ps_madds1 f0, f31, f5, f0
    lfd f15, 16(r1)
    psq_st f0, 40(mAB), 0, 0
    lfd f31, 40(r1)
    addi r1, r1, 64
    blr
}
