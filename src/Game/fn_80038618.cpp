// Turns +0x1C4 toward the heading of +0xC0 (GLOBALS 0x36 to 0x38); docs/versus.md row 21.

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
    char padD0[0x110 - 0xD0];
    int i110; // +0x110
    char pad114[0x180 - 0x114];
    char v180[0x190 - 0x180]; // +0x180
    float f190; // +0x190
    char pad194[0x1C4 - 0x194];
    float f1C4; // +0x1C4
    char pad1C8[0x210 - 0x1C8];
    float f210; // +0x210
};

extern "C" {
float fn_80433D20(void *record, int id, int slot);
int fn_80433D70(void *record, int id, int slot);
float *fn_8042FB28(void *p);
float fn_801BDE20(float a, float b);
float fn_801BDA3C(float a);
void fn_8042DC84(Vector *dst, void *src);
void fn_8042F76C(Vector *v);
float fn_8042FE6C(Vector *v);
int fn_8003932C(Obj *self, int a, int b);
int fn_800383D8(Obj *self, int b, float heading, float step, float *out);
extern void *lbl_8066C6C8; // the GLOBALS record
}

#define ABS(x) ((x) < 0.0f ? -(x) : (x))

extern "C" void fn_80038618(register Obj *self, int a, int b, unsigned int *flags)
{
    float x;
    float y;

    if (self->i110 == 0)
        return;
    if (*flags & 0x800000) {
        x = fn_80433D20(lbl_8066C6C8, 0x36, 0) * (1.0f / 30.0f) * 3.0f;
        y = fn_801BDE20(fn_8042FB28(self->v180)[2], self->f1C4);
        if (y > x)
            return;
    }
    if (fn_8003932C(self, a, b) == 2) {
        Vector v;
        fn_8042DC84(&v, &self->vC0);
        v.z = 0.0f;
        fn_8042F76C(&v);
        y = fn_8042FE6C(&v) + self->f190 + self->f210;
        float diff = fn_801BDE20(fn_8042FB28(self->v180)[2], y);
        float step;
        if (*flags & 0x800000) {
            float d = fn_801BDE20(fn_8042FB28(self->v180)[2], self->f1C4);
            step = d > 0.0f ? fn_80433D20(lbl_8066C6C8, 0x37, 0) : -fn_80433D20(lbl_8066C6C8, 0x37, 0);
        } else
            step = diff > 0.0f ? fn_80433D20(lbl_8066C6C8, 0x37, 0) : -fn_80433D20(lbl_8066C6C8, 0x37, 0);
        if (fn_800383D8(self, b, fn_8042FB28(self->v180)[2], step, &x)
            || fn_800383D8(self, b, fn_8042FB28(self->v180)[2], -step, &x))
            self->f1C4 = x;
        else if (ABS(diff) > fn_80433D20(lbl_8066C6C8, 0x37, 0) * fn_80433D70(lbl_8066C6C8, 0x38, 0))
            self->f1C4 = y;
        else
            self->f1C4 = fn_801BDA3C(y + 160.0f);
        *flags |= 0x800000;
    }
}
