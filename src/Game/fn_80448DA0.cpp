// An int as a String, returned by value: decimal digits written into a 16-char String from the end. The name is a guess.
extern "C" {
char fn_804491DC(int digit);
char fn_80449210(void);
}

class String
{
public:
    char data[0x4C];
    String(int len, char ch);
    String(const char *s) __asm__("__6StringPCc");
    String(const String &s) __asm__("__6StringRC6String");
    ~String();
    char &operator[](int idx) __asm__("fn_80449260");
    const char *c_str() __asm__("fn_804496C8");
} __attribute__((aligned(8)));

inline int sn_return_decl(int a) { return a; }

String IntToString(register int value)
{
    if (value == 0)
    {
        char str[2] = { fn_804491DC(0), 0 };
        return String(str);
    }
    int neg = 0;
    if (value < 0)
    {
        value = -value;
        neg = 1;
    }
    int width = 16;
    String buf(0x11, 0);
    buf[0x10] = 0;
    int n = 0;
    while (value != 0 && n < 16)
    {
        buf[15 - n] = fn_804491DC(value % 10);
        value = value / 10;
        n++;
    }
    if (neg && n < 16)
    {
        buf[15 - n++] = fn_80449210();
    }
    String res(buf.c_str() - (n - 16));
    return res;
}
