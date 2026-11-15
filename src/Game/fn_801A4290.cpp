// Draws a model instance: updates its node matrices, culls it, loads the palette and draws its meshes and its children's.
#define ABS(x) ((x) < 0.0f ? -(x) : (x))

class Vector
{
public:
    float x, y, z, w;
    Vector();
} __attribute__((aligned(8)));

struct Matrix {
    Vector r[4];
};

struct Model {
    char pad0[0xB0];
    char bounds[8];        // +0xB0
};

struct Camera {
    char pad0[0x40];
    char position[0x190];  // +0x40
    char frustum[8];       // +0x1D0
};

class Instance
{
public:
    Model *model;          // +0x00
    unsigned int flags;    // +0x04
    char pad8[0x8];
    Instance *children[4]; // +0x10
    char pad20[0x14];
    float depth;           // +0x34
    char pad38[0x28];
    int outline;           // +0x60
    char pad64[0x4];
    Matrix world;          // +0x68
    char padA8[0x3C];
    unsigned char shade;   // +0xE4
};

inline int sn_return_decl(int a) { return a; }

extern "C" {
extern Camera *lbl_8066C560;
void *fn_8042FA34();
void fn_804379BC(void *a, int b);
void fn_804379E0(void *a, int b, int c);
void fn_801A479C(Instance *self, Matrix *world, int force);
int fn_801B90A8(char *frustum, char *bounds, Matrix *world);
int fn_80466118(Model *m);
int fn_80466428(Camera *c);
void fn_801A5CC0(Instance *self, float f);
void fn_8042DA10(Vector *out, Vector *a, char *b);
float *fn_8042FB28(Vector *v);
void fn_801A46DC(Instance *self, float f);
void fn_8042E438(Matrix *dst, Matrix *src);
void fn_80218CD4(Instance *self);
void fn_80220980(Instance *self);
int fn_804662F8(Instance *self);
int fn_80466200(Instance *self);
int fn_80431258(Instance *self);
void fn_80223088(Instance *self, unsigned int flags, int a, int b);

int fn_801A4290(register Instance *self, Matrix *world, unsigned int flags, Instance *root, int mode)
{
    unsigned int i;
    float z = 0.0f;
    if (self == 0)
        return 0;
    if (root == 0)
        root = self;
    fn_804379BC(fn_8042FA34(), 0x22);
    if (!(self->flags & 0x400000))
        fn_801A479C(root, world, flags & 0x8);
    fn_804379E0(fn_8042FA34(), 0x22, 1);
    if (!(self->flags & 0x80) && !(flags & 0x80) && !fn_801B90A8(lbl_8066C560->frustum, self->model->bounds, world))
        return 0;
    if (fn_80466118(self->model) && !(self->flags & 0x10)) {
        if (fn_80466428(lbl_8066C560)) {
            fn_801A5CC0(self, 1.0f);
        } else {
            Vector v;
            fn_8042DA10(&v, &world->r[3], lbl_8066C560->position);
            z = fn_8042FB28(&v)[2];
            if (ABS(z - self->depth) > 0.2f) {
                fn_801A46DC(self, z);
                self->depth = z;
            }
        }
    }
    fn_8042E438(&self->world, world);
    fn_80218CD4(self);
    fn_80220980(root);
    int shade = fn_804662F8(self) ? self->shade : -1;
    if (self->model != 0 && (fn_80466200(self) || ((flags & 0x10) && self->outline != 0)))
        fn_80223088(self, flags, mode, shade);
    for (i = 0; i < 4; i++) {
        if (self->children[i] != 0 && self->children[i]->model != 0 && fn_80466200(self->children[i]))
            fn_80223088(self->children[i], flags, mode, shade);
    }
    if (self->outline != 0 && !(flags & 0x10)) {
        if (self->model != 0 && fn_80431258(self))
            fn_80223088(self, flags, self->outline, shade);
        for (i = 0; i < 4; i++) {
            if (self->children[i] != 0 && fn_80431258(self->children[i]))
                fn_80223088(self->children[i], flags, self->outline, shade);
        }
    }
    return 1;
}
}
