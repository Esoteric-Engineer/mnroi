// Vec4 setup and a basis-building helper that stores through call results; pool read through extern_pool.
extern "C" {
void fn_804363B8(void *self);
float *fn_80438360(void *self, int i);
void fn_8043C7CC(void *self);
void *fn_8043BBD0(void *self);
void fn_80434A18(void *self, void *a, void *b);
float fn_8043C69C(void *self, int i);
void fn_8043C6D8(void *self, float s, void *v);
void fn_804364BC(void *self, float s, void *v);
float fn_8043C764(void *a, void *b);
}

inline int sn_return_decl(int a) { return a; }

extern "C" void fn_8043BC48(register void *self)
{
    fn_804363B8(self);
    *fn_80438360(self, 3) = 1.0f;
}

extern "C" void fn_8043BCA0(register void *self)
{
    fn_8043C7CC(self);
}

extern "C" void fn_8043BCD8(register void *self, register void *a, register void *b)
{
    fn_80434A18(self, fn_8043BBD0(b), fn_8043BBD0(a));
    fn_8043C6D8(self, fn_8043C69C(a, 3), fn_8043BBD0(b));
    fn_804364BC(self, fn_8043C69C(b, 3), fn_8043BBD0(a));
    *fn_80438360(self, 3) = fn_8043C764(a, b);
}
