// Holder counter and leaf accessors on unidentified objects (docs/versus.md, row 8).

typedef struct Holder
{
    const void *vptr; // +0x0
    short pad;        // +0x4
    unsigned short n; // +0x6
} Holder;

typedef struct Obj
{
    unsigned int flags; // +0x0
} Obj;

typedef struct Slot
{
    char pad[0xE6];
    short id;   // +0xE6
    int value;  // +0xE8
} Slot;

extern "C" {
void fn_8043D65C(register Holder *self)
{
    self->n++;
}

int fn_8043D694(register Obj *self)
{
    return self->flags & 0x400;
}

int fn_8043D6CC(register Obj *self)
{
    return self->flags;
}

char *fn_8043D700(register char **self)
{
    if (*self)
        return *self + 0x8C;
    else
        return 0;
}

void fn_8043D750(register Slot *self, register int v)
{
    self->value = v;
}

void fn_8043D780(register Slot *self, register int on, register int v)
{
    if (on)
        self->id = v;
    else
        self->id = -1;
}
}
