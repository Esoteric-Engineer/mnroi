// String comparison helpers: fn_8044B97C is strcmp over two strings, fn_8044B9E8 tests a string against a C string (docs/versus.md section 5, row 2).
extern "C" int strcmp(const char *a, const char *b);

class String {
public:
    String(const char *s) __asm__("__6StringPCc");
    ~String();
    const char *c_str() __asm__("fn_804496C8");
    char data[0x4C];
} __attribute__((aligned(8)));

extern "C" int fn_8044B97C(register String *a, register String *b)
{
    return strcmp(a->c_str(), b->c_str());
}

extern "C" int fn_8044B9E8(String *self, const char *s)
{
    return fn_8044B97C(self, &String(s)) == 0;
}
