// x to the power n, n at least 1.
float fn_801BD9C4(float x, int n)
{
    int i;
    float r = x;

    for (i = 0; i < n - 1; i++)
        r *= x;
    return r;
}
