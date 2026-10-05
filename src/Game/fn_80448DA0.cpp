// String(int): decimal digits into a 16-char buffer from the end, copied into this; NonMatching, see docs/nonmatching.md.
class String;
extern "C" {
void *fn_80448CB0(void *self, int len, int ch);
char fn_804491DC(int digit);
char fn_80449210(void);
char *fn_80449260(void *self, int idx);
void *fn_80449298(void *self, int inChrg);
String &fn_804493A0(void *self, const char *s);
const char *fn_804496C8(void *self);
String &fn_804496F4(void *self, void *src);
}

inline int sn_return_decl(int a) { return a; }

struct Two
{
    char a;
    char b;
} __attribute__((aligned(2)));

class String
{
public:
    String(register int value);
};

String::String(register int value)
{
    if (value == 0)
    {
        Two str = { fn_804491DC(0), 0 };
        fn_804493A0(this, (const char *)&str);
    }
    else
    {
        int neg;
        int width;
        char buf[0x50];
        int n;
        char res[0x50];
        neg = 0;
        if (value < 0)
        {
            value = -value;
            neg = 1;
        }
        width = 16;
        fn_80448CB0(buf, 0x11, 0);
        *fn_80449260(buf, 0x10) = 0;
        n = 0;
        while (value != 0 && n < 16)
        {
            *fn_80449260(buf, 15 - n) = fn_804491DC(value % 10);
            value = value / 10;
            n++;
        }
        if (neg && n < 16)
        {
            *fn_80449260(buf, 15 - n++) = fn_80449210();
        }
        fn_804493A0(res, fn_804496C8(buf) - (n - 16));
        fn_804496F4(this, res);
        fn_80449298(res, 2);
        fn_80449298(buf, 2);
    }
}
