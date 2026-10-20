// A String as a String, returned by value: the conversion, the tag-dispatched overload and the one-argument front.
class String
{
public:
    char data[0x4C];
    String(const String &s) __asm__("__6StringRC6String");
    ~String();
} __attribute__((aligned(8)));

struct Tag
{
};

inline int sn_return_decl(int a) { return a; }

extern "C" String fn_80448A28(register const String &s)
{
    return s;
}

extern "C" String fn_80448A74(const String &s, Tag)
{
    return fn_80448A28(s);
}

struct TagV
{
    unsigned char v;
};

extern "C" String fn_80448A74_v(const String &value, const TagV &) __asm__("fn_80448A74");

extern "C" String fn_80448AC0(const String &value)
{
    int *p = 0;
    {
        register int z __asm__("r0") = 0;
        register unsigned char zero __asm__("r9") = 0;
        TagV tag;
        tag.v = zero;
        return fn_80448A74_v(value, tag);
    }
}
