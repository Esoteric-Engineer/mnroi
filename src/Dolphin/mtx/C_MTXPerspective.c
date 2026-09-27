typedef float f32;

extern float tanf(float x);

extern const float MtxOrthoOneConst;
extern const float MtxOrthoZeroConst;
extern const float MtxOrthoNegOneConst;
extern const float MtxPerspHalfConst;
extern const float MtxPerspDeg2RadConst;

void C_MTXPerspective(f32 m[4][4], f32 fovY, f32 aspect, f32 n, f32 f)
{
    f32 angle;
    f32 cot;
    f32 tmp;

    angle = MtxPerspHalfConst * fovY;
    angle = MtxPerspDeg2RadConst * angle;
    cot = MtxOrthoOneConst / tanf(angle);
    m[0][0] = cot / aspect;
    m[0][1] = MtxOrthoZeroConst;
    m[0][2] = MtxOrthoZeroConst;
    m[0][3] = MtxOrthoZeroConst;
    m[1][0] = MtxOrthoZeroConst;
    m[1][1] = cot;
    m[1][2] = MtxOrthoZeroConst;
    m[1][3] = MtxOrthoZeroConst;
    m[2][0] = MtxOrthoZeroConst;
    m[2][1] = MtxOrthoZeroConst;
    tmp = MtxOrthoOneConst / (f - n);
    m[2][2] = -n * tmp;
    m[2][3] = tmp * -(f * n);
    m[3][0] = MtxOrthoZeroConst;
    m[3][1] = MtxOrthoZeroConst;
    m[3][2] = MtxOrthoNegOneConst;
    m[3][3] = MtxOrthoZeroConst;
}
