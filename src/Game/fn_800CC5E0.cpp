// Entity to its actor (pointer at +0xE4; name is a guess from the callers). Row 19 of docs/versus.md.

inline int sn_return_decl(int a) { return a; }

struct Obj {
    char pad0[0xE4];
    void *actor; // +0xE4
};

extern "C" void *Entity_GetActor(register Obj *self)
{
    return self->actor;
}
