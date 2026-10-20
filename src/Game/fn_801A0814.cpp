// Builds a model from a .nod header, returns the .nod model <name> from the model registry (loading it on a miss), and parses one .nod file; layout in docs/characters.md section 4.

#define SWAP32(x) (((unsigned)(x) >> 24) | (((unsigned)(x) >> 8) & 0xFF00) | (((x) & 0xFF00) << 8) | ((x) << 24))

struct Model {
    unsigned int flags;     // +0x0
    unsigned char nMeshes;  // +0x4
    unsigned char nStreams; // +0x5
    unsigned short refs;    // +0x6
    unsigned char nParts;   // +0x8
    unsigned char nNodes;   // +0x9
    char padA[0x10 - 0xA];
    int nIndices;           // +0x10
    char pad14[0x4];
    void *meshes;           // +0x18, 0x5C each
    char pad1C[0x80 - 0x1C];
    void *nodes;            // +0x80, 0x30 each
    char pad84[0x4];
    void **parts;           // +0x88
    char name[0x20];        // +0x8C
    unsigned int memSize;   // +0xAC
};

struct NodHeader {
    unsigned int bounds[8]; // +0x0, a Segment (two Vectors)
    unsigned int version;   // +0x20
    unsigned char count;    // +0x24, parts
    unsigned char nNodes;   // +0x25
    unsigned char nStreams; // +0x26
    unsigned char nMeshes;  // +0x27
    unsigned int flags;     // +0x28
    int nIndices;           // +0x2C
    struct {
        unsigned int a;
        unsigned int b;
    } pairs[4];             // +0x30
    unsigned int u50[4];    // +0x50
    char pad60[0x10];
};

extern "C" {
void *memset(void *dst, int c, unsigned n);
void *fn_801AC9EC(unsigned size, const char *tag, int line, int align, int a, int b);
char *strncpy(char *dst, const char *src, unsigned n);
void OSReport(const char *fmt, ...);
int fn_801B3F00(char *path);
int fn_801B3FBC(char *path, const char *ext);
void *fn_801B48AC(void *registry, char *name);
int fn_80465FF4(Model *model);
void fn_801A33E0(Model *model);
void fn_801A8E54(void *file, const char *fmt, ...);
void fn_801A9334(void *file);
void *fn_801A8368(const char *path, const char *mode, int flags);
Model *fn_801A09F0(void *file, char *path, unsigned int flags);
void fn_801A875C(void *file);
void fn_80466054(NodHeader *hdr);
void fn_801A953C(void *file);
int fn_801A8B60(void *dst, int size, int count, void *file);
void fn_8042FC74(void *v);
Model *fn_801A05CC(NodHeader *hdr);
int fn_80220D54(Model *model, void *file, NodHeader *hdr, unsigned int flags);
int fn_802360C4(void *part);
void fn_801B4628(void *registry, const char *name, void *item);
void fn_801A15C0(Model *model);
extern const char lbl_8049D410[];
extern const char lbl_8049D420[];
extern const char lbl_8049D424[];
extern const char lbl_8049D440[];
extern const char lbl_8049D448[];
extern const char lbl_8049D44C[];
extern void *lbl_8066C5CC;
extern void *lbl_8066C5D8;
extern int lbl_8066C5C0;
extern unsigned int lbl_8066C5BC;
extern unsigned int lbl_8066C5D4;
}

extern "C" Model *fn_801A05CC(NodHeader *hdr)
{
    char *p;
    Model *model;
    unsigned int size;
    int nNodes;

    nNodes = hdr->nNodes > 1 ? hdr->nNodes : 1;
    size = 0x190;
    size += nNodes * 0x30;
    size += hdr->nMeshes * 0x5C;
    size += hdr->count * sizeof(void *);
    size += 0x10;
    p = (char *)fn_801AC9EC(size, lbl_8049D410, 0x12F, 2, 0x10, 0);
    if (!p)
        return 0;
    memset(p, 0, size);
    model = (Model *)p;
    p += 0x190;
    {
        unsigned int a = (unsigned int)p;
        a = (a + 0xF) & ~0xF;
        p = (char *)a;
    }
    model->nodes = p;
    p += nNodes * 0x30;
    model->meshes = p;
    p += hdr->nMeshes * 0x5C;
    if (hdr->count)
        model->parts = (void **)p;
    p += hdr->count * sizeof(void *);
    model->nNodes = hdr->nNodes;
    model->flags = hdr->flags;
    model->nMeshes = hdr->nMeshes;
    model->nParts = hdr->count;
    model->nIndices = hdr->nIndices;
    model->nStreams = hdr->nStreams;
    model->refs = 0;
    model->memSize = size;
    return model;
}

extern "C" Model *fn_801A0814(const char *name, unsigned int flags)
{
    void *file = 0;
    Model *model = 0;
    char path[0x80];
    int hasExt;

    strncpy(path, name, 0x80);
    path[0x7F] = 0;
    hasExt = fn_801B3F00(path);
    if (!hasExt)
        fn_801B3FBC(path, lbl_8049D420);
    model = (Model *)fn_801B48AC(lbl_8066C5CC, path);
    if (model) {
        model->refs++;
        if (fn_80465FF4(model))
            fn_801A33E0(model);
        return model;
    }
    OSReport(lbl_8049D424, name);
    if (lbl_8066C5D8) {
        if (flags & 0x10)
            fn_801A8E54(lbl_8066C5D8, lbl_8049D440, path);
        else
            fn_801A8E54(lbl_8066C5D8, lbl_8049D448, path);
        fn_801A9334(lbl_8066C5D8);
    }
    file = fn_801A8368(path, lbl_8049D44C, 2);
    if (!file)
        return 0;
    model = fn_801A09F0(file, path, flags);
    if (file)
        fn_801A875C(file);
    return model;
}

extern "C" Model *fn_801A09F0(void *file, char *path, unsigned int flags)
{
    NodHeader hdr;
    Model *model;
    int i;
    unsigned char j;

    fn_80466054(&hdr);
    model = 0;
    fn_801A953C(file);
    if (!fn_801A8B60(&hdr, 0x70, 1, file))
        goto bad;
    hdr.version = SWAP32(hdr.version);
    hdr.nIndices = SWAP32(hdr.nIndices);
    hdr.flags = SWAP32(hdr.flags);
    fn_8042FC74(&hdr.bounds[0]);
    fn_8042FC74(&hdr.bounds[4]);
    for (i = 0; i <= 3; i++) {
        hdr.pairs[i].b = SWAP32(hdr.pairs[i].b);
        hdr.pairs[i].a = SWAP32(hdr.pairs[i].a);
    }
    for (i = 0; i <= 3; i++)
        hdr.u50[i] = SWAP32(hdr.u50[i]);
    if (hdr.version < 10)
        goto old;
    if (hdr.version != 10)
        goto old;
    if (hdr.count > 0x40)
        goto bad;
    model = fn_801A05CC(&hdr);
    if (!model)
        goto fail;
    strncpy(model->name, path, 0x20);
    model->name[0x1F] = 0;
    if (!fn_80220D54(model, file, &hdr, flags))
        goto fail;
    lbl_8066C5C0++;
    lbl_8066C5BC += model->memSize;
    lbl_8066C5D4 = lbl_8066C5D4 > lbl_8066C5BC ? lbl_8066C5D4 : lbl_8066C5BC;
    if (!(flags & 1)) {
        for (j = 0; j < model->nParts; j++) {
            if (model->parts[j] && fn_802360C4(model->parts[j])) {
                model->flags |= 4;
                break;
            }
        }
    }
    if (flags & 0x800)
        model->flags |= 0x8000;
    else
        fn_801B4628(lbl_8066C5CC, model->name, model);
    if (flags & 2)
        model->refs = 1;
    return model;
bad:
    goto fail;
old:
    goto fail;
fail:
    if (model) {
        model->refs = 1;
        fn_801A15C0(model);
    }
    return 0;
}
