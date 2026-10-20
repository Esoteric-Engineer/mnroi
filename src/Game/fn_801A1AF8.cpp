// Allocates and fills a model's instance ("Models:Instance"); docs/characters.md section 4.
// The float pool is dtk's lbl_8049D478-lbl_8049D484 (extern_pool).

struct Stream {
    char pad0[0x14];
    void *data; // +0x14
};

struct Mesh {
    void *part; // +0x0
    char pad4[0x5C - 0x4];
};

struct Model {
    unsigned int flags;     // +0x0
    unsigned char nMeshes;  // +0x4
    unsigned char nStreams; // +0x5
    unsigned short refs;    // +0x6
    unsigned char nParts;   // +0x8
    unsigned char nNodes;   // +0x9
    char padA[0x18 - 0xA];
    Mesh *meshes;           // +0x18
    Stream streams[4];      // +0x1C
    char pad7C[0xB0 - 0x7C];
    float bounds[8];        // +0xB0, a Segment (two Vectors)
};

struct Instance {
    Model *model;        // +0x0
    unsigned int flags;  // +0x4
    float f8;            // +0x8
    unsigned char bC;    // +0xC
    unsigned char bD;    // +0xD
    char padE[0x20 - 0xE];
    float scale[4];      // +0x20
    float radius;        // +0x30
    float f34;           // +0x34
    int u38;             // +0x38
    int u3C;             // +0x3C
    char pad40[0x48 - 0x40];
    float f48;           // +0x48
    char pad4C[0x54 - 0x4C];
    float f54;           // +0x54
    float f58;           // +0x58
    float f5C;           // +0x5C
    char pad60[0x4];
    char *matrices;      // +0x64, 0x40 per node
    char pad68[0xA8 - 0x68];
    char *nodeVecs;      // +0xA8, 0x10 per node
    void **meshParts;    // +0xAC, one per mesh
    int uB0;             // +0xB0
    char padB4[0x4];
    void *streams[4];    // +0xB8
    char padC8[0xD0 - 0xC8];
    char bD0[0x10];      // +0xD0
    char padE0[0xE6 - 0xE0];
    short sE6;           // +0xE6
};

extern "C" {
void *memset(void *dst, int c, unsigned n);
void *fn_801AC9EC(unsigned size, const char *tag, int line, int align, int a, int b);
void fn_80428FA8(void *v, float x, float y, float z);
float fn_804290F8(void *a, void *b);
void fn_80445048(Instance *inst);
int fn_80466024(Model *model);
extern const char lbl_8049D468[];
extern unsigned int lbl_8066C5BC;
extern int lbl_8066C5C4;
}

extern "C" Instance *fn_801A1AF8(register Model *model)
{
    Instance *inst;
    char *mem;
    unsigned int size;
    unsigned int p;
    unsigned int i;
    unsigned int base;

    base = 0x1C0;
    base = (base + 0xF) & ~0xF;
    size = model->nNodes * 0x40 + base + model->nNodes * 0x10 + model->nMeshes * 4 + 0x10;
    mem = (char *)fn_801AC9EC(size, lbl_8049D468, 0x40E, 2, 0x10, 0);
    if (!mem)
        goto fail;
    lbl_8066C5BC += size;
    lbl_8066C5C4++;
    memset(mem, 0, size);
    inst = (Instance *)mem;
    mem += 0x1C0;
    p = (unsigned int)mem;
    p = (p + 0xF) & ~0xF;
    mem = (char *)p;
    inst->f48 = 1.0f;
    inst->f54 = 1.0f;
    inst->f58 = 1.0f;
    inst->f5C = 1.0f;
    inst->f8 = 1.0f;
    fn_80428FA8(inst->scale, 1.0f, 1.0f, 1.0f);
    memset(inst->bD0, 0, 0x10);
    inst->f34 = 0.0f;
    inst->bC = 0;
    inst->bD = 0x3F;
    inst->uB0 = 0;
    inst->flags = fn_80466024(model) ? 0x40 : 0;
    inst->u38 = inst->u3C = 0;
    fn_80445048(inst);
    inst->sE6 = -1;
    inst->radius = fn_804290F8(&model->bounds[4], &model->bounds[0]) * 0.2f + 0.5f;
    inst->matrices = mem;
    mem += model->nNodes * 0x40;
    inst->nodeVecs = mem;
    mem += model->nNodes * 0x10;
    inst->meshParts = (void **)mem;
    mem += model->nMeshes * 4;
    inst->model = model;
    for (i = 0; i < model->nStreams; i++) {
        if (model->streams[i].data) {
            inst->streams[i] = model->streams[i].data;
            inst->flags |= 0x401;
        }
    }
    for (i = 0; i < model->nMeshes; i++)
        inst->meshParts[i] = model->meshes[i].part;
    return inst;
fail:
    return 0;
}
