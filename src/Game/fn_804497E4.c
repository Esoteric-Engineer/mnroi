// Small accessors of the string iterator/triple objects (fn_804497E4: three-word store, fn_80449898: set to 1).
int *fn_804497E4(register int *self, register int a, register int b, register int c)
{
    self[0] = a;
    self[1] = b;
    self[2] = c;
    return self;
}

int fn_80449824(register int *self)
{
    return *self;
}


int fn_80449850(register int *self)
{
    return fn_80449824(self) + 4;
}

int *fn_80449898(register int *self)
{
    *self = 1;
    return self;
}
