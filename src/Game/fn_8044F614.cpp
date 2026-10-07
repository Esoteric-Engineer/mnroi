// String t(c) + IntToString-style conversion of b, handed to the builder fn_8044F4BC. See docs/versus.md.
class String
{
public:
    char data[0x50];
    String(const char *s) __asm__("__6StringPCc");
    ~String();
    void append(const String &s) __asm__("fn_80449B04");
};
extern "C" String fn_80449020(const int &v);
extern "C" void fn_8044F4BC(void *self, const String &b, int c);

inline int sn_return_decl(int a) { return a; }

extern "C" void fn_8044F614(void *self, int a, const char *b, int c)
{
    String t(b);
    t.append(fn_80449020(a));
    fn_8044F4BC(self, t, c);
}
