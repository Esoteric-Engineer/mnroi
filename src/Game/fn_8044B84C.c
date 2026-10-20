// AptObject's reference-counted payload: release (hand-written destructor), the +4 accessor and the copy (docs/versus.md section 5, row 2).
extern void __builtin_delete(void *p);
extern void fn_8044A108(int *count, void *obj);
extern int fn_80449824(register int *self);
extern void fn_8044B950(int *count);

void fn_8044B84C(register int **self, register int inChrg)
{
    if (*self)
    {
        fn_8044A108(*self, *self);
    }
    if (inChrg & 1)
    {
        __builtin_delete(self);
    }
    else
    {
    }
}

int fn_8044B8B0(register int *self)
{
    return fn_80449824(self) + 4;
}

int **fn_8044B8F8(register int **self, register int **other)
{
    *self = *other;
    if (*self)
    {
        fn_8044B950(*self);
    }
    return self;
}

void fn_8044B950(register int *count)
{
    *count = *count + 1;
}
