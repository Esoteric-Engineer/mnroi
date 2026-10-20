// Setters of a draw object and two globals.

extern int lbl_8066C644;
extern int lbl_8066C648;

void fn_80445F00(register char *self)
{
    *(int *)(self + 0x1000) = 0;
}

void fn_80445F28(register int a)
{
    lbl_8066C644 = a;
}

void fn_80445F4C(register int a)
{
    lbl_8066C648 = a;
}
