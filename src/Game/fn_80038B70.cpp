// Probes heading, +90, -90 and +180 at GLOBALS 0x18 until fn_80038A2C passes.

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

struct Obj {
    char pad0[0xC0];
    Vector vC0; // +0xC0
    char padD0[0x120 - 0xD0];
    Vector v120; // +0x120
    char pad130[0x180 - 0x130];
    char v180[0x190 - 0x180]; // +0x180
    float f190; // +0x190
    float f194; // +0x194
};

extern "C" {
float fn_80433D20(void *record, int id, int slot);
float *fn_8042FB28(void *p);
float fn_8042FE6C(Vector *v);
void fn_8042FDBC(Vector *out, Vector *v, float f);
float fn_804351AC(Obj *self);
float fn_8043517C(Obj *self);
int fn_80038A2C(Obj *self, int a, int b);
extern void *lbl_8066C6C8; // the GLOBALS record
extern float lbl_8066D5C0;
}

extern "C" void fn_80038B70(register Obj *self, int a, int b, int flags)
{
    float heading;

    if (fn_80038A2C(self, a, b))
        return;
    fn_8042FB28(self->v180)[1] = 0.0f;
    if (flags & 0x20000)
        heading = fn_804351AC(self);
    else
        heading = fn_8042FE6C(&self->vC0) + self->f190;
    if (flags & 0x10000)
        fn_8042FB28(self->v180)[0] = fn_8043517C(self);
    else
        fn_8042FB28(self->v180)[0] = lbl_8066D5C0 + self->f194;
    fn_8042FDBC(&self->v120, &self->vC0, fn_80433D20(lbl_8066C6C8, 0x18, 0));
    fn_8042FB28(self->v180)[2] = heading;
    if (fn_80038A2C(self, a, b))
        return;
    fn_8042FB28(self->v180)[2] = heading + 90.0f;
    if (fn_80038A2C(self, a, b))
        return;
    fn_8042FB28(self->v180)[2] = heading - 90.0f;
    if (fn_80038A2C(self, a, b))
        return;
    fn_8042FB28(self->v180)[2] = heading + 180.0f;
    if (fn_80038A2C(self, a, b))
        return;
}
