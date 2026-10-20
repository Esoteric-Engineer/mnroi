// Accessors on unidentified objects (docs/versus.md, row 8).

typedef struct Base
{
    char pad[0x7C];
    int f7C; // +0x7C
} Base;

typedef struct Obj
{
    int w0;             // +0x0
    Base *base;         // +0x4
    int w8;             // +0x8
    int wC;             // +0xC
    int w10;            // +0x10
    unsigned short s14; // +0x14
    unsigned short s16; // +0x16
    int w18;            // +0x18
    char pad1C[0x14];
    int w30; // +0x30
    char pad34[4];
    int w38; // +0x38
    char pad3C[4];
    unsigned char b40; // +0x40
} Obj;

void *fn_8043E540(register void *self)
{
    return self;
}

char *fn_8043E568(register char *self)
{
    return self + 0x10;
}

int fn_8043E594(register Obj *self)
{
    register int r = 0;

    if (self->w0 != 0 && self->w30 != 0)
        r = 1;
    return r;
}

void fn_8043E5DC(register Obj *self, register int v)
{
    self->w38 = v;
}

int fn_8043E604(register Obj *self)
{
    return (unsigned short)((unsigned int)self->s16 / 3) + (self->s14 - 2 >= 0 ? self->s14 - 2 : 0);
}

int fn_8043E664(register Obj *self)
{
    return self->w18;
}

int fn_8043E690(register Obj *self)
{
    return self->b40;
}

int fn_8043E6C0(register Obj *self)
{
    return self->base->f7C + self->wC * 2;
}

int fn_8043E700(register Obj *self)
{
    return self->base->f7C + self->w10 * 2;
}

int fn_8043E740(register Obj *self)
{
    return self->s14;
}

int fn_8043E770(register Obj *self)
{
    return self->s16;
}
