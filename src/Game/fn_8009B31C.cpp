// Path-node graph: unload step, the .npd loader, the hull and damage-volume link switches and the route queries (docs/ai.md row 15, section 4.7).

#define SWAP16(x) ((((x) & 0xFF) << 8) | ((unsigned short)(x) >> 8))

inline int sn_return_decl(int a) { return a; }

struct Sector // a level sector, found by position (fn_8004DD38)
{
    char pad0[0x11C];
    unsigned short firstNode; // +0x11C
    unsigned short nNodes;    // +0x11E
};

class Vector
{
public:
    float x, y, z, w;
    Vector();
} __attribute__((aligned(8)));

struct Link
{
    unsigned short from;  // +0x0 (node index)
    unsigned short to;    // +0x2
    unsigned short flags; // +0x4
    char pad6[0xA];
    Vector dir;           // +0x10 (from -> to, normalised)
    int pad20;            // +0x20
    char pad24[0xC];
};

struct Node
{
    unsigned short id;     // +0x0 (file value)
    char pad2[0xE];
    Vector spot;           // +0x10
    unsigned short sector; // +0x20 (the sector's index)
    unsigned char region;  // +0x22
    char pad23;
    unsigned short link[2]; // +0x24 (the file's two link fields)
    unsigned short firstLink; // +0x28 (index of its first link)
    unsigned char nLinks;  // +0x2A
    char pad2B;
    unsigned short flags; // +0x2C (bit 0: on the open list)
    char pad2E[2];
    Node *next;           // +0x30 open list, ordered by f
    Node *prev;           // +0x34
    unsigned short stamp; // +0x38 (search id, lbl_8066B984)
    char pad3A[2];
    float h;              // +0x3C
    float cost;           // +0x40 (cost from the start)
    float f;              // +0x44 (h + cost)
    Link *via;            // +0x48 (the link the search reached it by)
    char pad4C[4];
    Vector pos;           // +0x50
};

struct SectorSlot
{
    char pad[0x30];
};

struct SectorQuery // the sectors near a point (fn_8004E75C);
{
    char pad0[0x40];
    SectorSlot slot[0x80]; // +0x40
    unsigned int count;    // +0x1840
    char pad1844[0xC];
};

typedef int (*SpotTest)(Node *, Vector *, unsigned short, void *);

struct Query // the 0x58-byte base of the Mover's path (docs/ai.md section 4.6)
{
    unsigned count;       // +0x0
    Link *entries[16];    // +0x4
    unsigned short flags; // +0x44
    float length;         // +0x48
    int kind;             // +0x4C
    Node *spot;           // +0x50
};

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
void fn_8009CF44(Level *graph);
void fn_801ACC0C(void *p);
float *fn_8042FB28(void *v);
int fn_80444710(Node *node);
Node *fn_8009C55C(Vector *pos, Sector *world, unsigned mask, float radius, SpotTest test, void *ctx, int region);
void fn_8004E9C8(SectorQuery *q);
void fn_8004E75C(SectorQuery *q, Vector *pos, float radius, Sector *world);
Sector *fn_8042F1C4(SectorSlot *slot);
void fn_80429090(Vector *out, Vector *a, Vector *b, float t);
int fn_8004A758(Vector *from, Vector *dir, float len, int a, int b, int c, Sector *world, int d, int e);
int fn_8044483C(Node *node);
int fn_804447D4(Node *node);
extern Vector lbl_80593DE0;
float fn_8009D278(Node *a, Link *b, Vector *out);
float fn_8009D184(Vector *a, Vector *b);
int fn_804445D8(Link *link);
int fn_804445A4(Link *link);
int fn_80444570(Link *link);
int fn_8009C004(Query *query, Vector *from, Vector *to, Node *fromSpot, Node *toSpot, unsigned mask, float range);
float fn_80132DC4(int kind);
float fn_804290F8(Vector *a, Vector *b);
void fn_80429038(Vector *out, Vector *a, Vector *b);
float fn_8042EC54(Vector *v);
void fn_804448C0(Query *q);
Link *fn_80444770(Node *node, int i);
unsigned short fn_80444740(Node *node);
int fn_80444A5C(Link *link, unsigned mask);
int fn_80444BB0(Node *node, unsigned mask);
void fn_8009CFDC();
void fn_8009D024(Node *node);
void fn_8009D0F4(Node *node);
void fn_8009D1D0(Node *node);
void fn_8009D238(Node *node);
int fn_8009C92C(Query *q, Node *last, Vector *from, Vector *to);
extern Vector lbl_805528D0;
extern Vector lbl_805528E0;
extern unsigned short lbl_8066B984; // search id
extern int lbl_8066B980;
extern Node *lbl_8066B988;          // open list head
extern int lbl_8066B98C;            // open list count
extern float lbl_8066D678;
void fn_801B4094(char *path, const char *ext);
void *fn_801A8368(const char *path, const char *mode, int flags);
void fn_801A953C(void *file);
int fn_801A8B60(void *dst, int size, int count, void *file);
void fn_801A875C(void *file);
void *fn_801AC988(unsigned size, const char *tag, int line, int align);
void SetLoadProgress__8GameFlowfi(void *self, float f, int a);
Node *fn_80444904(Link *link, Level *lv);
Node *fn_80444984(Link *link, Level *lv);
void fn_80444638(Link *link, int off);
void fn_8042DC84(Vector *dst, Vector *src);
void fn_8009CB38(Node *node, void *file, unsigned version);
void fn_80428FA8(Vector *v, float x, float y, float z);
void fn_8042FC74(Vector *v);
void fn_8042F76C(Vector *v);
void fn_8042F984(Vector *out, Vector *a, Vector *b);
float fn_8042EBF4(Vector *a, Vector *b);
Vector *fn_8044460C(Link *link);
Vector *fn_80444A04(Link *link, int i);
int fn_801464E4(void *volume, Vector *p);
int fn_80146918(void *volume, Vector *from, Vector *to, Vector *hit);
void fn_8009CDE4(Link *link, Level *lv, void *file);
Sector *fn_8004DD38(Level *lv, void *pos);
void fn_804446B4(Node *node, Sector *s);
void fn_8044256C(void *out, const char *fmt, ...);
extern char lbl_80552920[];       // the GameFlow instance
extern void *lbl_8066B56C;
extern unsigned short lbl_8066B97C;

int fn_8009B31C(Level *graph)
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
int fn_8009BB7C(register Query *path, Vector *from, Vector *to, Sector *fromWorld, Sector *toWorld, unsigned mask, float range)
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
int fn_8009BD7C(register Query *path, Node *fromSpot, Vector *to, Sector *toWorld, unsigned mask, float range)
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
void fn_8009BEC4(register Query *path, Node *from, Link *to, Vector *dest, float *total, float *base)
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
    float extra = fn_8009D184(&v, dest);
    float t = b + extra;
    *total = t;
    *base = b;
}

#define ABS(x) ((x) < 0.0f ? -(x) : (x))

// A* between two spots: expands the open list over the links the mask allows.
int fn_8009C004(register Query *path, Vector *from, Vector *to, Node *fromSpot, Node *toSpot, unsigned mask, float range)
{
    Node *cur;
    Node *next;
    Link *l;
    unsigned short i;
    Link *link;
    float g;
    if (fromSpot == toSpot) {
        path->spot = fromSpot;
        path->length = fn_804290F8(from, fn_80444688(path->spot)) + fn_804290F8(fn_80444688(path->spot), to);
        path->flags |= 2;
        return 1;
    }
    if (fn_80444710(fromSpot) != fn_80444710(toSpot))
        return 0;
    fn_8009CFDC();
    fn_804448C0(path);
    fn_8042DC84(&lbl_805528E0, from);
    fn_80429038(&lbl_805528D0, to, from);
    lbl_8066D678 = fn_8042EC54(&lbl_805528D0);
    fromSpot->stamp = lbl_8066B984;
    fromSpot->cost = 0.0f;
    fromSpot->h = fn_8009D184(from, to);
    fromSpot->f = fromSpot->h;
    fromSpot->via = 0;
    fromSpot->next = fromSpot->prev = 0;
    fn_8042DC84(&fromSpot->pos, from);
    fromSpot->flags |= 1;
    lbl_8066B988 = fromSpot;
    lbl_8066B98C = 1;
    cur = lbl_8066B988;
    Vector v;
    float f;
    float h;
    while (lbl_8066B98C) {
        cur = lbl_8066B988;
        if (cur == toSpot) {
            if (fn_8009C92C(path, cur, from, to))
                return 2;
            else
                return 0;
        }
        fn_8009D0F4(cur);
        i = 0;
        link = fn_80444770(cur, 0);
        for (; i < fn_80444740(cur); i++, link++) {
            if (!fn_80444A5C(link, mask))
                continue;
            if (fn_80444570(link)) {
                float lim = fn_80132DC4(path->kind);
                Vector a;
                Vector b;
                fn_8042DC84(&a, fn_80444688(fn_80444904(link, 0)));
                fn_8042DC84(&b, fn_80444688(fn_80444984(link, 0)));
                float dz = ABS(a.z - b.z);
                if (lim < dz)
                    continue;
            }
            next = fn_80444984(link, 0);
            if (next != toSpot && !fn_80444BB0(next, mask))
                continue;
            l = cur->via;
            for (;;) {
                if (!l)
                    break;
                if (fn_80444904(l, 0) == next)
                    break;
                l = fn_80444904(l, 0)->via;
            }
            if (l)
                continue;
            fn_8009BEC4(path, cur, link, to, &f, &g);
            fn_8009D278(cur, link, &v);
            h = fn_8009D184(&v, to);
            if (next->stamp != lbl_8066B984) {
                fn_8009D1D0(next);
            } else {
                if (next->f <= f)
                    continue;
            }
            next->via = link;
            next->cost = g;
            fn_8042DC84(&next->pos, &v);
            next->h = h;
            next->f = f;
            if (!(next->flags & 1))
                fn_8009D024(next);
            else
                fn_8009D238(next);
        }
    }
    return 0;
}

// Nearest spot to pos within radius. Retried once at 40 with a 10 minimum.
Node *fn_8009C55C(Vector *pos, Sector *world, unsigned mask, float radius, SpotTest test, void *ctx, int region)
{
    if (!world)
        return 0;
    SectorQuery q;
    fn_8004E9C8(&q);
    Level *lv = (Level *)fn_80430050(lbl_8052F060);
    Node *node;
    Node *best = 0;
    Sector *sec;
    Vector d;
    float dist;
    float limit = radius + 1.0f;
    float least = 0.0f;
    unsigned int si;
    int ni;
    unsigned short m;
    Vector from;
    fn_80429090(&from, pos, &lbl_80593DE0, 0.05f);
top:
    fn_8004E75C(&q, pos, radius, world);
    limit = radius + 1.0f;
    for (si = 0; si < q.count; si++) {
        sec = fn_8042F1C4(&q.slot[si]);
        if (!sec->nNodes)
            continue;
        for (ni = sec->firstNode; ni < sec->firstNode + sec->nNodes; ni++) {
            node = lv->nodes + ni;
            if (region > -1 && fn_80444710(node) != region)
                continue;
            if ((mask & 0x40000000) && fn_8044483C(node))
                continue;
            if (fn_804447D4(node) && !(mask & 0x70))
                continue;
            m = mask;
            if (m && !(node->flags & m))
                continue;
            fn_80429038(&d, fn_80444688(node), pos);
            dist = fn_8042EC54(&d);
            if (dist > limit || dist < least)
                continue;
            if (!(mask & 0x80000000)) {
                if (fn_8004A758(&from, &d, dist, 1, 0, 0, world, 0, 2))
                    continue;
            }
            if (test) {
                if (!test(node, pos, (unsigned short)mask, ctx))
                    continue;
            }
            best = node;
            limit = dist;
        }
    }
    if (!best && radius < 40.0f) {
        radius = 40.0f;
        least = 10.0f;
        goto top;
    }
    return best;
}

// Builds the route: sums its legs into the query's length and keeps the last 16 links.
int fn_8009C92C(register Query *q, Node *last, Vector *from, Vector *to)
{
    Node *cur;
    Node *prev;
    unsigned n;
    n = 0;
    prev = 0;
    cur = last;
    while (cur->via) {
        if (prev)
            q->length += fn_804290F8(fn_80444688(prev), fn_80444688(cur));
        prev = cur;
        n++;
        if (n > 255)
            return 0;
        cur = fn_80444904(cur->via, 0);
    }
    q->length += fn_804290F8(to, fn_80444688(last)) + fn_804290F8(from, fn_80444688(cur));
    q->flags = 0;
    if (n > 16) {
        q->flags |= 1;
        while (n > 16) {
            n--;
            last = fn_80444904(last->via, 0);
        }
    }
    q->count = n;
    cur = last;
    while (n) {
        n--;
        q->entries[n] = cur->via;
        cur = fn_80444904(cur->via, 0);
    }
    lbl_8066B98C = 0;
    return 1;
}

// Reads one node record of the .npd file (version 2 and below keeps its position as 3 floats).
void fn_8009CB38(register Node *node, void *file, unsigned version)
{
    float v[3];
    unsigned short i;
    if (version > 1) {
        fn_801A8B60(&node->id, 2, 1, file);
        node->id = SWAP16(node->id);
    } else {
        node->id = lbl_8066B97C++;
    }
    if (version <= 2) {
        fn_801A8B60(v, 12, 1, file);
        fn_80428FA8(&node->spot, v[0], v[1], v[2]);
    } else {
        fn_801A8B60(&node->spot, 16, 1, file);
    }
    fn_8042FC74(&node->spot);
    fn_801A8B60(&node->flags, 2, 1, file);
    node->flags = SWAP16(node->flags);
    fn_801A8B60(&node->region, 1, 1, file);
    fn_801A8B60(node->link, 2, 2, file);
    for (i = 0; i < 2; i++)
        node->link[i] = SWAP16(node->link[i]);
    fn_801A8B60(&node->sector, 2, 1, file);
    node->sector = SWAP16(node->sector);
    fn_801A8B60(&node->firstLink, 2, 1, file);
    node->firstLink = SWAP16(node->firstLink);
    fn_801A8B60(&node->nLinks, 1, 1, file);
}

// Reads one link record of the .npd file and works out its direction.
void fn_8009CDE4(register Link *link, Level *lv, void *file)
{
    fn_801A8B60(link, 2, 1, file);
    link->from = SWAP16(link->from);
    fn_801A8B60(&link->to, 2, 1, file);
    link->to = SWAP16(link->to);
    fn_801A8B60(&link->flags, 2, 1, file);
    link->flags = SWAP16(link->flags);
    fn_80429038(&link->dir, fn_80444688(fn_80444984(link, lv)), fn_80444688(fn_80444904(link, lv)));
    fn_8042F76C(&link->dir);
    link->pad20 = 0;
}

// Frees the node and link arrays.
void fn_8009CF44(Level *graph)
{
    if (graph->nodes) {
        fn_801ACC0C(graph->nodes);
        graph->nodes = 0;
    }
    if (graph->links) {
        fn_801ACC0C(graph->links);
        graph->links = 0;
    }
    graph->nNodes = 0;
    graph->nLinks = 0;
}

// Starts a search: a fresh stamp (never 0).
void fn_8009CFDC()
{
    if (++lbl_8066B984 == 0)
        lbl_8066B984 = 1;
    lbl_8066B980 = 0;
}

// Puts a node in the open list, ordered by f.
void fn_8009D024(register Node *node)
{
    Node *cur;
    Node *prev;
    cur = lbl_8066B988;
    prev = 0;
    while (cur && cur->f <= node->f) {
        prev = cur;
        cur = cur->next;
    }
    node->next = cur;
    node->prev = prev;
    if (node->prev)
        node->prev->next = node;
    else
        lbl_8066B988 = node;
    if (node->next)
        node->next->prev = node;
    node->flags |= 1;
    lbl_8066B98C++;
}
}

// Takes a node out of the open list.
void fn_8009D0F4(register Node *node)
{
    if (node->prev)
        node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;
    if (node == lbl_8066B988)
        lbl_8066B988 = node->next;
    node->prev = 0;
    node->next = 0;
    node->flags &= ~1;
    lbl_8066B98C--;
}

// Distance between two points.
float fn_8009D184(register Vector *a, register Vector *b)
{
    return fn_804290F8(b, a);
}

// Resets a node's search fields.
void fn_8009D1D0(Node *node)
{
    node->stamp = lbl_8066B984;
    node->via = 0;
    node->next = node->prev = 0;
    node->flags &= ~3;
}

// Re-sorts a node in the open list.
void fn_8009D238(register Node *node)
{
    fn_8009D0F4(node);
    fn_8009D024(node);
}

// Distance along a link from a spot to the closest point on it; the point goes to out.
float fn_8009D278(register Node *a, register Link *b, register Vector *out)
{
    Vector v1;
    float len;
    Vector v2;
    float dot;
    float d;
    float res;
    float t;
    fn_8042F984(&v1, fn_8044460C(b), &lbl_805528D0);
    len = fn_8042EC54(&v1);
    if (len < 0.001f) {
        t = 0.0f;
    } else {
        fn_8042F984(&v2, &v1, &lbl_805528D0);
        fn_8042F76C(&v2);
        dot = fn_8042EBF4(fn_8044460C(b), &v2);
        d = (fn_80444A04(b, 0)->x - lbl_805528E0.x) * v2.x + (fn_80444A04(b, 0)->y - lbl_805528E0.y) * v2.y + (fn_80444A04(b, 0)->z - lbl_805528E0.z) * v2.z;
        t = -d / dot;
    }
    fn_80429090(out, fn_80444A04(b, 0), fn_8044460C(b), t);
    res = fn_804290F8(out, &a->pos);
    return res;
}

extern float lbl_8066B974; // .sdata
extern float lbl_8066B978;
extern float lbl_8066D668; // .sbss, set by the static initializer
extern float lbl_8066D66C;
extern float lbl_8066D670;
extern float lbl_8066D674;
extern "C" void __6Vector(void *self);

// 65535 is GCC 2.95's default init priority.
static void __static_initialization_and_destruction_0(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            lbl_8066D668 = 320.0f - lbl_8066B974 * 0.5f;
            lbl_8066D66C = lbl_8066D668 + lbl_8066B974 * 0.5f;
            lbl_8066D670 = 240.0f - lbl_8066B978 * 0.5f;
            lbl_8066D674 = lbl_8066B978 * 0.5f + lbl_8066D670 - 12.0f;
            __6Vector(&lbl_805528D0);
            __6Vector(&lbl_805528E0);
        } else {
        }
    }
}

void fn_8009D548(void)
{
    __static_initialization_and_destruction_0(1, 65535);
}

static void (*const sCtorEntry)(void) __attribute__((section(".ctors"))) = fn_8009D548;
