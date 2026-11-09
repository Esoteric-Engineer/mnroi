// Builds a model instance's node matrices for the frame: the animated pose (fn_8019D5E0), or the bind pose when it has no animator.

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

struct Model {
    char pad0[0x9];
    unsigned char nodes;   // +0x09
    char padA[0x76];
    ModelNode *nodeList;   // +0x80
};

class Instance
{
public:
    Model *model;          // +0x00
    unsigned int flags;    // +0x04, 0x400000 frozen
    char pad8[0x18];
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
}
