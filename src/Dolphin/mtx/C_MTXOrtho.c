typedef float f32;

// Owns the .sdata2 pool C_MTXPerspective.c also externs, so the literals it shares are named objects here.
// These are defined after the function so MWCC loads them rather than folding them into new literals.
// force_active stops mwld stripping the unreferenced ones.
#pragma force_active on

extern const f32 MtxOrthoOneConst;
extern const f32 MtxOrthoTwoConst;
extern const f32 MtxOrthoZeroConst;
extern const f32 MtxOrthoNegOneConst;

void C_MTXOrtho(f32 m[4][4], f32 t, f32 b, f32 l, f32 r, f32 n, f32 f)
{
    f32 tmp;

    tmp = MtxOrthoOneConst / (r - l);
    m[0][0] = MtxOrthoTwoConst * tmp;
    m[0][1] = MtxOrthoZeroConst;
    m[0][2] = MtxOrthoZeroConst;
    m[0][3] = tmp * -(r + l);
    tmp = MtxOrthoOneConst / (t - b);
    m[1][0] = MtxOrthoZeroConst;
    m[1][1] = MtxOrthoTwoConst * tmp;
    m[1][2] = MtxOrthoZeroConst;
    m[1][3] = tmp * -(t + b);
    m[2][0] = MtxOrthoZeroConst;
    m[2][1] = MtxOrthoZeroConst;
    tmp = MtxOrthoOneConst / (f - n);
    m[2][2] = MtxOrthoNegOneConst * tmp;
    m[2][3] = -f * tmp;
    m[3][0] = MtxOrthoZeroConst;
    m[3][1] = MtxOrthoZeroConst;
    m[3][2] = MtxOrthoZeroConst;
    m[3][3] = MtxOrthoOneConst;
}

// C_MTXPerspective.c externs these; the rest are unreferenced here.
// Kept alive by force_active above.
const f32 MtxOrthoOneConst = 1.0f;
const f32 MtxOrthoTwoConst = 2.0f;
const f32 MtxOrthoZeroConst = 0.0f;
const f32 MtxOrthoNegOneConst = -1.0f;
const f32 MtxPerspHalfConst = 0.5f;
const f32 MtxPerspDeg2RadConst = 0.01745329238474369f;
const f32 MtxOrthoThreeConst = 3.0f;
const f32 MtxOrthoPoolZeroConst = 0.0f;
