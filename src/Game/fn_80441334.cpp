// Quaternion helpers and small accessors on unidentified objects (docs/versus.md, row 8).
// fn_80441438 multiplies two quaternions {x, y, z; w at +0xC}: out = (wa*vb + wb*va + va x vb, wa*wb - va.vb).

inline int sn_return_decl(int a)
{
    return a;
}

struct Slotted
{
    char pad[0xA8];
    char (*arr)[0x10]; // +0xA8
};

struct Flagged
{
    int unk0;
    unsigned int flags; // +0x4
};

struct Info
{
    char pad[9];
    unsigned char b9; // +0x9
};

struct Holder
{
    Info *info; // +0x0
};

struct Rec
{
    char pad[0x18];
    unsigned short s18; // +0x18
    char pad1A[0xA];
    unsigned char b24;  // +0x24
    char pad25;
    unsigned short s26; // +0x26
};

extern "C" {
void fn_80434988(void *p);
void *fn_8043BBD0(void *q);
void fn_80434A18(void *out, void *a, void *b);
float fn_8043C69C(void *q, int i);
void fn_804364BC(void *out, float s, void *v);
float fn_80436548(void *a, void *b);
void fn_8043632C(void *dst, void *src);
float *fn_80438360(void *self, int i);
float *fn_804352C8(void *self, int i);
void fn_80438398(void *out, void *v);
void fn_804418F8(void *out, float w);
int fn_801B6A44(void *p);
int fn_801B5D3C(void *p, int a);
void fn_8043DBC8(void *p, int a);

char *fn_80441334(register Slotted *self, register int i)
{
    return self->arr[i];
}

void fn_80441370(register Flagged *self, register int on)
{
    if (on)
        self->flags |= 0x400000;
    else
        self->flags &= ~0x400000;
}

int fn_804413B8(register Holder *self)
{
    return self->info->b9;
}

float fn_804413EC(register void *self)
{
    return *fn_804352C8(self, 3);
}

void fn_80441438(register void *out, register void *a, register void *b)
{
    char tmp[0x10];
    float w;

    fn_80434988(tmp);
    fn_80434A18(tmp, fn_8043BBD0(a), fn_8043BBD0(b));
    fn_804364BC(tmp, fn_8043C69C(a, 3), fn_8043BBD0(b));
    fn_804364BC(tmp, fn_8043C69C(b, 3), fn_8043BBD0(a));
    w = fn_804413EC(a) * fn_804413EC(b) - fn_80436548(a, b);
    fn_8043632C(out, tmp);
    *fn_80438360(out, 3) = w;
}

void fn_80441564(register void *out, register void *q)
{
    fn_80438398(out, fn_8043BBD0(q));
    fn_804418F8(out, fn_804413EC(q));
}

int fn_804415C8(register Rec *self)
{
    return self->b24;
}

int fn_804415F8(register Rec *self)
{
    return self->s26;
}

int fn_80441628(register char *self)
{
    return (unsigned short)fn_801B6A44(self + 0x24);
}

int fn_80441674(register char *self, register int a)
{
    return fn_801B5D3C(self + 0x24, a);
}

int fn_804416C4(register Rec *self)
{
    return (unsigned short)(self->s18 & 4);
}

void fn_804416F8(register void *self, register int a)
{
    fn_8043DBC8(self, a);
}
}
