// The String builder fn_80448B24 with a C string for b: String(b) is a temporary bound by reference, c travels by value.
class String
{
public:
    char data[0x4C];
    String(const char *s) __asm__("__6StringPCc");
    String(const String &s) __asm__("__6StringRC6String");
    ~String();
} __attribute__((aligned(8)));

extern "C" void fn_80448B24(void *self, const String &b, String c);

inline int sn_return_decl(int a) { return a; }

extern "C" void fn_80448C18(void *self, const char *b, String c)
{
    fn_80448B24(self, String(b), c);
}
