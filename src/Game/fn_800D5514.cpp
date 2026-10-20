// Starts the entity's PLAYER effect handle (tuning field 168) and plays its slots 20, 44 and, if the actor has a position, 22.

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

struct Handle {
    char d[0xC8];
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22(Vector *v);
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual void s39();
    virtual void s40();
    virtual void s41();
    virtual void s42();
    virtual void s43();
    virtual void s44();
    virtual void s45();
};

extern "C" {
PEnt *Entity_GetActor(void *self);
int fn_800ACD20(Ent &actor, int id);
Handle *fn_80393A60(Ent &actor, int id, int a);
int fn_8039D3C0(Handle *h);
void fn_80393698(Ent &actor, Handle *h);
int fn_80067050(Ent &actor, Vector *v);
}

extern "C" void fn_800D5514(register void *self)
{
    Handle *h = fn_80393A60(*Entity_GetActor(self), fn_800ACD20(*Entity_GetActor(self), 0xA8), 0);
    if (h) {
        if (fn_8039D3C0(h))
            fn_80393698(*Entity_GetActor(self), h);
        h->s20();
        h->s44();
        Vector v;
        if (fn_80067050(*Entity_GetActor(self), &v))
            h->s22(&v);
    }
}
