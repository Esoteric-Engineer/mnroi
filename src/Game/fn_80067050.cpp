// An entity's Havok rigid body (fn_800B24AC):
// fn_80067050 copies its velocity out and says whether there is a body; fn_800670CC returns its speed, 0 without one.

inline int sn_return_decl(int a) { return a; }

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

struct Ent {
    int pad;
};

extern "C" {
void *fn_800B24AC(Ent &actor);
void *fn_80318EB4(void *body);
void fn_80434BA4(Vector *out, void *v);
float fn_804365A0(void *v);
}

extern "C" int fn_80067050(register Ent &actor, Vector *v)
{
    if (!fn_800B24AC(actor))
        return 0;
    fn_80434BA4(v, fn_80318EB4(fn_800B24AC(actor)));
    return 1;
}

extern "C" float fn_800670CC(register Ent &actor)
{
    if (!fn_800B24AC(actor))
        return 0.0f;
    return fn_804365A0(fn_80318EB4(fn_800B24AC(actor)));
}

// Two -0.11f literals the code never loads: the pool of a linkonce function (docs/matching_notes.md).
__asm__(".section .rodata\n\t.float -0.11\n\t.float -0.11\n\t.text");
