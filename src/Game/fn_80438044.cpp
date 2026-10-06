// Walks the list at +0x24 of its third argument and queues each node that passes fn_8043810C, a skip filter, then small float helpers and the Placement and Body constructors (names guessed; docs/versus.md, row 8).

struct Self;
struct Node
{
    char pad[0xB8];
    int tag; // +0xB8
};

extern "C" int fn_8043810C(Self *self, Node *node);
extern "C" int fn_800B0BEC(Node *node);
extern "C" int fn_800B1138(Node *node);
extern "C" int fn_800B0C58(Node *node);
extern "C" int fn_800B0CC0(Node *node);
extern "C" int fn_800B1258(Node *node);
extern "C" int fn_800B13A8(Node *node);
extern "C" int fn_8008582C(Node *node);
extern "C" int fn_80085EEC(Node *node);
extern "C" int fn_80085EBC(Node *node);
extern "C" int fn_80438580(Self *self);
extern "C" int fn_80438550(Self *self);
extern int lbl_8066B600;
extern "C" int fn_8004DDD8(Node *node, void *obj, float s, float *out);
extern "C" void fn_8043764C(Self *self, Node *node, float s);
extern "C" Node *fn_800B1CF4(Node *node);
extern "C" float fn_80438CC8(float x);

struct Self
{
    char pad0[0x28];
    unsigned flags; // +0x28
    char pad1[4];
    int cur;        // +0x30
    char pad2[0x1848 - 0x30 - 4];
    unsigned mask;  // +0x1848
};

struct Owner
{
    char pad[0x24];
    Node *list;
};

extern "C" void fn_80438044(register Self *self, register void *obj, register float s, register Owner *owner)
{
    Node *node;
    float out;
    for (node = owner->list; node; node = fn_800B1CF4(node))
    {
        if (fn_8043810C(self, node))
            continue;
        if (fn_8004DDD8(node, obj, s, &out))
            fn_8043764C(self, node, out);
    }
}

inline int sn_return_decl(int a)
{
    return a;
}

extern "C" int fn_8043810C(register Self *self, register Node *node)
{
    Node *p;
    if ((1 << fn_800B0BEC(node)) & self->mask)
        return 1;
    if ((int)node == self->cur)
        return 1;
    if (fn_800B1138(node))
        return 1;
    p = 0;
    if (fn_800B0C58(node))
    {
        p = node;
        if (self->flags & 0x800)
        {
            if (fn_8008582C(p))
                return 1;
        }
        if (self->flags & 0x200)
        {
            if (!fn_8008582C(p))
                return 1;
        }
        if (self->flags & 0x4)
        {
            if (fn_80085EEC(p))
                return 1;
        }
    }
    if (fn_80438580(self) && fn_800B0CC0(node) && !fn_800B1258(node))
        return 1;
    if (self->flags & 0x400)
    {
        if (node->tag != lbl_8066B600)
            return 1;
    }
    if (!fn_80438550(self) && fn_800B13A8(node))
    {
        if (p == 0 || fn_80085EBC(p) == 0)
            return 1;
    }
    return 0;
}

extern "C" float fn_80438308(register float x)
{
    return 1.0f / fn_80438CC8(x);
}

extern "C" float *fn_80438360(register float *base, register int i)
{
    return &base[i];
}

extern "C" void fn_80438398(register float *out, register float *v)
{
    out[0] = -v[0];
    out[1] = -v[1];
    out[2] = -v[2];
    out[3] = -v[3];
}

extern "C" float fn_804383EC(register float *v)
{
    float s = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
    return s != 0.0f ? fn_80438CC8(s) : 0.0f;
}

extern "C" int fn_80438480(register int x)
{
    return x;
}

struct Tagged
{
    char pad[4];
    char kind; // +0x4
};

extern "C" char fn_804384A8(register Tagged *self)
{
    return self->kind;
}

struct Cell
{
    char pad[0x14];
    float value; // +0x14
};

extern "C" void fn_804384D8(register Cell *self)
{
    self->value = 1.0f;
}

extern "C" char lbl_804F32F8[];
extern "C" void fn_80436F94(void *self);

class ShapeBaseB
{
public:
    float x;          // +0x0
    const void *vptr; // +0x4
    ShapeBaseB();
};

ShapeBaseB::ShapeBaseB() : vptr(lbl_804F32F8)
{
    fn_80436F94(this);
}

extern "C" int fn_80438550(register Self *self)
{
    return self->flags & 0x100;
}

extern "C" int fn_80438580(register Self *self)
{
    return self->flags & 0x1000;
}

extern "C" void __6Vector(void *self);
extern "C" void fn_80437210(void *self, void *a, void *b, void *c, int d, int e);

class Placement
{
public:
    char d[0x40];
    Placement(register void *a, register void *b, register void *c, register int d, register int e);
};

Placement::Placement(register void *a, register void *b, register void *c, register int d, register int e)
{
    __6Vector((char *)this + 0x10);
    __6Vector((char *)this + 0x20);
    fn_80437210(this, a, b, c, d, e);
}

extern "C" char lbl_804F3338[];

struct Chunk
{
    char d[0x40];
};

class Body
{
public:
    Chunk a;             // +0x0
    Chunk b;             // +0x40
    int slot80;          // +0x80
    int slot84;          // +0x84
    const void *vptr;    // +0x88
    Body(register void *src);
};

Body::Body(register void *src)
{
    vptr = lbl_804F3338;
    a = *(Chunk *)src;
    b = *(Chunk *)src;
    slot84 = 0;
    slot80 = 0;
}

extern "C" int fn_80438758(register void *self)
{
    return 0;
}

extern "C" int fn_804373A4(register char *self);
extern "C" int fn_800489BC(void *p);

extern "C" int fn_80438780(register char *self)
{
    return fn_804373A4(self) ? fn_800489BC(self + 0x90) : 0;
}

extern "C" int fn_804387E4(register char *self)
{
    return fn_804373A4(self) ? fn_800489BC(self + 0x90) : 0;
}

extern "C" int fn_80438848(register char *self)
{
    return fn_804373A4(self) ? fn_800489BC(self + 0xA0) : 0;
}

extern "C" int fn_804388AC(register char *self)
{
    return *(int *)(self + 0xE0);
}

extern "C" void fn_804388D8(register char *self, register int v)
{
    *(int *)(self + 0x90) = v;
}

extern "C" void fn_80438900(register char *self, register int v)
{
    *(int *)(self + 0x94) = v;
}

extern "C" void fn_8042DC84(void *dst, void *src);
extern "C" void fn_80429090(void *out, void *a, void *b, float s);
extern "C" float fn_80434E0C(char *self);
extern "C" float fn_80438D68(char *self);
extern "C" void fn_80438D94(char *self, float s);

extern "C" void fn_80438928(register char *self, register void *a, register void *b, register float s)
{
    fn_8042DC84(self, a);
    fn_8042DC84(self + 0x20, b);
    *(float *)(self + 0x30) = s;
    fn_80429090(self + 0x10, self, self + 0x20, *(float *)(self + 0x30));
}

extern "C" int fn_804389A8(register char *self, register char *v)
{
    *(Chunk *)(self + 0x90) = *(Chunk *)v;
    *(int *)(self + 0x84) = 1;
    *(int *)(self + 0x80) = 1;
    return 1;
}

extern "C" int fn_80438A54(register char *self, register char *v)
{
    register float rt;
    float t;
    rt = fn_80434E0C(v);
    t = rt;
    *(int *)(self + 0x80) = 1;
    if (fn_80438D68(self + 0x40) >= t)
    {
        fn_80438D94(self + 0x40, t);
        *(Chunk *)(self + 0x90) = *(Chunk *)v;
        return 1;
    }
    else
    {
        return 0;
    }
}

extern "C" int fn_80438B5C(register char *self, register char *v)
{
    int a;
    int b;
    register float rt;
    float t;
    *(int *)(self + 0x80) = 1;
    if (*(int *)(self + 0x90))
    {
        a = 0;
        b = 0;
        *(int *)(self + 0x84) = ((int (*)(char *, char *, int, int *, int *))(*(int *)(self + 0x90)))(self, v, *(int *)(self + 0x94), &a, &b);
        if (a)
        {
            *(Chunk *)(self + 0xA0) = *(Chunk *)v;
        }
        rt = fn_80434E0C(v);
        t = rt;
        if (b)
        {
            if (fn_80438D68(self + 0x40) >= t)
            {
                fn_80438D94(self + 0x40, t);
                return 1;
            }
        }
    }
    return 0;
}

extern "C" float fn_80438CC8(register float x)
{
    union { int i; float f; } a, b;
    float r;
    float y;
    if (x <= 0.0f)
    {
        a.i = 0x7F800000;
        b.i = 0x7F800000;
        return b.f;
    }
    register double in __asm__("45") = x;
    register double d __asm__("44");
    __asm__("frsqrte %0, %1" : "=f"(d) : "f"(in));
    y = d;
    r = y * 0.5f * (3.0f - x * y * y);
    return r;
}

extern "C" float fn_80438D68(register char *self)
{
    return *(float *)(self + 0x30);
}

extern "C" void fn_80438D94(register char *self, register float s)
{
    *(float *)(self + 0x30) = s;
    fn_80429090(self + 0x10, self, self + 0x20, *(float *)(self + 0x30));
}

extern "C" float fn_8042A2B8(float s);

extern "C" float fn_80438DF0(register float *v)
{
    float s;
    float r;
    s = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
    r = fn_8042A2B8(s);
    v[0] = v[0] * r;
    v[1] = v[1] * r;
    v[2] = v[2] * r;
    return s * r;
}

struct Swap
{
    unsigned int w;       // +0x0
    unsigned short h[4];  // +0x4
};

extern "C" void fn_80438EA4(register Swap *p)
{
    p->w = (p->w >> 24) | ((p->w >> 8) & 0xFF00) | ((p->w & 0xFF00) << 8) | (p->w << 24);
    p->h[0] = ((p->h[0] & 0xFF) << 8) | (p->h[0] >> 8);
    p->h[1] = ((p->h[1] & 0xFF) << 8) | (p->h[1] >> 8);
    p->h[2] = ((p->h[2] & 0xFF) << 8) | (p->h[2] >> 8);
    p->h[3] = ((p->h[3] & 0xFF) << 8) | (p->h[3] >> 8);
}

class Attr
{
public:
    int a;                   // +0x0
    const void *b;           // +0x4
    mutable const Attr *link; // +0x8
    Attr(int a, int b) __asm__("fn_80439B24");
    Attr(int a, const char *b) __asm__("fn_80439B64");
    const Attr &chain(const Attr &next) const __asm__("fn_80439BA4");
};

extern "C" char lbl_80593C58[];
extern "C" int fn_801B0C90(char *a, void *b, const Attr &c);
extern "C" char lbl_80486C2C[0x15];
extern "C" char lbl_80486C44[0x31];

extern "C" int fn_80438FAC(register void *self)
{
    int r;
    r = fn_801B0C90(lbl_80593C58, self, Attr(4, 1).chain(Attr(1, lbl_80486C2C)).chain(Attr(5, lbl_80486C44)).chain(Attr(6, 0xFA)));
    return r;
}

struct Slot
{
    int a, b, c;  // +0x0
    int *p;       // +0xC
    int *q;       // +0x10
    Slot() __asm__("fn_80439BD4");
};

class Streamer
{
public:
    int pad0;       // +0x0
    int f4;         // +0x4
    int f8;         // +0x8
    char pad1[0x1C];
    int f28;        // +0x28
    int f2C;        // +0x2C
    int f30;        // +0x30
    Slot slots[2];  // +0x34
    int f5C, f60, f64, f68, f6C, f70, f74;
    Streamer();
};

extern "C" void fn_80439DCC(Streamer *self);

Streamer::Streamer()
    : f4(0), f8(0), f28(0), f2C(0), f30(0), f5C(0), f60(0), f64(0), f68(0), f6C(1), f70(0), f74(0)
{
    for (unsigned i = 0; i <= 1; i++)
    {
        slots[i].p = &f28;
        slots[i].q = &f2C;
    }
    fn_80439DCC(this);
}
