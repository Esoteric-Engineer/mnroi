// NVB lookup by "<a>_<b>.nvb"; docs/versus.md section 5, row 12.

extern int sprintf(char *dst, const char *fmt, ...);
extern char lbl_8049E518[]; // "%s_%s.nvb"
extern void *lbl_8066C6D0;  // the NVB registry
extern int fn_801B48AC(void *registry, char *name);

int fn_801B301C(char *a, char *b)
{
    char name[0x80];
    sprintf(name, lbl_8049E518, a, b);
    return fn_801B48AC(lbl_8066C6D0, name);
}
