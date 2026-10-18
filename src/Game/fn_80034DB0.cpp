// Eases +0x1C0 toward a 0..1 ratio (GLOBALS 0x30, rates 0x32/0x33) and pulls +0xB0 by GLOBALS 0x31; docs/versus.md row 21.

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

struct Actor {
    char pad0[0x198];
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual Vector *s6(); // vtable +0x38
};

struct Obj {
    char pad0[0xB0];
    Vector vB0; // +0xB0
    Vector vC0; // +0xC0
    char padD0[0x1C0 - 0xD0];
    float f1C0; // +0x1C0
    char pad1C4[0x1F4 - 0x1C4];
    Actor *p1F4; // +0x1F4
    char pad1F8[0x370 - 0x1F8];
    Vector v370; // +0x370
};

extern "C" {
float fn_80433D20(void *record, int id, int slot);
float fn_8042E998(char *globals);
Vector *fn_800B1750(Actor &actor);
void fn_8042DC84(Vector *dst, void *src);
void fn_80429038(Vector *out, Vector *a, Vector *b);
float fn_8042EC54(Vector *v);
void fn_80067050(Actor *actor, Vector *out);
float fn_8042EBF4(Vector *a, Vector *b);
void fn_8042A7D8(float deg, float *s, float *c);
void fn_80429090(Vector *out, Vector *a, Vector *b, float t);
extern void *lbl_8066C6C8;  // the GLOBALS record
extern char lbl_80593BE8[]; // the globals object of Game/fn_80443908.cpp
}

#define ABS(x) ((x) < 0.0f ? -(x) : (x))

extern "C" void fn_80034DB0(register Obj *self, int a, int b, int c)
{
    fn_8042DC84(&self->vC0, fn_800B1750(*self->p1F4));
    Vector v18;
    fn_8042DC84(&v18, self->p1F4->s6());
    Vector v28;
    fn_80429038(&v28, &self->vB0, &v18);
    float dist = fn_8042EC54(&v28);
    Vector v40;
    fn_80067050(self->p1F4, &v40);
    float d = fn_8042EBF4(&v40, &self->v370);
    float target = d / fn_80433D20(lbl_8066C6C8, 0x30, 0);
    target = target >= 0.0f ? (target <= 1.0f ? target : 1.0f) : 0.0f;
    float diff = target - self->f1C0;
    float step = diff > 0.0f ? fn_80433D20(lbl_8066C6C8, 0x32, 0) : -fn_80433D20(lbl_8066C6C8, 0x33, 0);
    step = step * fn_8042E998(lbl_80593BE8);
    if (ABS(diff) < ABS(step))
        self->f1C0 = target;
    else
        self->f1C0 = self->f1C0 + step;
    self->f1C0 = self->f1C0 >= 0.0f ? (self->f1C0 <= 1.0f ? self->f1C0 : 1.0f) : 0.0f;
    float s;
    float co;
    fn_8042A7D8(self->f1C0 * 90.0f, &s, &co);
    s = self->f1C0;
    s = s * fn_80433D20(lbl_8066C6C8, 0x31, 0);
    fn_80429090(&self->vB0, &v18, &v28, s);
}
