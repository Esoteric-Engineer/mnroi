// Sets an axis target clamped to [-1, 1] and scaled by its owner's factor (+0x28): at once for a zero rate, as a target otherwise.
struct Owner
{
    char pad0[0x28];
    float unk28;
};

struct Axis
{
    Owner *owner;
    int pad4[2];
    float cur; // +0xC
    int pad10;
    float target; // +0x14
    float rate;   // +0x18
};

#define CLAMP(x) ((x) >= -1.0f ? ((x) <= 1.0f ? (x) : 1.0f) : -1.0f)

inline int sn_return_decl(int a) { return a; }

extern "C" void fn_8044655C(register Axis *self, register float v, register float w)
{
    if (self->owner != 0)
    {
        if (w == 0.0f)
        {
            v = CLAMP(v);
            self->cur = v * self->owner->unk28;
            self->target = self->cur;
            self->rate = 0.0f;
        }
        else if (v != self->cur)
        {
            self->rate = w * self->owner->unk28;
            self->target = CLAMP(v) * self->owner->unk28;
        }
    }
}
