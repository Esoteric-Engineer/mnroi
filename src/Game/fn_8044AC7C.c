// String(b) appended through fn_8044AB94; the temp is passed by reference; see docs/nonmatching.md.
extern int fn_804493A0(void *self, const char *s);
extern int fn_80449298(void *self, int inChrg);
extern void fn_8044AB94(void *self, void *b, int c);

void fn_8044AC7C(void *self, const char *b, int c)
{
    char tmp[0x50];
    fn_804493A0(tmp, b);
    fn_8044AB94(self, tmp, c);
    fn_80449298(tmp, 2);
}
