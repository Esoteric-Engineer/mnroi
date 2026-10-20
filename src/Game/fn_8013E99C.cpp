// A PLAYER state's effect spawn toward the target, gated by a clear path and PLAYER field 200.
// Owns .rodata 0x8049AEA0-0x8049AEB0 (1.0f, 0.0f, 0.5f, 0.08f).

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

class Placement {
public:
    char d[0x40];
    Placement();
};

struct Ent {
    int pad;
};

struct PEnt : Ent { // matching_notes 44
    int x;
};

struct Target {
    char pad0[0x50];
    float minX; // +0x50 (guess: bounds)
    float minY; // +0x54
    char pad58[0x8];
    float maxX; // +0x60
    float maxY; // +0x64
    char pad68[0x130];
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5(Vector *out, int a); // vtable +0x30
};

struct TSub : Target {
    int pad;
};

struct Actor {
    char pad0[0x308];
    unsigned int flags; // +0x308
};

#define ABS(x) ((x) < 0.0f ? -(x) : (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

extern "C" {
int fn_8015F384(void *a);
int fn_80461D48(void *a, int b);
int fn_8015E97C(float f);
int fn_8015F008(void *self);
int fn_80138738(int a, int b, int c);
void fn_80138A24(int h, int bit);
Target *fn_80134870(void *a);
PEnt *fn_80442080(void *a);
TSub *fn_80442080T(void *a) __asm__("fn_80442080");
Actor *fn_80442080A(void *a) __asm__("fn_80442080");
void *fn_800B1724(Ent &node);
Vector *fn_800B1750(Ent &actor);
void *fn_800B24AC(Ent &actor);
void *fn_800B1CC8(Ent &actor);
unsigned int fn_800B18EC(Ent &e, int id);
void fn_8042D8A8(Vector *dst, void *src);
float fn_8042EC54(Vector *v);
float fn_8042EBF4(Vector *a, Vector *b);
void fn_8042F76C(Vector *v);
int fn_8004A9CC(Vector *from, Vector *dir, float len, unsigned int mask, Placement *hit, void *a, void *b, int c, int d);
int fn_8015EEA0(void *self);
int fn_800862DC(void *a);
int fn_801369B0(void *self);
float fn_80461FC0(void *self);
int fn_8015EC1C(float f);
void fn_80138AE0(int h, int a, Vector *v, float f);
}

extern "C" int fn_8013E99C(void *self, int unused)
{
    if (!fn_8015F384(self) && !fn_80461D48(self, 0x35)) {
        if (fn_8015E97C(1.0f) && fn_8015F008(self) && !fn_80461D48(self, 5) && !fn_80461D48(self, 6)) {
            int e = fn_80138738(-1, 0, 0);
            if (e) {
                fn_80138A24(e, 0x13);
                return e;
            }
        }
        return 0;
    }
    Target *t = fn_80134870(self);
    if (!t)
        return 0;
    if (fn_80461D48(self, 0x29))
        return 0;
    Vector dir;
    t->s5(&dir, 0);
    fn_8042D8A8(&dir, fn_800B1724(*fn_80442080(self)));
    float len = fn_8042EC54(&dir);
    float facing = fn_8042EBF4(&dir, fn_800B1750(*fn_80442080(self)));
    float size = MAX(ABS(fn_80134870(self)->maxX - fn_80134870(self)->minX),
                     ABS(fn_80134870(self)->maxY - fn_80134870(self)->minY));
    len -= size;
    Vector from;
    fn_80442080T(self)->s5(&from, 0);
    if (facing > 0.5f) {
        Placement hit;
        int clear = !fn_8004A9CC(&from, &dir, len, 0x8000, &hit, fn_800B24AC(*fn_80442080(self)),
                                 fn_800B1CC8(*fn_80442080(self)), 0, 3);
        int color = 0xffff0000;
        if (clear)
            color = 0xff00ff00;
        if (clear) {
            int id = 200;
            int n = fn_800B18EC(*fn_80442080(self), 200);
            int h = fn_80138738(9, id, n);
            if (h) {
                if (fn_80442080A(self)->flags & 0x4000) {
                    fn_80138A24(h, 2);
                    fn_80138A24(h, 7);
                } else {
                    fn_80138A24(h, 1);
                    int a = fn_8015EEA0(self);
                    int b = fn_800862DC(fn_80442080(self));
                    if (fn_801369B0(self) && (b || (!b && !a)))
                        fn_80138A24(h, 7);
                    if (fn_801369B0(self) && fn_8015EC1C(fn_80461FC0(self)))
                        fn_80138A24(h, 0xd);
                }
                dir.z = 0.0f;
                fn_8042F76C(&dir);
                fn_80138AE0(h, 0, &dir, 0.08f);
            }
            return h;
        }
    }
    return 0;
}
