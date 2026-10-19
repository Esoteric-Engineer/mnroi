// Acts on the actor behind handle +0xD0 (virtual +0x130 with 0x5E, or 0x5F if its flags have 0x2000), adds GLOBALS field 6 to the entity's +0x324, then fn_800DDCB4(self, 0x4F or 0x50); docs/versus.md row 21.

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

struct Base {
    char pad0[0x10];
    unsigned int flags; // +0x10
    char pad14[0xD0 - 0x14];
    int hD0; // +0xD0
    char padD4[0x3AC - 0xD4];
    void m5A4(int v) __asm__("fn_800CD5A4");
    void m5EC(int v) __asm__("fn_800CD5EC");
    void m540() __asm__("fn_800CC540");
};

struct Obj : Base {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
    virtual void s36();
    virtual void s37(int id, int a, int b, float w, int c, int d, int e, int f); // vtable +0x130
};

extern char lbl_8064AA80[];
extern void *lbl_8066C6C8; // the GLOBALS record

extern "C" {
PEnt *Entity_GetActor(void *self);
PEnt &fn_800ACFA8(int handle);
void fn_803A0760(void *list, void *actor);
int fn_800B0C58(void *actor);
int fn_80085928(void *actor);
Obj *fn_80085954(void *actor);
float fn_80433D20(void *record, int id, int slot);
void fn_80086818(void *actor, float v);
void fn_800CC3A4(void *self);
void fn_8009AEC8(Ent &actor, int v);
void fn_800DDCB4(void *self, int a, int b);
Vector *fn_800B1724(Ent &actor);
Vector *fn_800B1750(Ent &actor);
void fn_80429090(Vector *out, Vector *a, Vector *b, float s);
void fn_800C7FF4(void *self, Vector *v, float s);
void fn_800C98BC(void *self, void *node, int v);
void fn_800CBE1C(void *self, void *node);
}

extern "C" void fn_800ECA34(register Base *self)
{
    PEnt &held = fn_800ACFA8(self->hD0);
    Vector v10;
    int f20 = 0;
    fn_803A0760(lbl_8064AA80, Entity_GetActor(self));
    if (&held && fn_800B0C58(&held) && fn_80085928(&held)) {
        if (fn_80085954(&held)->flags & 0x2000)
            f20 = 1;
        fn_80085954(&held)->m5A4(0);
        fn_80085954(&held)->m5EC(0);
        if (f20)
            fn_80085954(&held)->s37(0x5F, 0, 0, 1.0f, 0, 0, 0, 1);
        else
            fn_80085954(&held)->s37(0x5E, 0, 0, 1.0f, 0, 0, 0, 1);
        fn_80085954(&held)->m540();
    }
    fn_80086818(Entity_GetActor(self), fn_80433D20(lbl_8066C6C8, 6, 0));
    fn_800CC3A4(self);
    self->m540();
    fn_8009AEC8(*Entity_GetActor(self), 0);
    if (f20)
        fn_800DDCB4(self, 0x50, 0);
    else
        fn_800DDCB4(self, 0x4F, 0);
    fn_80429090(&v10, fn_800B1724(*Entity_GetActor(self)), fn_800B1750(*Entity_GetActor(self)), -1.0f);
    fn_800C7FF4(self, &v10, 0.2f);
    fn_800C98BC(self, &held, 1);
    fn_800CBE1C(self, &held);
}
