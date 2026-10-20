// An int as a String, returned by value: the tag overload that forwards to IntToString (Game/fn_80448DA0.cpp) and the one-argument front.
class String
{
public:
    char data[0x4C];
    ~String();
} __attribute__((aligned(8)));

struct Tag
{
};

String IntToString(int value);

inline int sn_return_decl(int a) { return a; }

extern "C" String fn_80448FD0(const int &value, Tag)
{
    return IntToString(value);
}

struct TagV
{
    unsigned char v;
};

extern "C" String fn_80448FD0_v(const int &value, const TagV &) __asm__("fn_80448FD0");

extern "C" String fn_80449020(const int &value)
{
    int *p = 0;
    {
        register int z __asm__("r0") = 0;
        register unsigned char zero __asm__("r9") = 0;
        TagV tag;
        tag.v = zero;
        return fn_80448FD0_v(value, tag);
    }
}
