// An int as a String, returned by value (Game/fn_80448DA0.cpp's IntToString): the conversion, its tag overload and the front.
class String
{
public:
    char data[0x4C];
    ~String();
} __attribute__((aligned(8)));

struct Tag
{
};

struct TagV
{
    unsigned char v;
};

String IntToString(int value);

inline int sn_return_decl(int a) { return a; }

extern "C" String fn_8044DCAC(register int value)
{
    return IntToString(value);
}

extern "C" String fn_8044DCF4(const int &value, Tag)
{
    return fn_8044DCAC(value);
}

extern "C" String fn_8044DCF4_v(const int &value, const TagV &) __asm__("fn_8044DCF4");

extern "C" String fn_8044DD44(const int &value)
{
    int *p = 0;
    {
        register int z __asm__("r0") = 0;
        register unsigned char zero __asm__("r9") = 0;
        TagV tag;
        tag.v = zero;
        return fn_8044DCF4_v(value, tag);
    }
}
