// String-array owner destructor (strings at +0xD0..+0xA50); see docs/versus.md.
extern void fn_80449298(void *self, int inChrg);
extern void fn_8044AA1C(void *self);
extern void fn_8044A9D0(void *self, int inChrg);

void fn_8044A880(register char *self, register int inChrg)
{
    if (self + 0xD0 != 0)
    {
        register char *p = self + 0xA50;
        while (self + 0xD0 != p)
        {
            p -= 0x4C;
            fn_80449298(p, 0);
        }
        {
            register int f __asm__("r9") = 1;
            if (f & 2)
            {
                fn_8044AA1C(self + 0xC8);
            }
            else
            {
            }
        }
    }
    else
    {
    }
    fn_80449298(self + 0x4, 2);
    fn_8044A9D0(self, inChrg);
}
