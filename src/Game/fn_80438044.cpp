// Walks the list at +0x24 of its third argument and queues each node that passes fn_8043810C, a skip filter, then three small float helpers (names guessed; docs/versus.md, row 8).

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
