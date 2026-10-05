// Classifies a character pair against the line-break sets lbl_8066FBA5 and lbl_8066FBA4; returns 10, 11, 13 or 0.
extern char *strchr(const char *s, int c);
extern char lbl_8066FBA4[1]; // "\r", .sdata2 pool is cyclic to claim
extern char lbl_8066FBA5[3]; // "\n\v"

int fn_804488C0(register int a, register int b)
{
    if (strchr(lbl_8066FBA5, a))
    {
        return 10;
    }
    if (strchr(lbl_8066FBA4, a))
    {
        if (strchr(lbl_8066FBA5, b))
        {
            return 11;
        }
        return 13;
    }
    return 0;
}
