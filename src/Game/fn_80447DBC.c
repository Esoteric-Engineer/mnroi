// The AIObject destructor, the BitSet one and the +0xD0 target list's (docs/ai.md 4.1), and a constructor with a Vector at +0x20.
// Hand-written in C because the DOL keeps the in-charge flag (bit 0 = delete) in a register.
extern void fn_801ACFD4(void *p) __asm__("__builtin_vec_delete");
extern void __builtin_delete(void *p);
extern void __6Vector(void *v);
extern void fn_801B5C74(void *list, int inChrg);
void BitSet_Destroy(register void **self, register int inChrg);
void fn_80447F1C(register char *self, register int inChrg);

void fn_80447DBC(register char *self, register int inChrg)
{
    BitSet_Destroy((void **)(self + 0x508), 2);
    BitSet_Destroy((void **)(self + 0x500), 2);
    fn_80447F1C(self + 0xD0, 2);
    fn_801B5C74(self + 0xAC, 2);
    BitSet_Destroy((void **)(self + 0x14), 2);
    BitSet_Destroy((void **)(self + 0xC), 2);
    if (inChrg & 1)
    {
        __builtin_delete(self);
    }
    else
    {
    }
}

char *fn_80447E68(register char *self)
{
    __6Vector(self + 0x20);
    return self;
}

void BitSet_Destroy(register void **self, register int inChrg)
{
    if (*self != 0)
    {
        if (*self != 0)
        {
            fn_801ACFD4(*self);
        }
        else
        {
        }
    }
    if (inChrg & 1)
    {
        __builtin_delete(self);
    }
    else
    {
    }
}

void fn_80447F1C(register char *self, register int inChrg)
{
    BitSet_Destroy((void **)(self + 0xFC), 2);
    if (inChrg & 1)
    {
        __builtin_delete(self);
    }
    else
    {
    }
}
