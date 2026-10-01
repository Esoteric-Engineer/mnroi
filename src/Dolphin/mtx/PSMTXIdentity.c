extern float MtxZeroConst;
extern float MtxOneConst;

// Owns .sdata2 from 0x806708D8: unreferenced constants of mtx.c functions this game dead-strips.
// MtxOneConst/MtxZeroConst above stay dtk-auto-named, unclaimed, since this unit's own code already supplies them.
#pragma force_active on

void PSMTXIdentity(register float* m)
{
    register float c_zero = MtxZeroConst;
    register float c_one = MtxOneConst;
    register float c_01;
    register float c_10;

    asm {
        psq_st c_zero, 8(m), 0, 0
        ps_merge01 c_01, c_zero, c_one
        psq_st c_zero, 24(m), 0, 0
        ps_merge10 c_10, c_one, c_zero
        psq_st c_zero, 32(m), 0, 0
        psq_st c_01, 16(m), 0, 0
        psq_st c_10, 0(m), 0, 0
        psq_st c_10, 40(m), 0, 0
    }
}

// Unreferenced constants from mtx.c functions this game dead-strips.
const float MtxPoolHalfConst = 0.5f;
const float MtxPoolThreeConst = 3.0f;
const float MtxPoolTwoConst = 2.0f;
const float MtxPoolNegTwoConst = -2.0f;
const float MtxPoolNegOneConst = -1.0f;
const float MtxPoolDeg2RadConst = 0.01745329238474369f;
