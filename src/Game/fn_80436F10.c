// ShapeBase-family float getter, destructor (vptr lbl_804F32F8) and float setter; see docs/versus.md, row 8.

extern void __builtin_delete(void *p);
extern char lbl_804F32F8[];

float fn_80436F10(register float *self)
{
    return *self;
}

void fn_80436F3C(register char *self, register int inChrg)
{
    *(char **)(self + 0x4) = lbl_804F32F8;
    if (inChrg & 1)
    {
        __builtin_delete(self);
    }
    else
    {
    }
}

void fn_80436F94(register float *self)
{
    *self = 1.0f;
}
