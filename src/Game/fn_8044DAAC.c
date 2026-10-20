// String builder: self += copy(b) + sep + String(&c). See docs/versus.md.
extern int fn_804496F4(void *self, void *src) __asm__("__6StringRC6String");
extern int fn_804494AC(void *self);
extern int fn_80449234(void *self);
extern int fn_80449A6C(void *self, const char *s);
extern int fn_80449B04(void *self, void *src);
extern int fn_80449298(void *self, int inChrg) __asm__("_._6String");
extern void fn_8044DA48(void *self, int *src);
extern char lbl_80491118[];
extern char lbl_8049111C[];

void fn_8044DAAC(void *self, void *b, int c)
{
    char tmp1[0x50];
    char tmp2[0x50];
    fn_804496F4(tmp1, b);
    fn_804494AC(tmp1);
    if (fn_80449234(self))
    {
        fn_80449A6C(self, lbl_80491118);
    }
    fn_80449B04(self, tmp1);
    fn_80449A6C(self, lbl_8049111C);
    fn_8044DA48(tmp2, &c);
    fn_804494AC(tmp2);
    fn_80449B04(self, tmp2);
    fn_80449298(tmp2, 2);
    fn_80449298(tmp1, 2);
}
