// Reads one model's body from a .ngm bundle into `model`; layout in docs/characters.md section 4.

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

struct Stream {
    void *data;            // +0x0, count2 * stride bytes
    void *p4;              // +0x4, count * 6 bytes
    void *p8;              // +0x8, count * 6 bytes, type > 2 only
    unsigned short count2; // +0xC
    unsigned short type;   // +0xE, index into lbl_806707F8 (stride)
    int count;             // +0x10
    int pad14;
};

struct Node {
    Vector a;          // +0x0
    Vector b;          // +0x10
    unsigned char b20; // +0x20
    unsigned char b21; // +0x21
    char pad22[0x30 - 0x22];
};

struct Bone {
    Vector rows[4];     // +0x0
    unsigned char b40;  // +0x40
    unsigned char b41;  // +0x41
    unsigned short u42; // +0x42
    char pad44[0x50 - 0x44];
};

struct Model;

struct Mesh {
    void *part;              // +0x0
    Model *owner;            // +0x4
    int u8;                  // +0x8
    int offC;                // +0xC
    int off10;               // +0x10
    unsigned short u14;      // +0x14
    unsigned short u16;      // +0x16
    int n18;                 // +0x18
    char pad1C[0x38 - 0x1C];
    int u38;                 // +0x38
    char pad3C;
    unsigned char b3D;       // +0x3D
    unsigned char b3E;       // +0x3E
    unsigned char b3F;       // +0x3F
    unsigned char b40;       // +0x40
    char pad41;
    unsigned char n42;       // +0x42
    char pad43[0x48 - 0x43];
    unsigned char b48[0x14]; // +0x48
};

struct Model {
    unsigned int flags;       // +0x0
    unsigned char nMeshes;    // +0x4
    unsigned char nStreams;   // +0x5
    unsigned short refs;      // +0x6
    unsigned char nParts;     // +0x8
    unsigned char nNodes;     // +0x9
    char padA[0x10 - 0xA];
    int nIndices;             // +0x10
    void *p14;                // +0x14
    Mesh *meshes;             // +0x18
    Stream streams[4];        // +0x1C
    unsigned short *indices;  // +0x7C
    Node *nodes;              // +0x80
    char pad84[0x4];
    void **parts;             // +0x88
    char name[0x20];          // +0x8C
    int memSize;              // +0xAC
    char bB0[0x20];           // +0xB0
    char padD0[0x150 - 0xD0];
    Bone *bones;              // +0x150
    unsigned int nBones;      // +0x154
    unsigned short u158;      // +0x158
    unsigned short u15A;      // +0x15A
};

struct ModelBundle;

#define ALIGN32(x) (((x) + 0x1F) & ~0x1F)

extern "C" {
void *memset(void *dst, int c, unsigned n);
int fn_801A8B60(void *dst, int size, int count, void *file);
void *fn_801AC988(unsigned size, const char *tag, int line, int align);
void *fn_801AC9EC(unsigned size, const char *tag, int line, int align, int a, int b);
void *fn_801AD324(unsigned size, const char *tag, int line);
void *fn_80234628(char *name, int flags);
int fn_802360C4(void *part);
void *fn_8042FB28(Vector *v);
void fn_8042DCC0(void *m);
void fn_801A2B40(Model *model);
void fn_801A3784(Model *model);
extern const char lbl_804A2308[];
extern const float lbl_804A231C[];
extern const unsigned char lbl_806707F8[];
extern int lbl_8066C5B8;
}

extern "C" int fn_80221C08(register Model *model, void *file, ModelBundle *bundle)
{
    unsigned int i;
    int unused14;
    int stride;
    unsigned char b;
    int index;
    unsigned short u;
    char name[0x20];
    int unused48[2];
    Stream *s;
    Node *node;
    int sum;
    int unused5C;
    int offsets[4];
    Mesh *m;
    Bone *bone;

    fn_801A8B60(model->name, 1, 0x20, file);
    fn_801A8B60(&model->nStreams, 1, 1, file);
    fn_801A8B60(model, 4, 1, file);
    fn_801A8B60(model->bB0, 0x20, 1, file);
    model->flags |= 0x400;
    for (i = 0; i < model->nStreams; i++) {
        s = &model->streams[i];
        fn_801A8B60(&b, 1, 1, file);
        s->type = b;
        fn_801A8B60(&s->count, 4, 1, file);
        s->p4 = fn_801AD324(s->count * 6, lbl_804A2308, 0x1D1);
        lbl_8066C5B8 += ALIGN32(s->count * 6);
        model->memSize += ALIGN32(s->count * 6);
        fn_801A8B60(s->p4, 6, s->count, file);
        stride = lbl_806707F8[s->type];
        fn_801A8B60(&s->count2, 2, 1, file);
        s->data = fn_801AC9EC(s->count2 * stride, lbl_804A2308, 0x1D9, 2, 0x20, 0);
        fn_801A8B60(s->data, stride, s->count2, file);
        lbl_8066C5B8 += ALIGN32(s->count2 * stride);
        model->memSize += ALIGN32(s->count2 * stride);
        if (s->type > 2) {
            stride = 6;
            s->p8 = fn_801AC988(stride * s->count, lbl_804A2308, 0x1E4, 2);
            fn_801A8B60(s->p8, stride, s->count, file);
            lbl_8066C5B8 += ALIGN32(stride * s->count);
            model->memSize += ALIGN32(stride * s->count);
        } else {
            s->p8 = 0;
        }
    }
    fn_801A8B60(&u, 2, 1, file);
    model->p14 = fn_801AC9EC(u * 4, lbl_804A2308, 0x1F1, 2, 0x20, 0);
    model->memSize += ALIGN32(u * 4);
    fn_801A8B60(model->p14, 4, u, file);
    fn_801A8B60(&model->nIndices, 4, 1, file);
    model->indices = (unsigned short *)fn_801AD324(model->nIndices * 2, lbl_804A2308, 0x1F7);
    model->memSize += ALIGN32(model->nIndices * 2);
    model->flags |= 0x800;
    if (fn_801A8B60(model->indices, 2, model->nIndices, file) != model->nIndices)
        return 0;
    for (i = 0; i < model->nParts; i++) {
        fn_801A8B60(name, 1, 0x20, file);
        model->parts[i] = fn_80234628(name, 0);
        if (model->parts[i] && fn_802360C4(model->parts[i]))
            model->flags |= 4;
    }
    for (i = 0; i < model->nNodes; i++) {
        node = &model->nodes[i];
        fn_801A8B60(fn_8042FB28(&node->a), 0x10, 1, file);
        fn_801A8B60(fn_8042FB28(&node->b), 0x10, 1, file);
        fn_801A8B60(&node->b20, 1, 1, file);
        fn_801A8B60(&node->b21, 1, 1, file);
        node->a.w = lbl_804A231C[0];
        node->b.w = lbl_804A231C[0];
    }
    fn_801A8B60(&model->u158, 2, 1, file);
    fn_801A8B60(&model->u15A, 2, 1, file);
    sum = 0;
    memset(offsets, 0, 0x10);
    for (i = 0; i < model->nMeshes; i++) {
        m = &model->meshes[i];
        m->owner = model;
        fn_801A8B60(&index, 4, 1, file);
        m->part = model->parts[index];
        fn_801A8B60(&m->b3D, 1, 1, file);
        fn_801A8B60(&m->u14, 2, 1, file);
        fn_801A8B60(&m->u16, 2, 1, file);
        fn_801A8B60(&u, 2, 1, file);
        m->n18 = u;
        m->offC = sum;
        m->off10 = sum + m->u14;
        sum += m->u14 + m->u16;
        fn_801A8B60(&m->b3E, 1, 1, file);
        fn_801A8B60(&m->b3F, 1, 1, file);
        fn_801A8B60(&m->b40, 1, 1, file);
        fn_801A8B60(&m->n42, 1, 1, file);
        fn_801A8B60(m->b48, 1, m->n42, file);
        m->u8 = offsets[m->b3D];
        offsets[m->b3D] += m->n18;
        m->u38 = 0;
    }
    Vector v;
    for (i = 0; i < model->nBones; i++) {
        bone = &model->bones[i];
        fn_801A8B60(&bone->b40, 1, 1, file);
        fn_801A8B60(&bone->b41, 1, 1, file);
        fn_801A8B60(&bone->u42, 2, 1, file);
        fn_8042DCC0(bone);
        fn_801A8B60(&bone->rows[0], 0x10, 1, file);
        fn_801A8B60(&bone->rows[1], 0x10, 1, file);
        fn_801A8B60(&bone->rows[2], 0x10, 1, file);
        fn_801A8B60(&bone->rows[3], 0x10, 1, file);
    }
    model->refs = 1;
    model->flags &= ~0x200;
    fn_801A2B40(model);
    fn_801A3784(model);
    return 1;
}
