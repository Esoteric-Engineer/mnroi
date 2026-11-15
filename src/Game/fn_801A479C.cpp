// Builds a model instance's node matrices for the frame: the animated pose (fn_8019D5E0), or the bind pose when it has no animator.
// Then the instance's attachment queries: an attachment's world matrix or position by kind, by kind and index, or by its place in the list.
// A kind the model lacks is looked up on the instance's up to 4 sub-instances (+0x10).

class Vector
{
public:
    float x, y, z, w;
    Vector();
} __attribute__((aligned(8)));

class Matrix
{
public:
    Vector r[4];
    Matrix() __asm__("fn_8042D7B0");
};

struct ModelNode {
    Vector offset;         // +0x00, from the parent
    Vector unbind;         // +0x10, the negated bind position
    signed char parent;    // +0x20
    char pad21[0xF];
};

struct Attachment {
    Matrix matrix;         // +0x00, from the node
    unsigned char node;    // +0x40
    unsigned char kind;    // +0x41
    unsigned short index;  // +0x42
    char pad44[0xC];
};

struct Model {
    char pad0[0x9];
    unsigned char nodes;   // +0x09
    char padA[0x76];
    ModelNode *nodeList;   // +0x80
    char pad84[0xCC];
    Attachment *attachments; // +0x150
    unsigned int attachmentCount; // +0x154
};

class Instance
{
public:
    Model *model;          // +0x00
    unsigned int flags;    // +0x04, 0x400000 frozen
    char pad8[0x8];
    Instance *subs[4];     // +0x10, searched for attachments the model lacks
    Vector scale;          // +0x20
    char pad30[0xC];
    int frame;             // +0x3C, frame the matrices were built on
    char pad40[0x24];
    Matrix *matrices;      // +0x64, one per node
    char pad68[0x48];
    void *animator;        // +0xB0
    char padB4[0x38];
    void (*onBuilt)(Instance *self, void *arg); // +0xEC
    void *onBuiltArg;      // +0xF0
};

inline int sn_return_decl(int a) { return a; }

extern "C" {
extern int lbl_8066C7D8; // frame counter
void fn_8042E438(Matrix *dst, Matrix *src);
int fn_80466268(Instance *self);
void fn_804602CC(Matrix *m, Vector *scale);
void fn_8042DCC0(Matrix *m);
void fn_8042DC84(Vector *dst, Vector *src);
void fn_8043570C(Matrix *out, Matrix *a, Matrix *b);
Vector *fn_80441334(Instance *self, int i);
void fn_80440F30(Matrix *m, Vector *v);
void fn_8019D5E0(Instance *self, Matrix *parent, int force);
Attachment *fn_801A1908(Model *model, unsigned char kind);
Attachment *fn_801A19B0(Model *model, unsigned char kind, unsigned short index);
void fn_80446420(Matrix *m, Attachment *a);
void fn_8042DA10(Vector *out, Vector *v, Matrix *m);

void fn_801A479C(register Instance *self, Matrix *world, int force)
{
    if (!force && self->frame == lbl_8066C7D8)
        return;
    if (self->flags & 0x400000)
        return;
    self->frame = lbl_8066C7D8;
    Matrix base;
    fn_8042E438(&base, world);
    if (fn_80466268(self))
        fn_804602CC(&base, &self->scale);
    if (self->animator == 0) {
        Matrix *out;
        ModelNode *node;
        Matrix local;
        unsigned int i;
        unsigned int n = self->model->nodes;
        for (i = 0, out = self->matrices, node = self->model->nodeList; i < n; i++, out++, node++) {
            fn_8042DCC0(&local);
            fn_8042DC84(&local.r[3], &node->offset);
            if (node->parent < 0)
                fn_8043570C(out, &base, &local);
            else
                fn_8043570C(out, &self->matrices[node->parent], &local);
            fn_8042DC84(fn_80441334(self, i), &out->r[3]);
        }
        for (i = 0, out = self->matrices, node = self->model->nodeList; i < n; i++, out++, node++)
            fn_80440F30(out, &node->unbind);
        if (self->onBuilt != 0)
            self->onBuilt(self, self->onBuiltArg);
    } else {
        fn_8019D5E0(self, &base, force);
        if (self->onBuilt != 0)
            self->onBuilt(self, self->onBuiltArg);
    }
}
void fn_801A4A4C(register Instance *self, int node, Vector *out, Matrix *world)
{
    fn_801A479C(self, world, 0);
    fn_8042DC84(out, fn_80441334(self, node));
}

void fn_801A4AB4(register Instance *self, int node, Vector *out)
{
    fn_8042DC84(out, fn_80441334(self, node));
}

void fn_801A4B08(register Instance *self, int node, Matrix *out)
{
    fn_8042E438(out, &self->matrices[node]);
    fn_8042DC84(&out->r[3], fn_80441334(self, node));
}

unsigned char fn_801A4B84(register Instance *self, unsigned char kind)
{
    int n = 0;
    if (!self->model || !self->model->attachmentCount)
        return 0;
    unsigned int i;
    for (i = 0; i < self->model->attachmentCount; i++) {
        if (self->model->attachments[i].kind == kind)
            n++;
    }
    return n;
}

Attachment *fn_801A4C58(register Instance *self, unsigned char kind)
{
    Attachment *a = fn_801A1908(self->model, kind);
    if (!a) {
        unsigned int i;
        for (i = 0; i <= 3; i++) {
            if (self->subs[i]) {
                a = fn_801A1908(self->subs[i]->model, kind);
                if (a)
                    break;
            }
        }
    }
    return a;
}

Attachment *fn_801A4D4C(register Instance *self, unsigned char kind, unsigned short index)
{
    Attachment *a = fn_801A19B0(self->model, kind, index);
    if (!a) {
        unsigned int i;
        for (i = 0; i <= 3; i++) {
            if (self->subs[i]) {
                a = fn_801A19B0(self->subs[i]->model, kind, index);
                if (a)
                    break;
            }
        }
    }
    return a;
}

Attachment *fn_801A4E5C(register Instance *self, unsigned int i)
{
    if (i < self->model->attachmentCount) {
        return &self->model->attachments[i];
    } else {
        return 0;
    }
}

int fn_801A4EBC(register Instance *self, unsigned char kind, Matrix *out, Matrix *world)
{
    Attachment *a = fn_801A4C58(self, kind);
    if (!a)
        return 0;
    if (world)
        fn_801A479C(self, world, 0);
    fn_801A4B08(self, a->node, out);
    fn_80446420(out, a);
    return 1;
}

int fn_801A4F78(register Instance *self, unsigned char kind, unsigned short index, Matrix *out, Matrix *world)
{
    Attachment *a = fn_801A4D4C(self, kind, index);
    if (!a)
        return 0;
    if (world)
        fn_801A479C(self, world, 0);
    fn_801A4B08(self, a->node, out);
    fn_80446420(out, a);
    return 1;
}

int fn_801A5048(register Instance *self, unsigned int i, Matrix *out, Matrix *world)
{
    if (i >= self->model->attachmentCount)
        return 0;
    Attachment *a = &self->model->attachments[i];
    if (world)
        fn_801A479C(self, world, 0);
    fn_801A4B08(self, a->node, out);
    fn_80446420(out, a);
    return 1;
}

int fn_801A5104(register Instance *self, unsigned char kind, unsigned short index, Vector *out, Matrix *world)
{
    Attachment *a = fn_801A4D4C(self, kind, index);
    if (!a)
        return 0;
    if (world)
        fn_801A479C(self, world, 0);
    Matrix m;
    fn_801A4B08(self, a->node, &m);
    fn_8042DA10(out, &a->matrix.r[3], &m);
    return 1;
}

int fn_801A51F4(register Instance *self, unsigned char kind, Vector *out, Matrix *world)
{
    Attachment *a = fn_801A4C58(self, kind);
    if (!a)
        return 0;
    if (world)
        fn_801A479C(self, world, 0);
    Matrix m;
    fn_801A4B08(self, a->node, &m);
    fn_8042DA10(out, &a->matrix.r[3], &m);
    return 1;
}

int fn_801A52D0(register Instance *self, unsigned int i, Vector *out, Matrix *world)
{
    if (i > self->model->attachmentCount)
        return 0;
    Attachment *a = &self->model->attachments[i];
    if (!a)
        return 0;
    if (world)
        fn_801A479C(self, world, 0);
    Matrix m;
    fn_801A4B08(self, a->node, &m);
    fn_8042DA10(out, &a->matrix.r[3], &m);
    return 1;
}

int fn_801A53C0(register Instance *self, int (*visit)(Instance *, Attachment *, unsigned int, Matrix *, void *, int *), void *arg, int kind, int index, Matrix *world)
{
    if (world)
        fn_801A479C(self, world, 0);
    int result = -1;
    Attachment *a;
    Matrix m;
    unsigned int i;
    for (i = 0; i < self->model->attachmentCount; i++) {
        a = &self->model->attachments[i];
        if (kind >= 0 && a->kind != kind)
            continue;
        if (index >= 0 && a->index != index)
            continue;
        fn_801A4B08(self, a->node, &m);
        fn_80446420(&m, a);
        if (visit(self, a, i, &m, arg, &result))
            return result;
    }
    return result;
}

int fn_801A5554(Attachment *a, int *list, unsigned short n)
{
    if (!list)
        return 0;
    unsigned short i;
    for (i = 0; i < n; i++) {
        if (a->index == list[i])
            return 1;
    }
    return 0;
}

void fn_801A5610(register Instance *self, unsigned char kind, Matrix *out, unsigned int *count, Matrix *world, int byIndex, int *skip, unsigned short skipCount)
{
    unsigned int i;
    int n = 0;
    if (world)
        fn_801A479C(self, world, 0);
    for (i = 0; i < self->model->attachmentCount; i++) {
        if (self->model->attachments[i].kind == kind) {
            Attachment *a = &self->model->attachments[i];
            if (fn_801A5554(a, skip, skipCount))
                continue;
            if (byIndex && a->index >= *count)
                continue;
            Matrix *m;
            if (byIndex)
                m = &out[a->index];
            else
                m = &out[n];
            fn_801A4B08(self, a->node, m);
            fn_80446420(m, a);
            n++;
            if (n == *count)
                return;
        }
    }
    *count = n;
}
}
