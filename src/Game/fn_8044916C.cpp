// String temp built from b and passed to the builder fn_80449084.
class String
{
public:
    char data[0x50];
    String(const char *s) __asm__("__6StringPCc");
    ~String();
};
extern "C" void fn_80449084(void *self, const String &b, int c);

inline int sn_return_decl(int a) { return a; }

extern "C" void fn_8044916C(void *self, const char *b, int c)
{
    fn_80449084(self, String(b), c);
}
