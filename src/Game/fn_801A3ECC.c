// Carves one model and its arrays from a .ngm bundle's data buffer; docs/characters.md section 4.

typedef struct Model
{
    char pad0[4];
    unsigned char nMeshes;  // +0x4
    char pad5[3];
    unsigned char nParts;   // +0x8
    unsigned char nNodes;   // +0x9
    char padA[0x18 - 0xA];
    void *meshes;           // +0x18, 0x5C each
    char pad1C[0x80 - 0x1C];
    void *nodes;            // +0x80, 0x30 each
    char pad84[4];
    void **parts;           // +0x88
    char pad8C[0x150 - 0x8C];
    void *attachments;      // +0x150, 0x50 each
    unsigned int nAttachments; // +0x154
} Model;

Model *fn_801A3ECC(unsigned int *cursor, unsigned char nNodes, unsigned char nMeshes, unsigned char nParts,
                   unsigned short nAttachments)
{
    Model *m;

    *cursor = (*cursor + 15) & ~15;
    m = (Model *)*cursor;
    *cursor = *cursor + 0x190;
    *cursor = (*cursor + 15) & ~15;
    if (nAttachments != 0) {
        m->attachments = (void *)*cursor;
    } else {
        m->attachments = 0;
    }
    *cursor = *cursor + nAttachments * 0x50;
    *cursor = (*cursor + 15) & ~15;
    m->nodes = (void *)*cursor;
    *cursor = *cursor + nNodes * 0x30;
    m->meshes = (void *)*cursor;
    *cursor = *cursor + nMeshes * 0x5C;
    if (nParts != 0) {
        m->parts = (void **)*cursor;
    } else {
        m->parts = 0;
    }
    *cursor = *cursor + nParts * sizeof(void *);
    m->nNodes = nNodes;
    m->nParts = nParts;
    m->nMeshes = nMeshes;
    m->nAttachments = nAttachments;
    return m;
}
