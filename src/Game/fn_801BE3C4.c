// Arcsine in degrees, from the odd terms of its series up to x^7.
extern float fn_801BD9C4(float x, int n);
extern double __ieee754_sqrt(double x);

float fn_801BE3C4(float x)
{
    float r;
    int neg = x < 0.0f;

    x = x < 0.0f ? -x : x;
    if (x > 0.70710677f)
    {
        x = __ieee754_sqrt(1.0f - x * x);
        r = 90.0f - (fn_801BD9C4(x, 3) / 6.0f + x + fn_801BD9C4(x, 5) * 0.075f + fn_801BD9C4(x, 7) * 0.066797f) * 57.295784f;
    }
    else
    {
        r = (fn_801BD9C4(x, 3) / 6.0f + x + fn_801BD9C4(x, 5) * 0.075f + fn_801BD9C4(x, 7) * 0.066797f) * 57.295784f;
    }
    if (neg)
        return -r;
    else
        return r;
}
