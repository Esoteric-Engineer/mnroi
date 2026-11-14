// Delete-if-non-null helper, a pair-carrying file start; see docs/versus.md.
extern "C" {
extern void fn_801ACFD4(void *p) __asm__("__builtin_vec_delete");
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
