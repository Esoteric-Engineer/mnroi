// Member address getters of one class (docs/core.md row 19). Names are placeholders.

inline int sn_return_decl(int a) { return a; }

struct Block
{
    char pad0[0x8];
    char f8[0x20];
    char f28[1];
};

extern "C" char *fn_8042E4FC(register Block *self)
{
    return self->f8;
}

extern "C" char *fn_8042E528(register Block *self)
{
    return self->f28;
}
