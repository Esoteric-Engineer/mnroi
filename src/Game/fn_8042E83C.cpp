// Two one-word getters (docs/core.md row 19). Names are placeholders.

inline int sn_return_decl(int a) { return a; }

struct A
{
    char pad[0x2C];
    void *f2C;
};

struct B
{
    char pad[0x14];
    int f14;
};

extern "C" void *fn_8042E83C(register A *self)
{
    return self->f2C;
}

extern "C" int fn_8042E868(register B *self)
{
    return self->f14;
}
