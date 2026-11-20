// Kind-3 class file: constructor, release, entity hooks, nearest-plane query, +0x240 flag accessors (docs/story.md row 14).
// Owns .rodata 0x8048B4E4-0x8048B508; the vtable lbl_804F5080 stays dtk's.

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));


struct Buf {
    char pad0[0x8];
    void *f8; // +0x8
};

struct Kind3 {
    char data[0x240];
    unsigned int f240; // +0x240
    int f244; // +0x244
    char r248[0x40]; // +0x248, built by fn_8042D7B0
    Buf *f288; // +0x288
};

struct Ent {
    char pad0[0x2C];
    unsigned int flags; // +0x2C
    char pad30[0xEC];
    unsigned int f11C; // +0x11C
};

struct Plane {
    float x; // +0x0
    float y; // +0x4
    float z; // +0x8
    float d; // +0xC
};

struct Planes {
    char pad0[0xB];
    unsigned char count; // +0xB
    char padC[0x78];
    Plane *planes; // +0x84
};

struct Model {
    Planes *f0; // +0x0
};

extern "C" {
extern char lbl_804F5080[];
void *Actor_ctor(void *self) __asm__("__5Actor");
extern char lbl_8064AA80[];
void fn_8042D7B0(void *self);
void fn_801ACC0C(void *p);
void fn_80097614(void *self);
void *fn_800531AC();
int fn_80430024(void *mgr);
int fn_800B0C58(void *e);
void *fn_800B14A0(void *e);
int fn_80085F1C(void *p);
void fn_8007E2FC(void *self, void *other);
void fn_8007E430(void *self, void *other);
int fn_800A4D08(Kind3 *self);
int fn_800A4D68(Kind3 *self);
int fn_800A4DC8(Kind3 *self);
void fn_8039DC9C(char *tbl, void *e, void *self);
void fn_8039DEA8(char *tbl, void *e, void *self);
int fn_8010CDCC(void *self, int event, void *target, int a3, int a4, int a5, int a6);
int fn_800B0C1C(void *e);
void *fn_800B14C8(void *e);
int fn_80085AF0(void *p);
void *fn_80085B1C(void *p);
void fn_804450F8(void *p, void *self);
void *fn_80085928(void *p);
int fn_800CD85C(void *p);
void *fn_800CD834(void *p);
void fn_800CE1DC(void *p, int a);
Model *fn_8009AD80(void *self);
void *fn_800B1724(void *e);
void fn_8042DA10(Vector *out, void *a, void *b);
void fn_8042FDBC(Vector *out, Plane *p, float f);
void fn_8042DC84(Vector *dst, Plane *src);
void *fn_800B1668(void *self);
void fn_80435754(Vector *v, void *m);
}

extern "C" Kind3 *fn_800A473C(register Kind3 *self)
{
    Actor_ctor(self);
    *(void **)(self->data + 0x198) = lbl_804F5080;
    fn_8042D7B0(self->r248);
    self->data[0] = 3;
    self->f288 = 0;
    self->f240 = 0;
    self->f244 = -1;
    return self;
}

extern "C" void fn_800A47B4(register Kind3 *self)
{
    if (self->f288) {
        if (self->f288->f8) {
            fn_801ACC0C(self->f288->f8);
        }
        fn_801ACC0C(self->f288);
    }
    fn_80097614(self);
}

extern "C" void fn_800A481C(register Kind3 *self, Ent *e, int bits)
{
    e->f11C = e->f11C | bits;
    if (!(e->flags & 0x1000) && !fn_80430024(fn_800531AC()) && (!fn_800B0C58(e) || !fn_80085F1C(fn_800B14A0(e)))) {
        fn_8007E2FC(self, e);
    }
    if (fn_800A4D08(self)) {
        fn_8039DC9C(lbl_8064AA80, e, self);
    }
    if (fn_800A4D68(self)) {
        fn_8010CDCC(self, 1, 0, 0, 0, 0, 0);
    }
}

extern "C" void fn_800A493C(register Kind3 *self, Ent *e, int bits)
{
    e->f11C = e->f11C & ~bits;
    if (!(e->flags & 0x1000) && !fn_80430024(fn_800531AC())) {
        fn_8007E430(self, e);
    }
    if (fn_800A4D08(self)) {
        fn_8039DEA8(lbl_8064AA80, e, self);
    }
    if (fn_800A4D68(self)) {
        fn_8010CDCC(self, 2, 0, 0, 0, 0, 0);
    }
    if (fn_800B0C1C(e)) {
        if (self->f288 && fn_80085AF0(fn_800B14C8(e))) {
            fn_804450F8(fn_80085B1C(fn_800B14C8(e)), self);
        }
        if (fn_800A4DC8(self) && fn_80085928(fn_800B14C8(e)) && fn_800CD85C(fn_80085928(fn_800B14C8(e)))) {
            fn_800CE1DC(fn_800CD834(fn_80085928(fn_800B14C8(e))), 0);
        }
    }
}

extern "C" int fn_800A4B1C(register Kind3 *self, void *e, Vector *out)
{
    if (self->f240 & 1) {
        return 0;
    }
    Planes *m = fn_8009AD80(self)->f0;
    Vector v;
    fn_8042DA10(&v, fn_800B1724(e), self->r248);
    Plane *p = m->planes;
    Plane *best = 0;
    float bestDist = 1000000.0f;
    for (unsigned int i = 0; i < m->count; i++, p++) {
        Vector w;
        fn_8042FDBC(&w, p, p->d);
        float dist = p->x * (v.x - w.x) + p->y * (v.y - w.y) + p->z * (v.z - w.z);
        dist = dist < 0.0f ? -dist : dist;
        if (dist < bestDist) {
            best = p;
            bestDist = dist;
        }
    }
    if (!best) {
        return 0;
    }
    fn_8042DC84(out, best);
    fn_80435754(out, fn_800B1668(self));
    return 1;
}

extern "C" int fn_800A4D08(register Kind3 *self)
{
    return self->f240 & 8;
}

extern "C" int fn_800A4D38(register Kind3 *self)
{
    return self->f240 & 4;
}

extern "C" int fn_800A4D68(register Kind3 *self)
{
    return self->f240 & 0x10;
}

extern "C" int fn_800A4D98(register Kind3 *self)
{
    return self->f240 & 0x80;
}

extern "C" int fn_800A4DC8(register Kind3 *self)
{
    return self->f240 & 0x400;
}

__asm__(".section .rodata\n\t.float 1.0\n\t.float 0.0\n\t.float 1.0\n\t.float 1.0\n\t.float 0.5\n\t.float 1.5\n\t.float 0.0\n\t.text"); // 0x8048B4EC-0x8048B508: header-tail words no code loads
