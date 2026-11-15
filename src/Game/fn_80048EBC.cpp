// fn_80048EBC moves a Havok collision object (fn_80322470) to a point and runs the collision query fn_80049474 there.

class Vector4
{
public:
    float v[4];
    Vector4(void *v) __asm__("fn_804362D4"); // (x, y, z, 0)
} __attribute__((aligned(8)));

inline int sn_return_decl(int a) { return a; }

class Vector
{
public:
    float v[4];
    Vector();
    Vector(const Vector &v) __asm__("fn_80436370");
    void zero() __asm__("fn_804363B8");
    void scale(float s) __asm__("fn_80436454");
    void addScaled(float s, const Vector *v) __asm__("fn_804364BC");
    float dot(const void *v) __asm__("fn_80436548");
    float length() __asm__("fn_804365A0");
    void normalize() __asm__("fn_80436610");
    void set(const void *v) __asm__("fn_80434BA4");
} __attribute__((aligned(8)));

class Point
{
public:
    float v[4];
    Point() __asm__("fn_80434988");
    void sub(const void *a, const void *b) __asm__("fn_804349B0");
    float length() __asm__("fn_804365A0");
} __attribute__((aligned(8)));

struct Flag { // returned by value
    signed char v;
    bool test() __asm__("fn_80436294");
};

struct Kind {
    virtual void s0();
    virtual void s1();
    virtual int kind();
};

struct Ent {
    Flag flag() __asm__("fn_80317960");
};

struct Filter {
    virtual Flag accept(void *sub, void *id);
};

struct Base8 {
    int a;
    int b;
};

struct Mgr : Base8, Filter {
};

struct Hit {
    char pad[0x20];
    void *a; // +0x20
    void *b; // +0x24
};

struct Body;

class Shape
{
public:
    float x;          // +0x0, distance of the nearest accepted hit
    const void *vptr; // +0x4
    unsigned int flags; // +0x8
    void *ignore0;    // +0xC
    void *ignore1;    // +0x10
    void *sink;       // +0x14
    char pad18[8];
    Vector v20;       // +0x20
    Vector v30;       // +0x30
    int blocked;      // +0x40
    char pad44[0xC];
    Vector v50;       // +0x50, summed push-out
    int count;        // +0x60

    void reset(float tol);
    void addHit(Hit *hit);
};

struct Body {
    Flag flag() __asm__("fn_8032A230");
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
    virtual void query(Shape *c);
};

extern "C" {
int fn_80436964(void);
void fn_80322470(void *body, const Vector4 &pos, float t);
int fn_80049474(Body *body, unsigned int flags, void *a, void *b, float tol, void *sink);
void fn_80436E44(void *self);
float fn_80436F10(void *self);
void *fn_80436684(void *hit);
void *fn_804366AC(void *hit);
float fn_804366D8(void *hit);
void *fn_80436754(void *p);
char *fn_804367A8(void *p);
int fn_804367D8(void *p);
Kind *fn_80317940(void *ent);
int fn_8006BCDC(void *ent);
void *fn_80436900(void *ent);
int fn_800B0CC0(void *p);
void *fn_8032A228(void *actor);
void fn_80437300(void *sink, void *id, Vector *a, Vector *b, float d);
void fn_80327378(void *world, Body *body);
void fn_80327934(void *world, Body *body);
}

extern Mgr *lbl_8066B83C;
extern void *lbl_8066B834;
extern unsigned int lbl_8066B85C;
extern Shape lbl_8053F8F0;

extern "C" int fn_80048EBC(void *body, void *pos, int a, int b, int c, float f, int d)
{
    if (fn_80436964())
        return 0;
    fn_80322470(body, Vector4(pos), 0.0f);
    return fn_80049474((Body *)body, a, (void *)b, (void *)c, f, (void *)d);
}

void Shape::reset(float tol)
{
    fn_80436E44(this);
    x = tol;
    blocked = 0;
    count = 0;
    v50.zero();
}

void Shape::addHit(Hit *hit)
{
    void *obj;
    Ent *ent;

    if (fn_804366D8(hit) > x)
        return;
    obj = fn_804367D8(fn_80436754(hit->a)) == 2 ? hit->b : hit->a;
    if (fn_804367D8(fn_80436754(obj)) == 2)
        return;
    ent = (Ent *)fn_804367A8(fn_80436754(obj));
    if (ent == ignore0 || ent == ignore1)
        return;
    if (flags & 1) {
        register int skip = !ent->flag().test() && fn_80317940(ent)->kind() != 6;
        if (skip)
            return;
        if (fn_8006BCDC(ent))
            return;
    }
    if (flags & 2) {
        void *u = fn_80436900(ent);
        if (!(u && fn_800B0CC0(u)))
            return;
    }
    if (ignore1) {
        if (!lbl_8066B83C->accept(fn_8032A228(ignore1), fn_80436754(obj)).test())
            return;
    }
    if (flags & 0x80000000) {
        Vector n(*(Vector *)fn_804366AC(hit));
        float d = -fn_804366D8(hit);
        float p = n.dot(fn_80436684(hit));
        if (n.dot(&v20) < p) {
            n.scale(-1.0f);
            Point t;
            t.sub(fn_80436684(hit), &v30);
            d = t.length();
            d = d + 0.2f;
        }
        if (count) {
            Vector m(v50);
            m.normalize();
            if (n.dot(&m) < -0.2f) {
                blocked = 1;
                x = -3.4028235e38f;
                return;
            }
        }
        v50.addScaled(d, &n);
        count++;
        return;
    }
    x = -3.4028235e38f;
    if (sink) {
        Vector a;
        Vector b;
        a.set(fn_80436684(hit));
        b.set(fn_804366AC(hit));
        fn_80437300(sink, fn_80436754(obj), &a, &b, fn_804366D8(hit));
    }
}

extern "C" int fn_80049474(Body *body, unsigned int flags, void *a, void *b, float tol, void *sink)
{
    if (fn_80436964())
        return 0;
    if (!body->flag().test())
        fn_80327378(lbl_8066B834, body);
    lbl_8053F8F0.flags = flags;
    lbl_8053F8F0.ignore0 = a;
    lbl_8053F8F0.ignore1 = b;
    lbl_8053F8F0.sink = sink;
    if (flags & 4)
        lbl_8066B85C |= 1;
    lbl_8053F8F0.reset(tol);
    body->query(&lbl_8053F8F0);
    lbl_8066B85C &= ~1;
    fn_80327934(lbl_8066B834, body);
    return fn_80436F10(&lbl_8053F8F0) == -3.4028235e38f;
}
