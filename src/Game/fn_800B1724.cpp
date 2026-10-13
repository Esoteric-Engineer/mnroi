// Address of the field at +0xA8 of an entity. Row 19 of docs/versus.md.

inline int sn_return_decl(int a) { return a; }

struct Obj {
    char pad0[0xA8];
    char field[1]; // +0xA8
};

extern "C" void *fn_800B1724(register Obj *self)
{
    return &self->field;
}
