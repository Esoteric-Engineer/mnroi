// Reads PLAYER tuning field 104; docs/versus.md rows 20-21.

extern float fn_800B1884(void *e, int id);

float fn_80086D54(register void *self)
{
    return fn_800B1884(self, 0x68);
}
