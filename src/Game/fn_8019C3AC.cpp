// The animator's root-motion accessors (docs/characters.md section 4).

class Vector
{
public:
    float x, y, z, w;
};

class Animator
{
public:
    char pad0[0x1C0];
    Vector rootPos;        // +0x1C0, node 0's position last frame
    Vector rootRot;        // +0x1D0, node 0's rotation last frame (z is the yaw)
    char pad1E0[0x10];
    Vector rootStep;       // +0x1F0, root movement this frame
    Vector rotStep;        // +0x200, root turn this frame (z is the yaw change)
    char pad210[0x10];
    unsigned int flags;    // +0x220, 0x1 reset the root
};

inline int sn_return_decl(int a) { return a; }

extern "C" {
void fn_8019BA58(Animator *self, int force, int root, int noTargets);
void fn_8042DC84(Vector *dst, Vector *src);

// Builds the pose if it is stale and returns the root movement for the frame.
void fn_8019C3AC(register Animator *self, Vector *out, int noTargets)
{
    fn_8019BA58(self, 0, 0, noTargets);
    fn_8042DC84(out, &self->rootStep);
}

// Resets the root, so the next pose reports no movement or turn.
void fn_8019C408(register Animator *self)
{
    self->flags |= 1;
}

// Builds the pose if it is stale and returns node 0's position.
void fn_8019C434(register Animator *self, Vector *out)
{
    fn_8019BA58(self, 0, 0, 0);
    fn_8042DC84(out, &self->rootPos);
}

// Returns the root turn for the frame; call after fn_8019C3AC.
void fn_8019C48C(register Animator *self, Vector *out)
{
    fn_8042DC84(out, &self->rotStep);
}

// Returns node 0's rotation.
void fn_8019C4D0(register Animator *self, Vector *out)
{
    fn_8042DC84(out, &self->rootRot);
}
}
