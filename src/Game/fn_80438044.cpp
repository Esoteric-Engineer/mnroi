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
