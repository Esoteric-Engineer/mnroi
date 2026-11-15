// Evaluates clips into per-node rotations and translations, and turns those into the instance's node matrices (docs/characters.md section 4).

class Vec4
{
public:
    float x, y, z, w;
    Vec4();
} __attribute__((aligned(8)));

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

class Key
{
public:
    float frame;
    short v[4];
    Vector value();
};

struct Track {
    unsigned int bone;     // +0x00
    int channel;           // +0x04, 0 rotation, 1 translation
    unsigned int count;    // +0x08
    Key *keys;             // +0x0C
};

struct Clip {
    char pad0[0x2C];
    unsigned int nTracks;  // +0x2C
    Track *tracks;         // +0x30
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
    char pad84[0xD4];
    unsigned short chain;      // +0x158
    unsigned short chainFirst; // +0x15A
};

class Channel
{
public:
    float speed;           // +0x00
    float time;            // +0x04
    char pad8[0x14];
    Clip *clip;            // +0x1C
    unsigned int *state;   // +0x20, each track's current key
    unsigned int count;    // +0x24, nodes the pose holds
    Model *model;          // +0x28
};

// A clip the pose is bent by at a time of its own.
class Target
{
public:
    Clip *clip;            // +0x00
    Clip *reverse;         // +0x04, played when the time is negative
    unsigned short flags;  // +0x08, 0x1 replaces the pose instead of adding to it
    float time;            // +0x0C
    Model *model;          // +0x10
};

struct Animator {
    char pad0[0x84];
    Vec4 *rot;             // +0x84
    Vector *pos;           // +0x88
};

class Instance
{
public:
    Model *model;          // +0x00
    unsigned int flags;    // +0x04
    char pad8[0x30];
    int frame;             // +0x38, frame the matrices were built on
    char pad3C[0x28];
    Matrix *matrices;      // +0x64, one per node
    char pad68[0x48];
    Animator *animator;    // +0xB0
    char padB4[0x40];
    void (*onPose)(Animator *anim, void *arg); // +0xF4
    void *onPoseArg;       // +0xF8
};

extern "C" {
extern int lbl_8066C7D8; // frame counter
float fn_804473BC(Key *k);
Vec4 fn_80465960(Key *k);
Vec4 fn_801BD1C0(const Vec4 &a, const Vec4 &b);
Vec4 fn_80465728(const Vec4 &a, const Vec4 &b, float t);
void fn_8042DC84(Vector *dst, Vector *src);
void fn_8042D854(Vector *a, Vector *b);
void fn_80429038(Vector *dst, Vector *a, Vector *b);
void fn_80435530(Vector *v, float s);
void fn_80428FE0(Vector *dst, Vector *a, Vector *b);
void *fn_8042FA34();
void fn_804379BC(void *a, int b);
void fn_804379E0(void *a, int b, int c);
void fn_8019BA58(Animator *self, int force, int root, int noTargets);
void fn_80440FFC(Vec4 *q, Matrix *m);
void fn_8043570C(Matrix *out, Matrix *a, Matrix *b);
Vector *fn_80441334(Instance *self, int i);
void fn_80440F30(Matrix *m, Vector *v);

void fn_8019C75C(register Target *self, Vec4 *rot, Vector *pos)
{
    unsigned int j;
    float time = self->time;
    Clip *clip = self->clip;
    if (time < 0.0f) {
        if (self->reverse != 0)
            clip = self->reverse;
        time = -self->time;
    }
    if (clip == 0)
        return;
    for (unsigned int i = 0; i < clip->nTracks; i++) {
        Track *t = &clip->tracks[i];
        unsigned int bone = t->bone;
        unsigned int chain;
        if ((chain = bone >> 16) != 0) {
            if (chain == self->model->chain)
                bone = self->model->chainFirst + (bone & 0xFFFF);
            else
                continue;
        }
        for (j = 1; j < t->count; j++) {
            if (fn_804473BC(&t->keys[j]) >= time)
                break;
        }
        float dt = time - fn_804473BC(&t->keys[j - 1]);
        register float rf = (time - fn_804473BC(&t->keys[j - 1])) / (fn_804473BC(&t->keys[j % t->count]) - fn_804473BC(&t->keys[j - 1]));
        float f = rf;
        if (dt == 0.0f) {
            if (t->channel == 1) {
                Vector v = t->keys[j - 1].value();
                if (self->flags & 1)
                    fn_8042DC84(&pos[bone], &v);
                else
                    fn_8042D854(&pos[bone], &v);
            } else {
                if (self->flags & 1)
                    rot[bone] = fn_80465960(&t->keys[j - 1]);
                else
                    rot[bone] = fn_801BD1C0(fn_80465960(&t->keys[j - 1]), rot[bone]);
            }
        } else {
            if (t->channel == 1) {
                Vector a = t->keys[j - 1].value();
                Vector b = t->keys[j % t->count].value();
                Vector d;
                fn_80429038(&d, &b, &a);
                fn_80435530(&d, f);
                if (self->flags & 1) {
                    fn_80428FE0(&pos[bone], &a, &d);
                } else {
                    fn_8042D854(&pos[bone], &a);
                    fn_8042D854(&pos[bone], &d);
                }
            } else {
                if (self->flags & 1)
                    rot[bone] = fn_80465728(fn_80465960(&t->keys[j - 1]), fn_80465960(&t->keys[j % t->count]), f);
                else
                    rot[bone] = fn_801BD1C0(fn_80465728(fn_80465960(&t->keys[j - 1]), fn_80465960(&t->keys[j % t->count]), f), rot[t->bone]);
            }
        }
    }
}

void fn_8019CEA0(register Channel *self, Vec4 *rot, Vector *pos)
{
    if (self->clip == 0 || self->time == 0.0f)
        return;
    for (unsigned int i = 0; i < self->clip->nTracks; i++) {
        Track *t = &self->clip->tracks[i];
        while (self->state[i] < t->count - 1) {
            if (fn_804473BC(&t->keys[self->state[i] + 1]) > self->time)
                break;
            self->state[i]++;
        }
        Key *k = &t->keys[self->state[i]];
        float dt = self->time - fn_804473BC(k);
        if (t->channel == 1) {
            Vector v = k->value();
            fn_8042D854(&pos[t->bone], &v);
        } else {
            rot[t->bone] = fn_801BD1C0(rot[t->bone], fn_80465960(k));
        }
    }
}

void fn_8019D128(register Channel *self, Vec4 *rot, Vector *pos)
{
    Track *t;
    unsigned int bone;
    unsigned int last;
    unsigned int chain;
    if (self->clip == 0)
        return;
    unsigned int n = self->clip->nTracks <= self->count ? self->clip->nTracks : self->count;
    for (unsigned int i = 0; i < n; i++) {
        t = &self->clip->tracks[i];
        bone = t->bone;
        last = t->count - 1;
        if ((chain = bone >> 16) != 0) {
            if (chain == self->model->chain)
                bone = self->model->chainFirst + (bone & 0xFFFF);
            else if (chain > 0x100)
                bone = bone & 0xFFFF;
            else
                continue;
        }
        if (bone > self->count)
            continue;
        for (; self->state[i] < last; self->state[i]++) {
            if (fn_804473BC(&t->keys[self->state[i] + 1]) > self->time)
                break;
        }
        Key *k0 = &t->keys[self->state[i]];
        Key *k1 = &t->keys[(self->state[i] + 1) % t->count];
        register float rf = (self->time - fn_804473BC(k0)) / (fn_804473BC(k1) - fn_804473BC(k0));
        float f = rf;
        const float eps = 0.001f;
        if (f < eps) {
            if (t->channel == 0)
                rot[bone] = fn_80465960(k0);
            else
                pos[bone] = k0->value();
        } else {
            if (t->channel == 0) {
                rot[bone] = fn_80465728(fn_80465960(k0), fn_80465960(k1), f);
            } else {
                Vector a = k0->value();
                Vector b = k1->value();
                Vector d;
                fn_80429038(&d, &b, &a);
                fn_80435530(&d, f);
                fn_80428FE0(&pos[bone], &a, &d);
            }
        }
    }
}

void fn_8019D5E0(register Instance *self, Matrix *parent, int force)
{
    if (self->animator == 0)
        return;
    if (!force && self->frame == lbl_8066C7D8)
        return;
    if (self->flags & 0x400000)
        return;
    fn_804379BC(fn_8042FA34(), 0x1E);
    self->frame = lbl_8066C7D8;
    fn_8019BA58(self->animator, 0, 0, 0);
    if (self->onPose != 0)
        self->onPose(self->animator, self->onPoseArg);
    unsigned int i;
    Matrix *m;
    for (i = 0, m = self->matrices; i < self->model->nodes; i++, m++) {
        Matrix local;
        int p = self->model->nodeList[i].parent;
        fn_80440FFC(&self->animator->rot[i], &local);
        fn_80428FE0(&local.r[3], &self->model->nodeList[i].offset, &self->animator->pos[i]);
        if (p < 0)
            fn_8043570C(m, parent, &local);
        else
            fn_8043570C(m, &self->matrices[p], &local);
        fn_8042DC84(fn_80441334(self, i), &m->r[3]);
    }
    for (i = 0, m = self->matrices; i < self->model->nodes; i++, m++) {
        fn_80440F30(m, &self->model->nodeList[i].unbind);
    }
    fn_804379E0(fn_8042FA34(), 0x1E, 1);
}
}
