// Rebinds an axis to a new owner (+0x0) and re-applies its target; 0 if the owner is rejected.
typedef struct
{
    void *owner;
    int pad4;
    short mode; // +0x8
} Axis;

typedef struct
{
    int pad0;
    unsigned int flags; // +0x4
} Flags;

extern void fn_8044655C(Axis *self, float v, float w);
extern int fn_80446FA8(void *owner);
extern int fn_801991FC(void *owner);

int fn_8044667C(register Axis *self, register void *owner, register float v, register float w, register int mode)
{
    self->mode = mode;
    if (self->owner == owner)
    {
        fn_8044655C(self, v, w);
        return 1;
    }
    if (owner != 0)
    {
        if (fn_80446FA8(owner) == 0)
        {
            if (fn_801991FC(owner) == 0)
                return 0;
        }
    }
    self->owner = owner;
    fn_8044655C(self, v, w);
    return 1;
}

void fn_8044674C(register Flags *self, register int set)
{
    if (set)
        self->flags |= 0x2000000;
}

void fn_80446784(register Flags *self)
{
    self->flags &= ~8;
}
