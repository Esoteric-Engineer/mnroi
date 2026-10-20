// Whether an axis is still moving: a nonzero rate (+0x18) and a current value (+0xC) that is not the target (+0x14) yet.
typedef struct Axis
{
    void *owner;
    int pad4[2];
    float cur;    // +0xC
    int pad10;
    float target; // +0x14
    float rate;   // +0x18
} Axis;

int fn_804464DC(register Axis *self)
{
    return self->rate != 0.0f && self->cur != self->target;
}
