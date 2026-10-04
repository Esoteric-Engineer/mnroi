// Retries fn_804460F4 on lbl_80628B00 after fn_80446214, plus three small methods.

extern char lbl_80628B00[];

extern int fn_804460F4(void *self, float x, float y, int a);
extern void fn_80446214(int a);
extern void fn_80445F00(char *self);

void fn_80445FD0(register float x, register float y, register int a, register int b)
{
    if (fn_804460F4(lbl_80628B00, x, y, a) != 0)
    {
        fn_80446214(b);
        fn_80445F00(lbl_80628B00);
        fn_804460F4(lbl_80628B00, x, y, a);
    }
}

void fn_8044606C(register char *self)
{
    *(int *)(self + 0x1DC) = 0;
}

void fn_80446094(register char *self, register int a)
{
    *(int *)(self + 0x17C) = a;
}

int fn_804460BC(register char *self)
{
    return *(int *)(self + 4) == 3;
}
