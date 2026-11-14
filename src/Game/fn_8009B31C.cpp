// Path-node graph: unload step, the .npd loader, the hull and damage-volume link switches and the route queries (docs/ai.md row 15, section 4.7).

#define SWAP16(x) ((((x) & 0xFF) << 8) | ((unsigned short)(x) >> 8))

inline int sn_return_decl(int a) { return a; }

struct Sector // a level sector, found by position (fn_8004DD38)
{
    char pad0[0x11C];
    unsigned short firstNode; // +0x11C
    unsigned short nNodes;    // +0x11E
};

struct Node
{
    char pad0[0x40];
    float cost; // +0x40
    char pad44[0x1C];
};

struct Link
{
    char pad[0x30];
};

class Vector
{
public:
    float x, y, z, w;
    Vector();
} __attribute__((aligned(8)));

struct Mat4
{
    float m[4][4];
};

struct Hull
{
    char pad0[0xB];
    unsigned char planeCount; // +0xB
    char padC[0x78];
    Vector *planes; // +0x84
};

struct Shape
{
    Hull *hull; // +0x0
};

struct Ent
{
    char pad[0x78];
    Mat4 xform; // +0x78
};

struct Level
{
    char pad0[0x28];
    unsigned short nNodes; // +0x28
    unsigned short nLinks; // +0x2A
    char name[0x20];       // +0x2C (only the part from +0x30 is the file name; see below)
    char pad50[0x154 - 0x4C];
    Node *nodes; // +0x154
    Link *links; // +0x158
};

extern "C" {
void *fn_80430050(void *level);
extern char lbl_8052F060[]; // the level object
void fn_8042D7B0(Mat4 *m);
void fn_80434420(Mat4 *dst, Mat4 *src);
void fn_8042DA10(Vector *out, Vector *v, Mat4 *m);
Shape *fn_8009AD80(Ent *e);
Vector *fn_80444688(Node *node);
int fn_8004D2D8(Vector *p, Vector *planes, int count);
void fn_80444870(Node *node, int on);
char *strncpy(char *dst, const char *src, unsigned n);
void fn_8009CF44(void *graph);
float *fn_8042FB28(void *v);
int fn_80444710(Node *node);
Node *fn_8009C55C(Vector *pos, void *world, unsigned mask, float radius, void *test, void *ctx, int n);
float fn_8009D278(Node *a, Node *b, Vector *out);
float fn_8009D184(Vector *v, unsigned n);
int fn_804445D8(Node *node);
int fn_804445A4(Node *node);
int fn_80444570(Node *node);
int fn_8009C004(void *query, Vector *from, Vector *to, Node *fromSpot, Node *toSpot, unsigned mask, float range);
void fn_801B4094(char *path, const char *ext);
void *fn_801A8368(const char *path, const char *mode, int flags);
void fn_801A953C(void *file);
int fn_801A8B60(void *dst, int size, int count, void *file);
void fn_801A875C(void *file);
void *fn_801AC988(unsigned size, const char *tag, int line, int align);
void SetLoadProgress__8GameFlowfi(void *self, float f, int a);
Node *fn_80444904(Link *link, int i);
Node *fn_80444984(Link *link, int i);
void fn_80444638(Link *link, int off);
void fn_8042DC84(Vector *dst, Vector *src);
int fn_801464E4(void *volume, Vector *p);
int fn_80146918(void *volume, Vector *from, Vector *to, Vector *hit);
void fn_8009CB38(Node *node, void *file, int version);
void fn_8009CDE4(Link *link, Level *lv, void *file);
Sector *fn_8004DD38(Level *lv, void *pos);
void fn_804446B4(Node *node, Sector *s);
void fn_8044256C(void *out, const char *fmt, ...);
extern char lbl_80552920[];       // the GameFlow instance
extern void *lbl_8066B56C;
extern unsigned short lbl_8066B97C;

int fn_8009B31C(void *graph)
{
    fn_8009CF44(graph);
    return 1;
}

int fn_8009B35C(Level *lv, char *h)
{
    char path[0x80];
    void *file;
    unsigned short version;
    int old;
    Node *node;
    Sector *s;
    unsigned short i;
    int missing;
    lbl_8066B97C = 0;
    if (h)
        strncpy(path, h + 0xC, 0x80);
    else
        strncpy(path, (char *)lv + 0x30, 0x80);
    fn_801B4094(path, "npd");
    file = fn_801A8368(path, "rb", 3);
    if (!file)
        return 0;
    fn_801A953C(file);
    fn_801A8B60(&version, 2, 1, file);
    version = SWAP16(version);
    if (version != 3 && version != 2 && version != 1)
        return 0;
    old = version == 1;
    fn_801A8B60(&lv->nNodes, 2, 1, file);
    lv->nNodes = SWAP16(lv->nNodes);
    fn_801A8B60(&lv->nLinks, 2, 1, file);
    lv->nLinks = SWAP16(lv->nLinks);
    if (!old) {
        fn_801A8B60(&lbl_8066B97C, 2, 1, file);
        lbl_8066B97C = SWAP16(lbl_8066B97C);
    }
    lv->nodes = (Node *)fn_801AC988(lv->nNodes * 0x60, "Game:Pathing", 0x9E, 2);
    lv->links = (Link *)fn_801AC988(lv->nLinks * 0x30, "Game:Pathing", 0x9F, 2);
    missing = 0;
    for (i = 0; i < lv->nNodes; i++) {
        SetLoadProgress__8GameFlowfi(lbl_80552920, (float)i / (float)(int)lv->nNodes, 1);
        node = lv->nodes + i;
        fn_8009CB38(node, file, version);
        s = fn_8004DD38(lv, fn_80444688(node));
        fn_804446B4(node, s);
        if (!s) {
            missing++;
        } else if (s->firstNode > i) {
            s->firstNode = i;
            s->nNodes = 1;
        } else {
            s->nNodes++;
        }
    }
    for (i = 0; i < lv->nLinks; i++)
        fn_8009CDE4(lv->links + i, lv, file);
    if (missing)
        fn_8044256C(lbl_8066B56C, "PATH WARNING!  %d nodes have no sector.\n", missing);
    fn_801A875C(file);
    return 1;
}

// Script command: with the nodes inside an entity's hull, `on` clears their disabled bit (+0x2C & 0x400) and 0 sets it
void fn_8009B83C(Ent *e, int on)
{
    Level *lv = (Level *)fn_80430050(lbl_8052F060);
    Mat4 inv;
    Node *node;
    fn_8042D7B0(&inv);
    fn_80434420(&inv, &e->xform);
    Vector p;
    for (unsigned short i = 0; i < lv->nNodes; i++) {
        node = lv->nodes + i;
        fn_8042DA10(&p, fn_80444688(node), &inv);
        if (!fn_8004D2D8(&p, fn_8009AD80(e)->hull->planes, fn_8009AD80(e)->hull->planeCount))
            continue;
        fn_80444870(node, on == 0);
    }
}

// Damage volume add (on 0) / remove (1): each link that touches the volume (an end or a crossing) is switched off / on
void fn_8009B994(void *volume, int on)
{
    Level *lv = (Level *)fn_80430050(lbl_8052F060);
    Link *link;
    Vector p;
    for (unsigned short i = 0; i < lv->nLinks; i++) {
        link = lv->links + i;
        Vector a, b, c;
        int hit;
        fn_8042DC84(&a, fn_80444688(fn_80444904(link, 0)));
        fn_8042DC84(&b, fn_80444688(fn_80444984(link, 0)));
        a.z = b.z = 0.0f;
        hit = 0;
        if (fn_801464E4(volume, &a)) {
            hit = 1;
        } else if (fn_801464E4(volume, &b)) {
            hit = 1;
        } else if (fn_80146918(volume, &a, &b, &c)) {
            hit = 1;
        }
        if (hit)
            fn_80444638(link, !on);
    }
}

// Route query between two points: snap each end to the nearest spot (within 20, the far end first), then search between them
int fn_8009BB7C(register void *path, Vector *from, Vector *to, Sector *fromWorld, Sector *toWorld, unsigned mask, float range)
{
    if (!fromWorld)
        fromWorld = fn_8004DD38((Level *)fn_80430050(lbl_8052F060), from);
    if (!toWorld)
        toWorld = fn_8004DD38((Level *)fn_80430050(lbl_8052F060), to);
    Vector a, b;
    Node *toSpot;
    Node *fromSpot;
    fn_8042DC84(&a, from);
    fn_8042FB28(&a)[2] += 0.3f;
    fn_8042DC84(&b, to);
    fn_8042FB28(&b)[2] += 0.3f;
    toSpot = fn_8009C55C(&b, toWorld, mask | 0x40000000, 20.0f, 0, 0, -1);
    if (!toSpot)
        return 0;
    fromSpot = fn_8009C55C(&a, fromWorld, mask & 0x80000000, 20.0f, 0, 0, fn_80444710(toSpot));
    if (!fromSpot)
        return 0;
    return fn_8009C004(path, from, to, fromSpot, toSpot, mask, range);
}

// Route query from a spot: snap the far end to the nearest spot (within 20, not the spot's own side), then search from the given spot
int fn_8009BD7C(register void *path, Node *fromSpot, Vector *to, Sector *toWorld, unsigned mask, float range)
{
    if (!toWorld)
        toWorld = fn_8004DD38((Level *)fn_80430050(lbl_8052F060), to);
    Vector b;
    Node *toSpot;
    fn_8042DC84(&b, to);
    fn_8042FB28(&b)[2] += 0.3f;
    toSpot = fn_8009C55C(&b, toWorld, mask + 0x40000000, 20.0f, 0, 0, fn_80444710(fromSpot));
    if (!toSpot)
        return 0;
    return fn_8009C004(path, fn_80444688(fromSpot), to, fromSpot, toSpot, mask, range);
}

// 0.3f and 20.0f with no reader in .text, between the two functions' pools
__asm__(".section .rodata\n\t.long 0x3E99999A\n\t.long 0x41A00000\n\t.text");

// Cost of the step between two spots
void fn_8009BEC4(register void *path, Node *from, Node *to, unsigned n, float *total, float *base)
{
    Vector v;
    float d = fn_8009D278(from, to, &v);
    if (fn_804445D8(to))
        d *= 0.9f;
    else if (fn_804445A4(to))
        d *= 0.7f;
    if (fn_80444570(to))
        d *= 1.1f;
    else {
    }
    float b = from->cost + d;
    float extra = fn_8009D184(&v, n);
    float t = b + extra;
    *total = t;
    *base = b;
}
}
