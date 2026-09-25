extern float MtxZeroConst;

void PSMTXScale(register float* m, register float xS, register float yS, register float zS)
{
    register float c0 = MtxZeroConst;

    asm {
        stfs xS, 0(m)
        psq_st c0, 4(m), 0, 0
        psq_st c0, 12(m), 0, 0
        stfs yS, 20(m)
        psq_st c0, 24(m), 0, 0
        psq_st c0, 32(m), 0, 0
        stfs zS, 40(m)
        stfs c0, 44(m)
    }
}
