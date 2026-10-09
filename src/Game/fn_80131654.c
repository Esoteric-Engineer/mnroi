// Calls fn_80007624 on the .sdata object lbl_8066B578. See docs/versus.md (section 5, row 9a).

extern void *lbl_8066B578;

extern void fn_80007624(void *obj);

void fn_80131654(void)
{
    fn_80007624(lbl_8066B578);
}
