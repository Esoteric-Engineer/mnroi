// The frame clock's real ms and real delta seconds (docs/core.md row 19, section 4.8).

inline int sn_return_decl(int a) { return a; }

struct Clock
{
    char pad[0x24];
    unsigned int realMs;  // +0x24
    char pad28[0x8];
    float realDt;         // +0x30
};

extern "C" unsigned int fn_8042E96C(register Clock *self)
{
    return self->realMs;
}

extern "C" float fn_8042E998(register Clock *self)
{
    return self->realDt;
}
