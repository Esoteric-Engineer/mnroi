// Whether a model instance has a scale of its own (flag 0x800).

struct Instance {
    int unk0;
    unsigned int flags; // +0x4
};

inline int sn_return_decl(int a) { return a; }

extern "C" unsigned int fn_80466268(register Instance *self)
{
    return self->flags & 0x800;
}
