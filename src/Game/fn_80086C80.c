// Reads PLAYER tuning field 0x86 + i; docs/versus.md rows 20-21.

extern float fn_800B1884(void *e, int id);

float fn_80086C80(register void *self, register int i)
{
    return 1.0f - fn_800B1884(self, 0x86 + i);
}
