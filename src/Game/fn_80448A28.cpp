// A String as a String, returned by value: the conversion and the tag-dispatched overload that forwards to it.
// The one-argument front, fn_80448AC0, is not matched yet (docs/nonmatching.md). Names are guesses.
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
