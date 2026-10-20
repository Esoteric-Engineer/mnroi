// A C string as a String, returned by value: the conversion, the tag overload and the one-argument front.
class String
{
public:
    char data[0x4C];
    String(const char *s) __asm__("__6StringPCc");
    ~String();
} __attribute__((aligned(8)));

struct Tag
{
};

inline int sn_return_decl(int a) { return a; }

extern "C" String fn_8044AA94(register const char *s)
{
    return String(s);
}

extern "C" String fn_8044AAE0(const char *const &s, Tag)
{
    return fn_8044AA94(s);
}

struct TagV
{
    unsigned char v;
};

extern "C" String fn_8044AAE0_v(const char *const &value, const TagV &) __asm__("fn_8044AAE0");

extern "C" String fn_8044AB30(const char *const &value)
{
    int *p = 0;
    {
        register int z __asm__("r0") = 0;
        register unsigned char zero __asm__("r9") = 0;
        TagV tag;
        tag.v = zero;
        return fn_8044AAE0_v(value, tag);
    }
}
