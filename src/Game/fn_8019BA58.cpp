// Builds the animator's pose for the frame and takes the root motion out of it (docs/characters.md section 4).

class Vec4
{
public:
    float x, y, z, w;
    Vec4();
};

class Vector
{
public:
    float x, y, z, w;
    Vector();
    Vector(float x, float y, float z, float w) __asm__("fn_8042D768");
};

class Handle
{
public:
    int target;
    int isSet();
};

struct Clip;

class Channel
{
public:
    float speed;           // +0x00
    float time;            // +0x04
    float weight;          // +0x08
    float fadeRate;        // +0x0C
    char pad10[0x4];
    unsigned int flags;    // +0x14
    char pad18[0x4];
    Clip *clip;            // +0x1C
    char pad20[0xC];
};

// An IK or look-at target the pose is bent toward (0x1C bytes).
class Target : public Handle
{
public:
    char pad4[0x18];
};

struct Attachment {
    char pad0[0x40];
    unsigned char node;    // +0x40
};

class Animator
{
public:
    Channel main;          // +0x000
    Channel blend;         // +0x02C
    Channel layer;         // +0x058
    Vec4 *rot;             // +0x084, one rotation per node
    Vector *pos;           // +0x088, one translation per node
    Vec4 *layerRot;        // +0x08C
    Vector *layerPos;      // +0x090
    Target t94;            // +0x094
    Target tB0;            // +0x0B0
    Target tCC;            // +0x0CC
    Target tE8;            // +0x0E8
    Target t104;           // +0x104
    Target t120;           // +0x120
    char pad13C[0x84];
    Vector rootPos;        // +0x1C0, node 0's position last frame
    char pad1D0[0x8];
    float rootYaw;         // +0x1D8, node 0's yaw last frame
    char pad1DC[0x14];
    Vector rootStep;       // +0x1F0, root movement this frame
    char pad200[0x8];
    float yawStep;         // +0x208, root turn this frame
    char pad20C[0x4];
    unsigned short nodes;  // +0x210
    char pad212[0x6];
    int frame;             // +0x218, frame the pose was built on
    char pad21C[0x4];
    unsigned int flags;    // +0x220, 0x1 reset the root, 0x4 skip tCC
};

inline int sn_return_decl(int a) { return a; }

extern "C" {
extern int lbl_8066C7D8; // frame counter
int fn_8043B1CC(Channel *ch);  // has a clip
int fn_80465A3C(Channel *ch);  // flags & 0x8000
int fn_80465A6C(Channel *ch);  // flags & 0x4000
void fn_8019D128(Channel *ch, Vec4 *rot, Vector *pos);
void fn_8019CEA0(Channel *ch, Vec4 *rot, Vector *pos);
Vec4 fn_80465728(Vec4 a, Vec4 *b, float t);
void fn_804304FC(Vector *dst, Vector *a, Vector *b, float t);
void fn_8019C75C(Target *t, Vec4 *rot, Vector *pos);
void fn_8042DC84(Vector *dst, Vector *src);
void *fn_80465ACC(Animator *anim);
Attachment *fn_801A4C58(void *model, int kind);
void fn_8042D854(Vector *a, Vector *b);
void fn_8042D8A8(Vector *a, Vector *b);
void fn_80429038(Vector *dst, Vector *a, Vector *b);
void fn_80447C38(Vector *v);
float fn_801BCF14(Vec4 *q);
}

extern "C" void fn_8019BA58(register Animator *self, int force, int root, int noTargets)
{
    if (!force && self->frame == lbl_8066C7D8)
        return;
    for (int i = 0; i < self->nodes; i++)
        self->rot[i] = Vec4();
    for (int j = 0; j < self->nodes; j++)
        self->pos[j] = Vector(0.0f, 0.0f, 0.0f, 0.0f);
    if (fn_8043B1CC(&self->blend)) {
        if (fn_80465A3C(&self->blend) && fn_8043B1CC(&self->main)) {
            fn_8019D128(&self->main, self->rot, self->pos);
            fn_8019D128(&self->blend, self->rot, self->pos);
        } else if (fn_80465A6C(&self->blend) && fn_8043B1CC(&self->main)) {
            fn_8019D128(&self->main, self->rot, self->pos);
            fn_8019CEA0(&self->blend, self->rot, self->pos);
        } else {
            fn_8019D128(&self->blend, self->rot, self->pos);
        }
    } else if (fn_8043B1CC(&self->main)) {
        fn_8019D128(&self->main, self->rot, self->pos);
    }
    if (fn_8043B1CC(&self->layer) && self->layer.weight > 0.0f) {
        float w = self->layer.weight;
        for (int k = 0; k < self->nodes; k++)
            self->layerRot[k] = Vec4();
        for (int l = 0; l < self->nodes; l++)
            self->layerPos[l] = Vector(0.0f, 0.0f, 0.0f, 0.0f);
        fn_8019D128(&self->layer, self->layerRot, self->layerPos);
        *self->layerPos = Vector(0.0f, 0.0f, 0.0f, 0.0f);
        *self->layerRot = Vec4();
        for (unsigned int m = 0; m < self->nodes; m++) {
            self->rot[m] = fn_80465728(self->rot[m], &self->layerRot[m], w);
            fn_804304FC(&self->pos[m], &self->pos[m], &self->layerPos[m], w);
        }
    }
    if (!noTargets) {
        if (self->tB0.isSet())
            fn_8019C75C(&self->tB0, self->rot, self->pos);
        if (self->t94.isSet())
            fn_8019C75C(&self->t94, self->rot, self->pos);
        if (self->tCC.isSet() && !(self->flags & 4))
            fn_8019C75C(&self->tCC, self->rot, self->pos);
        if (self->tE8.isSet())
            fn_8019C75C(&self->tE8, self->rot, self->pos);
        if (self->t104.isSet())
            fn_8019C75C(&self->t104, self->rot, self->pos);
        if (self->t120.isSet())
            fn_8019C75C(&self->t120, self->rot, self->pos);
    }
    if (root || self->frame != lbl_8066C7D8) {
        Vector v;
        fn_8042DC84(&v, self->pos);
        Attachment *a = fn_801A4C58(fn_80465ACC(self), 0x11);
        if (a) {
            fn_8042D854(&v, &self->pos[a->node]);
            fn_8042D8A8(&self->pos[1], &self->pos[a->node]);
            Attachment *b = fn_801A4C58(fn_80465ACC(self), 0x16);
            if (b)
                fn_8042D8A8(&self->pos[b->node], &self->pos[a->node]);
        }
        if (self->flags & 1)
            fn_80447C38(&self->rootStep);
        else
            fn_80429038(&self->rootStep, &v, &self->rootPos);
        fn_8042DC84(&self->rootPos, &v);
        fn_80447C38(self->pos);
        if (self->nodes > 1) {
            register float r = fn_801BCF14(self->rot) * 57.295792f;
            float yaw = r;
            if (self->flags & 1)
                self->yawStep = 0.0f;
            else
                self->yawStep = yaw - self->rootYaw;
            self->rootYaw = yaw;
            *self->rot = Vec4();
        }
        self->flags &= ~1;
    } else {
        fn_80447C38(self->pos);
        if (self->nodes > 1)
            *self->rot = Vec4();
    }
    self->frame = lbl_8066C7D8;
}
