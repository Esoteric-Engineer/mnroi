// Aim vector from an actor to a target, offset by a PLAYER distance (fields 209/211); docs/versus.md row 20.

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

struct Sub : Ent { // matching_notes 44
    int x;
};

extern "C" {
Vector *fn_800B1724(Ent &actor);
void fn_8042DC84(Vector *dst, Vector *src);
void fn_8042D8A8(Vector *dst, Vector *src);
void fn_8042F76C(Vector *v);
void fn_8042FE08(Vector *v, Vector *dir, float s);
void fn_80433FFC(Vector *v);
float fn_800B2670(Ent &actor);
float fn_800B1884(Ent &actor, int id);
int fn_800B0C1C(Ent &c);
int fn_800B0C58(Ent &c);
Sub *fn_800B14C8(Ent &c);
int fn_80095608(Ent &a);
int fn_80085D3C(Ent &a);
void *fn_80085980(Ent &a);
Ent *fn_80134870(void *a);
int fn_801332C0(Ent &a);
void fn_80149270(void *a, float f, Vector *v);
Sub *fn_80085954(Ent &a);
int fn_800CCA58(Ent &a);
int fn_800CCAE8(Ent &a);
}

extern "C" void fn_8014A574(Ent &self, Ent &target, Vector *out)
{
    Vector a;
    Vector b;
    float d;

    fn_8042DC84(&b, fn_800B1724(self));
    fn_8042D8A8(&b, fn_800B1724(target));
    b.z = 0.0f;
    fn_8042F76C(&b);
    d = fn_800B2670(self) + fn_800B2670(target);
    if (fn_800B0C1C(target) && fn_80095608(*fn_800B14C8(target)) && !fn_80085D3C(self))
        d = fn_800B1884(self, 211);
    else
        d = fn_800B1884(self, 209);
    fn_8042DC84(&a, fn_800B1724(target));
    fn_8042FE08(&a, &b, d);
    if (!fn_800B0C58(target)) {
        if (fn_80134870(fn_80085980(self))) {
            fn_8042DC84(&b, fn_800B1724(*fn_80134870(fn_80085980(self))));
            fn_8042D8A8(&b, fn_800B1724(target));
            fn_8042F76C(&b);
            fn_80433FFC(&b);
            fn_8042DC84(&a, fn_800B1724(target));
            fn_8042FE08(&a, &b, d);
        }
    } else {
        int t = fn_801332C0(self);
        if (t)
            fn_80149270(fn_80085980(self), d, &a);
        if (fn_800CCA58(*fn_80085954(self)) || fn_800CCAE8(*fn_80085954(self)))
            a.z = fn_800B1724(target)->z;
    }
    fn_8042DC84(out, &a);
}
