// Owns mtx.c's .sdata2 pool from 0x806708D0.
// MtxOneConst/MtxZeroConst are read here and, via extern, by PSMTXTrans/PSMTXTranspose/PSMTXScale.
// Load them only from the asm block: a C-level read of a const defined in this unit gets constant-folded into a second, anonymous copy of the pool.
#pragma force_active on

const float MtxOneConst = 1.0f;
const float MtxZeroConst = 0.0f;

void PSMTXIdentity(register float* m)
{
    register float c_zero;
    register float c_one;
    register float c_01;
    register float c_10;

    asm {
        lfs c_zero, MtxZeroConst
        lfs c_one, MtxOneConst
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
