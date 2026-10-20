// String(b) appended through fn_8044AB94; the temp is passed by reference.
class String
{
public:
    char data[0x50];
    String(const char *s) __asm__("__6StringPCc");
    ~String();
};
extern "C" void fn_8044AB94(void *self, const String &b, int c);

inline int sn_return_decl(int a) { return a; }

extern "C" void fn_8044AC7C(void *self, const char *b, int c)
{
    fn_8044AB94(self, String(b), c);
}
