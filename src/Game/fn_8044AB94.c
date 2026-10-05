// String builder: self += copy(b) + sep + String(&c); see docs/versus.md.
extern int fn_804496F4(void *self, void *src);
extern int fn_804494AC(void *self);
extern int fn_80449234(void *self);
extern int fn_80449A6C(void *self, const char *s);
extern int fn_80449B04(void *self, void *src);
extern int fn_80449298(void *self, int inChrg);
extern void fn_8044AB30(void *self, int *src);
extern char lbl_80490210[];
extern char lbl_80490214[];

void fn_8044AB94(void *self, void *b, int c)
{
    char tmp1[0x50];
    char tmp2[0x50];
    fn_804496F4(tmp1, b);
    fn_804494AC(tmp1);
    if (fn_80449234(self))
    {
        fn_80449A6C(self, lbl_80490210);
    }
    fn_80449B04(self, tmp1);
    fn_80449A6C(self, lbl_80490214);
    fn_8044AB30(tmp2, &c);
    fn_804494AC(tmp2);
    fn_80449B04(self, tmp2);
    fn_80449298(tmp2, 2);
    fn_80449298(tmp1, 2);
}
