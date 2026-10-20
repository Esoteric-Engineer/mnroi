// Address of player slot `slot` (0-8) at +0x4A4 + slot * 0x20 of the object fn_804326B4 returns, or 0 (docs/versus.md section 5, row 2).
void *fn_80454384(register char *self, register int slot)
{
    if (slot >= 0 && slot <= 8)
    {
        return self + (slot * 0x20 + 0x4A4);
    }
    else
    {
        return 0;
    }
}
