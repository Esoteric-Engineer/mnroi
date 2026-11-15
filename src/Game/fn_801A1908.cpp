// Finds a model's attachment: by kind, or by kind and index.

struct Attachment {
    char matrix[0x40];     // +0x00, from the node
    unsigned char node;    // +0x40
    unsigned char kind;    // +0x41
    unsigned short index;  // +0x42
    char pad44[0xC];
};

struct Model {
    char pad0[0x150];
    Attachment *attachments; // +0x150
    unsigned int count;      // +0x154
};

extern "C" {
Attachment *fn_801A1908(register Model *self, unsigned char kind)
{
    unsigned int i;
    for (i = 0; i < self->count; i++) {
        if (self->attachments[i].kind == kind)
            return &self->attachments[i];
    }
    return 0;
}

Attachment *fn_801A19B0(register Model *self, unsigned char kind, unsigned short index)
{
    unsigned int i;
    for (i = 0; i < self->count; i++) {
        if (self->attachments[i].kind == kind && self->attachments[i].index == index)
            return &self->attachments[i];
    }
    return 0;
}
}
