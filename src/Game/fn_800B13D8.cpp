// Null-checked read of the pointer at +0x24 of an entity.

inline int sn_return_decl(int a) { return a; }

struct Obj {
    char pad0[0x24];
    void *field; // +0x24
};

extern "C" void *fn_800B13D8(register Obj *self)
{
    if (self)
        return self->field;
    else
        return 0;
}
