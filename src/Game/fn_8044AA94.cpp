// A C string as a String, returned by value: the conversion and the tag-dispatched overload that forwards to it.
// The one-argument front, fn_8044AB30, is not matched yet (docs/nonmatching.md). Names are guesses.
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
