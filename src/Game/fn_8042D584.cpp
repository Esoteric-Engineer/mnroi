// The localization singleton's language getter (docs/core.md row 19). Field name is a guess.

inline int sn_return_decl(int a) { return a; }

struct Locale
{
    char pad[0x218];
    int language;
};

extern "C" int fn_8042D584(register Locale *self)
{
    return self->language;
}
