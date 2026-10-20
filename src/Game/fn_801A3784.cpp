// Builds a model's bone distance and index tables from its node chain; docs/characters.md section 4.

struct Node {
    float pos[4];      // +0x0, offset from the parent node
    char pad10[0x20 - 0x10];
    signed char parent; // +0x20
    char pad21[0x30 - 0x21];
};

struct Model {
    char pad0[0x9];
    unsigned char nNodes;           // +0x9
    char padA[0x80 - 0xA];
    Node *nodes;                    // +0x80
    char pad84[0x15A - 0x84];
    unsigned short u15A;            // +0x15A
    float *dis;                     // +0x15C
    unsigned char *boneIndices;     // +0x160
    unsigned char *parBoneIndices;  // +0x164
    float disSum;                   // +0x168
    unsigned int nDis;              // +0x16C
    float *dis2;                    // +0x170
    unsigned char *boneIndices2;    // +0x174
    unsigned char *parBoneIndices2; // +0x178
    float disSum2;                  // +0x17C
    unsigned int nDis2;             // +0x180
};

#define MIN(a, b) ((a) < (b) ? (a) : (b))

extern "C" {
void *fn_801AC988(unsigned size, const char *tag, int line, int align);
float fn_80434040(Node *v);
extern const char lbl_8049D540[];
extern const char lbl_8049D550[];
extern const char lbl_8049D568[];
}

extern "C" void fn_801A3784(register Model *model)
{
    int first = 1;
    int i;
    int parent;
    int end;
    int j;

    model->disSum = 0.0f;
    model->nDis = 0;
    end = MIN(model->nNodes, model->u15A) - 3;
    for (i = first; i < end; i++) {
        parent = model->nodes[i].parent;
        if (parent <= 0 && i > 1)
            continue;
        model->nDis++;
    }
    model->disSum = 0.0f;
    model->disSum2 = 0.0f;
    if (model->nDis != 0) {
        model->dis = (float *)fn_801AC988(model->nDis * sizeof(float), lbl_8049D540, 0x7AF, 2);
        model->boneIndices = (unsigned char *)fn_801AC988(model->nDis, lbl_8049D550, 0x7B0, 2);
        model->parBoneIndices = (unsigned char *)fn_801AC988(model->nDis, lbl_8049D568, 0x7B1, 2);
        j = 0;
        for (i = first; i < end && j < model->nDis; i++) {
            parent = model->nodes[i].parent;
            if (parent <= 0 && i > 1)
                continue;
            if (parent > 0)
                model->disSum += fn_80434040(&model->nodes[i]);
            model->dis[j] = model->disSum;
            model->boneIndices[j] = i;
            model->parBoneIndices[j] = parent;
            j++;
        }
    }
    if (model->u15A != 0 && model->u15A < model->nNodes) {
        end = model->nNodes - model->u15A - 3;
        if (end > 0) {
            model->nDis2 = 0;
            for (i = model->u15A; i < model->u15A + end; i++) {
                parent = model->nodes[i].parent;
                if (parent <= 0 && i > 1)
                    continue;
                model->nDis2++;
            }
            model->disSum2 = 0.0f;
            if (model->nDis2 != 0) {
                model->dis2 = (float *)fn_801AC988(model->nDis2 * sizeof(float), lbl_8049D540, 0x7EB, 2);
                model->boneIndices2 = (unsigned char *)fn_801AC988(model->nDis2, lbl_8049D550, 0x7EC, 2);
                model->parBoneIndices2 = (unsigned char *)fn_801AC988(model->nDis2, lbl_8049D568, 0x7ED, 2);
                j = 0;
                for (i = model->u15A; i < model->u15A + end && j < model->nDis2; i++) {
                    parent = model->nodes[i].parent;
                    if (parent <= 0 && i > 1)
                        continue;
                    if (parent > 0)
                        model->disSum2 += fn_80434040(&model->nodes[i]);
                    model->dis2[j] = model->disSum2;
                    model->boneIndices2[j] = i;
                    model->parBoneIndices2[j] = parent;
                    j++;
                }
            }
        }
    }
}
