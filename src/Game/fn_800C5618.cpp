// Jump, Fall and Flail states' event handler.

struct EObj {
    char pad0[0x10];
    unsigned int flags; // +0x10
    char pad14[0x3AC - 0x14];
};

struct Obj : EObj {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(int state); // +0x30
};

extern "C" {
void fn_800CD77C(void *self);

int fn_800C5618(register Obj *self, int ch, int type, int value, int extra)
{
    switch (type) {
    case 0x14:
        self->s5(5);
        break;
    case 0xD:
        break;
    case 0xE:
        self->flags |= 0x1;
        break;
    case 0xF:
        self->flags &= ~0x1;
        break;
    case 0x12:
        fn_800CD77C(self);
        break;
    case 0x2C:
        self->flags |= 0x10;
        break;
    case 0x2D:
        self->flags &= ~0x10;
        break;
    case 0x2F:
        self->flags |= 0x20;
        break;
    case 0x30:
        self->flags &= ~0x20;
        break;
    case 0x32:
        self->flags |= 0x40;
        break;
    case 0x33:
        self->flags &= ~0x40;
        break;
    default:
        return 0;
    }
    return 1;
}
}
