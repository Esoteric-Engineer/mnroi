// String(int, char): the fill constructor, n copies of ch. The explicit buf() is what leaves the three dead array-init temps.
extern "C" {
char *fn_80449330(int len);
}

class StringBase
{
public:
    int len;      // +0x0
    int shown;    // +0x4
    StringBase(int n) __asm__("fn_804492FC");
    void setShown(int n) __asm__("fn_80449378");
};

class String : public StringBase
{
public:
    char buf[0x40]; // +0x8
    char *data;     // +0x48
    String(int n, char ch);
};

inline int sn_return_decl(int a) { return a; }

String::String(register int n, register char ch) : StringBase(n), buf()
{
    data = buf;
    if (len > 0x3F)
    {
        data = fn_80449330(len);
    }
    if (len > 0)
    {
        int i = 0;
        while (i < len)
        {
            data[i] = ch;
            i++;
        }
    }
    data[len] = 0;
    setShown(len);
}
