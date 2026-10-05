// An int as a String, returned by value: the tag-dispatched overload that forwards to IntToString (Game/fn_80448DA0.cpp).
// The one-argument front, fn_80449020, is not matched yet (docs/nonmatching.md). Names are guesses.
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
