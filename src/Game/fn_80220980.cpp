// Makes an instance's node matrices the current palette and loads them transposed into the 3x4 matrices GX reads.

struct Matrix {
    float m[4][4];
};

class Vector
{
public:
    float x, y, z, w;
};

struct GXMatrix {
    Vector r[3];
};

struct Instance {
    struct Model *model;   // +0x00
    char pad4[0x60];
    Matrix *matrices;      // +0x64
};

struct Model {
    char pad0[0x9];
    unsigned char nodes;   // +0x09
};

extern "C" {
extern Matrix *lbl_8066C810;
extern GXMatrix lbl_8062AA70[];
float *fn_80433F10(Vector *v);

void fn_80220980(Instance *self)
{
    lbl_8066C810 = self->matrices;
    for (unsigned int i = 0; i < self->model->nodes; i++) {
        GXMatrix *out = lbl_8062AA70 + i;
        Matrix *m = lbl_8066C810 + i;
        *fn_80433F10(&out->r[0]) = m->m[0][0];
        fn_80433F10(&out->r[0])[1] = m->m[1][0];
        fn_80433F10(&out->r[0])[2] = m->m[2][0];
        fn_80433F10(&out->r[0])[3] = m->m[3][0];
        *fn_80433F10(&out->r[1]) = m->m[0][1];
        fn_80433F10(&out->r[1])[1] = m->m[1][1];
        fn_80433F10(&out->r[1])[2] = m->m[2][1];
        fn_80433F10(&out->r[1])[3] = m->m[3][1];
        *fn_80433F10(&out->r[2]) = m->m[0][2];
        fn_80433F10(&out->r[2])[1] = m->m[1][2];
        fn_80433F10(&out->r[2])[2] = m->m[2][2];
        fn_80433F10(&out->r[2])[3] = m->m[3][2];
    }
}
}
