// Dead-zone remap of a stick axis (+-0.1 to 0, rescaled, squared, clamped to [-1, 1]); the pool is another unit's.
extern const float lbl_8048CD34[]; // 0.0f
extern const float lbl_8048CD38[]; // 0.1f
extern const float lbl_8048CD3C[]; // 1.1111112f
extern const float lbl_8048CD40[]; // -1.0f
extern const float lbl_8048CD44[]; // 1.0f

float fn_80446ACC(register float x)
{
    if ((x < lbl_8048CD34[0] ? -x : x) <= lbl_8048CD38[0])
        return lbl_8048CD34[0];
    if (x < lbl_8048CD34[0])
    {
        x = (x + lbl_8048CD38[0]) * lbl_8048CD3C[0];
        x = x * -x;
    }
    else
    {
        x = (x - lbl_8048CD38[0]) * lbl_8048CD3C[0];
        x = x * x;
    }
    return x >= lbl_8048CD40[0] ? (x <= lbl_8048CD44[0] ? x : lbl_8048CD44[0]) : lbl_8048CD40[0];
}
