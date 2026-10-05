// String temp built from b and passed to the builder fn_80449084; NonMatching, see docs/nonmatching.md.
class String
{
public:
    char data[0x50];
    String(const char *s) __asm__("fn_804493A0");
};
extern "C" {
void fn_80449084(void *self, void *b, int c);
void fn_80449298(void *self, int inChrg);
}

inline int sn_return_decl(int a) { return a; }

extern "C" void fn_8044916C(void *self, const char *b, int c)
{
    String tmp = String(b);
    fn_80449084(self, &tmp, c);
    fn_80449298(&tmp, 2);
}
