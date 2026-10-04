// Vec4 setter and the quaternion-style combine built on fn_804467B0; see docs/versus.md section 5.
extern void fn_80434988(void *self);
extern void fn_8037BDF4(void *self, void *other, float s);
extern void fn_804349B0(void *out, void *a, void *b);
extern void fn_804467B0(void *self, void *a, void *b);
extern void fn_80446FD8(void *a, void *b, void *c);

void *fn_8044695C(register void *self, register void *other, register float s)
{
    fn_80434988(self);
    fn_8037BDF4(self, other, s);
    return self;
}

void fn_804469BC(register void *a, register void *b, register void *c)
{
    char tmp[16];

    fn_80434988(tmp);
    fn_804349B0(tmp, a, b);
    fn_804467B0(tmp, c, tmp);
    fn_80446FD8(a, b, tmp);
}
