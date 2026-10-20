// String(const char *): a copy of a C string; a null pointer gives the empty string.
// The explicit buf() is what leaves the three dead array-init temps (docs/matching_notes.md).
extern "C" {
char *fn_80449330(int len);
char *fn_80449B80(const char *first, const char *last, char *out);
char *fn_80449DA4(const char *first, const char *last, char *out);
}

class StringBase
{
public:
    int len;   // +0x0
    int shown; // +0x4
    StringBase(int n) __asm__("fn_804492FC");
    void setShown(int n) __asm__("fn_80449378");
};

class String : public StringBase
{
public:
    char buf[0x40]; // +0x8
    char *data;     // +0x48
    String();
    String(const char *s);
    String(const String &s);
    int length() const __asm__("fn_80449234");
};

inline int sn_return_decl(int a) { return a; }

String::String(register const char *s) : StringBase(0), buf()
{
    data = buf;
    if (s == 0)
    {
        buf[0] = 0;
        return;
    }
    else
    {
    }
    const char *p = s;
    while (*p++ != 0)
    {
        len++;
    }
    if (len > 0x3F)
    {
        data = fn_80449330(len);
    }
    fn_80449B80(s, s + len, data);
    data[len] = 0;
    setShown(len);
}
