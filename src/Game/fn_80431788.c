// Leaf accessors on the player slots and on `G` (docs/versus.md section 4.1).

typedef struct Slot
{
    char unk0[0x34];
    int flags; // +0x34
    int unk38;
    int unk3C;
    char unk40[0x70];
} Slot;

typedef struct G
{
    char unk0[0x10];
    Slot slots[8];       // +0x10
    int numSlots;        // +0x590
    char unk594[0x1DC];
    int role770;         // +0x770
    int role774;         // +0x774
} G;

typedef struct Flags
{
    unsigned int bits; // +0x0
} Flags;

void fn_80431788(register Slot *slot)
{
    slot->flags |= 4;
    slot->unk3C = 99;
}

Slot *fn_804317BC(register G *g, register int i)
{
    return &g->slots[i];
}

void fn_804317F4(register G *g, register int v)
{
    g->role770 = v;
}

void fn_8043181C(register G *g, register int v)
{
    g->role774 = v;
}

void fn_80431844(register G *g, register int v)
{
    g->numSlots = v;
}

void fn_8043186C(register char *g, register int v)
{
    *(int *)(g + 0x150) = v;
}

void fn_80431894(register Flags *f, register int on)
{
    if (on) {
        f->bits |= 0x4;
    } else {
        f->bits &= ~0x4;
    }
}

void fn_804318DC(register Flags *f, register int on)
{
    if (on) {
        f->bits |= 0x10;
    } else {
        f->bits &= ~0x10;
    }
}

void fn_80431924(register Flags *f, register int on)
{
    if (on) {
        f->bits |= 0x20;
    } else {
        f->bits &= ~0x20;
    }
}

void fn_8043196C(register Flags *f, register int on)
{
    if (on) {
        f->bits |= 0x40;
    } else {
        f->bits &= ~0x40;
    }
}

void fn_804319B4(register Flags *f, register int on)
{
    if (on) {
        f->bits |= 0x200;
    } else {
        f->bits &= ~0x200;
    }
}

void fn_804319FC(register Flags *f, register int on)
{
    if (on) {
        f->bits |= 0x80;
    } else {
        f->bits &= ~0x80;
    }
}

void fn_80431A44(register Flags *f, register int on)
{
    if (on) {
        f->bits |= 0x1000;
    } else {
        f->bits &= ~0x1000;
    }
}

void fn_80431A8C(register Flags *f, register int on)
{
    if (on) {
        f->bits |= 0x400;
    } else {
        f->bits &= ~0x400;
    }
}

void fn_80431AD4(register Flags *f, register int on)
{
    if (on) {
        f->bits |= 0x800;
    } else {
        f->bits &= ~0x800;
    }
}

void fn_80431B1C(register Flags *f, register int on)
{
    if (on) {
        f->bits |= 0x2000;
    } else {
        f->bits &= ~0x2000;
    }
}

void fn_80431B64(register Flags *f, register int on)
{
    if (on) {
        f->bits |= 0x4000;
    } else {
        f->bits &= ~0x4000;
    }
}

void fn_80431BAC(register Flags *f, register int on)
{
    if (on) {
        f->bits |= 0x8000;
    } else {
        f->bits &= ~0x8000;
    }
}

void fn_80431BF4(register Flags *f, register int on)
{
    if (on) {
        f->bits |= 0x80000000;
    } else {
        f->bits &= ~0x80000000;
    }
}

void fn_80431C3C(register Flags *f, register int on)
{
    if (on) {
        f->bits |= 0x40000000;
    } else {
        f->bits &= ~0x40000000;
    }
}

void fn_80431C84(register Flags *f, register int on)
{
    if (on) {
        f->bits |= 0x20000000;
    } else {
        f->bits &= ~0x20000000;
    }
}
