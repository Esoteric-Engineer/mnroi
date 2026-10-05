// String builder: self += copy(b) + sep + copy(c); fn_80449298 is the string destructor, fn_80448AC0 a copy constructor.
extern int fn_804496F4(void *self, void *src);
extern int fn_804494AC(void *self);
extern int fn_80449234(void *self);
extern int fn_80449A6C(void *self, const char *s);
extern int fn_80449B04(void *self, void *src);
extern int fn_80449298(void *self, int inChrg);
extern void fn_80448AC0(void *self, void *src);
extern char lbl_804900B4[];
extern char lbl_804900B8[];

void fn_80448B24(void *self, void *b, register void *c)
{
    char tmp1[0x50];
    char tmp2[0x50];
    fn_804496F4(tmp1, b);
    fn_804494AC(tmp1);
    if (fn_80449234(self))
    {
        fn_80449A6C(self, lbl_804900B4);
    }
    fn_80449B04(self, tmp1);
    fn_80449A6C(self, lbl_804900B8);
    fn_80448AC0(tmp2, c);
    fn_804494AC(tmp2);
    fn_80449B04(self, tmp2);
    fn_80449298(tmp2, 2);
    fn_80449298(tmp1, 2);
    goto end;
end:
    fn_80449298(c, 2);
}
