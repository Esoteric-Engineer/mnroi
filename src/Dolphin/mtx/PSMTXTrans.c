extern float MtxZeroConst;
extern float MtxOneConst;

void PSMTXTrans(register float* m, register float xT, register float yT, register float zT)
{
    register float c0 = MtxZeroConst;
    register float c1 = MtxOneConst;

    asm {
        stfs xT, 12(m)
        stfs yT, 28(m)
        psq_st c0, 4(m), 0, 0
        psq_st c0, 32(m), 0, 0
        stfs c0, 16(m)
        stfs c1, 20(m)
        stfs c0, 24(m)
        stfs c1, 40(m)
        stfs zT, 44(m)
        stfs c1, 0(m)
    }
}
