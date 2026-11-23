// A flag of the .nsc script record (docs/core.md row 19, docs/characters.md section 4).

inline int sn_return_decl(int a) { return a; }

struct ScriptRecord
{
    char pad[0x1AC];
    unsigned int flags;
};

extern "C" int fn_8042D444(register ScriptRecord *self)
{
    return self->flags & 2;
}
