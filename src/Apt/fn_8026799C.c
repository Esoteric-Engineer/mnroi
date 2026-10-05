// Four setters and a getter over consecutive words of an Apt runtime record, from the -O2 -fno-strength-reduce -G0 block (docs/prodg.md, "Middleware").

void fn_8026799C(int *self, int value)
{
    self[0] = value;
}

void fn_802679A4(int *self, int value)
{
    self[1] = value;
}

void fn_802679AC(int *self, int value)
{
    self[2] = value;
}

void fn_802679B4(int *self, int value)
{
    self[3] = value;
}

int fn_802679BC(int *self)
{
    return self[3];
}
