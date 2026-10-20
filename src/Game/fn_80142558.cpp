// A handler that spawns an effect when no actor is closer than PLAYER field 210 (guess).

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

struct PEnt : Ent { // matching_notes 44
    int x;
};

extern "C" {
Ent *fn_80134870(void *a);
PEnt *fn_80442080(void *a);
void *fn_800B1724(Ent &node);
float fn_800B1884(Ent &actor, int id);
float fn_804290F8(void *a, void *b);
int fn_80151D64(void *a, Vector *out, float *f);
int fn_80138738(int a, int b, int c);
void fn_80138AE0(int h, int a, Vector *v, float f);
}

extern "C" int fn_80142558(void *self, int unused)
{
    if (fn_80134870(self)) {
        if (fn_804290F8(fn_800B1724(*fn_80442080(self)), fn_800B1724(*fn_80134870(self))) <= fn_800B1884(*fn_80442080(self), 210))
            return 0;
    }
    Vector v;
    float f;
    if (fn_80151D64(self, &v, &f)) {
        int h = fn_80138738(26, 250, 10);
        if (!h)
            return 0;
        fn_80138AE0(h, 0, &v, f);
        return h;
    }
    return 0;
}
