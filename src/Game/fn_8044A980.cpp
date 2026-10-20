// Delete-if-non-null helper, a pair-carrying file start; see docs/versus.md.
extern "C" {
extern void fn_801ACFD4(void *p);
}

extern "C" void fn_8044A980(register void *p)
{
    if (p != 0)
    {
        fn_801ACFD4(p);
    }
    else
    {
    }
    return;
}
