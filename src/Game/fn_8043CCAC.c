// Length of a 4-float vector, 0 if it is zero; the pool 0x804873D0 is read through extern_pool (docs/versus.md, row 8).

extern float fn_80438CC8(float x);

float fn_8043CCAC(register float *self)
{
    float d = self[0] * self[0] + self[1] * self[1] + self[2] * self[2] + self[3] * self[3];
    return d != 0.0f ? fn_80438CC8(d) : 0.0f;
}
