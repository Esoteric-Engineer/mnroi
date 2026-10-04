// Broadcasts a call to every element of a list (count fn_801B6A44, element fn_801B5D3C).
// Element and callee types are guesses; see docs/versus.md section 5, step 4.

extern int fn_801B6A44(void *list);
extern void *fn_801B5D3C(void *list, int index);
extern void fn_804440B0(void *target, int a, int b, int c);
extern void fn_8044412C(void *target, int a, int b);

void fn_80443F0C(register void *list, register int a, register int b, register int c)
{
    void **item;
    int i;

    i = 0;
    while (i < fn_801B6A44(list))
    {
        item = fn_801B5D3C(list, i);
        fn_804440B0(*item, a, b, c);
        i++;
    }
}

void fn_80443FA4(register void *list, register int a, register int b)
{
    void **item;
    int i;

    i = 0;
    while (i < fn_801B6A44(list))
    {
        item = fn_801B5D3C(list, i);
        fn_8044412C(*item, a, b);
        i++;
    }
}
