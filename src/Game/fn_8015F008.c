// Compares a float of the same object (fn_8015E64C) with PLAYER tuning fields 211 and 212.

extern float fn_8015E64C(void *self);
extern void *fn_80442080(void *self);
extern float fn_800B1884(void *e, int id);

int fn_8015F008(void *self)
{
    register float v = fn_8015E64C(self);
    register void *p = fn_80442080(self);

    return v > fn_800B1884(p, 0xD3);
}

int fn_8015F07C(void *self)
{
    register float v = fn_8015E64C(self);
    register void *p = fn_80442080(self);

    return v < fn_800B1884(p, 0xD4);
}
