// String builder: self += copy(b) + sep + int(c); see docs/versus.md.
extern "C" {
void fn_80449020(void *self, int *src);
void fn_804494AC(void *self);
int fn_80449234(void *self);
void fn_80449298(void *self, int inChrg);
void fn_804496F4(void *self, void *src);
void fn_80449A6C(void *self, const char *s);
void fn_80449B04(void *self, void *src);
extern char lbl_804900B4[];
extern char lbl_804900B8[];
}

inline int sn_return_decl(int a) { return a; }

extern "C" void fn_80449084(void *self, void *b, int c)
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
    fn_80449020(tmp2, &c);
    fn_804494AC(tmp2);
    fn_80449B04(self, tmp2);
    fn_80449298(tmp2, 2);
    fn_80449298(tmp1, 2);
}
