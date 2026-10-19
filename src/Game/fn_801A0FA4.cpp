// Builds an unnamed model ("AUTO_%x") and its planes from an open .nod file, then its instance; docs/characters.md section 4.

#define SWAP32(x) (((unsigned)(x) >> 24) | (((unsigned)(x) >> 8) & 0xFF00) | (((x) & 0xFF00) << 8) | ((x) << 24))

struct Plane {
    float v[4]; // {x, y, z, d}
};

struct Model {
    unsigned int flags;     // +0x0
    char pad4[0x2];
    unsigned short refs;    // +0x6
    unsigned char nParts;   // +0x8
    char pad9[0x2];
    unsigned char nPlanes;  // +0xB
    char padC[0x84 - 0xC];
    Plane *planes;          // +0x84
    void **parts;           // +0x88
    char name[0x20];        // +0x8C
    unsigned int memSize;   // +0xAC
};

struct Instance {
    char pad0[0x4];
    unsigned int flags; // +0x4
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
int sprintf(char *dst, const char *fmt, ...);
void *fn_801AC988(unsigned size, const char *tag, int line, int align);
void fn_80466054(NodHeader *hdr);
int fn_801A8B60(void *dst, int size, int count, void *file);
void fn_8042FC74(void *v);
Model *fn_801A05CC(NodHeader *hdr);
int fn_80220D54(Model *model, void *file, NodHeader *hdr, unsigned int flags);
int fn_802360C4(void *part);
Instance *fn_801A1AF8(Model *model);
void fn_801A2B40(Model *model);
void fn_801A15C0(Model *model);
extern const char lbl_8049D450[];
extern const char lbl_8049D458[];
extern int lbl_8066C5C0;
extern unsigned int lbl_8066C5BC;
}

extern "C" Instance *fn_801A0FA4(void *file, unsigned int flags)
{
    Model *model = 0;
    Instance *inst = 0;
    NodHeader hdr;
    unsigned int i;
    unsigned int n;

    fn_80466054(&hdr);
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
    model = fn_801A05CC(&hdr);
    if (!model)
        goto fail;
    sprintf(model->name, lbl_8049D450, model);
    model->refs = 1;
    fn_80220D54(model, file, &hdr, flags | 0x200);
    if (model->parts) {
        for (i = 0; i < model->nParts; i++) {
            if (model->parts[i] && fn_802360C4(model->parts[i])) {
                model->flags |= 4;
                break;
            }
        }
    }
    fn_801A8B60(&n, 4, 1, file);
    n = SWAP32(n);
    model->nPlanes = n;
    if (model->nPlanes) {
        model->planes = (Plane *)fn_801AC988(model->nPlanes * sizeof(Plane), lbl_8049D458, 0x292, 2);
        fn_801A8B60(model->planes, sizeof(Plane), model->nPlanes, file);
        for (i = 0; i < model->nPlanes; i++)
            fn_8042FC74(&model->planes[i]);
        model->memSize += (model->nPlanes * sizeof(Plane) + 0x1F) & ~0x1F;
    }
    lbl_8066C5BC += model->memSize;
    lbl_8066C5C0++;
    inst = fn_801A1AF8(model);
    if (inst)
        inst->flags |= 0x100000;
    fn_801A2B40(model);
    return inst;
bad:
    goto fail;
fail:
    if (model)
        fn_801A15C0(model);
    return 0;
}
