// Leaf getters on an unidentified object: a word, a float, and flag-bit tests (docs/versus.md, row 8).

typedef struct Obj
{
    unsigned int flags0; // +0x0
    unsigned int flags4; // +0x4
    char unk8[0x20];
    float unk28; // +0x28
} Obj;

int fn_8043D544(register Obj *self)
{
    return self->flags0;
}

float fn_8043D570(register Obj *self)
{
    return self->unk28;
}

int fn_8043D59C(register Obj *self)
{
    return self->flags0 & 0x8;
}

int fn_8043D5CC(register Obj *self)
{
    return self->flags0 & 0x8000;
}

int fn_8043D5FC(register Obj *self)
{
    return self->flags4 & 0x20;
}

int fn_8043D62C(register Obj *self)
{
    return self->flags4 & 0x4000;
}
