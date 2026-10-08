// Getter for the word at +0x2D0 of a handle-holding object (docs/versus.md section 5, row 2).
int fn_80457368(register char *self)
{
    return *(int *)(self + 0x2D0);
}
