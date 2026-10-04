// Float setters on a subobject at +0x80; see docs/nonmatching.md.
extern float *fn_8042FB28(void *p);
extern float fn_801BDB9C(float v);

void fn_80446C80(register char *self, register float v)
{
    register float *p;
    *(p = fn_8042FB28(self + 0x80)) = v;
}

void fn_80446CD4(register char *self, register float v)
{
    register float *p;
    (p = fn_8042FB28(self + 0x80))[2] = v;
}

void fn_80446D28(register char *self, register float v)
{
    register float *p = fn_8042FB28(self + 0x80);
    *p = fn_801BDB9C(v);
}

void fn_80446D88(register char *self, register float v)
{
    register float *p = fn_8042FB28(self + 0x80);
    p[2] = fn_801BDB9C(v);
}
