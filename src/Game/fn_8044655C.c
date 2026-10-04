// Sets an axis target clamped to [-1, 1] and scaled by its owner's factor (+0x28); the pool is another unit's.
extern const float lbl_8048CD1C[]; // 0.0f
extern const float lbl_8048CD20[]; // -1.0f
extern const float lbl_8048CD24[]; // 1.0f

typedef struct
{
    char pad0[0x28];
    float unk28;
} Owner;

typedef struct
{
    Owner *owner;
    int pad4[2];
    float cur; // +0xC
    int pad10;
    float target; // +0x14
    float rate;   // +0x18
} Axis;

void fn_8044655C(register Axis *self, register float v, register float w)
{
    register float t;
    register float s;
    if (self->owner != 0)
    {
        if (w == lbl_8048CD1C[0])
        {
            if (v >= lbl_8048CD20[0])
            {
                if (v <= lbl_8048CD24[0])
                    t = v;
                else
                    t = lbl_8048CD24[0];
            }
            else
                t = lbl_8048CD20[0];
            v = t;
            self->cur = v * self->owner->unk28;
            self->target = self->cur;
            self->rate = lbl_8048CD1C[0];
        }
        else if (v != self->cur)
        {
            self->rate = w * self->owner->unk28;
            s = self->owner->unk28;
            if (v >= lbl_8048CD20[0])
            {
                if (v <= lbl_8048CD24[0])
                    t = v * s;
                else
                    t = s;
            }
            else
                t = s * lbl_8048CD20[0];
            self->target = t;
        }
    }
}
