// Wrappers over methods of the .sdata object lbl_8066B578. See docs/versus.md (section 5, row 9a).

extern void *lbl_8066B578;

extern void fn_80007624(void *obj);
extern void fn_80007678(void *obj);
extern void fn_800075EC(void *obj, unsigned a, unsigned b);
extern void fn_801AFD14(int total, int *units, unsigned *a, unsigned *b, int *carry);

void fn_80131654(void)
{
    fn_80007624(lbl_8066B578);
}

void fn_80131688(void)
{
    fn_80007678(lbl_8066B578);
}

void fn_801316BC(int total)
{
    int units;
    unsigned a;
    unsigned b;
    int carry;

    fn_801AFD14(total, &units, &a, &b, &carry);
    fn_800075EC(lbl_8066B578, a, b);
}
