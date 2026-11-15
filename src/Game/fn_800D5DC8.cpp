// A wire state's event handler (tuning field 168, the wire effect). Owns .rodata 0x8048D1F4-0x8048D1FC.
// Event 0x23 puts the wire's end 10 ahead of the actor and 3 up, 0x24 restarts the wire effect, 0x14 switches to state 6, 0x2C/0x2D set and clear bit 0 of the flags, and 0x5A sets bit 2.

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
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(Vector *pos, int z); // +0xE8
};

struct EObj {
    char pad0[0x10];
    unsigned int f10;
    char pad14[0x3AC - 0x14];
};

struct Obj : EObj {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(int state); // +0x30
};

extern "C" {
PEnt *Entity_GetActor(void *self);
int fn_800ACD20(Ent &actor, int id);
Handle *fn_80393D0C(Ent &actor, int id, int a, int b);
Vector *fn_800B1724(Ent &actor);
Vector *fn_800B1750(Ent &actor);
void fn_8042DC84(Vector *dst, Vector *src);
void fn_8042FE08(Vector *out, Vector *dir, float t);
void fn_800D5514(void *self);
}

extern "C" int fn_800D5DC8(register Obj *self, int unused, int type, int value, int extra)
{
    switch (type) {
    case 0x5A:
        self->f10 |= 4;
        break;
    case 0x14:
        self->s5(6);
        break;
    case 0x2C:
        self->f10 |= 1;
        break;
    case 0x2D:
        self->f10 &= ~1;
        break;
    case 0x23: {
        Handle *f18 = fn_80393D0C(*Entity_GetActor(self), fn_800ACD20(*Entity_GetActor(self), 0xA8), 0x15, 1);
        Vector v20;
        fn_8042DC84(&v20, fn_800B1724(*Entity_GetActor(self)));
        fn_8042FE08(&v20, fn_800B1750(*Entity_GetActor(self)), 10.0f);
        v20.z += 3.0f;
        if (f18)
            f18->s28(&v20, 0);
        break;
    }
    case 0x24:
        fn_800D5514(self);
        break;
    default:
        return 0;
    }
    return 1;
}
