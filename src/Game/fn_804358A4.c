// Linear congruential generator on lbl_8066C710; the .rodata float pool is read through extern_pool.

extern unsigned int lbl_8066C710;

float fn_804358A4(void)
{
    union {
        unsigned int i;
        float f;
    } u;
    lbl_8066C710 = lbl_8066C710 * 1664525 + 1013904223;
    u.i = (lbl_8066C710 & 0x7FFFFF) | 0x3F800000;
    return u.f - 1.0f;
}

unsigned int fn_80435904(void)
{
    lbl_8066C710 = lbl_8066C710 * 1664525 + 1013904223;
    return lbl_8066C710;
}
