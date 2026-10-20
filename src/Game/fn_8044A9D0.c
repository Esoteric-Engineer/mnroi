// String-array owner base destructor; see docs/versus.md.
extern void __builtin_delete(void *p);

void fn_8044A9D0(register void *self, register int inChrg)
{
    if (inChrg & 1)
    {
        __builtin_delete(self);
    }
    else
    {
    }
}
