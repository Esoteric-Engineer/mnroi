// Reads PLAYER tuning fields 103, 104 and 167; docs/versus.md rows 20-21.

extern float fn_800B1884(void *e, int id);

float fn_80086D54(register void *self)
{
    return fn_800B1884(self, 0x68);
}

float fn_80086D9C(register void *self)
{
    return fn_800B1884(self, 0x67);
}

float fn_80086DE4(register void *self)
{
    return fn_800B1884(self, 0xA7);
}
