// String builders: tmp1 = String(b); tmp1 += String(n); then fn_8044AB94 / fn_80449084; see docs/versus.md.
extern int fn_804493A0(void *self, const char *s) __asm__("__6StringPCc");
extern int fn_80449020(void *self, int *src);
extern int fn_80449298(void *self, int inChrg) __asm__("_._6String");
extern int fn_80449B04(void *self, void *src);
extern void fn_80449084(void *self, void *b, int c);
extern void fn_8044AB94(void *self, void *b, int c);

void fn_8044ACEC(void *self, int n, const char *b, int c)
{
    char tmp1[0x50];
    char tmp2[0x50];
    register char *p;
    fn_804493A0(tmp1, b);
    p = tmp1;
    fn_80449020(tmp2, &n);
    fn_80449B04(p, tmp2);
    fn_80449298(tmp2, 2);
    fn_8044AB94(self, tmp1, c);
    fn_80449298(tmp1, 2);
}

void fn_8044AD94(void *self, int n, const char *b, int c)
{
    char tmp1[0x50];
    char tmp2[0x50];
    register char *p;
    fn_804493A0(tmp1, b);
    p = tmp1;
    fn_80449020(tmp2, &n);
    fn_80449B04(p, tmp2);
    fn_80449298(tmp2, 2);
    fn_80449084(self, tmp1, c);
    fn_80449298(tmp1, 2);
}
