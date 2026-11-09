// GX vertex setup for skinned streams.

class Vector
{
public:
    float x, y, z, w;
} __attribute__((aligned(8)));

struct Stream {
    void *vertices;        // +0x00
    void *refs;            // +0x04
    char pad8[0x4];
    unsigned short count;  // +0x0C
    unsigned short type;   // +0x0E
    unsigned int refCount; // +0x10
    char pad14[0x4];
};

struct Model {
    char pad0[0x14];
    void *uvs;             // +0x14
    char pad18[0x4];
    Stream streams[4];     // +0x1C
};

struct Mesh {
    char pad0[0x4];
    Model *model;          // +0x04
    char pad8[0x35];
    unsigned char stream;  // +0x3D
};

struct Instance {
    Model *model;          // +0x00
    char pad4[0xF8];
    Vector *skinned[4];    // +0xFC
};

struct Renderer;

extern "C" {
extern char lbl_80594E00[];
void fn_8046EA4C(char *p);
void fn_8042F534(char *p, int a);
void GXClearVtxDesc();
int fn_8043D694(Model *m);
void GXSetVtxDesc(int attr, int type);
void GXSetArray(int attr, void *base, int stride);

int fn_80223B50(register Renderer *self, Mesh *mesh, void *p, Instance *inst)
{
    int pad[12];
    fn_8046EA4C(lbl_80594E00);
    fn_8042F534(lbl_80594E00, 1);
    GXClearVtxDesc();
    if (!fn_8043D694(mesh->model)) {
        GXSetVtxDesc(9, 1);
        GXSetVtxDesc(10, 1);
        GXSetVtxDesc(13, 1);
    } else {
        GXSetVtxDesc(9, 3);
        GXSetVtxDesc(10, 3);
        GXSetVtxDesc(13, 3);
        GXSetArray(9, inst->skinned[mesh->stream], 0x10);
        GXSetArray(10, inst->skinned[mesh->stream] + inst->model->streams[mesh->stream].count, 0x10);
        GXSetArray(13, mesh->model->uvs, 4);
    }
    return 0;
}

int fn_80223CC4(register Renderer *self, Mesh *mesh, void *p, Instance *inst)
{
    int pad[12];
    fn_8046EA4C(lbl_80594E00);
    fn_8042F534(lbl_80594E00, 1);
    GXClearVtxDesc();
    if (!fn_8043D694(inst->model)) {
        GXSetVtxDesc(9, 1);
        GXSetVtxDesc(10, 1);
        GXSetVtxDesc(13, 1);
    } else {
        GXSetVtxDesc(9, 3);
        GXSetVtxDesc(10, 3);
        GXSetVtxDesc(13, 3);
        GXSetArray(9, inst->skinned[mesh->stream], 0x10);
        GXSetArray(10, inst->skinned[mesh->stream] + inst->model->streams[mesh->stream].count, 0x10);
        GXSetArray(13, mesh->model->uvs, 4);
    }
    return 0;
}
}
