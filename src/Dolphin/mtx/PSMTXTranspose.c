asm void PSMTXTranspose(const register float* src, register float* xPose)
{
    nofralloc
    lfs     f0, -11276(r13)
    psq_l   f1, 0(src), 0, 0
    stfs    f0, 44(xPose)
    psq_l   f2, 16(src), 0, 0
    ps_merge00 f4, f1, f2
    psq_l   f3, 8(src), 1, 0
    ps_merge11 f5, f1, f2
    psq_l   f2, 24(src), 1, 0
    psq_st  f4, 0(xPose), 0, 0
    psq_l   f1, 32(src), 0, 0
    ps_merge00 f2, f3, f2
    psq_st  f5, 16(xPose), 0, 0
    ps_merge00 f4, f1, f0
    psq_st  f2, 32(xPose), 0, 0
    ps_merge10 f5, f1, f0
    psq_st  f4, 8(xPose), 0, 0
    lfs     f3, 40(src)
    psq_st  f5, 24(xPose), 0, 0
    stfs    f3, 40(xPose)
    blr
}
