// Steers the entity's PLAYER effect handle and settles its drift value (tuning fields 0x27, 0x28, 0x2A, 0x40); docs/versus.md row 20.

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
    virtual void s17(float a, float b);
};

struct Obj {
    char pad0[0xDC];
    float fDC;
    char padE0[0x3A0 - 0xE0];
    Handle *h; // +0x3A0
    char pad3A4[0x534 - 0x3A4];
    void *p534;
    char pad538[0x950 - 0x538];
    float f950;
};

extern char lbl_80593BE8[];

extern "C" {
PEnt *Entity_GetActor(void *self);
float fn_800B1884(Ent &actor, int id);
void *fn_800B1724(Ent &actor);
int fn_80085300(void *actor, void *node, float a, float b, float *out);
int fn_800CC60C(void *self);
void *fn_80085980(void *actor);
void *fn_804420AC(void *p);
void fn_8014BB4C(void *p, Vector *v);
void fn_80067050(Ent &actor, Vector *v);
int fn_800CC148(void *self, int id);
int fn_80133630();
Handle *fn_80393B28(Ent &actor, Handle *h);
void fn_80114D70(void *p, int v);
int fn_800664C0(Ent &actor);
float fn_80426A84(void *p);
float fn_800D9308(float a, float b, float c);
void fn_80065CB0(Ent &actor, Vector *v);
}

extern "C" int fn_800D80B4(register Obj *self)
{
    Vector v8;
    float f18 = 0.5f;
    Vector v20;
    float f30 = 0.0f;
    float f34 = -fn_800B1884(*Entity_GetActor(self), 0x28);
    float f38 = fn_800B1884(*Entity_GetActor(self), 0x27);
    float f3C = fn_800B1884(*Entity_GetActor(self), 0x2A);
    float f40;
    int f44 = fn_80085300(Entity_GetActor(self), fn_800B1724(*Entity_GetActor(self)), 0.7f, 10.0f, &f40);
    if (f44) {
        self->f950 = f40;
    } else {
        if (fn_800CC60C(self)) {
            Vector v48;
            fn_8014BB4C(fn_804420AC(fn_80085980(Entity_GetActor(self))), &v48);
        }
        self->f950 = -1.0f;
    }
    fn_80067050(*Entity_GetActor(self), &v20);
    float f58 = 0.0f;
    if (fn_800CC148(self, 9) || (fn_800CC60C(self) && fn_80133630())) {
        if (fn_800CC148(self, 0x10)) {
            f30 = f38;
            f58 = 1.0f;
        } else {
            f30 = 0.0f;
            f58 = 0.5f;
        }
    } else {
        f30 = f34;
        f58 = 0.0f;
    }
    self->h = fn_80393B28(*Entity_GetActor(self), self->h);
    if (self->h) {
        self->h->s17(f58, -1.0f);
        fn_80114D70(self->p534, (int)(f58 * 1000.0f));
    }
    if (fn_800664C0(*Entity_GetActor(self)))
        f30 = 0.0f;
    self->fDC = fn_800D9308(self->fDC, f30, fn_80426A84(lbl_80593BE8) * fn_800B1884(*Entity_GetActor(self), 0x40));
    self->fDC = self->fDC >= -4.0f ? (self->fDC <= 16.0f ? self->fDC : 16.0f) : -4.0f;
    v20.z = self->fDC;
    if (!fn_800664C0(*Entity_GetActor(self)))
        fn_80065CB0(*Entity_GetActor(self), &v20);
    return 0;
}
