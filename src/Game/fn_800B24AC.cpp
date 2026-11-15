// The entity's Havok rigid body, at +0x180; null for an entity without one. Read on actors and on picked-up props.

inline int sn_return_decl(int a) { return a; }

struct Actor {
    char pad0[0x180];
    void *body; // +0x180
};

extern "C" void *fn_800B24AC(register Actor *self)
{
    return self->body;
}
