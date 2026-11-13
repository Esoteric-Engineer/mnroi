// The volume registry lbl_80569890: script-registered volumes the AI avoids or stays inside (docs/ai.md row 10, section 4.5).
// The file's .rodata (0x8049B088-0x8049B204) is extern_pool: it ends in linkonce words and a header's strings this source doesn't emit.

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

struct Volume {
    int handle; // +0x0
    char pad4[0xC];
    Vector center; // +0x10

    unsigned int edgeCount; // +0x20
    char pad24[0xC];
    Vector from[16]; // +0x30
    Vector to[16];   // +0x130
    Vector normal[16]; // +0x230, guess
};

// The registry's volume kinds, one per list; lists 0 and 1 also record an owner
class Volume0 : public Volume
{
public:
    int owner; // +0x330
    char pad334[0xC];
    Volume0() __asm__("fn_80462F3C");
};

class Volume1 : public Volume
{
public:
    int owner; // +0x330, the actor id the volume holds
    char pad334[0xC];
    Volume1() __asm__("fn_80462F7C");
};

class Volume2 : public Volume
{
public:
    Volume2() __asm__("fn_80462FBC");
};

class Volume3 : public Volume
{
public:
    Volume3() __asm__("fn_80462FFC");
};

struct Registry {
    int pad;
    char lists[6][0x24]; // +0x4
};

struct PathLink;

struct Mat4 {
    float m[4][4];
};

struct Ent {
    char pad[0x78];
    Mat4 xform; // +0x78
};

struct Hull {
    char pad0[0xB];
    unsigned char planeCount; // +0xB
    char padC[0x78];
    Vector *planes; // +0x84, normal and distance (w)
};

struct Shape {
    Hull *hull; // +0x0
};

struct Colors { // matching_notes 98
    unsigned int c[6];
};

struct PathNode {
    char d[0x30];
};

struct Level {
    char pad0[0x2A];
    unsigned short nodeCount; // +0x2A
    char pad2c[0x12C];
    PathNode *nodes; // +0x158
};

extern "C" {
Level *fn_80430050(void *level);
extern char lbl_8052F060[]; // the level object
}

extern "C" {
void fn_801B60F4(void *list);
int fn_801B6A44(void *list);
void *fn_801B5D3C(void *list, int i);
void fn_801B6040(void *list, void *e);
void *fn_80444984(void *p, int i);
void *fn_80444904(void *p, int i);
int fn_80444740(void *p);
void *fn_80444770(void *p, unsigned short i);
Vector *fn_80444688(void *p);
int fn_804445A4(void *link);
int fn_804445D8(void *link);
void fn_8042DC84(Vector *dst, Vector *src);
float fn_8015E580(Vector *a, Vector *b);
void fn_80429038(Vector *out, Vector *a, Vector *b);
void fn_8042F76C(Vector *v);
float fn_8042EBF4(Vector *a, Vector *b);
extern Vector lbl_80593DE0; // up
int fn_80444D6C(void *link);
int fn_80444DE0(void *node);
void fn_80428FE0(Vector *out, Vector *a, Vector *b);
void fn_80435530(Vector *v, float s);
void fn_801BABC8(Vector *p, Vector *a, Vector *b, Vector *out);
float fn_804290F8(Vector *a, Vector *b);
float fn_801BB7EC(Vector *a, Vector *b, Vector *c, Vector *d, Vector *hit, int e);
void fn_80447C38(Vector *v);
void fn_8042FE08(Vector *v, Vector *dir, float t);
Ent *fn_800ACFA8(int handle);
int fn_800B0D64(Ent *e);
Shape *fn_8009AD80(Ent &e);
int fn_801BBCBC(Vector *a, Vector *b, Vector *point, Vector *dir);
void fn_80433FFC(Vector *v);
float *fn_8042FB28(Vector *v);
void fn_804354B8(Vector *dst, float *src);
void fn_80436100(Vector *v, Mat4 *m);
void fn_80435754(Vector *v, Mat4 *m);
void fn_8042D7B0(Mat4 *m);
void fn_80434420(Mat4 *dst, Mat4 *src);
void fn_8042D8A8(Vector *dst, Vector *src);
void fn_8042D854(Vector *dst, Vector *src);
float fn_8042CE28(unsigned int n);
Ent *fn_80442080(void *ai);
int fn_80462D68(Registry *self);
Volume *fn_80462DB0(Registry *self, int i);
Vector *fn_800B1724(Ent *e);
int fn_8004D2D8(Vector *p, Vector *planes, int count);
typedef int (*Pred)(void *elem, int key);
int fn_801B686C(void *list, int key, Pred pred);
int fn_801B6768(void *list, void *e);
void fn_8009B994(Volume *v, int on);
int fn_80462CD0(Registry *self);
Volume1 *fn_80462D18(Registry *self, int i);
int fn_800B13D8(Ent *e);
void fn_80429090(Vector *out, Vector *a, Vector *dir, float t);
extern Colors lbl_8049B0BC; // 0xFFFF0000, 0xFF00FF00, 0xFF0000FF, 0xFF00FFFF, 0xFFFF00FF, 0xFFFFFF00
void fn_8014601C(Registry *self);

// Predicate: the volume is the one for this handle
int fn_80145CB0(void *elem, int handle)
{
    if (!elem || !handle) {
        return 0;
    }
    Volume *v = (Volume *)elem;
    if (v->handle == handle) {
        return 1;
    }
    return 0;
}

// Predicate: the element is this handle
int fn_80145D24(int elem, int handle)
{
    if (!elem || !handle) {
        return 0;
    }
    if (elem == handle) {
        return 1;
    }
    return 0;
}

void fn_80145D8C(register Registry *self)
{
    fn_801B60F4(self->lists[0]);
    fn_801B60F4(self->lists[1]);
    fn_801B60F4(self->lists[3]);
    fn_801B60F4(self->lists[2]);
    fn_801B60F4(self->lists[4]);
}

void fn_80145DF8(register Registry *self)
{
    int i;
    for (i = 0; i < fn_801B6A44(self->lists[0]); i++) {
        Volume *v = (Volume *)fn_801B5D3C(self->lists[0], i);
        if (v) {
            delete v;
        }
    }
    int j;
    for (j = 0; j < fn_801B6A44(self->lists[1]); j++) {
        Volume *v = (Volume *)fn_801B5D3C(self->lists[1], j);
        if (v) {
            delete v;
        }
    }
    int k;
    for (k = 0; k < fn_801B6A44(self->lists[3]); k++) {
        Volume *v = (Volume *)fn_801B5D3C(self->lists[3], k);
        if (v) {
            delete v;
        }
    }
    int l;
    for (l = 0; l < fn_801B6A44(self->lists[2]); l++) {
        Volume *v = (Volume *)fn_801B5D3C(self->lists[2], l);
        if (v) {
            delete v;
        }
    }
    fn_801B60F4(self->lists[0]);
    fn_801B60F4(self->lists[1]);
    fn_801B60F4(self->lists[3]);
    fn_801B60F4(self->lists[2]);
    fn_801B60F4(self->lists[5]);
}

void fn_80145FE4(register Registry *self)
{
    fn_8014601C(self);
}

// Rebuilds list 5 from the level's path links that climb more than 1 unit
void fn_8014601C(register Registry *self)
{
    fn_801B60F4(self->lists[5]);
    Level *level = fn_80430050(lbl_8052F060);
    for (int i = 0; i < level->nodeCount; i++) {
        PathNode *node = &level->nodes[i];
        void *links = fn_80444984(node, 0);
        for (int j = 0; j < fn_80444740(links); j++) {
            void *link = fn_80444770(links, j);
            Vector from;
            Vector to;
            fn_8042DC84(&from, fn_80444688(fn_80444904(link, 0)));
            fn_8042DC84(&to, fn_80444688(fn_80444984(link, 0)));
            if (to.z - from.z - 1.0f <= 0.0f) {
                continue;
            }
            register float dist = fn_8015E580(&from, &to);
            if (to.z - from.z < 0.0f ? -(to.z - from.z) < dist : to.z - from.z < dist) {
                continue;
            }
            if (fn_804445D8(link)) {
                fn_801B6040(self->lists[5], link);
            } else if (fn_804445A4(link)) {
                Vector dir;
                fn_80429038(&dir, fn_80444688(fn_80444984(link, 0)), fn_80444688(fn_80444904(link, 0)));
                fn_8042F76C(&dir);
                if (fn_8042EBF4(&dir, &lbl_80593DE0) > 0.5) {
                    fn_801B6040(self->lists[5], link);
                }
            }
        }
    }
}

// The list-5 link whose midpoint is above pos and 2 to 5 units from it
void *fn_8014630C(register Registry *self, Vector *pos)
{
    for (int i = 0; i < fn_801B6A44(self->lists[5]); i++) {
        PathLink *link = (PathLink *)fn_801B5D3C(self->lists[5], i);
        if (!link) {
            continue;
        }
        if (fn_80444D6C(link) || fn_80444DE0(fn_80444904(link, 0)) || fn_80444DE0(fn_80444984(link, 0))) {
            continue;
        }
        Vector mid;
        fn_80428FE0(&mid, fn_80444688(fn_80444904(link, 0)), fn_80444688(fn_80444984(link, 0)));
        fn_80435530(&mid, 0.5f);
        if (mid.z <= pos->z) {
            continue;
        }
        float d = fn_8015E580(&mid, pos);
        if (d >= 2.0f && d <= 5.0f) {
            return link;
        }
    }
    return 0;
}

// Whether p is inside the volume's outline (on the inner side of every edge)
int fn_801464E4(register Volume *self, Vector *p)
{
    for (unsigned int i = 0; i < self->edgeCount; i++) {
        Vector *a = &self->from[i];
        Vector *b = &self->to[i];
        float c = (p->y - a->y) * (b->x - a->x) - (p->x - a->x) * (b->y - a->y);
        if (c < 0.0f) {
            continue;
        }
        if (c > 0.0f) {
            return 0;
        } else {
        }
    }
    return 1;
}

// The normal of the outline edge nearest p, flattened to z = 0
void fn_80146604(register Volume *self, Vector *p, Vector *out)
{
    Vector best;
    float bestDist = 3.4028235e+38f;
    for (unsigned int i = 0; i < self->edgeCount; i++) {
        Vector q;
        Vector a;
        Vector b;
        fn_8042DC84(&q, p);
        fn_8042DC84(&a, &self->from[i]);
        fn_8042DC84(&b, &self->to[i]);
        q.z = a.z = b.z = 0.0f;
        Vector c;
        fn_801BABC8(&q, &a, &b, &c);
        float d = fn_804290F8(&c, &q);
        if (d < bestDist) {
            fn_8042DC84(&best, &self->normal[i]);
            bestDist = d;
        }
    }
    fn_8042DC84(out, &best);
    return;
}

// The flat distance from p to the volume's outline
float fn_801467AC(register Volume *self, Vector *p)
{
    float bestDist = 3.4028235e+38f;
    for (unsigned int i = 0; i < self->edgeCount; i++) {
        Vector q;
        Vector a;
        Vector b;
        fn_8042DC84(&q, p);
        fn_8042DC84(&a, &self->from[i]);
        fn_8042DC84(&b, &self->to[i]);
        q.z = a.z = b.z = 0.0f;
        Vector c;
        fn_801BABC8(&q, &a, &b, &c);
        float d = fn_804290F8(&c, &q);
        if (d < bestDist) {
            bestDist = d;
        }
    }
    return bestDist;
}

// Whether the flat segment from-to crosses the volume's outline
int fn_80146918(register Volume *self, Vector *from, Vector *to, Vector *hit)
{
    for (unsigned int i = 0; i < self->edgeCount; i++) {
        Vector p;
        Vector q;
        Vector a;
        Vector b;
        fn_8042DC84(&p, from);
        fn_8042DC84(&q, to);
        fn_8042DC84(&a, &self->from[i]);
        fn_8042DC84(&b, &self->to[i]);
        p.z = q.z = a.z = b.z = 0.0f;
        float t = fn_801BB7EC(&a, &b, &p, &q, hit, 0);
        if (t == 0.0f) {
            return 1;
        }
    }
    return 0;
}

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.text"); // 0x8049B0BC-0x8049B0D4, lbl_8049B0BC

// The outline crossing of the flat segment from-to nearest from; a leftover debug pass computes each edge's midpoint
int fn_80146A88(register Volume *self, Vector *from, Vector *to, Vector *hit)
{
    Vector best;
    float bestDist = 3.4028235e+38f;
    for (unsigned int i = 0; i < self->edgeCount; i++) {
        Colors colors = lbl_8049B0BC;
        Vector mid;
        fn_80447C38(&mid);
        fn_80428FE0(&mid, &self->from[i], &self->to[i]);
        fn_80435530(&mid, 0.5f);
    }
    Vector p;
    Vector q;
    fn_8042DC84(&p, from);
    fn_8042DC84(&q, to);
    p.z = self->from[0].z;
    q.z = p.z;
    for (unsigned int j = 0; j < self->edgeCount; j++) {
        Vector a;
        Vector b;
        Vector e0;
        Vector e1;
        fn_8042DC84(&a, from);
        fn_8042DC84(&b, to);
        fn_8042DC84(&e0, &self->from[j]);
        fn_8042DC84(&e1, &self->to[j]);
        a.z = b.z = e0.z = e1.z = 0.0f;
        Vector h;
        float t = fn_801BB7EC(&e0, &e1, &a, &b, &h, 0);
        float d = fn_804290F8(&h, &a);
        if (t < 0.1f && d < bestDist) {
            fn_8042DC84(&best, &h);
            bestDist = d;
        }
    }
    if (bestDist != 3.4028235e+38f) {
        fn_8042DC84(hit, &best);
        return 1;
    }
    return 0;
}

// Clips the segment a-b (direction dir) to the side of the plane n.p = d below it; 0 if it lies wholly above
int fn_80146DA4(Vector *a, Vector *b, Vector *dir, Vector *n, float d)
{
    float da = fn_8042EBF4(a, n);
    float db = fn_8042EBF4(b, n);
    float t;
    float k;
    if (da > d) {
        if (db > d) {
            return 0;
        }
        k = -fn_8042EBF4(dir, n);
        t = (da - d) / k;
        fn_8042FE08(a, dir, t);
    } else if (db > d) {
        k = fn_8042EBF4(dir, n);
        t = (d - da) / k;
        fn_80429090(b, a, dir, t);
    }
    return 1;
}

// Builds the volume's outline from its entity's hull: one edge per near-vertical plane where it meets the
// downward-facing plane, clipped by the other planes, in world space; the centre is the mean of the edge starts
void fn_80146ED0(Volume *vol)
{
    if (!vol) {
        return;
    }
    Ent *e = fn_800ACFA8(vol->handle);
    if (!e || !fn_800B0D64(e)) {
        return;
    }
    Ent *o = e;
    if (!fn_8009AD80(*o)) {
        return;
    }
    Vector *ground = 0;
    Vector *pl = fn_8009AD80(*o)->hull->planes;
    unsigned int n = fn_8009AD80(*o)->hull->planeCount;
    unsigned int i;
    float dot;
    for (i = 0; i < n; i++, pl++) {
        dot = fn_8042EBF4(pl, &lbl_80593DE0);
        if (dot < -0.5f) {
            ground = pl;
            break;
        }
    }
    if (!ground) {
        return;
    }
    register Hull *hull = fn_8009AD80(*o)->hull;
    pl = hull->planes;
    for (unsigned int j = 0; j < n; j++, pl++) {
        Vector nrm;
        fn_8042DC84(&nrm, pl);
        fn_8042F76C(&nrm);
        dot = fn_8042EBF4(&nrm, &lbl_80593DE0);
        if (dot > -0.25f && dot < 0.25f) {
            Vector point;
            Vector dir;
            if (fn_801BBCBC(pl, ground, &point, &dir)) {
                Vector a;
                Vector b;
                fn_80429090(&a, &point, &dir, 1000.0f);
                fn_80433FFC(&dir);
                fn_80429090(&b, &point, &dir, 1000.0f);
                unsigned int k = vol->edgeCount;
                Vector *from = &vol->from[k];
                Vector *to = &vol->to[k];
                Vector *normal = &vol->normal[k];
                fn_804354B8(from, fn_8042FB28(&a));
                fn_80436100(from, &o->xform);
                fn_804354B8(to, fn_8042FB28(&b));
                fn_80436100(to, &o->xform);
                fn_804354B8(normal, fn_8042FB28(pl));
                fn_80435754(normal, &o->xform);
                normal->z = 0.0f;
                fn_8042F76C(normal);
                vol->edgeCount++;
            }
        }
    }
    Mat4 inv;
    fn_8042D7B0(&inv);
    fn_80434420(&inv, &o->xform);
    register Hull *hull2 = fn_8009AD80(*o)->hull;
    pl = hull2->planes;
    for (unsigned int p = 0; p < n; p++, pl++) {
        Vector a;
        Vector b;
        Vector d;
        for (unsigned int k = 0; k < vol->edgeCount; k++) {
            fn_8042DC84(&a, &vol->from[k]);
            fn_8042DC84(&b, &vol->to[k]);
            fn_80436100(&a, &inv);
            fn_80436100(&b, &inv);
            fn_8042DC84(&d, &b);
            fn_8042D8A8(&d, &a);
            fn_8042F76C(&d);
            dot = fn_8042EBF4(&d, pl);
            if (dot < -0.75f || dot > 0.75f) {
                if (fn_80146DA4(&a, &b, &d, pl, pl->w)) {
                    fn_80436100(&a, &o->xform);
                    fn_80436100(&b, &o->xform);
                    fn_8042DC84(&vol->from[k], &a);
                    fn_8042DC84(&vol->to[k], &b);
                }
            }
        }
    }
    Vector c;
    fn_80447C38(&c);
    for (unsigned int k = 0; k < vol->edgeCount; k++) {
        fn_8042D854(&c, &vol->from[k]);
    }
    fn_80435530(&c, 1.0f / fn_8042CE28(vol->edgeCount));
    c.z = 0.0f;
    fn_8042DC84(&vol->center, &c);
}

// Whether pos (or, without one, the AI's actor) is inside the hull of any list-2 volume
int fn_801475D8(register Registry *self, void *ai, Vector *pos)
{
    Ent *actor = fn_80442080(ai);
    for (int i = 0; i < fn_80462D68(self); i++) {
        Volume *v = fn_80462DB0(self, i);
        if (v) {
            Ent &e = *fn_800ACFA8(v->handle);
            if (&e && fn_800B0D64(&e)) {
                void *level = fn_80430050(lbl_8052F060);
                Mat4 inv;
                fn_8042D7B0(&inv);
                fn_80434420(&inv, &e.xform);
                Vector p;
                if (!pos) {
                    fn_8042DC84(&p, fn_800B1724(actor));
                } else {
                    fn_8042DC84(&p, pos);
                }
                Vector local;
                fn_8042DC84(&local, &p);
                fn_80436100(&local, &inv);
                if (fn_8004D2D8(&local, fn_8009AD80(e)->hull->planes, fn_8009AD80(e)->hull->planeCount)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void fn_801477B0(register Registry *self, int handle, int owner)
{
    if (fn_800ACFA8(handle)) {
        int idx = fn_801B686C(self->lists[0], handle, fn_80145CB0);
        if (idx == -1) {
            Volume0 *v = new Volume0;
            v->handle = handle;
            v->owner = owner;
            fn_80146ED0(v);
            fn_801B6040(self->lists[0], v);
            fn_8009B994(v, 0);
        }
    }
}

void fn_80147884(register Registry *self, int handle)
{
    int idx = fn_801B686C(self->lists[0], handle, fn_80145CB0);
    if (idx != -1) {
        Volume0 *v = (Volume0 *)fn_801B5D3C(self->lists[0], idx);
        if (!v) {
            return;
        }
        Ent &e = *fn_800ACFA8(handle);
        if (&e && fn_800B0D64(&e)) {
            fn_8009B994(v, 1);
        }
        idx = fn_801B6768(self->lists[0], v);
        delete v;
    }
}

void fn_80147968(register Registry *self, int owner, int handle)
{
    if (fn_800ACFA8(handle)) {
        int idx = fn_801B686C(self->lists[1], handle, fn_80145CB0);
        Volume1 *v = new Volume1;
        v->handle = handle;
        v->owner = owner;
        fn_80146ED0(v);
        fn_801B6040(self->lists[1], v);
    }
}

void fn_80147A20(register Registry *self, int owner, int handle)
{
    int idx = fn_801B686C(self->lists[1], handle, fn_80145CB0);
    if (idx != -1) {
        Volume1 *v = (Volume1 *)fn_801B5D3C(self->lists[1], idx);
        if (!v) {
            return;
        }
        idx = fn_801B6768(self->lists[1], v);
        delete v;
    }
}

// The list-1 volume that holds this actor
Volume1 *fn_80147ACC(register Registry *self, Ent *actor)
{
    for (int i = 0; i < fn_80462CD0(self); i++) {
        Volume1 *v = fn_80462D18(self, i);
        if (!v) {
            continue;
        }
        if (v->owner == fn_800B13D8(actor)) {
            return v;
        }
    }
    return 0;
}

void fn_80147B88(register Registry *self, int handle)
{
    if (fn_800ACFA8(handle)) {
        int idx = fn_801B686C(self->lists[2], handle, fn_80145CB0);
        if (idx == -1) {
            Volume2 *v = new Volume2;
            v->handle = handle;
            fn_80146ED0(v);
            fn_801B6040(self->lists[2], v);
        }
    }
}

void fn_80147C40(register Registry *self, int handle)
{
    if (fn_800ACFA8(handle)) {
        int idx = fn_801B686C(self->lists[3], handle, fn_80145CB0);
        if (idx == -1) {
            Volume3 *v = new Volume3;
            v->handle = handle;
            fn_80146ED0(v);
            fn_801B6040(self->lists[3], v);
        }
    }
}

// List 4 holds bare handles
void fn_80147CF8(register Registry *self, int handle)
{
    if (!handle) {
        return;
    }
    void *e = fn_800ACFA8(handle);
    if (!e) {
        return;
    }
    fn_801B6040(self->lists[4], (void *)handle);
}

void fn_80147D68(register Registry *self, int handle)
{
    int idx = fn_801B686C(self->lists[4], handle, (Pred)fn_80145D24);
    if (idx != -1) {
        idx = fn_801B6768(self->lists[4], (void *)handle);
    }
}
}
