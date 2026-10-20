// Float setters on a subobject at +0x80: a store through the call result, which only cc1plus compiles this way.
extern "C" {
float *fn_8042FB28(void *p);
float fn_801BDB9C(float v);
}

inline int sn_return_decl(int a) { return a; }

extern "C" void fn_80446C80(register char *self, register float v)
{
    *fn_8042FB28(self + 0x80) = v;
}

extern "C" void fn_80446CD4(register char *self, register float v)
{
    fn_8042FB28(self + 0x80)[2] = v;
}

extern "C" void fn_80446D28(register char *self, register float v)
{
    *fn_8042FB28(self + 0x80) = fn_801BDB9C(v);
}

extern "C" void fn_80446D88(register char *self, register float v)
{
    fn_8042FB28(self + 0x80)[2] = fn_801BDB9C(v);
}
