// Offsets the z of a target-supplied vector by a random amount that grows with distance (tuning fields 7, 8); docs/versus.md row 20.

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

struct PEnt : Ent { // matching_notes 44
    int x;
};

struct EObj {
    char d[0x3AC];
};

struct Obj : EObj {
    int pad;
};

struct TObj {
    char d[0x198];
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5(Vector *out, int mode); // vtable +0x30
};

extern "C" {
PEnt *Entity_GetActor(void *self);
void *fn_800B1724(Ent &node);
float fn_800B1884(Ent &actor, int id);
float fn_804290F8(void *a, void *b);
int fn_80171F8C(void);
void fn_80429038(void *out, void *a, void *b);
void fn_8042F76C(void *v);
}

extern "C" void fn_800F0AA0(register Obj *self, void *dir, TObj *target, void *out)
{
    float dist = fn_804290F8(fn_800B1724(*Entity_GetActor(self)), fn_800B1724(*(Ent *)target));
    float spread = 0.0f;
    float lo = fn_800B1884(*Entity_GetActor(self), 7);
    float hi = fn_800B1884(*Entity_GetActor(self), 8);
    if (dist > hi)
        dist = hi;
    if (dist > lo) {
        spread = fn_80171F8C() * 4.656613e-10f - 0.5f;
        spread = spread * ((dist - lo) / hi);
        Vector v;
        target->s5(&v, 0);
        v.z += spread;
        fn_80429038(out, &v, dir);
        fn_8042F76C(out);
    }
}
