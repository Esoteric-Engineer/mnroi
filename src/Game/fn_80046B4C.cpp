// Plays one recorded node back onto its actor.

__asm__(".section .rodata\n\t.globl lbl_80486560\nlbl_80486560:\n\t.float 0\n\t.text");

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

struct Vec3 {
    float v[3];
};

struct Vec4 {
    float v[4];
};

struct Snap {
    int f0;           // +0x0
    int f4;           // +0x4
    float f8;         // +0x8
    int fC;           // +0xC
    float f10;        // +0x10
    int f14;          // +0x14
    int f18;          // +0x18
    float f1C;        // +0x1C
    int f20;          // +0x20
    float f24;        // +0x24
    int f28;          // +0x28
    float f2C;        // +0x2C
    float f30;        // +0x30
    float f34;        // +0x34
    int f38;          // +0x38
    unsigned int f3C; // +0x3C
    int f40;          // +0x40
    char pad44[0x4];
    float f48;        // +0x48
    int f4C;          // +0x4C
};

struct Hit {
    float f0; // +0x0
    int f4;   // +0x4
    int f8;   // +0x8
    int fC;   // +0xC
};

union Word {
    float f;
    int i;
};

struct Evt {
    int a;  // +0x0
    Word b; // +0x4
    Word c; // +0x8
    Word d; // +0xC
    int e;  // +0x10
};

struct Emit {
    int id;    // +0x0
    float f;   // +0x4
    int has1;  // +0x8
    Vec3 v1;   // +0xC
    int has2;  // +0x18
    Vec3 v2;   // +0x1C
    Vec4 q;    // +0x28
};

struct Node {
    int time;           // +0x0
    int dur;            // +0x4
    unsigned int flags; // +0x8
    int fC;             // +0xC
    Vec4 v10;           // +0x10
    Vec4 v20;           // +0x20
    char pad30[0x10];
    Vec4 v40;           // +0x40
    Vec4 v50;           // +0x50
    Vec4 v60;           // +0x60
    union {
        Snap snap;
        Hit hit;
        Evt evt;
        Emit emit;
        Vec4 v70;
    };                  // +0x70
};

struct Rec {
    int handle;         // +0x0
    char pad4[0x4];
    unsigned int until; // +0x8
    unsigned int flags; // +0xC
    char pad10[0x10];
    Vec4 pos;           // +0x20
    float radius;       // +0x30
};

struct Clock {
    char pad0[0xC];
    int offset;         // +0xC
};

struct Ctl {
    char d[0x3AC];
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5(int state); // +0x30
};

struct Fx {
    char d[0x10];
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5(Vec4 *v, int a, int b); // +0x30
};

struct Clip {
    char pad0[0x28];
    float length;       // +0x28
};

struct Anim {
    char pad0[0x14];
    int f14;            // +0x14
    int f18;            // +0x18
    int f1C;            // +0x1C
    char pad20[0xC];
    char ch2[0x14];     // +0x2C
    int f40;            // +0x40
    int f44;            // +0x44
    Clip *f48;          // +0x48
    char pad4C[0xC];
    char ch3[0x8];      // +0x58
    float f60;          // +0x60
    char pad64[0x8];
    int f6C;            // +0x6C
    char pad70[0x4];
    int f74;            // +0x74
};

struct Actor {
    char pad0[0x2C];
    unsigned int f2C;   // +0x2C
    int f30;            // +0x30
    char pad34[0x31C - 0x34];
    float f31C;         // +0x31C
};

struct Body {
    char pad0[0x298];
    float f298;         // +0x298
};

extern char lbl_8064AA80[];
extern int lbl_8066B794;
extern Clock *lbl_8066B798;

extern "C" {
void fn_80046A2C(Node *node, Rec *rec);
int fn_800B0CC0(int actor);
Body *fn_800B1478(int actor);
void fn_800A2B3C(Body *b, int a, int c, int d, int e);
int fn_800ACFA8(int handle);
void fn_800A3588(Body *b, int other, float f, void *a, void *v, float g);
int fn_800B1138(int actor);
void fn_800B01C8(int actor, int a);
void fn_80075774(int actor, Vec4 *v);
void fn_80065F28(int actor, Vec4 *v);
void fn_8039F4D8(char *tbl, int a, int n, Vec4 *d, void *e, int one, float f1, float f2, int z1, int z2, float f3);
int fn_800B0C58(int actor);
Actor *fn_800B14A0(int actor);
void fn_80066A48(Actor *a, int b);
void fn_8006683C(Actor *a, int b);
void fn_804354B8(void *dst, void *src);
int fn_80041864(Actor *a, int b, int c);
void fn_804306D8(Vec4 *out, void *in);
void fn_80070228(Actor *a, int b, float f, void *c, void *d, Vec4 *q);
int fn_80085EBC(Actor *a);
Fx *fn_800707CC(Actor *a);
int fn_800B0C1C(int actor);
int fn_800B0F0C(int actor);
int fn_800B1CC8(int actor);
void fn_8005A9B8(int actor, Vec4 *v);
void fn_80065CB0(int actor, Vec4 *v);
void fn_80065D60(int actor, Vec4 *v);
void fn_80042158(Node *node, int handle);
Ctl *fn_80085954(Actor *a);
int fn_8009AE00(Actor *a);
Anim *fn_8009AF80(Actor *a);
void fn_8019DB24(void *ch, float time);
void fn_80435578(void *ch, float rate);
Clip *fn_804355C0(void *ch);
void fn_800BD2D0(Ctl *c, int ms);
void fn_8019BA58(Anim *a, int force, int root, int noTargets);
void fn_8019C408(Anim *a);
void fn_800CD70C(Ctl *c, unsigned int on);
void fn_80048274(int actor, unsigned int color, float f, int a);

void fn_80046B4C(int actor, Node *node, Rec *rec, int kind)
{
    if (node->flags & 0x40) {
        fn_80046A2C(node, rec);
    } else if ((node->flags & 4) && fn_800B0CC0(actor)) {
        Body *b = fn_800B1478(actor);
        Hit &h = node->hit;
        b->f298 = h.f0;
        fn_800A2B3C(b, h.f4, h.f8, h.fC, 0);
    } else if ((node->flags & 0x200) && fn_800B0CC0(actor)) {
        Body *b = fn_800B1478(actor);
        int other = fn_800ACFA8(node->evt.a);
        void *a = 0;
        if (node->evt.d.i)
            a = &node->v10;
        void *v = 0;
        if (node->evt.e)
            v = &node->v20;
        if (other)
            fn_800A3588(b, other, node->evt.b.f, a, v, node->evt.c.f);
    } else if (node->flags & 0x100) {
        if ((node->flags & 0x20) && (kind & 0x10)) {
            if (fn_800B1138(actor))
                fn_800B01C8(actor, 1);
            fn_80075774(actor, &node->v10);
            fn_80065F28(actor, &node->v10);
            ((Actor *)actor)->f2C &= ~0x01000000;
        } else {
        }
    } else if (node->flags & 0x80) {
        void *v = 0;
        if (node->evt.d.i)
            v = &node->v10;
        fn_8039F4D8(lbl_8064AA80, node->evt.a, fn_800ACFA8(node->evt.c.i), &node->v40, v, node->evt.b.i, 0.0f, -99999.0f, 0, 0, 0.0f);
    } else if (node->flags & 0x400) {
        int a = fn_800ACFA8(node->evt.a);
        int b = fn_800ACFA8(node->evt.b.i);
        if (a && fn_800B0C58(a) && b) {
            Actor *c = fn_800B14A0(a);
            if (node->evt.c.i)
                fn_80066A48(c, b);
            else
                fn_8006683C(c, b);
        }
    } else if ((node->flags & 0x1000) && fn_800B0C58(actor)) {
        Actor *a = fn_800B14A0(actor);
        int b = fn_800ACFA8(node->emit.id);
        Vector v1;
        Vector v2;
        void *p1 = 0;
        void *p2 = 0;
        if (node->emit.has1) {
            fn_804354B8(&v1, &node->emit.v1);
            p1 = &v1;
        }
        if (node->emit.has2) {
            fn_804354B8(&v2, &node->emit.v2);
            p2 = &v2;
        }
        if (fn_80041864(a, 0, 1)) {
            Vec4 q;
            fn_804306D8(&q, &node->emit.q);
            fn_80070228(a, b, node->emit.f, p1, p2, &q);
        }
    } else if ((node->flags & 0x2000) && fn_800B0C58(actor)) {
        Actor *a = fn_800B14A0(actor);
        if (a && fn_80085EBC(a)) {
            Fx *fx = fn_800707CC(a);
            if (fx) {
                Vec4 v;
                fn_804306D8(&v, &node->v70);
                fx->s5(&v, 1, 0);
            }
        }
    } else if ((node->flags & 0x8000) && fn_800B0C1C(actor)) {
        rec->flags |= 0x80;
        fn_804354B8(&rec->pos, &node->v70);
        rec->radius = node->evt.d.f;
    } else {
        rec->flags &= ~0x80;
        if (fn_800B1138(actor))
            fn_800B01C8(actor, 1);
        if (fn_800B0F0C(actor)) {
            int a = actor;
            if (fn_800B1CC8(a)) {
                if (kind & 1) {
                    if (!(rec->flags & 0x100)) {
                        fn_80075774(a, &node->v10);
                        fn_80065F28(a, &node->v10);
                        rec->flags |= 0x100;
                    } else {
                        fn_8005A9B8(a, &node->v20);
                    }
                }
                if (kind & 2) {
                    fn_80065CB0(a, &node->v50);
                    fn_80065D60(a, &node->v60);
                }
            }
            if (node->flags & 8)
                fn_80042158(node, rec->handle);
            node->dur = 0;
        }
        if (fn_800B0C58(actor)) {
            Actor *a = fn_800B14A0(actor);
            Snap &s = node->snap;
            a->f30 = s.f4C;
            if (node->flags & 1) {
                Ctl *c = fn_80085954(a);
                if (c) {
                    int unused = fn_8009AE00(a);
                    Anim *an = fn_8009AF80(a);
                    an->f1C = s.f18;
                    an->f18 = s.f14;
                    fn_8019DB24(an, s.f1C);
                    an->f14 = s.f20;
                    fn_80435578(an, s.f24);
                    an->f48 = (Clip *)s.f4;
                    an->f44 = s.f0;
                    fn_8019DB24(an->ch2, s.f8);
                    an->f40 = s.fC;
                    fn_80435578(an->ch2, s.f10);
                    an->f74 = s.f28;
                    fn_8019DB24(an->ch3, s.f2C);
                    an->f6C = s.f38;
                    fn_80435578(an->ch3, s.f34);
                    an->f60 = s.f30;
                    if (!(node->flags & 2) && an->f48)
                        node->dur = (int)(an->f48->length / 30.0f * 1000.0f);
                    else
                        node->dur = 0;
                    fn_800BD2D0(c, node->dur);
                    float f5C = s.f1C;
                    float time = s.f8;
                    if (kind & 8) {
                        float elapsed = node->dur <? (lbl_8066B794 - node->time);
                        float t = (elapsed - (float)lbl_8066B798->offset) / (float)node->dur;
                        t = t > 0.0f ? t : 0.0f;
                        t = t < 1.0f ? t : 1.0f;
                        Clip *clip = fn_804355C0(an->ch2);
                        if (clip)
                            time += clip->length * t;
                        fn_8019DB24(an->ch2, time);
                    }
                    fn_8019BA58(an, 1, 1, 0);
                    fn_8019C408(an);
                    if ((kind & 4) && (node->flags & 0x10)) {
                        c->s5(s.f40);
                        fn_800CD70C(c, s.f3C & 4);
                    }
                }
            }
            a->f31C = node->snap.f48;
        }
        if (fn_800B0C58(actor))
            fn_80048274(actor, 0xFF00FF00, 1.1f, 1);
    }
    unsigned int end = node->time + node->dur + lbl_8066B798->offset;
    if (rec->until >= end && (node->flags & 1) == 0)
        return;
    rec->until = end;
}
}
