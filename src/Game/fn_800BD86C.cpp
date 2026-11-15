// Fallback state event handler, used when the state's own handler returns 0.

struct Obj {
    char pad0[0x18];
    unsigned int f18;      // +0x18
};

extern "C" int fn_800BD86C(register Obj *self, void *ch, int type, int value, int extra)
{
    switch (type) {
    case 0x12:
        self->f18 |= 0x4000;
        break;
    case 0x51:
        if (value)
            self->f18 |= 0x80000;
        else
            self->f18 &= ~0x80000;
        break;
    default:
        return 0;
    }
    return 1;
}
