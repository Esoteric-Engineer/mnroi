// String(const char *) front for the int-to-String builder fn_8044F4BC (Game/fn_8044F4BC.c). See docs/versus.md.

inline int sn_return_decl(int a) { return a; }

class String
{
public:
    char data[0x4C];
    String(const char *s);
    ~String();
} __attribute__((aligned(8)));

extern "C" void fn_8044F4BC(void *self, const String &b, int c);

extern "C" void fn_8044F5A4(void *self, const char *b, int c)
{
    fn_8044F4BC(self, String(b), c);
}
