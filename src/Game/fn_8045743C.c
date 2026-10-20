// Tests whether the word at +0x8 of a handle-holding object is nonzero (docs/versus.md section 5, row 2).
int fn_8045743C(register int *self)
{
    register int r = 1;
    if (self[2] == 0)
        r = 0;
    return r;
}
