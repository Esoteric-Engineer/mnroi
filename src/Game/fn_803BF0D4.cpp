// Constraint: the point at t along the line.

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

struct Constraint {
    char pad0[0x20];
    Vector pos;   // +0x20
    char pad30[0xE0];
    Vector end;   // +0x110
    char pad120[0x54];
    int f174;     // +0x174
    char pad178[0x118];
    Vector f290;  // +0x290
};

extern "C" {
int fn_803CCFD4(Constraint *self);
void fn_804304FC(Vector *out, Vector *a, Vector *b, float t);
int fn_803BAE8C(Constraint *self, Vector *out, float t);

int fn_803BF0D4(register Constraint *self, Vector *out, float t)
{
    if (!out)
        return 0;
    if (fn_803CCFD4(self)) {
        fn_804304FC(out, &self->pos, &self->end, t);
        return 1;
    }
    if (self->f174)
        return fn_803BAE8C(self, out, t);
    fn_804304FC(out, &self->pos, &self->f290, t);
    return 1;
}
}
