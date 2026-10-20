// fn_804437D8 builds a 0x30-byte descriptor its caller (fn_8008A010) then fills in
// place; +0x10 and +0x11 are two one-byte members with a constructor and setter each.

typedef struct Byte
{
    char value;
} Byte;

typedef struct Desc
{
    char unk0[0x10];
    Byte unk10;
    Byte unk11;
    char unk12[0xA];
    int unk1C;
    int unk20;
    int unk24;
    int unk28;
    int unk2C;
} Desc;

extern Byte *fn_8044388C(register Byte *b);
extern Byte *fn_804438B4(register Byte *b);
extern void fn_804438DC(register Byte *b, register int value);

Desc *fn_804437D8(register Desc *d)
{
    fn_8044388C(&d->unk10);
    fn_804438B4(&d->unk11);
    fn_804438DC(&d->unk11, 1);
    d->unk20 = 0;
    d->unk28 = 0;
    d->unk2C = 1;
    d->unk24 = 0;
    d->unk1C = 0;
    return d;
}

void fn_80443860(register Byte *b, register int value)
{
    b->value = value;
}

Byte *fn_8044388C(register Byte *b)
{
    return b;
}

Byte *fn_804438B4(register Byte *b)
{
    return b;
}

void fn_804438DC(register Byte *b, register int value)
{
    b->value = value;
}
