// Fast inverse square root, one Newton step (docs/core.md row 19).

extern "C" float fn_8042A2B8(register float x)
{
    float half = x * 0.5f;
    int i = *(int *)&x;
    i = 0x5F3759DF - (i >> 1);
    x = *(float *)&i;
    x = x * (1.5f - half * x * x);
    return x;
}
