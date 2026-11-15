// CPU skinning: transforms a stream's vertices and normals by the node palette into a scratch buffer, once per frame (docs/characters.md section 4).

class Vector
{
public:
    float x, y, z, w;
    Vector();
} __attribute__((aligned(8)));

struct Matrix {
    float m[4][4];
};

struct Point {
    float x, y, z;
};

// Stream type 1 and 4: rigid, one node per vertex.
struct RigidVertex {
    Point pos;             // +0x00
    int node;              // +0x0C
};

// Stream type 2 and 5: three weights and three nodes per vertex.
struct SkinVertex {
    Point pos;             // +0x00
    float weight[3];       // +0x0C
    unsigned char node[3]; // +0x18
};

struct RenderVertex {
    unsigned short vertex; // +0x00
    unsigned short normal; // +0x02
    unsigned short uv;     // +0x04
};

struct Stream {
    void *vertices;        // +0x00
    RenderVertex *refs;    // +0x04
    char pad8[0x4];
    unsigned short count;  // +0x0C
    unsigned short type;   // +0x0E
    unsigned int refCount; // +0x10
    char pad14[0x4];
};

struct Model {
    char pad0[0x1C];
    Stream streams[4];     // +0x1C
};

struct Instance {
    Model *model;          // +0x00
    char pad4[0xF8];
    Vector *skinned[4];    // +0xFC, this frame's vertices of each stream
    int stamp[4];          // +0x10C, frame they were built on
};

extern "C" {
extern int lbl_8066C7D8;          // frame counter
extern Matrix *lbl_8066C810;      // the node palette being drawn
extern unsigned int lbl_8066C814; // used bytes of the scratch buffer
extern Point *lbl_8066F5A8;       // Misc/NormalTable.ngn
extern char lbl_80595280[];       // the scratch buffer
extern char lbl_804A2340[];
int fn_8043D694(Model *m);
void OSReport(char *fmt, ...);
void DCStoreRange(void *p, unsigned int n);
void fn_804708F8(void *out, Point *p, Matrix *m); // p * m
void fn_804709C8(void *out, Point *p, Matrix *m); // p * m, without the translation
void fn_8042FDBC(void *out, Vector *v, float f);  // out = v * f
void fn_8042FE08(void *out, Vector *v, float f);  // out += v * f

void fn_802244BC(Instance *self, unsigned char n)
{
    if (!fn_8043D694(self->model))
        return;
    if (self->stamp[n] == lbl_8066C7D8)
        return;
    Stream *s = &self->model->streams[n];
    if (s->type == 0 || s->type == 3)
        return;
    unsigned int size = (s->refCount + s->count) * 0x10;
    size += 0x20;
    if (lbl_8066C814 + size > 0x80000) {
        OSReport(lbl_804A2340);
        lbl_8066C814 = 0;
    }
    Vector *out = (Vector *)(lbl_80595280 + lbl_8066C814);
    lbl_8066C814 += size;
    self->skinned[n] = out;
    self->stamp[n] = lbl_8066C7D8;
    unsigned int i;
    switch (s->type) {
    case 1:
    case 4: {
        RigidVertex *base = (RigidVertex *)s->vertices;
        RigidVertex *v = base;
        RenderVertex *r = s->refs;
        for (i = 0; i < s->count; i++, v++, out++)
            fn_804708F8(out, &v->pos, &lbl_8066C810[v->node]);
        for (i = 0; i < s->refCount; i++, r++, out++)
            fn_804709C8(out, &lbl_8066F5A8[r->normal], &lbl_8066C810[base[r->vertex].node]);
        break;
    }
    case 2:
    case 5: {
        SkinVertex *base = (SkinVertex *)s->vertices;
        SkinVertex *v = base;
        RenderVertex *r = s->refs;
        Vector tmp;
        for (i = 0; i < s->count; i++, v++, out++) {
            fn_804708F8(&tmp, &v->pos, &lbl_8066C810[v->node[0]]);
            fn_8042FDBC(out, &tmp, v->weight[0]);
            fn_804708F8(&tmp, &v->pos, &lbl_8066C810[v->node[1]]);
            fn_8042FE08(out, &tmp, v->weight[1]);
            fn_804708F8(&tmp, &v->pos, &lbl_8066C810[v->node[2]]);
            fn_8042FE08(out, &tmp, v->weight[2]);
        }
        for (i = 0; i < s->refCount; i++, r++, out++)
            fn_804709C8(out, &lbl_8066F5A8[r->normal], &lbl_8066C810[base[r->vertex].node[0]]);
        break;
    }
    }
    DCStoreRange(self->skinned[n], size);
}
}
