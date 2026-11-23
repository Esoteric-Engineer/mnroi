// A field getter of the loading-screen singleton (docs/core.md row 19).

inline int sn_return_decl(int a) { return a; }

struct LoadScreen
{
    char pad[0xF8];
    int fF8;
};

extern "C" int fn_8042D52C(register LoadScreen *self)
{
    return self->fF8;
}
